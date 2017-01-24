//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>
#include "Level.h"

class PowerUp;

class Character {
    private:
        PowerUp* powerUp = NULL;
        sf::Vector2f position;
        sf::Image img;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::FloatRect colRect;
        int sprite_state = 0;
        float sprite_scale;
        int sprite_height = 260;
        int sprite_width = 172;
        float gravity;
        float jumpHeight;
        float jumpTime;
        float speed;
        bool jumping = false;
        bool descending = true;
        bool moving = false;
        bool directionRight = true;
        Level *level;
        void move(sf::Vector2f direction);
        void jump(const sf::Time delta);
        void animation();

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale, Level &level);
        void draw(sf::RenderWindow &window);
        void update(const sf::Time delta);
        void input(sf::Event &event);

        void left();
        void right();
        void up();
        void stop();
        ScreenObject* collisionWithLevel(Level &level);

        sf::FloatRect get_rect();
        void set_powerUp(PowerUp* p);
};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
