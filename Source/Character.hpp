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
        float sprite_scale = 0.3;
        int sprite_height = 260;
        int sprite_width = 160;
        float gravity;
        float startHeight;
        float jumpHeigth;
        float speed;
        bool jumping = false;
        bool descending = false;
        void move(sf::Vector2f direction);
        void jump();

    public:
        Character(sf::Vector2f startPos, float gravity, float speed, float jumpHeight);
        void draw(sf::RenderWindow &window);
        void update(const sf::Time delta);
        void input(sf::Event &event);

};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
