//
// Created by jer on 19-1-2017.
//

#include "speler.hpp"

speler::speler(std::string s, sf::Vector2f newPosition,  sf::Vector2f size, sf::Color color):
        color ( color ),
        size ( size ),
        player_box ( sf::RectangleShape(size))

{
    player_box.setFillColor(color);
    name = s;
    position = newPosition;

}

void speler::update(sf::Vector2f delta){
    position += delta;
    wapen->update_weapon_position(position);
    wapen->update();
    return;
}

void speler::assign_weapon(weapon * obj){
    wapen = obj;

}

void speler::move_to_position(sf::Vector2f newPosition){
    position = newPosition;
}

void speler::draw(sf::RenderWindow & window){
    player_box.setPosition(position);
    wapen->draw(window);
    window.draw(player_box);
}



sf::FloatRect & speler::getFloatrect(){
    hitbox = player_box.getGlobalBounds();
    return hitbox;
}