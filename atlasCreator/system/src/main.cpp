#include <iostream>
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../Include/imageRendering/stb_image.h"
#include "../../Include/imageRendering/stb_image_write.h"

#include "../../../atlasIndexing.h"

using string = std::string;

int texSize = 16;//size of the texture

int atlasWidth = 16; //the width of the atlas
int atlasHeight; //height gets calced

int channels = 4; //the channels we want

int main() {

    int count = amountOfBlocks + amountDiffringBlocks;

    string blocksPath = "Images";

    atlasHeight = std::ceil(count / (float)atlasWidth); //calc the new height
    size_t atlasPixels = static_cast<size_t>(atlasWidth) * texSize * atlasHeight * texSize * channels;


    string textureFiles[amountOfBlocks + amountDiffringBlocks];
    int texFileIndex = 0;

    for (int i = 1; i < amountOfBlocks + 1; i++) {
        bool Done = false;

        for (int j = 0; j < amountDiffringBlocks; j++) {
            if (blockFiles[i] == diffrentBlocks[j]) {
                Done = true;
                for (int k = 1; k < differingAmounts[j]+1; k++) {
                    textureFiles[texFileIndex] = blockFiles[i] + std::to_string(k);
                    texFileIndex++;
                }
            }
        }

        if (Done) {continue;}

        textureFiles[texFileIndex] = blockFiles[i];
        texFileIndex++;
    }

    
    unsigned char* newImage = new unsigned char[atlasPixels]();

    int xINDEX = 0;
    int yINDEX = 0;

    for (int i = 0; i < count; i++) {

        string currentPath = blocksPath + "/" + textureFiles[i] + ".png";

        std::cout << currentPath << std::endl;

        int width, height, fileChannels;

        unsigned char* image = stbi_load(
            currentPath.c_str(),
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
