
#include <SFML/Graphics/RenderWindow.hpp>
#include "SplashState.hpp"
#include "../Game.h"

SplashState::SplashState() {

}

SplashState::SplashState(Game *pGame ){
    game = pGame;

    texture_name = sf::Texture(pGame->getTextures().get(Textures::SplashName));
    sprite_name.setTexture(texture_name);
    sprite_name.setPosition(0,0);

    texture_eagle = sf::Texture(pGame->getTextures().get(Textures::SplashScreen));
    sprite_eagle.setTexture(texture_eagle);
    sprite_eagle.setPosition(0,0);

    texture_presents = sf::Texture(pGame->getTextures().get(Textures::SplashPresents));
    sprite_presents.setTexture(texture_presents);
    sprite_presents.setPosition(0,0);

}


void SplashState::input(sf::Event &event) {
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        game->go_to_menu();
    }
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



