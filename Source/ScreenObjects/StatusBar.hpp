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
    void set_StatusBar(float newCurrentStatus, sf::Vector2f position);
    void set_StatusBar_hudSize();
    float Calculate_percentage_of(float  newCurrentstatus ,float maximumOfStatus);
private:

    std::string name;
    sf::Vector2f position;
    sf::Color color;
    sf::RectangleShape shape;
    float currentStatus;
    int  bar_height = 5;
};


#endif //SKILLED_EAGLE_GAME_STATUSBAR_HPP
