//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w): menuState(), settingsState(), playState(), window(w) {
    iState = &playState;
}

Game::~Game() {

}

void Game::update() {
    iState->update();
}

void Game::draw() {
   iState->draw();
}