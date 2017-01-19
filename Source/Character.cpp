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
<<<<<<< HEAD
    img.loadFromFile("Nuken.png");
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_widths, sprite_height));
    sprite.setScale(sprite_scale, sprite_scale);
    sprite_state = 0;
=======
>>>>>>> Character class with jump and moving capabilities (main.cpp contains test values and code)
}

void Character::move(sf::Vector2f direction){
    position += direction;
}

void Character::jump(){
    if(position.y < startHeight && descending){
<<<<<<< HEAD
        move(sf::Vector2f(0, speed));
    }
    if(position.y <= startHeight - jumpHeigth){
        jumping = false;
=======
        move(sf::Vector2f(0, gravity));
    }
    if(position.y <= startHeight - jumpHeigth){
<<<<<<< HEAD
        setJumping(false);
>>>>>>> Character class with jump and moving capabilities (main.cpp contains test values and code)
=======
        jumping = false;
>>>>>>> Changed to fit gamestate structure. Also deleted some obsolete functions
        descending = true;
    }
    if(position.y <= startHeight && jumping && !descending){
        move(sf::Vector2f(0, -speed));
    }
    if(position.y == startHeight){
        descending = false;
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
void Character::draw(sf::RenderWindow &window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

void Character::update(const sf::Time delta) {
    jump();
}

void Character::input(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if(sprite_state == 0){
            sprite.setTextureRect(sf::IntRect(160, 260, -160, 260));
            sprite_state++;
        }
        move(sf::Vector2f(-speed, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(sf::Vector2f(speed, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        jumping = true;
    }
}

//void Character::animation(int state){

//}
=======
void Character::update(sf::RenderWindow &w) {
=======
void Character::draw(sf::RenderWindow &window) {
>>>>>>> Changed to fit gamestate structure. Also deleted some obsolete functions
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
>>>>>>> Character class with jump and moving capabilities (main.cpp contains test values and code)
