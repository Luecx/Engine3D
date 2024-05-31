//
// Created by Luecx on 02.06.2021.
//

#ifndef ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
#define ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_

#include "../../core/config.h"
#include "../../material/MaterialMap.h"
#include "../ShaderProgram.h"

class EntityShader : public ShaderProgram {

    private:
    int loc_transformationMatrix;
    int loc_viewMatrix;
    int loc_projectionMatrix;
    int loc_shadowViewMatrix;
    int loc_cameraPosition;
    int loc_lightCount;
    int loc_lightPosition[MAX_LIGHTS];
    int loc_lightColor[MAX_LIGHTS];
    int loc_lightFactors[MAX_LIGHTS];
    int loc_shininess;
    int loc_useNormalMap;
    int loc_useSpecularMap;
    int loc_useShadowMap;
    int loc_parallaxDepth;
    int loc_textureStretch;

    int loc_normalMap;
    int loc_colorMap;
    int loc_specularMap;
    int loc_parallaxMap;
    int loc_shadowMap;

    public:
    EntityShader();

    protected:
    void getAllUniformLocations() override;
    void bindAttributes() override;
    void connectAllTextureUnits() override;

    public:
    void loadTransformationMatrix(Matrix<4, 4>& transformationMatrix);
    void loadVPMatrix(Matrix<4, 4>& viewMatrix, Matrix<4, 4>& projectionMatrix);
    void loadShadowView(bool useShadows, Matrix<4, 4>& viewMatrix);
    void loadCameraPosition(Vector<3>& position);
    void loadLightCount(int count);
    void loadLight(int index, Vector<3>& position, Vector<3>& color, Vector<3>& factors);
    void loadMaterialMapUsage(bool useNormalMap, bool useSpecularMap);
    void loadParallaxDepth(float parallaxDepth);
    void loadMaterialData(float shininess);
    void loadTextureStretch(float textureStretch);
};

#endif    // ENGINE3D_SRC_RENDER_IMPLEMENTATIONS_ENTITIES_ENTITYSHADER_H_
