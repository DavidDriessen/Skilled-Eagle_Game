//
// Created by jer on 19-1-2017.
//

#include "Bullet.hpp"

Bullet::Bullet(std::string s, sf::Vector2f newPosition, int damage, sf::Vector2f direction, float fly_range, sf::Color color,
               sf::Vector2f size) :
        color(color),
        size(size),
        bullet_box(sf::RectangleShape(size)),
        damage(damage),
        direction(direction),
        fly_distance(fly_range){
    bullet_box.setFillColor(color);
    name = s;
    position = newPosition;;
}

void Bullet::draw(sf::RenderWindow &window) {
    bullet_box.setPosition(position);
    window.draw(bullet_box);
}

void Bullet::update(sf::Time delta) {
    position += direction;
    fly_distance-= fabs(direction.x);
}

void Bullet::set_hasCollision() {
    hasCollision = true;
}

bool Bullet::collision(ScreenObject &obj) {
    return false;
//    return bullet_box.getGlobalBounds().intersects(obj.getFloatrect());
}

sf::FloatRect Bullet::getFloatRect() {
    hitbox = bullet_box.getGlobalBounds();
    return hitbox;
}