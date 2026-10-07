#include <iostream>
#include <filesystem>
#include <cmath>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../include/imageRendering/stb_image.h"
#include "../include/imageRendering/stb_image_write.h"

int texSize = 16;//size of the texture

int atlasWidth = 16; //the width of the atlas
int atlasHeight; //height gets calced

int channels = 4; //the channels we want

int main() {
    int count{};

    std::filesystem::path p1{"Images"};

    for (auto& p : std::filesystem::directory_iterator(p1)) {
        count++;
    }

    atlasHeight = std::ceil(count / (float)atlasWidth); //calc the new height

    size_t atlasPixels = static_cast<size_t>(atlasWidth) * texSize * atlasHeight * texSize * channels;

    unsigned char* newImage = new unsigned char[atlasPixels]();

    int xINDEX = 0;
    int yINDEX = 0;

    for (const auto& p : std::filesystem::directory_iterator(p1)) {
        std::string filename = p.path().string();

        int width, height, fileChannels;

        unsigned char* image = stbi_load(
            filename.c_str(),
            &width,
            &height,
            &fileChannels,
            4
        );

        for (int y = 0; y < texSize; y++) {
            for (int x = 0; x < texSize; x++) {
                int atlasX = x + xINDEX * texSize;
                int atlasY = y + yINDEX * texSize;

                int pixelPosition = (atlasY * (atlasWidth*texSize) + atlasX) * channels;
                int localPosition = (y * texSize + x) * channels;

                newImage[pixelPosition + 0] = image[localPosition + 0]; // R
                newImage[pixelPosition + 1] = image[localPosition + 1]; // G
                newImage[pixelPosition + 2] = image[localPosition + 2]; // B
                newImage[pixelPosition + 3] = image[localPosition + 3]; // A
            }
        }

        xINDEX++;
        if (xINDEX >= 16) {
            yINDEX++;
            xINDEX = 0;
        }

        stbi_image_free(image); 
    }

    stbi_write_png(
        "output.png",
        atlasWidth * texSize,
        atlasHeight * texSize,
        channels,
        newImage,
        atlasWidth * texSize * channels
    );

    std::filesystem::rename("output.png", "output_folder/output.png");
}
