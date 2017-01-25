//
// Created by jer on 19-1-2017.
//

#include "RangedWeapon.hpp"

RangedWeapon::RangedWeapon(std::string s, int damage, sf::Vector2f playerPosition, int range) :
        name(s),
        damage(damage),
        position(playerPosition),
        range(range){
    std::string path = "assets/images/"+ s + ".png";
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setPosition(playerPosition);
    sprite.scale(0.6,0.6);
}


void RangedWeapon::update() {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        kogel->update(sf::Time::Zero);
    }

    bulletVector.erase(std::remove_if(bulletVector.begin(), bulletVector.end(), [](std::unique_ptr<bullet> &kogel) {
                                          return kogel->hasCollision;
                                      }
    ), bulletVector.end());
    cooldown = clock.getElapsedTime();
}

void RangedWeapon::draw(sf::RenderWindow &window) {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        kogel->draw(window);
    }
    window.draw(sprite);
}

void RangedWeapon::update_weapon_position(sf::Vector2f playerPosition, bool character_right_direction) {
    if(right_direction != character_right_direction) {
        sprite.scale(-1.f, 1.f);
        right_direction = character_right_direction;
    }
    position = right_direction ? sf::Vector2f(playerPosition.x, playerPosition.y + 10) : sf::Vector2f(playerPosition.x + 30 , playerPosition.y + 10);
    sprite.setPosition(position);
}

void RangedWeapon::set_direction(sf::Vector2f newDirection) {
    direction = newDirection;
}

void RangedWeapon::use() {
    if (cooldown > cooldownPeriod) {
        sf::Vector2f spawnVec = position;
        spawnVec.x += right_direction ? 0 : -sprite.getTextureRect().width / 2;
        spawnVec.y += 10;
        bulletVector.push_back(std::make_unique<bullet>("bullet", spawnVec, 20, direction));
        cooldown = sf::Time::Zero;
        clock.restart();
    }
}

void RangedWeapon::check_collision(ScreenObject &obj) {
    for (std::unique_ptr<bullet> &kogel  : bulletVector) {
        if (kogel->collision(obj)) {
            kogel->set_hasCollision();
        }
    }
}