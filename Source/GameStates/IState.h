//
// Created by robbie on 17-1-2017.
//

#ifndef WAVEFORMS_ISTATE_H
#define WAVEFORMS_ISTATE_H
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

// Game use state pattern. Each state of the game requires update and draw method.
class IState {
public:
    virtual void input(sf::Event &event) = 0;
    virtual void update(const sf::Time delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};


#endif //WAVEFORMS_ISTATE_H
