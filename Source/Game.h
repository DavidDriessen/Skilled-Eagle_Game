//
// Created by robbie on 17-1-2017.
//

#ifndef WAVEFORMS_APP_H
#define WAVEFORMS_APP_H

#include "GameStates/IState.h"
#include "GameStates/MenuState.h"
#include "GameStates/SettingsState.h"
#include "GameStates/PlayState.h"
#include "GameStates/SplashState.hpp"
#include "Audio/FmodApi.hpp"
#include "GameStates/SoundTestState.hpp"
#include "GameStates/ControlsState.hpp"
#include "GameStates/PauseState.hpp"
#include "Audio/SoundManager.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

    sf::RenderWindow &window;
    IState * iState;
    MenuState* menuState;
    SettingsState* settingsState;
    ControlsState* controlsState;
    PauseState* pauseState;
    PlayState* playState;
    SplashState* splashState;
    SoundTestState* soundTestState;
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

    void go_to_controls();

    void go_to_pause();

    void go_to_test();

    void quite();

    sf::RenderWindow * get_window() {
        return &window;
    }

    sf::Vector2i get_Mouse_Position();

    void update_debug(sf::Time dt);

    ControlsState* getControls();
};


#endif //WAVEFORMS_APP_H
