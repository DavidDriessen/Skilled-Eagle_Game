//
// Created by jer on 19-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_SCREEN_OBJECT_HPP
#define SKILLED_EAGLE_GAME_SCREEN_OBJECT_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

class screen_object {
private:


public:



    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void update(sf::Vector2f delta) = 0;

    virtual sf::FloatRect &getFloatrect() =0;


};



#endif //SKILLED_EAGLE_GAME_SCREEN_OBJECT_HPP
