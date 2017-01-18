//
// Created by Mbeun on 18-1-2017.
//

#include <iostream>
#include "Character.hpp"

Character::Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight) {
    this->position = startPos;
    this->gravity = gravity;
    this->speed = speed;
    this->jumpHeigth = jumpHeight;
    this->startHeight = startPos.y;
}

void Character::move(sf::Vector2f direction){
    position += direction;
}

void Character::jump(){
    if(position.y < startHeight && descending){
        move(sf::Vector2f(0, gravity));
    }
    if(position.y <= startHeight - jumpHeigth){
        setJumping(false);
        descending = true;
    }
    if(position.y <= startHeight && jumping && !descending){
        move(sf::Vector2f(0, -speed));
    }
    if(position.y == startHeight){
        descending = false;
    }
}

void Character::update(sf::RenderWindow &w) {
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    w.draw(shape);
    jump();
}

void Character::setJumping(bool status) {
    jumping = status;
}

float Character::getSpeed() {
    return speed;
}
