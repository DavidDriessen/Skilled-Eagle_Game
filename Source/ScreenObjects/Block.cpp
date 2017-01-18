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
void Block::update(float delta) {

}

void Block::draw(sf::RenderWindow &window) {
    std::cout << "SHAPE DRAWING \n";
    window.draw(shape);
}