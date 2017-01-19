//
// Created by robbie on 17-1-2017.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IState.h"

class Game;
class MenuState : public IState {
private:
    Game *game;
public:
    MenuState();

    MenuState(Game *pGame);

    void input(sf::Event &event);
    void update(float delta);
    void draw(sf::RenderWindow &window);
};


#endif //WAVEFORMS_MENU_H
