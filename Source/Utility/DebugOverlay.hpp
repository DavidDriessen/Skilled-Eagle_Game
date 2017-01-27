//
// Created by endargon on 1/27/17.
//

#ifndef SKILLED_EAGLE_GAME_DEBUGOVERLAY_HPP
#define SKILLED_EAGLE_GAME_DEBUGOVERLAY_HPP

#include <map>
#include <SFML/Graphics/Text.hpp>
#include "../ScreenObjects/ScreenObject.h"
#include "ResourceIdentifiers.hpp"

class Game;

struct debugStruct {
    std::string name;
    std::string value;
    sf::Text text;
};

class DebugOverlay : public ScreenObject {
private:
    std::map<std::string, debugStruct> debugValues;
    Game *game;
    sf::Font font;
    bool show = false;
    sf::Vector2f pos;
public:
    DebugOverlay(Game *game);

    void input(sf::Event &event);

    void update(const sf::Time delta);

    void draw(sf::RenderWindow &window);

    void addDebugValue(std::string name, std::string value);

    void removeDebugValue(std::string name);

    sf::FloatRect getFloatRect();

    const sf::Vector2f &getPos() const;

    void setPos(const sf::Vector2f &pos);

    void toggleHide();

};

#endif //SKILLED_EAGLE_GAME_DEBUGOVERLAY_HPP
