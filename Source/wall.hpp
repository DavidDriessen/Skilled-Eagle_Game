//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_WALL_HPP
#define SKILLED_EAGLE_GAME_WALL_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"
class wall : public screen_object{
public:
    std::string name;
    sf::Vector2f position;
    sf::RectangleShape box;
    sf::Vector2f size;
    sf::FloatRect hitbox;
    sf::Color color;

    wall(std::string s, sf::Vector2f newPosition, sf::Vector2f size, sf::Color color = sf::Color::Blue );
    void update(sf::Vector2f delta);
    void draw(sf::RenderWindow & window);
    sf::FloatRect & getFloatrect();

};


#endif //SKILLED_EAGLE_GAME_WALL_HPP
