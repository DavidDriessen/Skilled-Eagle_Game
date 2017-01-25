//
// Created by jer on 19-1-2017.
//

#include "bullet.hpp"

bullet::bullet(std::string s, sf::Vector2f newPosition, int damage, sf::Vector2f direction, sf::Color color,
               sf::Vector2f size) :
        color(color),
        size(size),
        bullet_box(sf::RectangleShape(size)),
        damage(damage),
        direction(direction) {
    bullet_box.setFillColor(color);
    name = s;
    position = newPosition;;
}

void bullet::draw(sf::RenderWindow &window) {
    bullet_box.setPosition(position);
    window.draw(bullet_box);
}

void bullet::update(sf::Time delta) {
    position += direction;
}

void bullet::set_hasCollision() {
    hasCollision = true;
}

bool bullet::collision(ScreenObject &obj) {
    return false;
//    return bullet_box.getGlobalBounds().intersects(obj.getFloatrect());
}

sf::FloatRect bullet::getFloatRect() {
    hitbox = bullet_box.getGlobalBounds();
    return hitbox;
}