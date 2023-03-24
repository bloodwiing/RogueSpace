#include "graphics/mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
    : vertices(vertices)
    , indices(indices)
    , textures(textures)
    , VAO()
{
    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    VAO.linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    VAO.linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}

void Mesh::draw(Shader &shader, Camera &camera) {
    if (!shader.isErrored()) {
        shader.activate();
        VAO.bind();

        camera.applyMatrix(shader, "CameraMatrix");
        glUniform3f(shader.getUniform("CameraPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

        uint16_t diffuse_counter = 0,
                 specular_counter = 0;

        for (uint64_t i = 0; i < textures.size(); ++i) {
            std::string uniform_name;

            switch (textures[i].getTextureType()) {
                case TextureType::TEX_DIFFUSE:
                    uniform_name = std::string("Diffuse") + std::to_string(diffuse_counter++);
                    break;
                case TextureType::TEX_SPECULAR:
                    uniform_name = std::string("Specular") + std::to_string(diffuse_counter++);
                    break;
                default:
                    break;
            }

            textures[i].assign(shader, uniform_name.c_str(), i);
            textures[i].bind();
        }

        glDrawElements(GL_TRIANGLES, (GLint)indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}
