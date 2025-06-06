#ifndef JAGE_MODEL_3D_HPP
#define JAGE_MODEL_3D_HPP

#include <vector>
#include <json/json.h>
#include <memory>
#include <mutex>

#include "jage/graphics/mesh3d/mesh3d.hpp"
#include "jage/graphics/mesh3d/vbo3d.hpp"
#include "jage/graphics/mesh3d/material.hpp"
#include "jage/runtime/asset/abc/asset_abc.hpp"
#include "jage/runtime/asset/assetstream.hpp"

namespace jage::graphics::mesh3d {

    using json = nlohmann::json;

    class Model3D
            : public jage::runtime::asset::abc::AssetABC<Model3D> {
    public:
        explicit Model3D(std::string fileName);
        static std::shared_ptr<Model3D> create(std::string fileName);

        void onQueue(int priority) override;

        void draw(Shader& shader, glm::mat4 worldMatrix = glm::mat4(1.0f));

    private:
        /// The path fo the glTF model file
        const std::string m_fileName;
        /// Raw binary data read from a binary buffer
        std::vector<uint8_t> m_data;
        /// Deserialized glTF file
        json m_json;

        /// List of all Meshes detected while traversing glTF Nodes
        std::vector<Mesh3D> m_meshes;
        /// List of all Relative-to-Model Transformations for each of the Meshes
        std::vector<glm::mat4> m_meshMatrices;

        /// List of Materials assigned to each of the Meshes
        std::vector<Material> m_materials;
        std::vector<std::shared_ptr<Texture>> m_textures;

        /// \brief              Reads and saves a Mesh from the index
        /// \param meshIndex    The index of which Mesh to load
        void loadMesh(uint32_t meshIndex);

        /// \brief              Travels through glTF Nodes, compiles Relative-to-Model Transformations
        /// \details            This is a recursive function that begins walking through the first node references
        ///                     and continues until all nodes and their children have been processed
        /// \param nodeIndex    The index of which Node to traverse
        /// \param matrix       The Parent node inherited Transformation
        void traverseNode(uint16_t nodeIndex, glm::mat4 matrix = glm::mat4(1.0f));

        void getData(int priority = JAGE_ASSET_BASE_PRIORITY);
        /// \param accessor     The glTF accessor where Floats are to be read
        /// \return             The generated list of Floats from the Accessor's reference
        std::vector<float> getFloats(json accessor);
        /// \param accessor     The glTF accessor where Indices are to be read
        /// \return             The generated list of Indices from the Accessor's reference
        std::vector<GLuint> getIndices(json accessor);
        void getTextures(int priority = JAGE_ASSET_BASE_PRIORITY);
        /// \brief              Creates a Material from the Json data of the glTF Mesh entry and the full list of Textures
        /// \param data         glTF Material entry
        /// \param textures     The list of textures, made via getTextures()
        /// \return             A compiled Material
        Material getMaterial(json data, std::vector<std::shared_ptr<Texture>>& textures);

        static glm::vec2 flipUVVertically(const glm::vec2& vec);
        /// \brief              Combines all 3 lists of vertex data into a single list of Vertex objects
        /// \param positions    The Vertex Position list
        /// \param normals      The Vertex Normal list
        /// \param texCoords    The Vertex UV coordinate list
        /// \return             Newly assembled list of Vertex objects
        std::vector<Vertex3D> assembleVertices(
                std::vector<glm::vec3> positions,
                std::vector<glm::vec3> normals,
                std::vector<glm::vec2> texCoords);

        /// \brief              Helper function to convert a list of Floats into a list of glm::vec types
        /// \tparam TVec        The type of the new list's glm::vec objects
        /// \param floats       The list of original floats to read
        /// \return             The newly created list of glm::vec objects
        template<class TVec>
        std::vector<TVec> groupFloatsVec(std::vector<float> floats);

        /// \brief              Updates a glm::vec2 from a float vector iterator
        /// \param iterator     The iterator reference
        /// \param[out] vector  The applied glm::vec2
        static void setVector(std::vector<float>::iterator& iterator, glm::vec2& vector);
        /// \brief              Updates a glm::vec3 from a float vector iterator
        /// \param iterator     The iterator reference
        /// \param[out] vector  The applied glm::vec3
        static void setVector(std::vector<float>::iterator& iterator, glm::vec3& vector);
        /// \brief              Updates a glm::vec4 from a float vector iterator
        /// \param iterator     The iterator reference
        /// \param[out] vector  The applied glm::vec4
        static void setVector(std::vector<float>::iterator& iterator, glm::vec4& vector);
    };
}

#endif //JAGE_MODEL_3D_HPP
