#ifndef MESH_H
#define MESH_H

#include "config/config.h"

inline void paste_face(const float vertices[30], int x, int y, int z, std::vector<float>& sub_chunk_vertices,int textureNumber) {

    float tileMAX = textureNumber / 16.0f;
    float tileMIN = (textureNumber+1) / 16.0f;

    for (int i = 0; i < 6; i++) {// voor iedere vertex (6)  bottom left, bottom right, top right, top right, top left, bottom left

        sub_chunk_vertices.push_back(vertices[i * 5 + 0] + x); //iedere vertex is 5 floats dus als we 1 extra vertex doen moeten we ook 5 offset hebben
        sub_chunk_vertices.push_back(vertices[i * 5 + 1] + y);//plus 0 1 2 3 4 omdat iedere vertex heeft 5 parameters en we moeten ze alle 5 afhandelen
        sub_chunk_vertices.push_back(vertices[i * 5 + 2] + z);

        float u = vertices[i * 5 + 3];
        sub_chunk_vertices.push_back(tileMIN + u * (tileMAX - tileMIN));
                
        sub_chunk_vertices.push_back(vertices[i * 5 + 4] * 1.0f);
    }
}

inline int decode_sub_chunk_index(int x, int y, int z) {
    int index = (z * World_n::SUB_CHUNK_SIZE * World_n::SUB_CHUNK_SIZE) + (y * World_n::SUB_CHUNK_SIZE) + x;

    return index;
}

#endif