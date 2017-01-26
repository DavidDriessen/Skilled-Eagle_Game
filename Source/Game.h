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
#include "GameStates/SoundTestState.hpp"
#include "GameStates/ControlsState.hpp"
#include "GameStates/PauseState.hpp"
#include "Audio/SoundManager.h"
#include "GameStates/SoonState.hpp"
#include <SFML/Graphics.hpp>

class Game {
private:
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

    sf::RenderWindow &window;
    IState * iState;
    SoundManager* soundManager = nullptr;
    SplashState* splashState = nullptr;
    SoundTestState* soundTestState = nullptr;
    MenuState* menuState = nullptr;
    PlayState* playState = nullptr;
    SoonState* soonState = nullptr;
    SettingsState* settingsState = nullptr;
    ControlsState* controlsState = nullptr;
    PauseState* pauseState = nullptr;
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

    void go_to_soon();

    void quit();

    sf::RenderWindow * get_window() {
        return &window;
    }

    sf::Vector2i get_Mouse_Position();

    void update_debug(sf::Time dt);

    ControlsState* getControls();
};


#endif //WAVEFORMS_APP_H
