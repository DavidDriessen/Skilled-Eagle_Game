//
// Created by robbie on 18-1-2017.
//

#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include <iostream>

Level::Level(const char * location) {
    std::string loc = location;
    init_new_map(loc);
}

Level::~Level() {
    for (auto &block : blocks) {
        delete block;
    }
    for (auto &cyberEnforcer : cyber_enforcers) {
        delete cyberEnforcer;
    }
    blocks.clear();
    cyber_enforcers.clear();
}

void Level::init_object(char c, float x, float y) {
    switch (c) {
    case '-':
        blocks.push_back(new Block(sf::Vector2f(x, y)));
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
        powerUps.push_back(new PowerUp(sf::Vector2f(x, y)));
        break;
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        blocks.push_back(new Block(sf::Vector2f(x, y)));
        break;
    case 'C':
        cyber_enforcers.push_back(new CyberEnforcer(this, sf::Vector2f(x, y - 16)));
        break;
    case '@':
        weapons.push_back(new RangedWeapon("pistol1", 2, sf::Vector2f(x, y), 15 * 32));
        break;
    case '#':
        weapons.push_back(new RangedWeapon("pistol", 2, sf::Vector2f(x, y), 15 * 32));
        break;
    case '!':
        weapons.push_back(new RangedWeapon("pistol2", 2, sf::Vector2f(x, y), 15 * 32));
        break;
    default:
        std::string resultString = "\nUndifined char : ";
        throw resultString + c + "\n";
    }
}

std::vector<ScreenObject*> &Level::get_blocks() {
    return blocks;
}

std::vector<CyberEnforcer*> &Level::get_cyber_enforcers() {
    return cyber_enforcers;
}

std::vector<PowerUp*> &Level::get_powerUps() {
    return powerUps;
}

std::vector<Weapon*> &Level::get_weapons() {
    return weapons;
}

Character& Level::get_player() {
    return player;
}

void Level::init_new_map(std::string &map) {
    // current position
    float current_x = 0;
    float current_y = 0;
    // load file
    std::ifstream input(map);
    char c;
    while(input.get(c)) {
        // when new line..
        if(c == '\n') {
            current_x = 0;
            current_y += 32;
            continue;
        } else if(c != '.') {
            try {
                init_object(c, current_x, current_y);
            } catch(std::string & exception) {
                std::cout << exception;
            }
        }
        current_x += 32;
    }
    input.close();
}