#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// from vs
in vec4 worldPosition;
in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in mat3 TBN;

// to pixel
out vec4 color;

// material
uniform float shineDamper;
uniform float reflectivity;

// texture stretching
uniform float textureStretch;

// maps
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform bool useNormalMap;
uniform bool useSpecularMap;

// lights
struct LightSource
{
    vec3 position;
    vec3 color;
    vec3 factors;
};

uniform LightSource lights[4];
uniform int lightCount;

void main()
{
    vec4 textureColour = texture(colorMap,pass_textureCoords * textureStretch);

    vec3 h = surfaceNormal;

    vec3 lightColor = vec3(0,0,0);
    vec3 unitNormal;

    // adjust the normal using the TBN matrix if normal mapping is supported
    if(useNormalMap){
        unitNormal = texture(normalMap, pass_textureCoords * textureStretch).rgb;
        unitNormal = unitNormal * 2.0 - 1.0;
        unitNormal = normalize(TBN * unitNormal);
    }else{
        unitNormal = normalize(surfaceNormal);
    }

    // dont do any diffuse lighting if there are no lights at all
    vec3 totalDiffuse   = vec3(lightCount == 0 ? 1:0);
    vec3 totalSpecular  = vec3(0);

    vec3 unitVectorToCamera = normalize(toCameraVector);

    for(int i = 0; i < lightCount; i++){
        float dist       = length(toLightVector[i]);
        vec3  unitLight  = normalize(toLightVector[i]);
        float scalar     = lights[i].factors.x * pow(lights[i].factors.y, lights[i].factors.z / dist);
        float angleScale = dot(unitLight, unitNormal);

        float brightness     = max(angleScale,0.2);
        vec3  lightDirection = -unitLight;
        vec3  reflectedLight = reflect(lightDirection, unitNormal);
        float specularFactor = dot(reflectedLight, unitVectorToCamera);
        specularFactor       = max(specularFactor,0.0);
        float dampedFactor  = pow(specularFactor,shineDamper);

        totalDiffuse  = totalDiffuse  + (brightness * lights[i].color) / scalar;
        totalSpecular = totalSpecular + (dampedFactor * reflectivity * lights[i].color) / scalar;
    }

//    color = vec4(totalDiffuse,1.0) * textureColour + vec4(totalSpecular,0.0);
    color = vec4(unitNormal,1.0);
}