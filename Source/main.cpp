#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include<memory>

#include "bullet.hpp"
#include "rangedWeapon.hpp"
#include "speler.hpp"
#include "wall.hpp"

#include "screen_object.hpp"




int main() {
    sf::RenderWindow window(sf::VideoMode(600, 480), "SFML werkt!");


    speler player("the player", sf::Vector2f(200.0, 200.0), sf::Vector2f(20.0, 20.0), sf::Color::Green);
    wall theWall("the wall", sf::Vector2f(300.0, 200.0), sf::Vector2f(80.0, 300.0), sf::Color::Blue);

    rangedWeapon gun("ak74", 20, player.position);


    player.assign_weapon(&gun);






    while (window.isOpen()) {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            sf::Vector2f posF;
            posF.x = static_cast<float>(pos.x);
            posF.y = static_cast<float>(pos.y);
            player.move_to_position(posF);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.wapen->set_direction( sf::Vector2f(0.0,-2.0) );
            player.wapen->use();

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.wapen->set_direction(sf::Vector2f(-2.0,0.0));
            player.wapen->use();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player.wapen->set_direction(sf::Vector2f(2.0,0.0));
            player.wapen->use();
        }


        player.update(sf::Vector2f(0.0,0.0));
        theWall.update(sf::Vector2f(0.0,0.0));


        player.wapen->check_collision(theWall);


        player.draw(window);
        theWall.draw(window);







        window.display();
        window.clear();
        sf::sleep(sf::milliseconds(20));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //test push in my branched



    }

    return 0;
}