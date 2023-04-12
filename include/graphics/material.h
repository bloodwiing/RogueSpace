#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include <string>
#include <cinttypes>
#include <glm/glm.hpp>

#include "texture.h"

class Material {
public:
    struct TextureRef {
        bool enabled = false;
        Texture texture;
        uint8_t texCoord = 0;
    };

    explicit Material(std::string& name);

    [[nodiscard]] std::string getName() const;

    void setDiffuse0(Texture texture, uint8_t texCoord);
    void setDiffuseFactor(glm::vec4 factor);

    void apply(Shader& shader) const;

private:
    const std::string m_name;

    TextureRef m_diffuse0;
    glm::vec4 m_diffuseFactor;

    TextureRef m_specular0;
    float m_metallicFactor;
    float m_roughnessFactor;
};

#endif //MATERIAL_CLASS_H
