//
// Created by robbie on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_SCREENOBJECT_H
#define SKILLED_EAGLE_GAME_SCREENOBJECT_H


#include <SFML/Graphics/RenderWindow.hpp>

class ScreenObject {
public:
    virtual void input(sf::Event &event) = 0;
    virtual void update(const sf::Time delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual sf::FloatRect getFloatRect() = 0;
};


#endif //SKILLED_EAGLE_GAME_SCREENOBJECT_H
