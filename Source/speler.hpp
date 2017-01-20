//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_SPELER_HPP
#define SKILLED_EAGLE_GAME_SPELER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"
#include "weapon.hpp"
class speler  : public screen_object{


public:
        std::string name;
        sf::Vector2f position;
        sf::RectangleShape player_box;
        sf::FloatRect hitbox;
        sf::Vector2f size;
        sf::Color color;
        weapon * wapen;


        speler(std::string s, sf::Vector2f newPosition,  sf::Vector2f size, sf::Color color = sf::Color::Blue);

        void move_to_position(sf::Vector2f newPosition);

        void assign_weapon(weapon * obj);

        void update(sf::Vector2f delta);

        void draw(sf::RenderWindow & window);


        sf::FloatRect & getFloatrect();






};


#endif //SKILLED_EAGLE_GAME_SPELER_HPP
