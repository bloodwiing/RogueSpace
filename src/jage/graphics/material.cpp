#include "jage/graphics/material.hpp"

#include <utility>

using jage::graphics::Material;

Material* Material::defaultMaterial = nullptr;

Material::Material(std::string name)
        : m_name(std::move(name))
        , m_diffuseFactor(1.0)
        , m_metallicFactor(1.0)
        , m_roughnessFactor(1.0)
{

}

Material& Material::getDefaultMaterial() {
    if (defaultMaterial == nullptr)
        defaultMaterial = new Material("Default");
    return *defaultMaterial;
}

void Material::clearDefaultMaterial() {
    delete defaultMaterial;
    defaultMaterial = nullptr;
}

std::string Material::getName() const {
    return m_name;
}

void Material::setDiffuse0(std::shared_ptr<Texture> texture, uint8_t texCoord) {
    m_diffuse0 = (TextureRef){
        .texture = std::move(texture),
        .texCoord = texCoord
    };
}

void Material::setDiffuseFactor(glm::vec4 factor) {
    m_diffuseFactor = factor;
}

std::shared_ptr<jage::graphics::Texture> Material::getDiffuse0() const {
    if (m_diffuse0.texture)
        return m_diffuse0.texture;
    return Texture::getDefaultTexture();
}

void Material::setSpecular0(std::shared_ptr<Texture> texture, uint8_t texCoord) {
    m_specular0 = (TextureRef){
        .texture = std::move(texture),
        .texCoord = texCoord
    };
}

void Material::setMetallicFactor(float factor) {
    m_metallicFactor = factor;
}

void Material::setRoughnessFactor(float factor) {
    m_roughnessFactor = factor;
}

std::shared_ptr<jage::graphics::Texture> Material::getSpecular0() const {
    if (m_specular0.texture)
        return m_specular0.texture;
    return Texture::getDefaultTexture();
}

bool Material::apply(Shader &shader) const {
    if (shader.isErrored())
        return false;

    auto diffuse0 = getDiffuse0();
    diffuse0->prepare();
    if (!diffuse0->isReady())
        return false;
    diffuse0->assign(shader, "Diffuse0", 0);
    diffuse0->bind(0);

    glUniform4f(
            shader.getUniform("DiffuseFactor"),
            m_diffuseFactor.x, m_diffuseFactor.y, m_diffuseFactor.z, m_diffuseFactor.w);

    auto specular0 = getSpecular0();
    diffuse0->prepare();
    if (!specular0->isReady())
        return false;
    specular0->assign(shader, "Specular0", 1);
    specular0->bind(1);

    glUniform1f(shader.getUniform("MetallicFactor"), m_metallicFactor);
    glUniform1f(shader.getUniform("RoughnessFactor"), m_roughnessFactor);

    return true;
}
