//
// Created by jer on 19-1-2017.
//

#include "wall.hpp"

wall::wall(std::string s, sf::Vector2f newPosition, sf::Vector2f size, sf::Color color):
color ( color ),
size ( size ),
box ( sf::RectangleShape(size))
{
    box.setFillColor(color);
    name = s;
    position = newPosition;
}

void wall::update(sf::Vector2f delta){
    return;
}


void wall::draw(sf::RenderWindow & window){
//    sf::RectangleShape rectangle(size);
//    rectangle.setFillColor(color);
//    rectangle.setPosition(position);
//
//    window.draw(rectangle);

    box.setPosition(position);
    window.draw(box);

}

sf::FloatRect & wall::getFloatrect(){
    hitbox = box.getGlobalBounds();
    return hitbox;
}