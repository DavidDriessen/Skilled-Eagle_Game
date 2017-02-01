//
// Created by Mbeun on 18-1-2017.
//

#include <iostream>
#include "Character.hpp"
#include "Level.h"
#include "ScreenObjects/PowerUp.hpp"

Character::Character(sf::Texture text, sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width, int sprite_height, float sprite_scale, Level &level, bool isEnemy) {
    this->position = startPos;
    this->gravity = gravity;
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->sprite_scale = sprite_scale;
    this->level = &level;
    img = text.copyToImage();
    img.createMaskFromColor(sf::Color::Magenta);
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setScale(this->sprite_scale, this->sprite_scale + 0.03f);
    colRect = sprite.getGlobalBounds();
    sprite_state = 0;

    healthBar =  new StatusBar("health bar", position + healthBarOffset, sf::Color(34,139,34));
    staminaBar = new StatusBar("stamina bar", position + staminaBarOffset, sf::Color::Blue);

    this->isEnemy = isEnemy;
    this->hudLocation = sf::Vector2f(10.0,50.0);

    if(!isEnemy){
        healthBar->set_StatusBar_hudSize();
        staminaBar->set_StatusBar_hudSize();
    }
    sprite.setPosition(position);
    sprite.setPosition(position);
}

Character::~Character() {
    if(weapon != nullptr) {
        weapon->set_is_owned(false);
        assign_weapon(nullptr);
    }
}

bool Character::get_is_right_direction() const {
    return directionRight;
}

Weapon* Character::get_weapon() {
    return weapon;
}

void Character::assign_weapon(Weapon *new_weapon) {
    if(weapon != nullptr) {
        weapon->update_weapon_position(sf::Vector2f(position.x, position.y), directionRight);
        weapon->set_is_owned(false);
    }
    weapon = new_weapon;
    if(weapon != nullptr) {
        weapon->set_is_owned(true);
    }
}

void Character::grab_for_weapon(std::vector<Weapon*> &weapons) {
    for(auto &gun : weapons) {
        if(gun->get_sprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) &&
           !gun->get_is_owned()) {
            assign_weapon(gun);
            break;
        }
    }
}

void Character::attack() {
    if(weapon != nullptr) {
        if(weapon->get_type() == "ranged") {
            int s = directionRight ? weapon->get_bullet_speed() : -weapon->get_bullet_speed();
            weapon->set_direction(sf::Vector2f(s, 0));
        }
        weapon->use();
        if(weapon->get_type() == "sword") {
            sf::FloatRect hit_rectangle;
            hit_rectangle.left = position.x;
            hit_rectangle.top = position.y;
            hit_rectangle.width = directionRight ? weapon->get_range() : -weapon->get_range();
            hit_rectangle.height = 32;
            int index = 0;
            // each enemy
            for(auto &obj : level->get_cyber_enforcers()) {
                // if enemy intersects with sword rect..
                if(obj->getFloatRect().intersects(hit_rectangle)) {
                    // if enemy has taken the damage and enemy is dead..
                    if(obj->get_character()->take_damage(weapon->get_damage())) {
                        // remove the enemy..
                        obj->get_character()->assign_weapon(nullptr);
                        level->get_cyber_enforcers().erase(level->get_cyber_enforcers().begin() + index);
                    }
                }
                index++;
            }
        }
    }
}

sf::Sprite &Character::get_sprite() {
    return sprite;
}

void Character::move(sf::Vector2f direction){
    position += direction;
}

void Character::jump(const sf::Time delta){
    //ascending
    if(jumping && !descending){
        float currentVelocity = -gravity * delta.asMilliseconds();
        colRect.top += currentVelocity * 1.5;
        jumpTime ++;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
            descending = true;
        }
        else{
            move(sf::Vector2f(0, currentVelocity));
            sprite_state ++;
            colRect = sprite.getGlobalBounds();
        }
    }
    //switch
    if(jumpTime > jumpHeight){
        descending = true;
    }
    //descending
    if(descending){
        float currentVelocity = gravity * delta.asMilliseconds();
        colRect.top += currentVelocity * 1.5;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
            descending = false;
            jumping = false;
            jumpTime = 0;
            sprite_state = 1;
        }
        else{
            move(sf::Vector2f(0, currentVelocity));
            sprite_state ++;
            colRect = sprite.getGlobalBounds();
        }
    }
    if(!descending && !jumping){
        colRect.top += gravity * delta.asMilliseconds() * 2;
        auto col = collisionWithLevel(*level);
        if(!col){
            descending = true;
        }
        else{
            position = {position.x, col->getFloatRect().top - sprite.getGlobalBounds().height};
            colRect = sprite.getGlobalBounds();
        }
    }
}

void Character::draw(sf::RenderWindow &window) {
    window.draw(sprite);

    if(isEnemy){
        healthBar->draw(window);
    }
}

void Character::update(const sf::Time delta) {
    if(directionRight && moving){
        float currentVelocity = speed * delta.asMilliseconds();
        colRect.left += currentVelocity * 2;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
        }
        else{
            move(sf::Vector2f(currentVelocity, 0));
            if(!jumping){
                sprite_state++;
            }
        }
    }
    if(!directionRight && moving){
        float currentVelocity = -speed * delta.asMilliseconds();
        colRect.left += currentVelocity * 2;
        if(collisionWithLevel(*level)){
            colRect = sprite.getGlobalBounds();
        }
        else{
            move(sf::Vector2f(currentVelocity , 0));
            if(!jumping){
                sprite_state++;
            }
        }
    }
    jump(delta);
    animation();
    sprite.setPosition(position);
    if(weapon != nullptr) {
        weapon->update_weapon_position(sprite.getPosition(), directionRight);
    }
    update_status_bars();
    if(get_powerUp()) {
        if (get_powerUp()->getDone()) {
            set_powerUp(nullptr);
        }
    }

}

void Character::update_status_bars(){

    staminaTimer = staminaClock.getElapsedTime();
    healthTimer =  healthClock.getElapsedTime();

    if (hp < 0 ){
        hp = 0;
    }
    if (characterStaminaPoints < 0 ){
        characterStaminaPoints = 0;
    }

    if(healthTimer > healthRegenCooldown && hp < maximumHealth){
        hp+=10;
        healthTimer = sf::Time::Zero;
        healthClock.restart();
    }

    if(staminaTimer > staminaRegenCooldown && characterStaminaPoints < maximumStamina){
        characterStaminaPoints+=10;
        staminaTimer = sf::Time::Zero;
        staminaClock.restart();
    }

    if(isEnemy) {
        healthBarOffset.y = -15;
        healthBar->set_StatusBar(healthBar->Calculate_percentage_of(hp, maximumHealth), position + healthBarOffset);
    }
    else{
        healthBar->set_StatusBar(healthBar->Calculate_percentage_of(hp, maximumHealth)*3, hudLocation +  healthBarOffset);
        staminaBar->set_StatusBar(staminaBar->Calculate_percentage_of(characterStaminaPoints, maximumStamina)*3, hudLocation + staminaBarOffset);
    }
}

void Character::input(sf::Event &event) {
}

void Character::animation(){
    if(!directionRight && !jumping){
        if(sprite_state % 4 == 0)
            sprite.setTextureRect(sf::IntRect(sprite_state / 4 * sprite_width, sprite_height, -sprite_width, sprite_height));
    }
    if(directionRight && !jumping){
        if(sprite_state % 4 == 0)
            sprite.setTextureRect(sf::IntRect(sprite_state / 4 * sprite_width - sprite_width, sprite_height, sprite_width, sprite_height));
    }
    if(jumping && directionRight){
        if(sprite_state % 7 == 0)
            sprite.setTextureRect(sf::IntRect(6 * sprite_width + (sprite_state / 7) * sprite_width, 0, sprite_width, sprite_height));
    }
    if(jumping && !directionRight){
        if(sprite_state % 7 == 0)
            sprite.setTextureRect(sf::IntRect(5 *sprite_width + (sprite_state / 7) * sprite_width, 0, -sprite_width, sprite_height));
    }
    if(!jumping && !moving && directionRight){
        sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    }
    if(!jumping && !moving && !directionRight){
        sprite.setTextureRect(sf::IntRect(sprite_width, 0, -sprite_width, sprite_height));
    }
    if(sprite_state == 24){
        sprite_state = 0;
    }
}

void Character::left() {
    moving = true;
    directionRight = false;
}

void Character::right() {
    moving = true;
    directionRight = true;
}

void Character::up() {
    jumping = true;
    sprite_state = 0;
}

void Character::stop() {
    moving = false;
}

ScreenObject* Character::collisionWithLevel(Level &level) {
    for(auto &object : level.get_blocks()){
        if(colRect.intersects(object->getFloatRect())){
            return object;
        }
    }
    for(auto &object : level.get_finish()){
        if(colRect.intersects(object->getFloatRect())){
            return object;
        }
    }
    return nullptr;
}

sf::FloatRect Character::get_rect() {
    return sprite.getGlobalBounds();
}

void Character::set_powerUp(PowerUp *p) {
    powerUp = p;
}

PowerUp *Character::get_powerUp() {
    return powerUp;
}

void Character::setSpeed(float s) {
    speed = s;
}

StatusBar * Character::get_HealthBar() {
        return healthBar;
}

StatusBar * Character::get_StaminaBar() {
        return staminaBar;
}



float Character::getSpeed() {
    return speed;
}

sf::Vector2f Character::getPosition() {
    return sprite.getPosition();
}

void Character::set_position(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(pos);
}

bool Character::take_damage(int damage) {
    hp -= damage;
    return hp <= 0;
}
