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
    SoundManager *soundManager = nullptr;
    BeatDetector *beatDec = nullptr;
    sf::RectangleShape shape;
    sf::RectangleShape *shapes[2048];
    sf::Font font;
    sf::Text cyka;
    bool showBeat = false;
public:
    SoundTestState(Game *pGame, SoundManager *pManager);

    ~SoundTestState();

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);


};


#endif //SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP
