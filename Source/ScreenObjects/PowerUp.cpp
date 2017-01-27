//
// Created by david on 1/24/2017.
//

#include "PowerUp.hpp"
#include "../Character.hpp"

PowerUp::PowerUp(sf::Texture active, sf::Texture used, sf::Vector2f vec) : rect(vec, sf::Vector2f(32, 32)) {
    texture = sf::Texture(active);
    texture2 = sf::Texture(used);
    sprite.setPosition(rect.left, rect.top);
    sprite.setTexture(texture);
    sprite.setScale(1, 1);
}

void PowerUp::update(const sf::Time delta, Character &player) {
    if (available && rect.intersects(player.get_rect())) {
        player.set_powerUp(this);
        available = false;
        sprite.setTexture(texture2);
        timer.restart();
    }
    if(activated && !used) {
        timer.restart();
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
sf::Time PowerUp::getActiveTime(){
    return timer.getElapsedTime();
}

bool PowerUp::getDone(){
    return done;
}
void PowerUp::setDone(bool status){
    done = status;
}

bool PowerUp::getUsed() {
    return used;
}

void PowerUp::setUsed(bool status){
    used = status;
}

