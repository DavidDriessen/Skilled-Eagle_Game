//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w): window(w), menuState(new MenuState(this)), playState(new PlayState(this)), settingsState(new SettingsState(this)), splashState(new SplashState(this)), controllesState(new ControllesState(this)), soundTestState(new SoundTestState(this, &fmod)) {
    iState = playState;
Game::Game(sf::RenderWindow &w) : window(w), menuState(new MenuState(this)), playState(new PlayState(this)),
                                  settingsState(new SettingsState(this)), splashState(new SplashState(this)),
                                  controlsState(new ControlsState(this)), pauseState(new PauseState(this)) {
    iState = splashState;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        input();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            input();
            update(TimePerFrame);

        }
        update_debug(elapsedTime);
        draw();
    }
}

Game::~Game() {
    delete playState;
    delete menuState;
    delete settingsState;
}

void Game::input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        iState->input(event);
    }
}

void Game::update(const sf::Time delta) {
    iState->update(delta);
}

void Game::draw() {
    window.clear();
    iState->draw(window);
    window.display();
}

void Game::go_to_play() {
    iState = playState;
}

void Game::go_to_menu() {
    iState = menuState;
}

void Game::go_to_options() {
    if (iState == pauseState) {
        settingsState->setBack([&]() { go_to_pause(); });
    } else if (iState == menuState) {
        settingsState->setBack([&]() { go_to_menu(); });
    }
    iState = settingsState;
}
void Game::go_to_test() {
    iState = soundTestState;
}

void Game::go_to_controls() {
    iState = controlsState;
}

void Game::go_to_pause() {
    iState = pauseState;
}

void Game::quite() {
    window.close();
}

sf::Vector2i Game::get_Mouse_Position() {
    return sf::Mouse::getPosition(window);
}


void Game::update_debug(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        std::cout << "FPS: " + std::to_string(mStatisticsNumFrames) << "\n";
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

ControlsState *Game::getControls() {
    return controlsState;
}
