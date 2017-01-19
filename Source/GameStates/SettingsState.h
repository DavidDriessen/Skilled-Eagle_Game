//
// Created by robbie on 17-1-2017.
//

#ifndef WAVEFORMS_SETTINGSSTATE_H
#define WAVEFORMS_SETTINGSSTATE_H
#include "IState.h"

class Game;

class SettingsState : public IState {
private:
    Game *game;
public:
    SettingsState();

    SettingsState(Game *pGame);

    void input(sf::Event &event);
    void update(float delta);
    void draw(sf::RenderWindow &window);

};


#endif //WAVEFORMS_SETTINGSSTATE_H
