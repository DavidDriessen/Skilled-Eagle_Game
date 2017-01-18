//
// Created by robbie on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_LEVEL_H
#define SKILLED_EAGLE_GAME_LEVEL_H
#include <vector>
#include <string>
#include <fstream>
#include "screenObjects/ScreenObject.h"
#include "screenObjects/Block.h"

class Level {
private:
    std::vector<ScreenObject*> screen_objects;
public:
    Level();
    ScreenObject * screen_object_factory(char c, float x, float y);
    std::vector<ScreenObject*> get_screen_objects_from_map(std::string &map);
};

#endif //SKILLED_EAGLE_GAME_LEVEL_H
