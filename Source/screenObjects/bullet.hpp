//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_BULLET_HPP
#define SKILLED_EAGLE_GAME_BULLET_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScreenObject.h"

class bullet : public ScreenObject {
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


    bullet(std::string s, sf::Vector2f newPosition, int damage, sf::Vector2f direction,
           sf::Color color = sf::Color::Red, sf::Vector2f size = sf::Vector2f(5.0, 3.0));

    void input(sf::Event &event){};

    void draw(sf::RenderWindow &window);

    void update(sf::Time delta);

    bool collision(ScreenObject &obj);

    void set_hasCollision();

    sf::FloatRect &getFloatrect();


};


#endif //SKILLED_EAGLE_GAME_BULLET_HPP
