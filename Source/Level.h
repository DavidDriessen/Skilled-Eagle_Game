//
// Created by robbie on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_LEVEL_H
#define SKILLED_EAGLE_GAME_LEVEL_H
#include <vector>
#include <string>
#include <fstream>
#include "ScreenObjects/ScreenObject.h"
#include "ScreenObjects/Block.h"

class Level {
private:
    std::vector<ScreenObject*> blocks;
    void init_object(char c, float x, float y);
public:
    Level(const char *location);
    ~Level();
    std::vector<ScreenObject*> &get_blocks();
    void init_new_map(std::string &map);
};

#endif //SKILLED_EAGLE_GAME_LEVEL_H
