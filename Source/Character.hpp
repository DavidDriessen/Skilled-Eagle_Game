//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>


class Character {
    private:
        sf::Vector2f position;
        sf::Image img;
        sf::Texture texture;
        sf::Sprite sprite;
        int sprite_state = 0;
        float sprite_scale;
        int sprite_height = 260;
        int sprite_width = 172;
        float gravity;
        float groundHeight;
        float jumpHeigth;
        float speed;
        bool jumping = false;
        bool descending = false;
        bool moving = false;
        bool directionRight = true;
        void move(sf::Vector2f direction);
        void jump(const sf::Time delta);
        void animation();

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale);
        void draw(sf::RenderWindow &window);
        void update(const sf::Time delta);
        void input(sf::Event &event);

        void left();
        void right();
        void up();
        void stop();

};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
