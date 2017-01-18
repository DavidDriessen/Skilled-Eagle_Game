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
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

    IState * iState;
    MenuState* menuState;
    SettingsState* settingsState;
    PlayState* playState;
    sf::RenderWindow &window;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
public:
    Game(sf::RenderWindow &w);

    ~Game();
    void draw();
    void update(const sf::Time delta);
    void input();

    void go_to_play();
    void go_to_menu();

    void go_to_options();

    void quite();

    sf::Vector2i get_Mouse_Position();

<<<<<<< HEAD
=======

    void update_debug(sf::Time dt);
>>>>>>> GAME-47 fps based update and input loop
};


#endif //WAVEFORMS_APP_H
