#ifndef SUB_CHUNK_H
#define SUB_CHUNK_H

#include "rendering/buffer.h"
#include <vector>

#include "rendering/shader.h"
#include "rendering/textures.h"

#include "world/world.h"

typedef unsigned short uint16_t;

class sub_chunk {
    public:
        int xPosition; //0 is center
        int yPosition; //0 is top of the chunk
        int zPosition;

        VAO VAO1;
        VBO VBO1;

        int faceCount = 0;

        int global_sub_chunk_array_index = 0;

        uint16_t sub_chunk_array[16 * 16 * 16];

        std::vector<float> sub_chunk_vertices;

        Minecraft_World chunkWorld;

        sub_chunk(int xPos, int yPos, int zPos, Minecraft_World chunkWorld_insert);

        void fill_sub_chunk();

        void mesh_sub_chunk();

        void add_face(int face, int x, int y, int z);

        bool is_air(int x, int y, int z);

        void draw(Texture tex1, Shader shaderProgram);
};

#endif