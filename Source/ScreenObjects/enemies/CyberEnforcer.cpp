//
// Created by robbie on 23-1-2017.
//

#include "CyberEnforcer.h"
#include "../../Level.h"
#include <iostream>
CyberEnforcer::CyberEnforcer(sf::Texture t, Level &lvl, sf::Vector2f vec) : level(lvl), character(new Character(t, vec, 0.3, 0.1, 10, 172, 260, 0.17, lvl, true)){

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
    //clock
    sf::Time time = clock.getElapsedTime();
    // random walk for seconds
    if(time.asSeconds() >= 0.5) {
        direction = !direction;
        clock.restart();
    }
    // turn around when seconds are over
    direction ? character->right() : character->left();

    // check if enemy has any weapon
    if(character->get_weapon() != nullptr) {
        // if ranged weapon
        if(character->get_weapon()->get_type() == "ranged") {
            // if enemy is in range of weapon on right side
            if(character->get_is_right_direction() &&
                    level.get_player().getPosition().x >= character->getPosition().x &&
                    level.get_player().getPosition().x <= (character->getPosition().x + ( 0.66 *character->get_weapon()->get_range()))) {
                character->attack();
            }
            // if enemy is in range of weapon on right side
            if(!character->get_is_right_direction() &&
               level.get_player().getPosition().x <= character->getPosition().x &&
               level.get_player().getPosition().x >= (level.get_player().getPosition().x - ( 0.66 *character->get_weapon()->get_range()))) {
                character->attack();
            }
        }
    }
    character->update(delta);
}

void CyberEnforcer::draw(sf::RenderWindow &window) {
    character->draw(window);
}

sf::FloatRect CyberEnforcer::getFloatRect() {
    return character->get_sprite().getGlobalBounds();
}