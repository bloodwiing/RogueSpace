#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <vector>
#include <json/json.h>
#include <memory>

#include "mesh.hpp"
#include "material.hpp"

#include "engine/actor/dynamicactor.hpp"

namespace Graphics {

    using json = nlohmann::json;
    using namespace Engine;

    /// \brief          A Graphical 3D Actor that can be drawn.
    /// \details        Contains a 3D Mesh, created from the glTF 2.0 standard
    class Model : public Actors::DynamicActor {
    public:
        /// \note           Should not be used raw, please use addChild
        /// \param scene    Containing Scene of the Actor node
        /// \param parent   Parent of the Actor node
        /// \param name     Name of the Actor node
        /// \param filename The path fo the glTF model file
        /// \see            Scene#addChild
        /// \see            Actor#addChild
        explicit Model(Scene *scene, ActorBase *parent, std::string name, const char* filename);

        void draw(Shader& shader) override;

    protected:
        [[nodiscard]] std::string getTypeName() const override;

    private:
        /// The path fo the glTF model file
        const char* m_filename;
        /// Raw binary data read from a binary buffer
        std::vector<uint8_t> m_data;
        /// Deserialized glTF file
        json m_json;

        /// List of all Meshes detected while traversing glTF Nodes
        std::vector<Mesh> m_meshes;
        /// List of all Relative-to-Model Transformations for each of the Meshes
        std::vector<glm::mat4> m_meshMatrices;

        /// List of Materials assigned to each of the Meshes
        std::vector<Material> m_materials;
        /// Optimised pre-loaded Texture Map, containing pairs of the Texture file path and the Texture created.
        /// In this case there is able to be multiple Textures that have a repeat path but are only loaded once
        std::unordered_map<std::string, std::shared_ptr<Texture> > m_loadedTexNames;

        /// \brief              Reads and saves a Mesh from the index
        /// \param meshIndex    The index of which Mesh to load
        void loadMesh(uint32_t meshIndex);

        /// \brief              Travels through glTF Nodes, compiles Relative-to-Model Transformations
        /// \details            This is a recursive function that begins walking through the first node references
        ///                     and continues until all nodes and their children have been processed
        /// \param nodeIndex    The index of which Node to traverse
        /// \param matrix       The Parent node inherited Transformation
        void traverseNode(uint16_t nodeIndex, glm::mat4 matrix = glm::mat4(1.0f));

        /// \return             Binary data read from a buffer
        std::vector<uint8_t> getData();
        /// \param accessor     The glTF accessor where Floats are to be read
        /// \return             The generated list of Floats from the Accessor's reference
        std::vector<float> getFloats(json accessor);
        /// \param accessor     The glTF accessor where Indices are to be read
        /// \return             The generated list of Indices from the Accessor's reference
        std::vector<GLuint> getIndices(json accessor);
        /// \return             The created list of Textures, optimised via m_loadedTexNames
        /// \see                Model#m_loadedTexNames
        std::vector<std::shared_ptr<Texture> > getTextures();
        /// \brief              Creates a Material from the Json data of the glTF Mesh entry and the full list of Textures
        /// \param data         glTF Material entry
        /// \param textures     The list of textures, made via getTextures()
        /// \return             A compiled Material
        Material getMaterial(json data, std::vector<std::shared_ptr<Texture> >& textures);

        /// \brief              Combines all 3 lists of vertex data into a single list of Vertex objects
        /// \param positions    The Vertex Position list
        /// \param normals      The Vertex Normal list
        /// \param texCoords    The Vertex UV coordinate list
        /// \return             Newly assembled list of Vertex objects
        std::vector<Vertex> assembleVertices(
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

#endif //MODEL_CLASS_H
