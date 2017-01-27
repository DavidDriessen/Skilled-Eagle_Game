//
// Created by robbie on 17-1-2017.
//

#ifndef GAME_H
#define GAME_H

#include "IState.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level.h"
#include "../ScreenObjects/ScreenObject.h"
#include "../Character.hpp"
#include "../Audio/BeatListener.hpp"
#include "../Audio/BeatDetector.h"

class Game;

class PlayState : public IState, public BeatListener {
private:
    Game *game;
    Level level;
    SoundManager *soundManager = nullptr;
    BeatDetector *beatDec = nullptr;
public:
    PlayState(Game *pGame, SoundManager* soundManager);
    ~PlayState() {
        delete beatDec;
    }
    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);


    void onBeat();

    void onPeak(float peak);
};


#endif //WAVEFORMS_GAME_H
