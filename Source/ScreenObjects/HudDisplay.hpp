//
// Created by jer on 27-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_HUDDISPLAY_HPP
#define SKILLED_EAGLE_GAME_HUDDISPLAY_HPP

#include "ScreenObject.h"
#include "../Character.hpp"
#include "StatusBar.hpp"

class HudDisplay : public ScreenObject{
private:
    Character * player = nullptr;
    StatusBar * Health = nullptr;
    StatusBar * Stamina= nullptr;
    sf::Vector2f position;

    sf::Vector2f healthBarOffset = sf::Vector2f(0,-40.0);
    sf::Vector2f staminaBarOffset = sf::Vector2f(0,-10.0);

public:
    HudDisplay();
     void input(sf::Event &event);
     void update(const sf::Time delta);
     void draw(sf::RenderWindow &window);
     sf::FloatRect getFloatRect();
    void set_Position(sf::Vector2f pos);
    void set_hud_player(Character * newPlayer);

};


#endif //SKILLED_EAGLE_GAME_HUDDISPLAY_HPP
