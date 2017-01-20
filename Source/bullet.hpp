//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_BULLET_HPP
#define SKILLED_EAGLE_GAME_BULLET_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"
#include "wall.hpp"

class bullet : public screen_object{
public:
    std::string name;
    sf::Vector2f position;
    sf::RectangleShape bullet_box;
    sf::FloatRect hitbox;
    sf::Vector2f size;
    sf::Vector2f direction;
    sf::Color color;
    int damage;
    bool hasCollision = false;


    bullet(std::string s, sf::Vector2f newPosition,  int damage , sf::Vector2f direction, sf::Color color = sf::Color::Red, sf::Vector2f size = sf::Vector2f(5.0,3.0));

    void draw(sf::RenderWindow & window);
    void update(sf::Vector2f delta);

    bool collision(screen_object & obj);

    void set_hasCollision();
    sf::FloatRect & getFloatrect();


};


#endif //SKILLED_EAGLE_GAME_BULLET_HPP
