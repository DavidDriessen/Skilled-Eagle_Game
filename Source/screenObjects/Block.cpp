//
// Created by robbie on 18-1-2017.
//

#include "Block.h"

Block::Block(sf::Vector2f vec) {
    shape.setPosition(vec);
    shape.setFillColor(sf::Color::Black);
    shape.setSize(sf::Vector2f(32, 32));
}

Block::~Block() {

}

void Block::input(sf::Event &event) {


}
void Block::update(float delta) {

}

void Block::draw(sf::RenderWindow &window) {
    window.draw(shape);
}