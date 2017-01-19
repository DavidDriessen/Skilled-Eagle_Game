
#include <SFML/Graphics/RenderWindow.hpp>
#include "SplashState.hpp"
#include "../Game.h"

SplashState::SplashState() {

}

SplashState::SplashState(Game *pGame ){
    game = pGame;


    texture.loadFromFile("assets\\images\\splashScreen.png");
    sprite.setTexture(texture);
    sprite.setPosition(0,0);

}


void SplashState::input(sf::Event &event) {
}


void SplashState::update(const sf::Time delta) {
}

void SplashState::draw(sf::RenderWindow &window) {
    size = (sf::Vector2f)window.getSize();
    sprite.setScale(1/(1920/size.x), 1/(1080/size.y));

    elapsed = clock.getElapsedTime();
    if(elapsed <= time_limit){
        window.draw(sprite);
    }
    else{
        game->go_to_menu();
    }


}



