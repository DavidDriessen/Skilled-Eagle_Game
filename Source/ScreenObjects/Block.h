//
// Created by robbie on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_BLOCK_H
#define SKILLED_EAGLE_GAME_BLOCK_H

#include <SFML/Graphics.hpp>
#include "ScreenObject.h"
class Block : public ScreenObject {
private:
    sf::RectangleShape shape;
    sf::FloatRect rect;
public:
    Block(sf::Vector2f vec);
    ~Block();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow & window);
    sf::Rect<float> getRect();
};


#endif //SKILLED_EAGLE_GAME_BLOCK_H
