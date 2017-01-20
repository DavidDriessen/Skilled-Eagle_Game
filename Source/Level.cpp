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
    blocks.clear();
}

void Level::init_object(char c, float x, float y) {
    switch (c) {
    case '-':
        blocks.push_back(new Block(sf::Vector2f(x, y)));
        break;
    default:
        std::string resultString = "\nUndifined char : ";
        throw resultString + c;
    }
}

std::vector<ScreenObject*> &Level::get_blocks() {
    return blocks;
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
        if(c == 10) {
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