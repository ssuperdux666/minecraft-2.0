#include "world/world.h"
#include "config/config.h"
#include "world/sub_chunk.h"

void Minecraft_World::fill_chunks() {
    for (int x = 0; x < World_n::WORLD_SIZE; x++) {

        for (int y = 0; y < World_n::WORLD_SIZE; y++) {

            sub_chunk* chunk1 = new sub_chunk(x,0,y,this);

            worldChunks.push_back(chunk1);

        }
    }
}

void Minecraft_World::pre_mesh_chunks() {
    for (sub_chunk* chunk : worldChunks) {
        chunk->mesh_sub_chunk();
    }
}