//
// Created by endargon on 1/23/17.
//

#include <stdlib.h>
#include "SoundTestState.hpp"
#include "../Game.h"

SoundTestState::SoundTestState(Game *pGame) : game(pGame) {
    soundManager->load_song((char *) "./assets/sounds/song.mp3");
    soundManager->play();
    soundManager->pause();
    soundManager->play();
    beatDec = new BeatDetector(soundManager);
//      for(int i = 0; i < 64; i++) {
//          shapes[i] = new sf::RectangleShape;
//          shapes[i]->setFillColor(sf::Color());
//
//      }
    shape.setSize({game->get_window()->getSize().x, game->get_window()->getSize().y});
    shape.setPosition({0, 0});
    beatDec->audio_process(); // launch beats detection
    float *beat = beatDec->get_beat();
    for(int i = 0; i < soundManager->get_length()/1024; i++) {
        std::cout << ((beat[i] == 1) ? "YAAS" : "NOPE") << "\n";
    }
}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        soundManager->toggle_play();
    }
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        soundManager->reset();
        game->go_to_menu();
    }
    if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f);
    }

    if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f);
    }
}

void SoundTestState::update(const sf::Time delta) {
//    float *beat = beatDec->get_beat();
//
//    float current_pos = soundManager->get_current_time_PCM() / 1024.f;
//    bool found = false;
//
//    int lower_pos = (int) current_pos + 1;
//    while (found == false) {
//        lower_pos--;
//        if (beat[lower_pos] > 0) found = true;
//    }
//    found = false;
//    int upper_pos = (int) current_pos - 1;
//    while (found == false) {
//        upper_pos++;
//        if (beat[upper_pos] > 0) found = true;
//    }
//
//    int L = upper_pos - lower_pos;
//    float t = current_pos - (float) lower_pos;
//    std::cout << t << "\n";
//    if (t > 10) {
//        shape.setFillColor(sf::Color::Red);
//
//    } else {
//        shape.setFillColor(sf::Color::Black);
//    }
}

void SoundTestState::draw(sf::RenderWindow &window) {
    window.draw(shape);




// OUT DATED SPECTRUM STUFF
//    int blockGap = 4 / (64 / 64);
//    int blockWidth = int((int(window.getSize().x) * 2.0f) / int(64) - blockGap);
//    int blockMaxHeight = 200;
//    float *spec = fmod->get_spec();
//    if(fmod->isBeat()) {
//        window.draw(shape);
//    }
//    for (int b = 0; b < 64 - 1; b++) {
//        float hzRange = (44100 / 2) / spec[b];
////        if(hzRange == 22050) {
////            std::cout << hzRange << "\n";
//            sf::RectangleShape *t = shapes[b];
//            t->setPosition({int(0.1f + (blockWidth + blockGap) * b), window.getSize().y});
//            t->setSize({blockWidth, int(-blockMaxHeight * spec[b])});
//            window.draw(*t);
////        }
//    }
}









