#include "world/world.h"
#include "config/config.h"
#include "world/sub_chunk.h"
#include "world/mesh.h"

void Minecraft_World::fill_chunks() {
    for (int x = 0; x < World_n::WORLD_SIZE; x++) {

        for (int z = 0; z < World_n::WORLD_SIZE; z++) {

            sub_chunk* chunk1 = new sub_chunk(x,0,z,this);

            worldChunks[decode_sub_chunk_index(x,0,z)] = chunk1;

        }
    }
}

void Minecraft_World::pre_mesh_chunks() {
    for (auto& [key, chunk] : worldChunks) {
        chunk->mesh_sub_chunk();
    }
}