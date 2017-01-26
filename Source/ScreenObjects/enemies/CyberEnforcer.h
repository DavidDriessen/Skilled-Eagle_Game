//
// Created by robbie on 23-1-2017.
//

#ifndef SKILLED_EAGLE_GAME_CYBERENFORCER_H
#define SKILLED_EAGLE_GAME_CYBERENFORCER_H

#include "../../Character.hpp"
#include "../../ScreenObjects/ScreenObject.h"
class Level;
class Character;

class CyberEnforcer : public ScreenObject {
private:
    Level &level;
    Character* character;
    sf::Clock clock;
    bool direction;
public:
    CyberEnforcer(Level &lvl, sf::Vector2f vec);
    ~CyberEnforcer();
    Character* get_character();
    void input(sf::Event &event);
    void update(const sf::Time delta);
    void draw(sf::RenderWindow &window);

    sf::FloatRect getFloatRect();

};


#endif //SKILLED_EAGLE_GAME_CYBERENFORCER_H
