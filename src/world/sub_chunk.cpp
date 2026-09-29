#include "world/sub_chunk.h"
#include "config/config.h"
#include "world/cube.h"
#include "world/mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/shader.h"
#include "rendering/textures.h"


sub_chunk::sub_chunk(int xPos, int yPos, int zPos) { //x and z start at the center and y top is 0 and y bottom is 15
    xPosition = xPos;
    yPosition = yPos;
    zPosition = zPos;

    fill_sub_chunk();
}

void sub_chunk::fill_sub_chunk() {
    for (int i = 0; i < World::SUB_CHUNK_LENGTH; i++) {
        sub_chunk_array[i] = 1;
    }
}

void sub_chunk::add_face(int face, int x, int y, int z) {
    switch (face) {
    case 0: paste_face(CUBE_VERTICES_FRONT,x,y,z, sub_chunk_vertices); break;
    case 1: paste_face(CUBE_VERTICES_BACK,x,y,z, sub_chunk_vertices); break;
    case 2: paste_face(CUBE_VERTICES_LEFT,x,y,z, sub_chunk_vertices); break;
    case 3: paste_face(CUBE_VERTICES_RIGHT,x,y,z, sub_chunk_vertices); break;
    case 4: paste_face(CUBE_VERTICES_UP,x,y,z, sub_chunk_vertices); break;
    case 5: paste_face(CUBE_VERTICES_BOTTOM,x,y,z, sub_chunk_vertices); break;
    default:
        break;
    }

    faceCount++;
}

bool sub_chunk::is_air(int x, int y, int z)
{
    if (x < 0 || x >= World::SUB_CHUNK_SIZE ||
        y < 0 || y >= World::SUB_CHUNK_SIZE ||
        z < 0 || z >= World::SUB_CHUNK_SIZE)
    {
        return true;
    }

    return sub_chunk_array[decode_sub_chunk_index(x, y, z)] == 0;
}

void sub_chunk::mesh_sub_chunk() {
    
    for (int index = 0; index < World::SUB_CHUNK_LENGTH; index++) {

        int remainder = index % (World::SUB_CHUNK_SIZE * World::SUB_CHUNK_SIZE);

        int z = index / (World::SUB_CHUNK_SIZE * World::SUB_CHUNK_SIZE);
        int y = remainder / World::SUB_CHUNK_SIZE;
        int x = remainder % World::SUB_CHUNK_SIZE;

        if (sub_chunk_array[index] != 0) {

            for (int face = 0; face < 6; face++) {
                int nx = x + directions[face][0];
                int ny = y + directions[face][1];
                int nz = z + directions[face][2];

                if (is_air(nx, ny, nz)) {
                    add_face(face, x, y, z);
                }
            }
        }
    }

    VBO1.insert_data(sub_chunk_vertices,sub_chunk_vertices.size() * sizeof(float));
}

void sub_chunk::draw(Texture tex1, Shader shaderProgram) {
    glBindTexture(GL_TEXTURE_2D, tex1.ID);

    glUseProgram(shaderProgram.ID);
    VAO1.Bind();

    glDrawArrays(
        GL_TRIANGLES,
        0,
        static_cast<GLsizei>(sub_chunk_vertices.size() / 5)
    );
}