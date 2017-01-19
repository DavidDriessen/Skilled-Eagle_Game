//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>


class Character {
    private:
        sf::Vector2f position;
        float gravity;
        float startHeight;
        float jumpHeigth;
        float speed;
        bool jumping = false;
        bool descending = false;

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight);
        void move(sf::Vector2f direction);
        void jump();
        void draw(sf::RenderWindow &window);
        void update(const sf::Time delta);
        void input(sf::Event &event);

};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
