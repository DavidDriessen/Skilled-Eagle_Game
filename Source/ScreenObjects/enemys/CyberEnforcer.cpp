//
// Created by robbie on 23-1-2017.
//

#include "CyberEnforcer.h"
#include "../../Level.h"
#include <iostream>
CyberEnforcer::CyberEnforcer(Level &lvl, sf::Vector2f vec) : level(lvl), character(new Character(vec, 0.3, 0.4, 10, 172, 260, 0.2, lvl)){

}

CyberEnforcer::~CyberEnforcer() {
    delete character;
}

Character* CyberEnforcer::get_character() {
    return character;
}

void CyberEnforcer::input(sf::Event &event) {

}

void CyberEnforcer::update(const sf::Time delta) {
    sf::Time time = clock.getElapsedTime();
    if(time.asSeconds() >= 0.5) {
        direction = !direction;
        clock.restart();
    }
    direction ? character->right() : character->left();
    character->update(delta);
}

void CyberEnforcer::draw(sf::RenderWindow &window) {
    character->draw(window);
}

sf::FloatRect CyberEnforcer::getFloatRect() {
    return character->get_sprite().getGlobalBounds();
}