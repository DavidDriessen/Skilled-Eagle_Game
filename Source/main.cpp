#include "Audio/SoundManager.h"
#include "Audio/BeatDetector.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#define K_GRAVITE 4

int main(int argc, char *argv[]) {
    // Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Beat detector");
    App.setFramerateLimit(60);
    Game waveForms(App);
    // Create SoundManager
//    SoundManager *snd_mng = new SoundManager();
//    snd_mng->load_song((char *) "./assets/sounds/song.mp3"); // load song in arguments
//    snd_mng->play();
//    snd_mng->pause();
//    snd_mng->play();
//    // Create BeatDetector
//    BeatDetector *beatdec = new BeatDetector(snd_mng);
//    float time = (float) (snd_mng->get_current_time_PCM() / 44100.f);
//    sf::CircleShape beat_light;
//    int window = 430; // (44100/1024)*10sec
//    float offset = 0;
//    beat_light.setRadius(100);
//    beat_light.setFillColor(sf::Color::Blue);
//    float hight = 100.f;
//    beatdec->audio_process(); // launch beats detection
//    while (App.isOpen()) {
//        sf::Event event;
//        while (App.pollEvent(event)) {
//            if (event.key.code == sf::Keyboard::H) {
//                snd_mng->change_pitch(0.01f);
//            }
//
//            if (event.key.code == sf::Keyboard::J) {
//                snd_mng->change_pitch(-0.01f);
//            }
//        }
//        float *beat = beatdec->get_beat();
//
//        // saut dynamique de la beat_light
//        // verifie ou sont les beats les plus proches
//        float current_pos = snd_mng->get_current_time_PCM() / 1024.f;
//        // celui de gauche
//        bool found = false;
//        int lower_pos = (int) current_pos + 1;
//        while (found == false) {
//            lower_pos--;
//            if (beat[lower_pos] > 0) found = true;
//        }
//        // celui de droite
//        found = false;
//        int upper_pos = (int) current_pos - 1;
//        while (found == false) {
//            upper_pos++;
//            if (beat[upper_pos] > 0) found = true;
//        }
//        // calcul de la hauteur
//        int L = upper_pos - lower_pos; // la distance a sauter
//        float t = current_pos - (float) lower_pos; // le temps ecoul� depuis le debut du saut
//        hight = -(K_GRAVITE / 2) * t * t + (K_GRAVITE / 2) * L * t; // equation de cinematique
////        beat_light.setPosition(App.getSize().x/2, (beat_light.getPosition().y+100) - hight);
//        if (t > 10) {
//            App.clear(sf::Color::Red);
//            beat_light.setFillColor(sf::Color::Red);
//        } else {
//            App.clear(sf::Color::Black);
//            beat_light.setFillColor(sf::Color::Blue);
//        }
////        App.draw(beat_light);
////        beat_light.setPosition(beat_light.getPosition().x, 0);
//
//        App.display();
//        std::cout << beatdec->get_tempo() << "\n";
//    }

    return EXIT_SUCCESS;
}
