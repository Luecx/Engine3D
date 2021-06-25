#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// from vs
in VS_OUT{
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentCameraPos;
    vec3 tangentFragPos;
    vec3 tangentLightPos[4];
} fsIn;

// to pixel
out vec4 color;

// material
uniform float shineDamper;
uniform float reflectivity;

// texture stretching
uniform float textureStretch;

// parallax
uniform float parallaxDepth;

// maps
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D parallaxMap;

uniform bool useNormalMap;

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


void main()
{

    vec2 textureCoords = fsIn.texCoords;
    // compute parallax if needed
    if(parallaxDepth != 0){
        textureCoords = transformTexCoords(textureCoords, fsIn.tangentCameraPos);
        if(textureCoords.x > 1.0 || textureCoords.y > 1.0 || textureCoords.x < 0.0 || textureCoords.y < 0.0)
            discard;
    }
    vec4 textureColour = texture(colorMap,textureCoords * textureStretch);




    vec3 lightColor = vec3(0,0,0);
    vec3 unitNormal = vec3(0,0,1);

    // adjust the normal using the TBN matrix if normal mapping is supported
    if(useNormalMap){
        unitNormal = texture(normalMap, textureCoords * textureStretch).rgb;
        unitNormal = unitNormal * 2.0 - 1.0;
        unitNormal = normalize(unitNormal);
    }

    // dont do any diffuse lighting if there are no lights at all
    vec3 totalDiffuse   = vec3(lightCount == 0 ? 1:0);
    vec3 totalSpecular  = vec3(0,0,0);

    vec3 unitVectorToCamera = normalize(fsIn.tangentCameraPos);

    for(int i = 0; i < lightCount; i++){
        float dist       = length(fsIn.tangentLightPos[i]);
        vec3  unitLight  = normalize(fsIn.tangentLightPos[i]);
        float scalar     = lights[i].factors.x * pow(lights[i].factors.y, lights[i].factors.z * dist);
        float angleScale = dot(unitLight, unitNormal);

        float brightness     = max(angleScale,0.2);
        vec3  lightDirection = -unitLight;
        vec3  reflectedLight = reflect(lightDirection, unitNormal);

        float specularFactor = max(0.0,dot(reflectedLight, normalize(fsIn.tangentCameraPos)));
        float dampedFactor   = pow(specularFactor,shineDamper);


        totalDiffuse  = totalDiffuse  + (brightness * lights[i].color) * scalar;
        if(angleScale > 0)
            totalSpecular = totalSpecular + (dampedFactor * reflectivity * lights[i].color) * scalar;
    }

    color = vec4(totalDiffuse,1.0) * textureColour + vec4(totalSpecular,1.0);
}