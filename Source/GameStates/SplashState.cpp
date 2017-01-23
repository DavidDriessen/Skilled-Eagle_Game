
#include <SFML/Graphics/RenderWindow.hpp>
#include "SplashState.hpp"
#include "../Game.h"

SplashState::SplashState() {

}

SplashState::SplashState(Game *pGame ){
    game = pGame;

    texture_name.loadFromFile("assets/images/splashName.png");
    sprite_name.setTexture(texture_name);
    sprite_name.setPosition(0,0);

    texture_eagle.loadFromFile("assets/images/splashScreen.png");
    sprite_eagle.setTexture(texture_eagle);
    sprite_eagle.setPosition(0,0);

    texture_presents.loadFromFile("assets/images/splashPresents.png");
    sprite_presents.setTexture(texture_presents);
    sprite_presents.setPosition(0,0);

}


void SplashState::input(sf::Event &event) {

}


void SplashState::update(const sf::Time delta) {
    elapsed = clock_eagle.getElapsedTime();
    if(elapsed > time_limit_eagle){
        game->go_to_menu();
    }
}

void SplashState::draw(sf::RenderWindow &window) {
    size = (sf::Vector2f)window.getSize();
    sprite_eagle.setScale(1/(1920/size.x), 1/(1080/size.y));
    sprite_presents.setScale(1/(1920/size.x), 1/(1080/size.y));

    sprite_name.setScale(1/(1920/size.x), 1/(1080/size.y));

    if(elapsed < time_limit_name){
        window.draw(sprite_name);
    }

    if(elapsed > time_limit_name && elapsed < time_limit_presents){
        window.draw(sprite_presents);
    }

    if(elapsed > time_limit_presents && elapsed < time_limit_eagle){
        window.draw(sprite_eagle);
    }
}



