//
// Created by robbie on 23-1-2017.
//

#include "CyberEnforcer.h"
#include <iostream>
CyberEnforcer::CyberEnforcer(Level *lvl, sf::Vector2f vec) : level(lvl), character(new Character(vec, 0.3, 0.1, 100, 172, 260, 0.2)){

}

CyberEnforcer::~CyberEnforcer() {
    delete character;
}

void CyberEnforcer::input(sf::Event &event) {

}

void CyberEnforcer::update(const sf::Time delta) {
    sf::Time time = clock.getElapsedTime();
    if(time.asSeconds() >= 1.5) {
        direction = !direction;
        clock.restart();
    }
    direction ? character->right() : character->left();
    character->update(delta);
}

void CyberEnforcer::draw(sf::RenderWindow &window) {
    character->draw(window);
}