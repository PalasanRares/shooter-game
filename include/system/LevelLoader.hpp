#ifndef __LEVEL_LOADER_HPP__
#define __LEVEL_LOADER_HPP__

#include <vector>
#include <string>

#include "LevelObject.hpp"

class LevelLoader {
private:
    static LevelLoader* instance;

public:
    static const LevelLoader& getInstance();

    std::vector<LevelObject*> load(const std::string& levelFileName) const;
};

#endif
