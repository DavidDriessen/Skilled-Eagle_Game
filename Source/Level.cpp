//
// Created by robbie on 18-1-2017.
//

#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "Game.h"
#include <iostream>

Level::Level(const char * location, Game* game) : game(game), player(game->getTextures().get(Textures::Cyber),sf::Vector2f(100, 100), 0.3, 0.4, 10, 172, 260, 0.2, *this) {
    std::string loc = location;
    init_new_map(loc);
}

Level::~Level() {
    for (auto &block : blocks) {
        delete block;
    }
    for (auto &cyberEnforcer : cyber_enforcers) {
        delete cyberEnforcer;
    }
    blocks.clear();
    cyber_enforcers.clear();
}

void Level::init_object(char c, float x, float y) {
    switch (c) {
        case '-':
            blocks.push_back(new Block(game->getTextures().get(Textures::Floor), sf::Vector2f(x, y)));
            break;
        case '*':
            blocks.push_back(new Block(game->getTextures().get(Textures::Floor2), sf::Vector2f(x, y)));
            break;
        case '&':
            blocks.push_back(new Block(game->getTextures().get(Textures::Floor3), sf::Vector2f(x, y)));
            break;
        case '^':
            blocks.push_back(new Block(game->getTextures().get(Textures::Floor4), sf::Vector2f(x, y)));
            break;
        case '$':
            blocks.push_back(new Block(game->getTextures().get(Textures::Finish), sf::Vector2f(x, y), sf::Vector2f(128, 32)));
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
            powerUps.push_back(new PowerUp(game->getTextures().get(Textures::Loot), game->getTextures().get(Textures::LootUsed), sf::Vector2f(x, y)));
            break;
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            powerUps.push_back(new PowerUp(game->getTextures().get(Textures::Loot), game->getTextures().get(Textures::LootUsed), sf::Vector2f(x, y)));
            break;
        case 'C':
            cyber_enforcers.push_back(new CyberEnforcer(game->getTextures().get(Textures::Cyber), *this, sf::Vector2f(x, y - 16)));
            break;
        case '@':
            weapons.push_back(new RangedWeapon(game->getTextures().get(Textures::Assault), 6, sf::Vector2f(x, y), 7 * 32, sf::milliseconds(200)));
            break;
        case '#':
            weapons.push_back(new RangedWeapon(game->getTextures().get(Textures::Pistol), 4, sf::Vector2f(x, y), 4 * 32, sf::milliseconds(100)));
            break;
        case '!':
            weapons.push_back(new RangedWeapon(game->getTextures().get(Textures::Sniper), 8, sf::Vector2f(x, y), 13 * 32, sf::milliseconds(500)));
            break;
        case 'P':
            player.set_position({x, y});
            break;
        default:
            std::string resultString = "\nUndifined char : ";
            throw resultString + c + "\n";
    }
}

std::vector<ScreenObject*> &Level::get_blocks() {
    return blocks;
}

std::vector<CyberEnforcer*> &Level::get_cyber_enforcers() {
    return cyber_enforcers;
}

std::vector<PowerUp*> &Level::get_powerUps() {
    return powerUps;
}

std::vector<Weapon*> &Level::get_weapons() {
    return weapons;
}

Character& Level::get_player() {
    return player;
}

void Level::init_new_map(std::string &map) {
    // current position
    float current_x = 0;
    float current_y = 0;
    // load file
    std::ifstream input(map);
    char c;
    while(input.get(c)) {
        // when new line..
        if(c == '\n') {
            current_x = 0;
            current_y += 32;
            continue;
        } else if(c != '.') {
            try {
                init_object(c, current_x, current_y);
            } catch(std::string & exception) {
                std::cout << exception;
            }
        }
        current_x += 32;
    }
    input.close();
}