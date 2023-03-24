#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <vector>
#include <string>

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"

class Mesh {
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

    void draw(Shader& shader, Camera& camera);

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;
};

#endif //MESH_CLASS_H
