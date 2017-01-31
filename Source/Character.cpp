//
// Created by Mbeun on 18-1-2017.
//

#include <iostream>
#include "Character.hpp"
#include "Level.h"
#include "ScreenObjects/PowerUp.hpp"

Character::Character(sf::Texture text, sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale, Level &level) {
    this->position = startPos;
    this->gravity = gravity;
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->sprite_scale = sprite_scale;
    this->level = &level;
    img = text.copyToImage();
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setScale(this->sprite_scale, this->sprite_scale);
    colRect = sprite.getGlobalBounds();
    sprite_state = 0;
    sprite.setPosition(position);
}

Weapon* Character::get_weapon() {
    return weapon;
}

void Character::assign_weapon(Weapon *new_weapon) {
    if(weapon != nullptr) {
        weapon->update_weapon_position(sf::Vector2f(position.x, position.y), directionRight);
        weapon->set_is_owned(false);
    }
    weapon = new_weapon;
    weapon->set_is_owned(true);
}

void Character::grab_for_weapon(std::vector<Weapon*> &weapons) {
    for(auto &gun : weapons) {
        if(gun->get_sprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) &&
           !gun->get_is_owned()) {
            assign_weapon(gun);
            break;
        }
    }
}

void Character::attack() {
    if(weapon != nullptr) {
        if(weapon->get_type() == "ranged") {
            int s = directionRight ? 10 : -10;
            weapon->set_direction(sf::Vector2f(s, 0));
        }
        weapon->use();
        if(weapon->get_type() == "sword") {
            sf::FloatRect hit_rectangle;
            hit_rectangle.left = position.x;
            hit_rectangle.top = position.y;
            hit_rectangle.width = directionRight ? 64 : -32;
            hit_rectangle.height = 32;
            int index = 0;
            // each enemy
            for(const auto &obj : level->get_cyber_enforcers()) {
                // if enemy intersects with sword rect..
                if(obj->getFloatRect().intersects(hit_rectangle)) {
                    // if enemy has taken the damage AND hp is lower or equal to 0
                    if(obj->get_character()->take_damage(weapon->get_damage())) {
                        // remove
                        level->get_cyber_enforcers().erase(level->get_cyber_enforcers().begin() + index);
                    }
                }
                index++;
            }
        }
    }
}

sf::Sprite &Character::get_sprite() {
    return sprite;
}

void Character::move(sf::Vector2f direction){
    position += direction;
}

void Character::jump(const sf::Time delta){
    //ascending
    if(jumping && !descending){
        float currentVelocity = -gravity * delta.asMilliseconds();
        colRect.top += currentVelocity * 1.5;
        jumpTime ++;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
            descending = true;
        }
        else{
            move(sf::Vector2f(0, currentVelocity));
            sprite_state ++;
            colRect = sprite.getGlobalBounds();
        }
    }
    //switch
    if(jumpTime > jumpHeight){
        descending = true;
    }
    //descending
    if(descending){
        float currentVelocity = gravity * delta.asMilliseconds();
        colRect.top += currentVelocity * 1.5;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
            descending = false;
            jumping = false;
            jumpTime = 0;
            sprite_state = 1;
        }
        else{
            move(sf::Vector2f(0, currentVelocity));
            sprite_state ++;
            colRect = sprite.getGlobalBounds();
        }
    }
    if(!descending && !jumping){
        colRect.top += gravity * delta.asMilliseconds() * 2;
        auto col = collisionWithLevel(*level);
        if(!col){
            descending = true;
        }
        else{
            position = {position.x, col->getFloatRect().top - sprite.getGlobalBounds().height};
            colRect = sprite.getGlobalBounds();
        }
    }
}

void Character::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Character::update(const sf::Time delta) {
    if(directionRight && moving){
        float currentVelocity = speed * delta.asMilliseconds();
        colRect.left += currentVelocity * 2;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
        }
        else{
            move(sf::Vector2f(currentVelocity, 0));
            if(!jumping){
                sprite_state++;
            }
        }
    }
    if(!directionRight && moving){
        float currentVelocity = -speed * delta.asMilliseconds();
        colRect.left += currentVelocity * 2;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
        }
        else{
            move(sf::Vector2f(currentVelocity , 0));
            if(!jumping){
                sprite_state++;
            }
        }
    }
    jump(delta);
    animation();
    sprite.setPosition(position);
    if(weapon != nullptr) {
        weapon->update_weapon_position(sprite.getPosition(), directionRight);
    }
}

void Character::input(sf::Event &event) {
}

void Character::animation(){
    if(!directionRight && !jumping){
        if(sprite_state % 4 == 0)
            sprite.setTextureRect(sf::IntRect(sprite_state / 4 * sprite_width, sprite_height, -sprite_width, sprite_height));
    }
    if(directionRight && !jumping){
        if(sprite_state % 4 == 0)
            sprite.setTextureRect(sf::IntRect(sprite_state / 4 * sprite_width - sprite_width, sprite_height, sprite_width, sprite_height));
    }
    if(jumping && directionRight){
        if(sprite_state % 7 == 0)
            sprite.setTextureRect(sf::IntRect(6 * sprite_width + (sprite_state / 7) * sprite_width, 0, sprite_width, sprite_height));
    }
    if(jumping && !directionRight){
        if(sprite_state % 7 == 0)
            sprite.setTextureRect(sf::IntRect(5 *sprite_width + (sprite_state / 7) * sprite_width, 0, -sprite_width, sprite_height));
    }
    if(!jumping && !moving && directionRight){
        sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    }
    if(!jumping && !moving && !directionRight){
        sprite.setTextureRect(sf::IntRect(sprite_width, 0, -sprite_width, sprite_height));
    }
    if(sprite_state == 24){
        sprite_state = 0;
    }
}

void Character::left() {
    moving = true;
    directionRight = false;
}

void Character::right() {
    moving = true;
    directionRight = true;
}

void Character::up() {
    jumping = true;
    sprite_state = 0;
}

void Character::stop() {
    moving = false;
}

ScreenObject* Character::collisionWithLevel(Level &level) {
    for(auto &object : level.get_blocks()){
        if(colRect.intersects(object->getFloatRect())){
            return object;
        }
    }
    for(auto &object : level.get_finish()){
        if(colRect.intersects(object->getFloatRect())){
            return object;
        }
    }
    return nullptr;
}

sf::FloatRect Character::get_rect() {
    return sprite.getGlobalBounds();
}

void Character::set_powerUp(PowerUp *p) {
    powerUp = p;
}

PowerUp *Character::get_powerUp() {
    return powerUp;
}



void Character::setSpeed(float s) {
    speed = s;
}


float Character::getSpeed() {
    return speed;
}

sf::Vector2f Character::getPosition() {
    return sprite.getPosition();
}

void Character::set_position(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(pos);
}

bool Character::take_damage(int damage) {
    hp -= damage;
    return hp <= 0;
}
