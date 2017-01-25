//
// Created by jer on 19-1-2017.
//

#include "rangedWeapon.hpp"

rangedWeapon::rangedWeapon(std::string s, int damage, sf::Vector2f playerPosition) :
        name(s),
        damage(damage),
        position(playerPosition) {}


void rangedWeapon::update() {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        kogel->update(sf::Time::Zero);
    }

    bulletVector.erase(std::remove_if(bulletVector.begin(), bulletVector.end(), [](std::unique_ptr<bullet> &kogel) {
                                          return kogel->hasCollision;
                                      }
    ), bulletVector.end());
    cooldown = clock.getElapsedTime();
}

void rangedWeapon::draw(sf::RenderWindow &window) {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        kogel->draw(window);
    }
}

void rangedWeapon::update_weapon_position(sf::Vector2f playerPosition) {
    position = playerPosition;
}

void rangedWeapon::set_direction(sf::Vector2f newDirection) {
    direction = newDirection;
}

void rangedWeapon::use() {
    if (cooldown > cooldownPeriod) {
        bulletVector.push_back(std::make_unique<bullet>("bullet", position, 20, direction));
        cooldown = sf::Time::Zero;
        clock.restart();
    }
}


void rangedWeapon::check_collision(ScreenObject &obj) {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        if (kogel->collision(obj)) {
            kogel->set_hasCollision();
            std::cout << name << "\n";
        }
    }
}