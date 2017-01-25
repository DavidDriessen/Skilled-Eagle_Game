//
// Created by robbie on 18-1-2017.
//

#include "Block.h"
#include <iostream>

Block::Block(sf::Vector2f vec) : rect(vec, sf::Vector2f(32, 32)) {
    shape.setPosition(vec);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);
    shape.setSize(sf::Vector2f(32, 32));
}

Block::~Block() {

}

void Block::input(sf::Event &event) {


}
void Block::update(const sf::Time delta) {

}

void Block::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::Rect<float> Block::getRect() {
    return sf::Rect<float>();
}
