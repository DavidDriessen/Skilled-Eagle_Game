//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP
#define SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP

#include <docobjectservice.h>
#include "Weapon.hpp"

class RangedWeapon : public Weapon {
private:
    int damage;
    std::string name;
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<std::unique_ptr<bullet>> bulletVector;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Time cooldownPeriod = sf::milliseconds(200);
    sf::Time cooldown = sf::Time::Zero;
    int range;
    bool is_owned = false;
    bool right_direction = true;
public:
    RangedWeapon(std::string s, int damage, sf::Vector2f playerPosition, int range);
    bool get_is_owned() const {
        return is_owned;
    }
    void set_is_owned(bool owned) {
        is_owned = owned;
    }
    std::string get_name() {
        return name;
    }
    std::string get_type() {
        std::string type = "ranged";
        return type;
    }
    int get_range() {
        return range;
    }
    sf::Sprite &get_sprite() {
        return sprite;
    }
    void set_direction(sf::Vector2f newDirection);
    void use();
    void update();
    void update_weapon_position(sf::Vector2f playerPosition, bool right_direction);
    void draw(sf::RenderWindow &window);
    void check_collision(ScreenObject &obj);
};


#endif //SKILLED_EAGLE_GAME_RANGEDWEAPON_HPP
