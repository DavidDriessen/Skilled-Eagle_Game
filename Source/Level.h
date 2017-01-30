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
#include "ScreenObjects/Finish.hpp"
#include "ScreenObjects/enemies/CyberEnforcer.h"
#include "Character.hpp"
#include "ScreenObjects/items/Weapon.hpp"
#include "ScreenObjects/PowerUp.hpp"


class Game;
class CyberEnforcer;
class Level {
private:
    std::vector<ScreenObject*> blocks;
    std::vector<ScreenObject*> ends;
    std::vector<PowerUp*> powerUps;
    std::vector<CyberEnforcer*> cyber_enforcers;
    std::vector<Weapon*> weapons;
    Character player;
    Game *game = nullptr;
    void init_object(char c, float x, float y);
public:
    Level(const char *location, Game* game);
    ~Level();
    std::vector<ScreenObject*> &get_blocks();
    std::vector<ScreenObject*> &get_finish();
    std::vector<PowerUp*> &get_powerUps();
    std::vector<CyberEnforcer*> &get_cyber_enforcers();
    std::vector<Weapon*> &get_weapons();
    Character &get_player();
    void init_new_map(std::string &map);

};

#endif //SKILLED_EAGLE_GAME_LEVEL_H
