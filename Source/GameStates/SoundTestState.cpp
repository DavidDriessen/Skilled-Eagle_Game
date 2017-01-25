//
// Created by endargon on 1/23/17.
//

#include <stdlib.h>
#include "SoundTestState.hpp"
#include "../Game.h"
#include <sstream>


SoundTestState::SoundTestState(Game *pGame, SoundManager *soundManager) : game(pGame) {
    std::ifstream input("./assets/sounds/beats/cyka.blyat");
    std::string line = "";
    this->soundManager = soundManager;
    font.loadFromFile("./assets/font.ttf");
    soundManager->load_song((char *) "./assets/sounds/cyka.mp3");
    soundManager->play();
    soundManager->pause();
    beatDec = new BeatDetector(soundManager);
    int length = soundManager->get_length();
    int count = 0;
    if (input.is_open()) {
        std::cout << "LOAD FROM FILE\n";
        beat = new float[soundManager->get_length() / 1024];
        if(getline(input, line)) {
            bpm = std::stoi(line);
        }
        char c;
        while (input.get(c)) {
            if (c == '\n') {
                break;
            }
            float k = float(int(c) - '0');
            beat[count++] = k;
        }
    }


    cyka = sf::Text("CHEEKI BREEKI", font, 175);
    cyka.setPosition({30, 225});

    if(count != (soundManager->get_length()/1024)-1) {
        beatDec->audio_process(); // launch beats detection
        beat = beatDec->get_beat();

        std::ofstream output("./assets/sounds/beats/cyka.blyat");
        if (output.is_open()) {
            output.clear();
            output << beatDec->get_tempo() << "\n";
            for (int i = 0; i < soundManager->get_length() / 1024; i++) {
                output << ((beat[i] == 0) ? 0 : 1);
            }
        }
    }

}

SoundTestState::~SoundTestState() {

}

void SoundTestState::input(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        soundManager->pause();
    }
    else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        soundManager->reset();
        game->go_to_menu();
    }
    else if (event.key.code == sf::Keyboard::H) {
        soundManager->change_pitch(0.01f);
    }

    else if (event.key.code == sf::Keyboard::J) {
        soundManager->change_pitch(-0.01f);
    }
}

void SoundTestState::update(const sf::Time delta) {
    float current_pos = soundManager->get_current_time_PCM() / 1024.f;
    bool found = false;

    int lower_pos = (int) current_pos + 1;
    while (found == false) {
        lower_pos--;
        if (beat[lower_pos] > 0) found = true;
    }
    found = false;
    int upper_pos = (int) current_pos - 1;
    while (found == false) {
        upper_pos++;
        if (beat[upper_pos] > 0) found = true;
    }

    int L = upper_pos - lower_pos;
    float t = current_pos - (float) lower_pos;
    if (t > 10) {
        cyka.setFillColor(sf::Color::Yellow);
    } else {
        cyka.setFillColor(sf::Color::Black);
    }
}

void SoundTestState::draw(sf::RenderWindow &window) {
    window.draw(cyka);
}










