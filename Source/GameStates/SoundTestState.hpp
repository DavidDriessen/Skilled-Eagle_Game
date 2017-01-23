//
// Created by endargon on 1/23/17.
//

#ifndef SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP
#define SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP

#include "../Audio/FmodApi.hpp"
#include <SFML/Graphics.hpp>
#include "IState.h"

class Game;

class SoundTestState : public IState {
private:
    Game *game;
    FmodApi *fmod;
public:
    SoundTestState(Game *pGame, FmodApi *fmod);
    ~SoundTestState();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow &window);


};


#endif //SKILLED_EAGLE_GAME_SOUNDTESTSTATE_HPP
