#ifndef __LEVEL_OBJECT_HPP__
#define __LEVEL_OBJECT_HPP__

enum LevelObjectType {
    PLATFORM
};

struct LevelObject {
    LevelObjectType type;
    void* object;
};

#endif
