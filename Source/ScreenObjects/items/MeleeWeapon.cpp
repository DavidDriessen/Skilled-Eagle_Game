//
// Created by jer on 19-1-2017.
//

#include "MeleeWeapon.hpp"

MeleeWeapon::MeleeWeapon(sf::Texture s, int damage, sf::Vector2f playerPosition, int range, sf::Time cooldown) :
        damage(damage),
        position(playerPosition),
        range(range),
        cooldownPeriod(cooldown){
    texture = sf::Texture(s);
    sprite.setTexture(texture);
    sprite.setPosition(playerPosition);
    sprite.scale(0.4,0.4);
    sprite.setRotation(90);
}

void MeleeWeapon::update() {
    cooldown = clock.getElapsedTime();
    if(cooldown < cooldownPeriod && is_attack_drawable) {
        if(right_direction) {
            sprite.setRotation(sprite.getRotation() + 50);
            sprite.setPosition(sf::Vector2f(sprite.getPosition().x + 25, sprite.getPosition().y + 25));
        } else {
            sprite.setRotation(sprite.getRotation() - 50);
            sprite.setPosition(sf::Vector2f(sprite.getPosition().x - 30, sprite.getPosition().y + 20));
        }
    }
}

void MeleeWeapon::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void MeleeWeapon::update_weapon_position(sf::Vector2f playerPosition, bool character_right_direction) {
    if(right_direction != character_right_direction) {
        sprite.scale(-1.f, 1.f);
        right_direction = character_right_direction;
    }
    position = right_direction ? sf::Vector2f(playerPosition.x + 20, playerPosition.y - 25) : sf::Vector2f(playerPosition.x , playerPosition.y - 25);
    if(right_direction) {
        sprite.setRotation(20);
    } else {
        sprite.setRotation(340);
    }
    sprite.setPosition(position);
}

void MeleeWeapon::set_direction(sf::Vector2f newDirection) {
    direction = newDirection;
}

void MeleeWeapon::use() {
    if (cooldown > cooldownPeriod) {
        is_attack_drawable = true;
        clock.restart();
    }
}

void MeleeWeapon::check_collision(ScreenObject &obj) {

}