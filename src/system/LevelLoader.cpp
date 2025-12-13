#include "LevelLoader.hpp"

#include <iostream>
#include <fstream>

LevelLoader* LevelLoader::instance = nullptr;

const LevelLoader& LevelLoader::getInstance() {
    if (instance == nullptr) {
        instance = new LevelLoader();
    }
    return *instance;
}

std::vector<LevelObject*> LevelLoader::load(const std::string& levelFileName) const {
    std::vector<LevelObject*> result;
    std::string delimiter = ",";

    std::string line;
    std::ifstream levelFile(levelFileName);
    while (std::getline(levelFile, line)) {
        std::size_t position;
        while ((position = line.find(delimiter)) != std::string::npos) {
            std::string token = line.substr(0, position);
            line.erase(0, position + delimiter.length());

            std::cout << token << std::endl;
        }
    }

    levelFile.close();
    return std::vector<LevelObject*>();
}

