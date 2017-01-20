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
        move(sf::Vector2f(0, speed));
    }
    if(position.y <= startHeight - jumpHeigth){
        jumping = false;
        descending = true;
    }
    if(position.y <= startHeight && jumping && !descending){
        move(sf::Vector2f(0, -speed));
    }
    if(position.y == startHeight){
        descending = false;
    }
}

void Character::draw(sf::RenderWindow &window) {
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    window.draw(shape);
}

void Character::update(const sf::Time delta) {
    jump();
}

void Character::input(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move(sf::Vector2f(-speed, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(sf::Vector2f(speed, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        jumping = true;
    }
}
