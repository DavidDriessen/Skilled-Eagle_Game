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
#include "GameStates/LevelSelectState.hpp"
#include "GameStates/GameOverState.hpp"
#include "GameStates/HighScoreState.hpp"
#include "GameStates/MusicSelectState.hpp"
#include "GameStates/SoonState.hpp"
#include "Audio/SoundManager.h"
#include "Utility/ResourceHolder.hpp"
#include "Utility/ResourceIdentifiers.hpp"
#include "Utility/DebugOverlay.hpp"
#include <SFML/Graphics.hpp>

class Game {
private:
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    sf::RenderWindow &window;
    sf::View view;
    IState *iState;
private:
    SoundManager *soundManager = nullptr;
    SplashState *splashState = nullptr;
    SoundTestState *soundTestState = nullptr;
    LevelSelectState *levelSelectState = nullptr;
    MusicSelectState *musicSelectState = nullptr;
    MenuState *menuState = nullptr;
    PlayState *playState = nullptr;
    SoonState *soonState = nullptr;
    HighScoreState *highScoreState = nullptr;
    SettingsState *settingsState = nullptr;
    ControlsState *controlsState = nullptr;
    PauseState *pauseState = nullptr;
    GameOverState *gameOverState = nullptr;
    DebugOverlay *overlay;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
    TextureHolder textures;
    FontHolder fonts;

    void loadResources();

public:
    Game(sf::RenderWindow &w);

    ~Game();

    void draw();

    void update(const sf::Time delta);

    void input();

    void go_to_play();

    void go_to_level_select();

    void go_to_menu(bool play = false);

    void go_to_options();

    void go_to_controls();

    void go_to_highscore();

    void go_to_pause(bool play = false);

    void go_to_test();

    void go_to_soon();

    void go_to_game_over(bool dead);

    void go_to_music_select();

    void quit();

    void set_level(std::string string);

    sf::View *getView();

    void setView(sf::View &view);

    sf::RenderWindow *get_window();

    sf::Vector2i get_Mouse_Position();

    void update_debug(sf::Time dt);

    ControlsState *getControls();

    const TextureHolder &getTextures() const;

    const FontHolder &getFonts() const;

    DebugOverlay *getOverlay() const;

    SoundManager *getSoundManager() const;

    HighScoreState *getHighScore() const;

    PlayState *getPlayState() const;

};


#endif //WAVEFORMS_APP_H
