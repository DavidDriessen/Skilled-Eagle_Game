//
// Created by MuscioCraft on 30-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_FINISH_HPP
#define SKILLED_EAGLE_GAME_FINISH_HPP

#include <SFML/Graphics.hpp>
#include "ScreenObject.h"
class Finish : public ScreenObject {

private:
    sf::Texture texture_block;
    sf::RectangleShape shape;
    sf::String file;
public:
    Finish(sf::Texture t, sf::Vector2f vec, sf::Vector2f size = sf::Vector2f(128, 32));
    ~Finish();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow & window);
    sf::FloatRect getFloatRect();
};



#endif //SKILLED_EAGLE_GAME_FINISH_HPP
