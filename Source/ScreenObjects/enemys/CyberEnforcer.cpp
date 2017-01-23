//
// Created by robbie on 23-1-2017.
//

#include "CyberEnforcer.h"

CyberEnforcer::CyberEnforcer(Level *lvl, sf::Vector2f vec) : level(lvl), character(vec, 0.3, 0.1, 100, 172, 260, 0.2){

}

void CyberEnforcer::input(sf::Event &event) {

}

void CyberEnforcer::update(const sf::Time delta) {
    // idle/default state. Walk alround in map
    sf::Time time = clock.getElapsedTime();
    if(time.asSeconds() >= 1.5) {
        direction = !direction;
        clock.restart();
    }
    direction ? character.left() : character.right();
    // if enemy spotted, go to attack state

    // update the character itself always
    character.update(delta);
}

void CyberEnforcer::draw(sf::RenderWindow &window) {
    character.draw(window);
}