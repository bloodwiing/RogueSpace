#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <vector>
#include <string>

#include <glm/detail/type_quat.hpp>

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"
#include "material.h"

class Mesh {
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material);

    void draw(
        Shader& shader,
        Camera* camera,
        glm::mat4 relative = glm::mat4(1.0f),
        glm::mat4 model = glm::mat4(1.0f));

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    Material m_material;

    VAO m_VAO;
};

#endif //MESH_CLASS_H
