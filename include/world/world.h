#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "world/sub_chunk.h"

class sub_chunk;

class Minecraft_World {
    public:
        std::vector<sub_chunk*> worldChunks;  

        void fill_chunks();

        void pre_mesh_chunks();
};

#endif