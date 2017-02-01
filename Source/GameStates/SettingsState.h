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
    std::function<void(void)> back = [](){};
    std::vector<std::function<void(void)>> actions;
    std::vector<sf::String> resA = {"1080p", "720p", "600p"};
    std::vector<sf::Vector2u> resV = {{1920, 1080},
                                      {1280, 720},
                                      {800, 600}};
    int res = 0, oldres = 0, direction = 1;
    float volume = 100, oldVolume = 100;
    std::vector<sf::String> btn = {
            "Resolutions",
            "Volume",
            "Controls",
            "Apply"};
public:
    SettingsState(Game *pGame);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void setBack(const std::function<void()> &func);

    void save();
};


#endif //WAVEFORMS_SETTINGSSTATE_H
