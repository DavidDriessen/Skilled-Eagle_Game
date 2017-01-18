//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w): window(w), menuState(new MenuState(this)), playState(new PlayState(this)), settingsState(new SettingsState(this)) {
    iState = playState;
    while(window.isOpen()) {
        input();
        update();
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

void Game::update() {
    float delta = 0;
    iState->update(delta);
}

void Game::draw() {
    window.clear(sf::Color::Blue);
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
