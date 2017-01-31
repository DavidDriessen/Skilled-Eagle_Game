//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>
#include "ScreenObjects/items/Weapon.hpp"
#include "ScreenObjects/items/RangedWeapon.hpp"
#include "ScreenObjects/items/MeleeWeapon.hpp"

class Level;

class PowerUp;

class Character {
private:
    int hp = 100;
    PowerUp *powerUp = NULL;
    sf::Vector2f position;
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect colRect;
    int sprite_state = 0;
    float sprite_scale;
    int sprite_height = 260;
    int sprite_width = 172;
    float gravity;
    float jumpHeight;
    float jumpTime;
    float speed;
    bool jumping = false;
    bool descending = true;
    bool moving = false;
    bool directionRight = true;
    Level *level;

    void move(sf::Vector2f direction);

    void jump(const sf::Time delta);

    void animation();

    Weapon *weapon = nullptr;
public:
    Character(sf::Texture t, sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width,
              int sprite_height, float sprite_scale, Level &level);
    ~Character();
    sf::Sprite &get_sprite();

    Weapon *get_weapon();

    bool get_is_right_direction() const;

    void assign_weapon(Weapon *new_weapon);

    void grab_for_weapon(std::vector<Weapon *> &weapons);

    void attack();

    void draw(sf::RenderWindow &window);

    void update(const sf::Time delta);

    void input(sf::Event &event);

    void left();

    void right();

    void up();

    void stop();

    void setSpeed(float s);

    float getSpeed();

    ScreenObject *collisionWithLevel(Level &level);

    sf::FloatRect get_rect();

    void set_powerUp(PowerUp *p);

    PowerUp *get_powerUp();

    void set_position(sf::Vector2f pos);

    sf::Vector2f getPosition();

    bool take_damage(int damage);
};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
