//
// Created by jer on 27-1-2017.
//

#include "HudDisplay.hpp"


HudDisplay::HudDisplay()
{

}

void HudDisplay::input(sf::Event &event) {

}

void HudDisplay::update(const sf::Time delta){
    Health->update(delta);
    Stamina->update(delta);
}

void HudDisplay::draw(sf::RenderWindow &window) {
    Health->add_position(position + healthBarOffset);
    Stamina->add_position(position + staminaBarOffset);
    powerup->setPosition(position + powerupOffset);
    Health->draw(window);
    Stamina->draw(window);
    if(player->get_powerUp()){
        window.draw(*powerup);
    }

}



sf::FloatRect HudDisplay::getFloatRect() {

}

void HudDisplay::set_hud_player(Character * newPlayer) {
    player = newPlayer;
    Health = player->get_HealthBar();
    Stamina = player->get_StaminaBar();
    powerup->setSize(sf::Vector2f(64, 64));
    powerup->setFillColor(sf::Color::Red);
}

void HudDisplay::set_Position(sf::Vector2f pos) {
    position = pos;
}




