//
// Created by endargon on 2/1/17.
//

#include <stdlib.h>
#include "GameOverState.hpp"
#include "../Game.h"

GameOverState::GameOverState(Game *pGame, bool dead): game(pGame), dead(dead) {
    status.setFont(pGame->getFonts().get(Fonts::Default));
    score.setFont(pGame->getFonts().get(Fonts::Default));
    textColor = sf::Color(255, 0, 0, 0);
    status.setFillColor(textColor);
    status.setCharacterSize(200);
    if(dead) {
        status.setString("You died");
    } else {
        status.setString("Good jobu");
    }
    score.setString("HIGHSCORE: " + std::to_string(game->getHighScore()->get_current_score()));
    score.setFillColor(sf::Color::Yellow);
    score.setCharacterSize(150);
    sf::Vector2i mid = sf::Vector2i(game->get_window()->getSize().x / 2, game->get_window()->getSize().y / 2);
    sf::Vector2f offset1(mid.x - status.getGlobalBounds().width/2, 20);
    sf::Vector2f offset2(mid.x - score.getGlobalBounds().width/2, 300);
    status.setPosition(offset1);
    score.setPosition(offset2);
}

void GameOverState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        game->go_to_level_select();
    }
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_menu(true);
    }
}

void GameOverState::update(const sf::Time delta) {
    if(blink.getElapsedTime() >= sf::milliseconds(1)) {
        if(textColor.a <= 0 && direction == 0) {
            direction = 1;
        } else if(textColor.a >= 255 && direction == 1 ) {
            direction = 0;
        }
        if(direction) {
            textColor.a+= 5;
        } else {
            textColor.a-= 5;
        }
        if(!dead) {
            textColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
        }
        status.setFillColor(textColor);
        blink.restart();
    }
}

void GameOverState::draw(sf::RenderWindow &window) {
    window.draw(status);
    window.draw(score);
}