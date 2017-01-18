//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>


class Character {
    private:
        sf::Vector2f position;
<<<<<<< HEAD
        sf::Image img;
        sf::Texture texture;
        sf::Sprite sprite;
        int sprite_state = 0;
        float sprite_scale = 0.3;
        int sprite_height = 260;
        int sprite_width = 160;
=======
>>>>>>> Character class with jump and moving capabilities (main.cpp contains test values and code)
        float gravity;
        float startHeight;
        float jumpHeigth;
        float speed;
        bool jumping = false;
        bool descending = false;
<<<<<<< HEAD
        void move(sf::Vector2f direction);
        void jump();

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight);
        void draw(sf::RenderWindow &window);
        void update(const sf::Time delta);
        void input(sf::Event &event);

=======

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight);
        void move(sf::Vector2f direction);
        void jump();
        void update(sf::RenderWindow &w);
        void setJumping(bool status);
        float getSpeed();
>>>>>>> Character class with jump and moving capabilities (main.cpp contains test values and code)
};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
