//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_WEAPON_HPP
#define SKILLED_EAGLE_GAME_WEAPON_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../ScreenObject.h"
#include "../Bullet.hpp"

class Character;

class Weapon{
public:
    virtual std::string get_type() = 0;
    virtual int get_range() = 0;
    virtual float get_bullet_speed() const = 0;
    virtual void set_bullet_speed(float speed) = 0;
    virtual void update() = 0;
    virtual void use() = 0;
    virtual bool get_is_owned() const = 0;
    virtual void set_is_owned(bool owned) = 0;
    virtual sf::Sprite &get_sprite() = 0;
    virtual void set_direction(sf::Vector2f newDirection) = 0;
    virtual void update_weapon_position(sf::Vector2f playerPosition, bool right_direction) = 0;
    virtual void draw(sf::RenderWindow & window)=0;
    virtual void check_collision(ScreenObject & obj) = 0;
    virtual bool check_collision(Character & obj) = 0;
    virtual int get_damage() const = 0;
};


#endif //SKILLED_EAGLE_GAME_WEAPON_HPP
