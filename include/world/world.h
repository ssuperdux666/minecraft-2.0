#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "world/sub_chunk.h"
#include <unordered_map>

class sub_chunk;

class Minecraft_World {
    public:
        std::unordered_map<int, sub_chunk*> worldChunks;  

        void fill_chunks();

        void pre_mesh_chunks();
};

#endif