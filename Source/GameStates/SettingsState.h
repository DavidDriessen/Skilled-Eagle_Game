//
// Created by robbie on 17-1-2017.
//

#ifndef WAVEFORMS_SETTINGSSTATE_H
#define WAVEFORMS_SETTINGSSTATE_H

#include <functional>
#include "IState.h"
#include "../Menu.hpp"

class Game;

class SettingsState : public IState, public Menu {
private:
    Game *game;
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> resA = {"1080", "720"};
    int res = 0, volume = 50, direction = 1;
    std::vector<sf::String> btn = {
            "Resolutions",
            "Volume",
            "Controlles",
            "Apply"};
public:
    SettingsState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

};


#endif //WAVEFORMS_SETTINGSSTATE_H
