//
// Created by robbie on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_BLOCK_H
#define SKILLED_EAGLE_GAME_BLOCK_H

#include <SFML/Graphics.hpp>
#include "ScreenObject.h"
class Block : public ScreenObject {
private:
    sf::Texture texture_block;
    sf::RectangleShape shape;
    sf::String file;
public:
    Block(sf::Texture t, sf::Vector2f vec, sf::Vector2f size = sf::Vector2f(32, 32));
    ~Block();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow & window);
    sf::FloatRect getFloatRect();
};


#endif //SKILLED_EAGLE_GAME_BLOCK_H
