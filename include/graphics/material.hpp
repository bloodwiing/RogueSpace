#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include <string>
#include <cinttypes>
#include <glm/glm.hpp>

#include "texture.hpp"

/// \brief      Texture and Multiplier value set
/// \details    Can be applied onto a Shader to be immediately used
class Material {
public:
    /// \brief          A Texture with the corresponding UV coordinates reference
    struct TextureRef {
        bool enabled = false;
        Texture texture;
        uint8_t texCoord = 0;
    };

    /// \brief          Creates a new Material container
    /// \param name     The name of the material (used for identification purposes)
    explicit Material(std::string& name);

    /// \return         The name of the Material
    [[nodiscard]] std::string getName() const;

    /// \brief          Sets a Diffuse texture under the 0th Diffuse sampler
    /// \param texture  The texture to use for Diffuse colour
    /// \param texCoord The UV coordinate reference index
    void setDiffuse0(Texture texture, uint8_t texCoord);
    /// \brief          Sets a Diffuse colour multiplier
    /// \param factor   The factor or colour that multiplies after the Diffuse Texture
    void setDiffuseFactor(glm::vec4 factor);

    /// \brief          Updates Texture and Factor uniforms on the Shader
    /// \param shader   The Shader to update
    void apply(Shader& shader) const;

private:
    /// The name of the Material
    const std::string m_name;

    /// Texture used for Diffuse 0
    TextureRef m_diffuse0;
    /// Multiplier for Diffuse
    glm::vec4 m_diffuseFactor;

    /// Texture used for Specular 0
    TextureRef m_specular0;
    /// Metallic influence multiplier
    float m_metallicFactor;
    /// Roughness influence multiplier
    float m_roughnessFactor;
};

#endif //MATERIAL_CLASS_H
