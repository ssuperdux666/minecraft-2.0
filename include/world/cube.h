#ifndef CUBE_H
#define CUBE_H

const float CUBE_VERTICES[120] = {

    // FRONT
    // position              // UV
    -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,

    // BACK
     0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,     0.0f, 1.0f,

    // LEFT
    -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,

    // RIGHT
     0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,     0.0f, 1.0f,

    // TOP
    -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,

    // BOTTOM
    -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,     1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,     0.0f, 1.0f
};

const unsigned int CUBE_INDICES[36] = {
    // face 1
    0, 1, 2,
    2, 3, 0,

    // face 2
    4, 5, 6,
    6, 7, 4,

    // face 3
    8, 9, 10,
    10, 11, 8,

    // face 4
    12, 13, 14,
    14, 15, 12,

    // face 5
    16, 17, 18,
    18, 19, 16,

    // face 6
    20, 21, 22,
    22, 23, 20
};

const unsigned int CUBE_INDEX_SINGLE[6] = {
    0, 1, 2,
    2, 3, 0,
};

const float CUBE_VERTICES_FRONT[30] = {
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right

     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom left
};

const float CUBE_VERTICES_BACK[30] = {
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right

    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top left
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
};

const float CUBE_VERTICES_LEFT[30] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right

    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
};

const float CUBE_VERTICES_RIGHT[30] = {
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right

     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom left
};

const float CUBE_VERTICES_UP[30] = {
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right

     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom left
};

const float CUBE_VERTICES_BOTTOM[30] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom right
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // top right

     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // top right
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // top left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
};

const int directions[6][3] = {
    { 0,  0,  1}, // front
    { 0,  0, -1}, // back
    {-1,  0,  0}, // left
    { 1,  0,  0}, // right
    { 0,  1,  0}, // top
    { 0, -1,  0}  // bottom
};

#endif