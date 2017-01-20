//
// Created by jer on 19-1-2017.
//

#include "rangedWeapon.hpp"

rangedWeapon::rangedWeapon(std::string s, int damage, sf::Vector2f playerPosition):
    name ( s ),
    damage ( damage ),
    position ( playerPosition)
{}


void rangedWeapon::update(){
    for( std::unique_ptr<bullet> & kogel  : bulletVector){
        kogel->update(sf::Vector2f(0.0,0.0));
    }

    bulletVector.erase(std::remove_if(bulletVector.begin(), bulletVector.end(), [](std::unique_ptr<bullet> & kogel){
                                                                                    return kogel->hasCollision;}
    ), bulletVector.end());
    return;
}

void rangedWeapon::draw(sf::RenderWindow & window){
    for( std::unique_ptr<bullet> & kogel  : bulletVector){
        kogel->draw(window);
    }
    return;
}

void rangedWeapon::update_weapon_position(sf::Vector2f playerPosition){
    position = playerPosition;
}

void rangedWeapon::set_direction(sf::Vector2f newDirection){
    direction = newDirection;
}

void rangedWeapon::use(){
    bulletVector.push_back(std::make_unique<bullet>("bullet", position,  20, direction));
}


void rangedWeapon::check_collision(screen_object & obj){
    for( std::unique_ptr<bullet> & kogel  : bulletVector){
        if( kogel->collision(obj) ){
            kogel->set_hasCollision();
            std::cout<< "bullet collision set \n";
        }


    }
}