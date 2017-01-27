//
// Created by david on 1/24/2017.
//

#ifndef SKILLED_EAGLE_GAME_POWERUP_HPP
#define SKILLED_EAGLE_GAME_POWERUP_HPP

#include <SFML/Graphics.hpp>
class Character;
class PowerUp {
    bool available = true;
    sf::Image img;
    sf::Image img2;
    sf::Texture texture2;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect rect;
    int function = rand() % 3;
    bool activated = false;

public:
    PowerUp(sf::Texture active, sf::Texture used, sf::Vector2<float> vector2);
    void update(const sf::Time delta, Character &player);
    void draw(sf::RenderWindow & window);
    int getFunction();

    void setActive(bool status);
    bool getActive();

};


#endif //SKILLED_EAGLE_GAME_POWERUP_HPP
