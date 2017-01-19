//
// Created by robbie on 18-1-2017.
//

#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include <iostream>
Level::Level() {

}

ScreenObject * Level::screen_object_factory(char c, float x, float y) {
    if(c == '-') {
        return new Block(sf::Vector2f(x, y));
    }
    std::string resultString = "\nUndifined char : ";
    throw resultString + c;
}

std::vector<ScreenObject*> Level::get_screen_objects_from_map(std::string &map) {
    // return factor
    std::vector<ScreenObject*> objects;
    // current position
    float current_x = 0;
    float current_y = 0;
    // load file
    std::ifstream input(map);

    std::cout << input.fail();
    char c;
    while(input.get(c)) {
        // when new line..
        if(c == 10) {
            current_x = 0;
            current_y += 32;
            continue;
        } else if(c != '.') {
            try {
                objects.push_back(screen_object_factory(c, current_x, current_y));
            } catch(std::string & exception) {
                std::cout << exception;
            }
        }
        current_x += 32;
    }
    input.close();
    return objects;
}