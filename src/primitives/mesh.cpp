/* Mesh.cpp
 * methods for the Mesh class
 */

#include "primitives.h"

Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t)
{
    vertices = v;
    indices = i;
    textures = t;

    init();
}

// Mesh::~Mesh()
// {
//     glDeleteBuffers(1, &vbo);
//     glDeleteVertexArrays(1, &vao);
// }

void Mesh::init()
{
    // create buffers/arrays
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);   
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}
/*
void Mesh::attachMaterial(Material *aimaterial)
{
    this->material = aimaterial;
}
*/
void Mesh::draw(Shader shader)
{
    // unsigned int modelLoc = glGetUniformLocation(glprogram, "mModel");
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

    // unsigned int viewLoc = glGetUniformLocation(glprogram, "mView");
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));

    // unsigned int projLoc = glGetUniformLocation(glprogram, "mProjection");
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));
    for (unsigned i = 0; i < textures.size(); i++) {
        glUniform1i(glGetUniformLocation(shader.shaderid, "texture_diffuse1"), i);
        glBindTexture(GL_TEXTURE_2D, textures[0].id);
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}



// void Mesh::combinebuffers()
// {


//  combined_data = vertices;
//  combined_data.insert(combined_data.end(), normals.begin(), normals.end());

//  if(contains_vts){
//      //combined_data.insert(combined_data.end(), uvs.begin(), uvs.end());
//  }

//  std::cout << contains_vts << std::endl;
//  //Debug
//  // printf("%lu\n", vertices.size());
//  // printf("%lu\n", normals.size());
//  // printf("%lu\n", combined_data.size());

// }

