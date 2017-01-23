//
// Created by david on 1/19/2017.
//

#include <sstream>
#include "ControllesState.hpp"
#include "../Game.h"

ControllesState::ControllesState(Game *pGame) : Menu(600, 500) {
    game = pGame;

    std::string line;
    std::ifstream f("./assets/Settings/controles.txt");

    for (int i = 0; i < ActionsCount; ++i) {
        if (std::getline(f, line)) {
            std::stringstream linestream(line);
            std::string data;
            std::getline(linestream, data, '\n');
            key[(Actions) i].key = (sf::Keyboard::Key) atoi(data.c_str());
        }
    }

    actions.push_back([&]() {
        key_to_bind = &key[Jump];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Left];
    });
    actions.push_back([&]() {
        key_to_bind = &key[Right];
    });
    key_to_bind = NULL;
}

void ControllesState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && key_to_bind) {
        if (event.key.code != sf::Keyboard::Key::Escape) {
            key_to_bind->key = event.key.code;
        }
        key_to_bind = NULL;
    } else {
        if (event.type == sf::Event::KeyPressed &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game->go_to_options();
            save();
        }
        Menu::input(event, game->get_Mouse_Position(), actions, true);
    }
}

void ControllesState::update(const sf::Time delta) {
}

void ControllesState::draw(sf::RenderWindow &window) {
    if (key_to_bind) {
        sf::Font font;
        font.loadFromFile("./assets/font.ttf");
        sf::Vector2i mid = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);

        sf::RectangleShape shape({500, 150});
        shape.setPosition(sf::Vector2f(mid.x - 250, mid.y - 50));
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::Yellow);
        shape.setOutlineThickness(5);
        window.draw(shape);

        sf::String t("Press the key to bind.");
        sf::Text text(t, font);
        text.setPosition((float) mid.x - (float) t.getSize() / 2.0f * 20.0f, (float) mid.y + 5);
        text.setScale(2, 1);
        text.setStyle(sf::Text::Italic);
        text.setFillColor(sf::Color::Blue);
        window.draw(text);
    } else {
        btn[0] = sf::String("Jump: ") + KeyboardKeyNames[key[Jump].key];
        btn[1] = sf::String("Left: ") + KeyboardKeyNames[key[Left].key];
        btn[2] = sf::String("Right: ") + KeyboardKeyNames[key[Right].key];
        Menu::draw(window, btn);
    }
}

void ControllesState::assign_pressed(const Actions &action, const std::function<void()> &func) {
    key[action].pressed = func;
}

void ControllesState::assign_released(const Actions &action, const std::function<void()> &func) {
    key[action].released = func;
}

void ControllesState::run_actions(sf::Event &event) {
    for (auto &k:key) {
        if (event.key.code == k.second.key) {
            if (event.type == sf::Event::KeyPressed) {
                k.second.pressed();
            } else if (event.type == sf::Event::KeyReleased) {
                k.second.released();
            }
        }
    }
}

void ControllesState::save() {
    std::ofstream f("./assets/Settings/controles.txt");
    f.clear();
    std::string *data = new std::string[ActionsCount];
    for (auto &k: key) {
        data[k.first].append(std::to_string(k.second.key));
        data[k.first].append("\n");
    }
    for (int i = 0; i < ActionsCount; i++) {
        f.write(data[i].c_str(), data[i].size());
    }
    f.close();
}
