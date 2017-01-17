//
// Created by robbie on 17-1-2017.
//

#ifndef CDOJO_APP_H
#define CDOJO_APP_H

#include "GameStates/IState.h"
#include "GameStates/MenuState.h"
#include "GameStates/SettingsState.h"
#include "GameStates/PlayState.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    IState * iState;
    MenuState menuState;
    SettingsState settingsState;
    PlayState playState;
    sf::RenderWindow &window;
public:
    Game(sf::RenderWindow &w);
    ~Game();
    void update();
    void draw();
};


#endif //CDOJO_APP_H
