#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// from vs
in VS_OUT {
    vec3 fragPos;
    vec3 fragNormal;
    vec3 fragTangent;
    vec3 fragBitangent;
    vec4 fragPosLightSpace;
    vec2 texCoords;
} fsIn;

// to pixel
out vec4 color;

uniform vec3 cameraPosition;

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
uniform bool useSpecularMap;
uniform bool useShadowMap;

// lights
struct LightSource {
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform LightSource lights[4];
uniform int lightCount;

vec2 transformTexCoords(vec2 texCoords, vec3 viewDir) {
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
    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
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
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(parallaxMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

float computeShadowIntensity(vec4 lightSpace) {
    float bias = 0.003;

    vec3 projCoords = lightSpace.xyz / lightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    shadow = 0;

    return shadow;
}

vec3 computeLight(int index, vec3 unitNormal, vec2 texCoords, float shadow) {
    vec3 lightDir = normalize(lights[index].position - fsIn.fragPos);
    vec3 viewDir = normalize(cameraPosition - fsIn.fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Compute Lambertian reflectance
    float lambert = max(dot(unitNormal, lightDir), 0.0);

    // Get texture color
    vec3 col = vec3(texture(colorMap, texCoords));

    // Initialize light components
    float ambient = 0.15;
    float diffuse = 0.0;
    float specular = 0.0;

    if (lambert > 0.0) {
        // Compute distance between the fragment and the light source
        float dist = length(lights[index].position - fsIn.fragPos);

        // Scale for the intensity
        float scalar = lights[index].factors.x * pow(lights[index].factors.y, lights[index].factors.z * dist);

        // Diffuse light
        diffuse = lambert * scalar;

        // Specular light (Blinn-Phong)
        float spec = pow(max(dot(unitNormal, halfwayDir), 0.0), shininess);
        specular = spec * scalar;
    }

    // Compute ambient, diffuse, and specular contributions
    vec3 ambientColor = lights[index].color * ambient * col;
    vec3 diffuseColor = lights[index].color * diffuse * col;
    vec3 specularColor = lights[index].color * specular * col;

    // Return combined light, considering shadow
    return ambientColor + (1.0 - shadow) * (diffuseColor + specularColor);
}


void main() {
    vec2 textureCoords = fsIn.texCoords;


    vec4 textureColour = texture(colorMap, textureCoords * textureStretch);

    // compute shadows
    float shadow = 0;
    if (useShadowMap) {
        shadow = computeShadowIntensity(fsIn.fragPosLightSpace);
    }

    vec3 unitNormal = fsIn.fragNormal;

    // adjust the normal using the TBN matrix if normal mapping is supported
    if (useNormalMap) {
        mat3 TBN = mat3(fsIn.fragTangent, fsIn.fragBitangent, fsIn.fragNormal);
        vec3 normal = texture(normalMap, textureCoords * textureStretch).rgb;
        normal = normal * 2.0 - 1.0; // Transform from [0, 1] to [-1, 1]
        unitNormal = normalize(TBN * normal);
    }

    // summarize light sources
    vec3 lightStrength = vec3(0, 0, 0);
    for (int i = 0; i < lightCount; i++) {
        lightStrength += computeLight(i, unitNormal, textureCoords, shadow);
    }

    color = vec4(lightStrength, 1);
}
