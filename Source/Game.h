//
// Created by robbie on 17-1-2017.
//

#ifndef WAVEFORMS_APP_H
#define WAVEFORMS_APP_H

#include "GameStates/IState.h"
#include "GameStates/MenuState.h"
#include "GameStates/SettingsState.h"
#include "GameStates/PlayState.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    IState *iState;
    MenuState *menuState;
    SettingsState *settingsState;
    PlayState *playState;
    sf::RenderWindow &window;
public:
    Game(sf::RenderWindow &w);

    ~Game();

    void update();

    void draw();

    void input();

    void go_to_play();

    void go_to_menu();

    void go_to_options();

    void quite();

    sf::Vector2i get_Mouse_Position();

};


#endif //WAVEFORMS_APP_H
