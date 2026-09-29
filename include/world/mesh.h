#ifndef MESH_H
#define MESH_H

void paste_face(const float vertices[30], int x, int y, int z, std::vector<float>& sub_chunk_vertices) {
    for (int i = 0; i < 6; i++) {// voor iedere vertex (6)
        sub_chunk_vertices.push_back(vertices[i * 5 + 0] + x); //iedere vertex is 5 floats dus als we 1 extra vertex doen moeten we ook 5 offset hebben
        sub_chunk_vertices.push_back(vertices[i * 5 + 1] + y);//plus 0 1 2 3 4 omdat iedere vertex heeft 5 parameters en we moeten ze alle 5 afhandelen
        sub_chunk_vertices.push_back(vertices[i * 5 + 2] + z);

        sub_chunk_vertices.push_back(vertices[i * 5 + 3]);
        sub_chunk_vertices.push_back(vertices[i * 5 + 4]);
    }
}

int decode_sub_chunk_index(int x, int y, int z) {
    int index = (z * 16 * 16) + (y * 16) + x;

    return index;
}

#endif