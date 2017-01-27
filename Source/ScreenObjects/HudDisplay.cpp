//
// Created by jer on 27-1-2017.
//

#include "HudDisplay.hpp"


HudDisplay::HudDisplay()
{

}

void HudDisplay::input(sf::Event &event) {

}

void HudDisplay::update(const sf::Time delta) {

}

void HudDisplay::draw(sf::RenderWindow &window) {
    Health->add_position(position + healthBarOffset);
    Stamina->add_position(position + staminaBarOffset);
    Health->draw(window);
    Stamina->draw(window);
}



sf::FloatRect HudDisplay::getFloatRect() {

}

void HudDisplay::set_hud_player(Character * newPlayer) {
    player = newPlayer;
    Health = player->get_HealthBar();
    Stamina = player->get_StaminaBar();

}

void HudDisplay::set_Position(sf::Vector2f pos) {
    position = pos;
}




