#ifndef ATLAS_INDEXING
#define ATLAS_INDEXING

#include <string>

constexpr int amountOfBlocks = 10;
constexpr int amountDiffringBlocks = 2;

using string = std::string;

inline string diffrentBlocks[amountDiffringBlocks] = {
    "grass",
    "oakLog",
};

inline int differingAmounts[amountDiffringBlocks] = {
    2,
    2,
};

inline string blockFiles[amountOfBlocks + 1] = { // + 1 is voor de air.json maar die wordt niet gebruit en telt niet
    "air.json", //0
    "dirt", //1
    "grass", //2
    "oakLog", //3
    "oakPlank", //4
    "leaves", //5
    "sand", //6
    "stone", //7
    "cobblestone", //8
    "coalOre", //9
    "ironOre", //10
};




#endif