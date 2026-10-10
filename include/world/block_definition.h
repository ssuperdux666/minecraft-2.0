#ifndef BLOCK_DEFINITION
#define BLOCK_DEFINITION

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../../atlasIndexing.h"

#include "json.hpp"

using json = nlohmann::json;

using string = std::string;

inline json FINALIZED_BLOCK_DATA[256];

inline void load_ALL_blocks() {
    string blocksPath = "../blocks";

    for (int i = 1; i < amountOfBlocks+1; i++) {

        string currentPath = blocksPath + "/" + blockFiles[i] + ".JSON";

        std::ifstream file(currentPath);

        if (!file.is_open()) {
            std::cerr << "Failed to open: " << currentPath << '\n';
            continue;
        }

        if (file.peek() == std::ifstream::traits_type::eof()) {
            std::cerr << "File is empty: " << currentPath << '\n';
            continue;
        }

        json block_j;

        try {
            file >> block_j;
        }
        catch (const json::parse_error& e) {
            std::cerr << "Invalid JSON in: " << currentPath << '\n';
            std::cerr << e.what() << '\n';
            continue;
        }

        FINALIZED_BLOCK_DATA[i] = block_j;
    }
}



inline int getTexture(const char* faceName, const int blockID){

    json& textures = FINALIZED_BLOCK_DATA[blockID]["texCoords"][0];
    json& faces = FINALIZED_BLOCK_DATA[blockID]["faces"][0];

    std::string textureName = faces[faceName].get<std::string>();
    return textures[textureName].get<int>();

};

inline string getNameWithID(int blockID) {
    return FINALIZED_BLOCK_DATA[blockID]["name"];
}

#endif