//
// Created by Mbeun on 18-1-2017.
//

#include <iostream>
#include "Character.hpp"

Character::Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale) {
    this->position = startPos;
    this->groundHeight = startPos.y;
    this->gravity = gravity;
    this->speed = speed;
    this->jumpHeigth = jumpHeight;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->sprite_scale = sprite_scale;
    img.loadFromFile("assets/images/Nuken.png");
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setScale(this->sprite_scale, this->sprite_scale);
    sprite_state = 0;
}

void Character::move(sf::Vector2f direction){
    position += direction;
}

void Character::jump(const sf::Time delta){
    //ascending
    if(jumping && !descending){
        move(sf::Vector2f(0, -speed * delta.asMilliseconds()));
        sprite_state ++;
    }
    //switch
    if(position.y <= groundHeight - jumpHeigth){
        descending = true;
    }
    //descending
    if(position.y < groundHeight && descending){
        move(sf::Vector2f(0, gravity * delta.asMilliseconds()));
        sprite_state ++;
    }
    //touch ground
    if(position.y >= groundHeight){
        descending = false;
        jumping = false;
    }
}

void Character::draw(sf::RenderWindow &window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

void Character::update(const sf::Time delta) {
    if(directionRight && moving){
        move(sf::Vector2f(speed * delta.asMilliseconds(), 0));
        if(!jumping){
            sprite_state++;
        }
    }
    if(!directionRight && moving){
        move(sf::Vector2f(-speed * delta.asMilliseconds() , 0));
        if(!jumping){
            sprite_state++;
        }
    }
    jump(delta);
    animation();
}

void Character::input(sf::Event &event) {
    if(event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)){
        moving = true;
    }
    if(event.type == event.KeyReleased && (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)){
        moving = false;
    }
    if (moving){
        if(event.key.code == sf::Keyboard::Key::Left){
            directionRight = false;
        }
        if(event.key.code == sf::Keyboard::Key::Right){
            directionRight = true;
        }
        if(event.key.code == sf::Keyboard::Key::Up){
            jumping = true;
            sprite_state = 0;
        }
    }
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
