//
// Created by MuscioCraft on 30-1-2017.
//

#include "Finish.hpp"
#include <iostream>

Finish::Finish(sf::Texture t, sf::Vector2f vec, sf::Vector2f size){
    texture_block = sf::Texture(t);
    shape.setPosition(vec);
    shape.setTexture(&texture_block);
    shape.setSize(size);

}

Finish::~Finish() {

}

void Finish::input(sf::Event &event) {


}
void Finish::update(const sf::Time delta) {

}

void Finish::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::FloatRect Finish::getFloatRect() {
    return shape.getGlobalBounds();
}
