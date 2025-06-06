#ifndef JAGE_MATERIAL_HPP
#define JAGE_MATERIAL_HPP

#include <string>
#include <cinttypes>
#include <glm/glm.hpp>

#include "jage/graphics/texture.hpp"

namespace jage::graphics::mesh3d {

    /// \brief      Texture and Multiplier value set
    /// \details    Can be applied onto a Shader to be immediately used
    class Material {
    public:
        /// \brief          A Texture with the corresponding UV coordinates reference
        struct TextureRef {
            std::shared_ptr<Texture> texture;
            uint8_t texCoord = 0;
        };

        /// \brief          Creates a new Material container
        /// \param name     The name of the material (used for identification purposes)
        explicit Material(std::string name);
        Material(const Material &ref) = default;
        ~Material() = default;

        /// \return         The name of the Material
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] static Material& getDefaultMaterial();
        static void clearDefaultMaterial();

        /// \brief          Sets a Diffuse texture under the 0th Diffuse sampler
        /// \param texture  The texture to use for Diffuse colour
        /// \param texCoord The UV coordinate reference index
        void setDiffuse0(std::shared_ptr<Texture> texture, uint8_t texCoord);
        /// \brief          Sets a Diffuse colour multiplier
        /// \param factor   The factor or colour that multiplies after the Diffuse Texture
        void setDiffuseFactor(glm::vec4 factor);
        [[nodiscard]] std::shared_ptr<Texture> getDiffuse0() const;

        void setSpecular0(std::shared_ptr<Texture> texture, uint8_t texCoord);
        void setMetallicFactor(float);
        void setRoughnessFactor(float);
        [[nodiscard]] std::shared_ptr<Texture> getSpecular0() const;

        /// \brief          Updates Texture and Factor uniforms on the Shader
        /// \param shader   The Shader to update
        bool apply(Shader& shader) const;

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

        static Material* defaultMaterial;
    };
}

#endif //JAGE_MATERIAL_HPP
