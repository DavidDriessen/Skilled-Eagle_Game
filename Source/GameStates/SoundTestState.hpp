//
// Created by endargon on 1/23/17.
//

#ifndef SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP
#define SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP

#include "../Audio/FmodApi.hpp"
#include <SFML/Graphics.hpp>
#include "IState.h"
#include "../Audio/SoundManager.h"
#include "../Audio/BeatDetector.h"

class Game;

class SoundTestState : public IState {
private:
    Game *game;
    SoundManager *soundManager = new SoundManager();
    BeatDetector *beatDec;
    sf::RectangleShape shape;
    sf::RectangleShape* shapes[2048];

    bool showBeat = false;
public:
    SoundTestState(Game *pGame);
    ~SoundTestState();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow &window);


};


#endif //SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP
