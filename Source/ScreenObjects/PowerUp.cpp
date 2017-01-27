//
// Created by david on 1/24/2017.
//

#include "PowerUp.hpp"
#include "../Character.hpp"

PowerUp::PowerUp(sf::Vector2f vec) : rect(vec, sf::Vector2f(32, 32)) {
    img.loadFromFile("assets/images/loot2.png");
    img2.loadFromFile("assets/images/loot.png");
    texture.loadFromImage(img);
    texture2.loadFromImage(img2);
    sprite.setPosition(rect.left, rect.top);
    sprite.setTexture(texture);
    sprite.setScale(1, 1);
}

void PowerUp::update(const sf::Time delta, Character &player) {
    if (available && rect.intersects(player.get_rect())) {
        player.set_powerUp(this);
        available = false;
        sprite.setTexture(texture2);
    }
}

void PowerUp::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

int PowerUp::getFunction(){
    return function;
}

void PowerUp::setActive(bool status){
    activated = status;
}

bool PowerUp::getActive(){
    return activated;
}

