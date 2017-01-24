//
// Created by david on 1/24/2017.
//

#include "PowerUp.hpp"

PowerUp::PowerUp(sf::Vector2f vec) : rect(vec, sf::Vector2f(32, 32)) {
    img.loadFromFile("assets/images/Nuken.png");
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setPosition(rect.left, rect.top);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32 * 5, 32 * 5));
    sprite.setScale(0.2, 0.2);
}

void PowerUp::update(const sf::Time delta, Character &player) {
    if (available && rect.intersects(player.get_rect())) {
        player.set_powerUp(this);
        available = false;
    }
}

void PowerUp::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

