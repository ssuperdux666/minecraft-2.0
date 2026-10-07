#ifndef TEXTURES_H
#define TEXTURES_H

class Texture {
    public:
        unsigned int ID;

        Texture(const char* path);

        void getTexCoords();
};

#endif