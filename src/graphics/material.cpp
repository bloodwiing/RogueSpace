#include "graphics/material.hpp"

#include <utility>

Graphics::Material::Material(std::string& name)
    : m_name(std::move(name))
    , m_diffuseFactor(1.0)
    , m_metallicFactor(1.0)
    , m_roughnessFactor(1.0)
{

}

std::string Graphics::Material::getName() const {
    return m_name;
}

void Graphics::Material::setDiffuse0(Texture texture, uint8_t texCoord) {
    m_diffuse0 = (TextureRef){
        .enabled = true,
        .texture = texture,
        .texCoord = texCoord
    };
}

void Graphics::Material::setDiffuseFactor(glm::vec4 factor) {
    m_diffuseFactor = factor;
}

void Graphics::Material::apply(Shader &shader) const {
    if (shader.isErrored())
        return;

    if (m_diffuse0.enabled) {
        m_diffuse0.texture.assign(shader, "Diffuse0", 0);
        m_diffuse0.texture.bind(0);
    }

    glUniform4f(
            shader.getUniform("DiffuseFactor"),
            m_diffuseFactor.x, m_diffuseFactor.y, m_diffuseFactor.z, m_diffuseFactor.w);

    if (m_specular0.enabled) {
        m_specular0.texture.assign(shader, "Specular0", 1);
        m_specular0.texture.bind(1);
    }

    glUniform1f(shader.getUniform("MetallicFactor"), m_metallicFactor);
    glUniform1f(shader.getUniform("RoughnessFactor"), m_roughnessFactor);
}
