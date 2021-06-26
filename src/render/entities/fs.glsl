#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// from vs
in VS_OUT{
    vec3 fragPos;
    vec4 fragPosLightSpace;
    vec2 texCoords;
    vec3 tangentCameraPos;
    vec3 tangentFragPos;
    vec3 tangentLightPos[4];
} fsIn;

// to pixel
out vec4 color;

// material
uniform float shininess;

// texture stretching
uniform float textureStretch;

// parallax
uniform float parallaxDepth;

// maps
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D parallaxMap;
uniform sampler2D shadowMap;

uniform bool useNormalMap;
uniform bool useShadowMap;

// lights
struct LightSource
{
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform LightSource lights[4];
uniform int lightCount;


//vec2 transformTexCoords(vec2 texCoords, vec3 viewDir){
//    float height =  texture(parallaxMap, texCoords).r;
//    vec2 p = viewDir.xy / viewDir.z * (height * parallaxDepth);
//    return texCoords - p;
//}

vec2 transformTexCoords(vec2 texCoords, vec3 viewDir){


    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * parallaxDepth;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(parallaxMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;

}

float computeShadowIntensity(vec4 lightSpace){
//    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float bias = 0.003;

    vec3 projCoords = lightSpace.xyz / lightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
//    float shadow = currentDepth -bias > closestDepth  ? 1.0 : 0.2;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

vec3 computeLight(int index, vec3 unitNormal, vec2 texCoords, float shadow){

    // normalize the view direction
    vec3 viewDir    = normalize(fsIn.tangentCameraPos);
    // normalize the direction to the light
    vec3 lightDir   = normalize(fsIn.tangentLightPos[index]);
    // compute the halfway direction for blinn phong
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // compute the angle between the normal and the light source for diffuse shading
    float diff = max(dot(unitNormal, lightDir), 0.0);

    // compute the distance between the fragment and the light source
    float dist       = length(fsIn.tangentLightPos[index]);

    // scale for the intensity
    float scalar     = lights[index].factors.x * pow(lights[index].factors.y, lights[index].factors.z * dist);

    // constant for ambient light
    float ambi       = 0.15;

    // constant for specular
    float spec = pow(max(dot(unitNormal, halfwayDir), 0.0), shininess);

    // compute the light strength at the given distance
    vec3 ambient     = lights[index].color * ambi * vec3(texture(colorMap, texCoords));
    vec3 diffuse     = lights[index].color * diff * vec3(texture(colorMap, texCoords));
    vec3 specular    = lights[index].color * spec * vec3(texture(colorMap, texCoords));

    return (ambient + (1.0 - shadow) * (diffuse + specular)) * scalar;

}

void main()
{

    vec2 textureCoords = fsIn.texCoords;
    // compute parallax if needed
    if (parallaxDepth != 0){
        textureCoords = transformTexCoords(textureCoords, fsIn.tangentCameraPos);
        if (textureCoords.x > 1.0 || textureCoords.y > 1.0 || textureCoords.x < 0.0 || textureCoords.y < 0.0)
        discard;
    }
    vec4 textureColour = texture(colorMap, textureCoords * textureStretch);

    // compute shadows
    float shadow = 0;
    if (useShadowMap){
        shadow = computeShadowIntensity(fsIn.fragPosLightSpace);
    }

    vec3 lightColor = vec3(0, 0, 0);
    vec3 unitNormal = vec3(0, 0, 1);

    // adjust the normal using the TBN matrix if normal mapping is supported
    if (useNormalMap){
        unitNormal = texture(normalMap, textureCoords * textureStretch).rgb;
        unitNormal = unitNormal * 2.0 - 1.0;
        unitNormal = normalize(unitNormal);
    }

    // summarize light sources
    vec3 lightStrength = vec3(0, 0, 0);

    for(int i = 0; i < lightCount; i++){
        lightStrength += computeLight(i, unitNormal, textureCoords, shadow);
    }

    color = vec4(lightStrength, 1.0);
}