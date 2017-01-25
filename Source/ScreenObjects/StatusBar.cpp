//
// Created by jer on 24-1-2017.
//

#include "StatusBar.hpp"

StatusBar::StatusBar(std::string name, sf::Vector2f position, sf::Color color) :
        name( name ),
        position ( position ),
        color ( color )
{
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Cyan);
    shape.setOutlineThickness(1.f);
    shape.setSize(sf::Vector2f(50, 5));
}

void StatusBar::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void StatusBar::input(sf::Event &event) {
}

void StatusBar::update(const sf::Time delta) {
}

float StatusBar::Calculate_percentage_of(float  newCurrentstatus ,float maximumOfStatus){
    return (newCurrentstatus / maximumOfStatus) * 100;

}


void StatusBar::set_StatusBar(float newCurrentStatus, sf::Vector2f position){
    currentStatus = newCurrentStatus;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(currentStatus/2.9, bar_height));
}

StatusBar::~StatusBar() {

}

void StatusBar::set_StatusBar_hudSize() {
    bar_height = 20;
}
