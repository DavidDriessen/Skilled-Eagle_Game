//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP
#define SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP

#include "weapon.hpp"

class rangedWeapon : public weapon {
public:
    int damage;
    std::string name;
    sf::Vector2f position;
    std::vector<std::unique_ptr<bullet>> bulletVector;
    sf::Vector2f direction;

    sf::Clock clock;
    sf::Time cooldownPeriod = sf::milliseconds(200);
    sf::Time cooldown = sf::Time::Zero;

    rangedWeapon(std::string s, int damage, sf::Vector2f playerPosition);

    void set_direction(sf::Vector2f newDirection);

    void use();

    void update();

    void update_weapon_position(sf::Vector2f playerPosition);

    void draw(sf::RenderWindow &window);

    void check_collision(ScreenObject &obj);


};


#endif //SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP
