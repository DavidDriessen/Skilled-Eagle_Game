//
// Created by Mbeun on 18-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_MOVEMENT_H
#define SKILLED_EAGLE_GAME_MOVEMENT_H

#include <SFML/Graphics.hpp>
#include "ScreenObjects/StatusBar.hpp"
#include "ScreenObjects/items/Weapon.hpp"
#include "ScreenObjects/items/RangedWeapon.hpp"
#include "ScreenObjects/items/MeleeWeapon.hpp"
#include "ScreenObjects/StatusBar.hpp"

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
    bool isEnemy = false;
    Level *level;

    void move(sf::Vector2f direction);

    void jump(const sf::Time delta);

    void animation();

    Weapon *weapon = nullptr;

    int playerHealthPoints;
    int playerStaminaPoints;

    int characterHealthPoints;
    int characterStaminaPoints;
    int maximumStamina = 100;
    int maximumHealth = 100;
    sf::Vector2f hudLocation;
    sf::Vector2f healthBarOffset = sf::Vector2f(0, -30.0);
    sf::Vector2f staminaBarOffset = sf::Vector2f(0, -20.0);

    StatusBar *healthBar;
    StatusBar *staminaBar;

    sf::Clock healthClock;
    sf::Time healthRegenCooldown = sf::milliseconds(5000);
    sf::Time healthTimer = sf::Time::Zero;

    sf::Clock staminaClock;
    sf::Time staminaRegenCooldown = sf::milliseconds(100);
    sf::Time staminaTimer = sf::Time::Zero;
public:
    Character(sf::Texture t, sf::Vector2f startPos, float gravity, float speed, float jumpHeight, int sprite_width,
              int sprite_height, float sprite_scale, Level &level, bool isEnemy);
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

    void update_status_bars();

    StatusBar *get_HealthBar();

    StatusBar *get_StaminaBar();
};


#endif //SKILLED_EAGLE_GAME_MOVEMENT_H
