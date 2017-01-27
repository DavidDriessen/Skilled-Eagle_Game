//
// Created by endargon on 1/27/17.
//

#include "DebugOverlay.hpp"
#include "../Game.h"

DebugOverlay::DebugOverlay(Game *game) : game(game) {
    font = sf::Font(game->getFonts().get(Fonts::Default));
}

void DebugOverlay::input(sf::Event &event) {

}

void DebugOverlay::update(const sf::Time delta) {
    int index = 0;
    for (auto &t : debugValues) {
        t.second.text.setFillColor(sf::Color::Yellow);
        t.second.text.setPosition(pos.x, pos.y + (index++ * (t.second.text.getCharacterSize() * 2)));
    }
}

void DebugOverlay::draw(sf::RenderWindow &window) {
    if (show) {
        for (auto &t : debugValues) {
            window.draw(t.second.text);
        }
    }
}

void DebugOverlay::addDebugValue(std::string name, std::string value) {
    if (debugValues.count(name) > 0) {
        debugValues.find(name)->second.value = value;
        debugValues.find(name)->second.text.setString(name + " : " + value);
    } else {
        sf::Text t(name + ": " + value, font, 20);
        t.setPosition(0, debugValues.size() * 60);
        t.setScale(3, 2);
        t.setStyle(sf::Text::Italic);
        debugValues.insert({name, {name, value, t}});
    }
}

void DebugOverlay::toggleHide() {
    show = !show;
}

void DebugOverlay::removeDebugValue(std::string name) {
    debugValues.erase(name);
}

sf::FloatRect DebugOverlay::getFloatRect() {
    return sf::Rect<float>();
}

const sf::Vector2f &DebugOverlay::getPos() const {
    return pos;
}

void DebugOverlay::setPos(const sf::Vector2f &pos) {
    DebugOverlay::pos = pos;
}