//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w): window(w), menuState(new MenuState(this)), playState(new PlayState(this)), settingsState(new SettingsState(this)), splashState(new SplashState(this)) {
    iState = playState;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(window.isOpen()) {
        input();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            input();
            update(TimePerFrame);

        }
        update_debug(elapsedTime);
        draw();
    }
}

Game::~Game() {
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
    iState = settingsState;
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
        if (mStatisticsUpdateTime >= sf::seconds(1.0f))
        {
            mStatisticsUpdateTime -= sf::seconds(1.0f);
            mStatisticsNumFrames = 0;
        }
}