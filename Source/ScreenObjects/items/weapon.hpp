//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_WEAPON_HPP
#define SKILLED_EAGLE_GAME_WEAPON_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../ScreenObject.h"
#include "../bullet.hpp"




class weapon{
public:

    virtual void update() = 0;
    virtual void use() = 0;
    virtual void set_direction(sf::Vector2f newDirection) = 0;
    virtual void update_weapon_position(sf::Vector2f playerPosition) = 0;
    virtual void draw(sf::RenderWindow & window)=0;
    virtual void check_collision(ScreenObject & obj) = 0;


};


#endif //SKILLED_EAGLE_GAME_WEAPON_HPP
