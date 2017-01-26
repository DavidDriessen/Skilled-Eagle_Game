//
// Created by robbie on 18-1-2017.
//

#include "Block.h"
#include <iostream>

Block::Block(sf::String file, sf::Vector2f vec, sf::Vector2f size){
    texture_block.loadFromFile("assets/images/" + file);
    shape.setPosition(vec);
    shape.setTexture(&texture_block);
    shape.setSize(size);

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

sf::FloatRect Block::getFloatRect() {
    return shape.getGlobalBounds();
}
