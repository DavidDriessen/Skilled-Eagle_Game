//
// Created by Mbeun on 18-1-2017.
//

#include <iostream>
#include "Character.hpp"
#include "Level.h"
#include "ScreenObjects/PowerUp.hpp"

Character::Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale, Level &level) {
    this->position = startPos;
    this->gravity = gravity;
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->sprite_scale = sprite_scale;
    this->level = &level;
    img.loadFromFile("assets/images/Nuken.png");
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setScale(this->sprite_scale, this->sprite_scale);
    colRect = sprite.getGlobalBounds();
    sprite_state = 0;
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
        float currentVelocity = -speed * delta.asMilliseconds();
        colRect.top += currentVelocity * 2;
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
        float currentVelocity = speed * delta.asMilliseconds();
        colRect.top += currentVelocity * 2;
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
        colRect.top += speed * delta.asMilliseconds() * 2;
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
    sprite.setPosition(position);
    window.setView(sf::View(sf::Vector2f(colRect.left, colRect.top-(window.getSize().y/6)) ,sf::Vector2f(window.getSize().x, window.getSize().y)));
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
    if(weapon != nullptr) {
        weapon->update_weapon_position(sprite.getPosition(), directionRight);
    }
}

void Character::input(sf::Event &event) {
//    if(event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)){
//        moving = true;
//    }
//    if(event.type == event.KeyReleased && (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)){
//        moving = false;
//    }
//    if (moving){
//        if(event.key.code == sf::Keyboard::Key::Left){
//            directionRight = false;
//        }
//        if(event.key.code == sf::Keyboard::Key::Right){
//            directionRight = true;
//        }
//        if(event.key.code == sf::Keyboard::Key::Up){
//            jumping = true;
//            sprite_state = 0;
//        }
//    }
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
    return nullptr;
}

sf::FloatRect Character::get_rect() {
    return sprite.getGlobalBounds();
}

void Character::set_powerUp(PowerUp *p) {
    powerUp = p;
}

void Character::setSpeed(float s) {
    speed = s;
}