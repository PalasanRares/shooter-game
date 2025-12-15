#include "LevelLoader.hpp"

#include <iostream>
#include <fstream>

#include "Platform.hpp"

LevelLoader* LevelLoader::instance = nullptr;

const LevelLoader& LevelLoader::getInstance() {
    if (instance == nullptr) {
        instance = new LevelLoader();
    }
    return *instance;
}

LevelObjectType LevelLoader::mapLevelObjectType(const std::string& token) const {
    if (token == "PLATFORM") {
        return LevelObjectType::PLATFORM;
    }
    return LevelObjectType::UNDEFINED;
}

std::vector<LevelObject*> LevelLoader::load(const WindowRenderer& windowRenderer, const std::string& levelFileName) const {
    std::vector<LevelObject*> result;
    std::string delimiter = ",";

    std::string line;
    std::ifstream levelFile(levelFileName);

    LevelObjectType levelObjectType;
    int xPosition, yPosition, width, height;
    std::string textureFile;

    while (std::getline(levelFile, line)) {
        std::size_t position;
        std::size_t tokenPosition = 0;
        while ((position = line.find(delimiter)) != std::string::npos) {
            std::string token = line.substr(0, position);
            line.erase(0, position + delimiter.length());

            switch (tokenPosition) {
                case 0:
                    levelObjectType = mapLevelObjectType(token);
                    break;
                case 1:
                    xPosition = stoi(token);
                    break;
                case 2:
                    yPosition = stoi(token);
                    break;
                case 3:
                    width = stoi(token);
                    break;
                case 4:
                    height = stoi(token);
                    break;
            }
            tokenPosition += 1;
        }
        textureFile = line;
        LevelObject* levelObject = new LevelObject();

        switch (levelObjectType) {
            case LevelObjectType::UNDEFINED:
                continue;
            case LevelObjectType::PLATFORM:
                levelObject->type = LevelObjectType::PLATFORM;
                levelObject->object = (void*) new Platform(
                    new Transform(Vector2(xPosition, yPosition)),
                    new Sprite(IMG_LoadTexture(windowRenderer.getRenderer(), textureFile.c_str()))
                );
                result.push_back(levelObject);
                break;
        }
    }

    levelFile.close();
    return result;
}

