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

    if(!is_owned) {
        // set sword not in attack modus when is not owned anymore
        is_attacking = false;
    }

    if(is_attacking){
        if(right_direction) {
            sprite.setRotation(sprite.getRotation() + 50);
            sprite.setPosition(sf::Vector2f(sprite.getPosition().x + 25, sprite.getPosition().y + 25));
        } else {
            sprite.setRotation(sprite.getRotation() - 50);
            sprite.setPosition(sf::Vector2f(sprite.getPosition().x - 30, sprite.getPosition().y + 20));
        }
        if(cooldown > cooldownPeriod) {
            is_attacking = false;
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
        is_attacking = true;
        clock.restart();
    }
}

void MeleeWeapon::check_collision(ScreenObject &obj) {

}

bool MeleeWeapon::check_collision(Character &obj) {
    if(is_attacking) {
        sf::FloatRect hit_rectangle;
        hit_rectangle.left = position.x;
        hit_rectangle.top = position.y;
        hit_rectangle.width = right_direction ? range : -range;
        hit_rectangle.height = sprite.getTextureRect().height;
        return hit_rectangle.intersects(obj.get_rect());
    }
    return false;
}