//
// Created by jer on 24-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_STATUSBAR_HPP
#define SKILLED_EAGLE_GAME_STATUSBAR_HPP


#include <SFML/Graphics.hpp>
#include "ScreenObject.h"

class StatusBar : public ScreenObject {
public:



    StatusBar(std::string name, sf::Vector2f location, sf::Color color);
    ~StatusBar();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow & window);
    void set_StatusBar(int newCurrentStatus, sf::Vector2f position);

private:
    std::string name;
    sf::Vector2f position;
    sf::Color color;
    sf::RectangleShape shape;
    int currentStatus;
};


#endif //SKILLED_EAGLE_GAME_STATUSBAR_HPP
