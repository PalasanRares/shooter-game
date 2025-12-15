#ifndef __LEVEL_LOADER_HPP__
#define __LEVEL_LOADER_HPP__

#include <vector>
#include <string>

#include "LevelObject.hpp"
#include "WindowRenderer.hpp"

class LevelLoader {
private:
    static LevelLoader* instance;

    LevelObjectType mapLevelObjectType(const std::string& token) const;

public:
    static const LevelLoader& getInstance();

    std::vector<LevelObject*> load(const WindowRenderer& windowRenderer, const std::string& levelFileName) const;
};

#endif
