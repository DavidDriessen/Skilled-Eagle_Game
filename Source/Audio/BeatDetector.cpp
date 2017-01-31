#include "BeatDetector.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <thread>

#define K_ENERGIE_RATIO  1.3 // le ratio entre les energie1024 et energie44100 pour la d�tection des peak d'energie
#define K_TRAIN_DIMP_SIZE 108 // la taille du train d'impulsions pour la convolution (en pack de 1024 (430=10sec))
#define MS_MINUTE 60000
using namespace std;

BeatDetector::BeatDetector(SoundManager *snd_mgr, SOUND_TYPES t) {
    this->sound = snd_mgr->get_sound(t);
    std::string songPath = sound->path;
    songName = songPath.substr(songPath.find_last_of("/\\") + 1);
    std::ifstream input("assets/sounds/beats/" + songName + ".beats");
    std::string line = "";
    this->snd_mgr = snd_mgr;
    found_beats = 0;
    length = sound->length;
    energie1024 = new float[length / 1024];
    energie44100 = new float[length / 1024];
    conv = new float[length / 1024];
    beat = new float[length / 1024];
    energie_peak = new float[length / 1024 + 21];
    for (int i = 0; i < length / 1024 + 21; i++) energie_peak[i] = 0;
    int count = 0;
    if (input.is_open()) {
        if (getline(input, line)) {
            tempo = std::stoi(line);
        }
        char c;
        while (input.get(c)) {
            if (c == '\n') {
                break;
            }
            float k = float(int(c) - '0');
            beat[count++] = k;
            if(k == 1) {
                found_beats++;
            }
        }
    }
    if (count < (length / 1024)) {
        std::cout << "DECODING MUSIC\n";
        audio_process(); // launch beats detection
    } else {
        std::cout << "LOADED FROM FILE\n";
    }

}

BeatDetector::~BeatDetector() {

}

int BeatDetector::energie(int *data, int offset, int window) {
    float energie = 0.f;
    for (int i = offset; (i < offset + window) && (i < length); i++) {
        energie = energie + data[i] * data[i] / window;
    }
    return (int) energie;
}

void BeatDetector::normalize(float *signal, int size, float max_val) {
    // recherche de la valeur max du signal
    float max = 0.f;
    for (int i = 0; i < size; i++) {
        if (abs(signal[i]) > max) max = abs(signal[i]);
    }
    // ajustage du signal
    float ratio = max_val / max;
    for (int i = 0; i < size; i++) {
        signal[i] = signal[i] * ratio;
    }
}

int BeatDetector::search_max(float *signal, int pos, int fenetre_half_size) {
    float max = 0.f;
    int max_pos = pos;
    for (int i = pos - fenetre_half_size; i <= pos + fenetre_half_size; i++) {
        if (signal[i] > max) {
            max = signal[i];
            max_pos = i;
        }
    }
    return max_pos;
}

void BeatDetector::audio_process(void) {
    found_beats = 0;
    loading = true;
// recupere les donn�es de la musique
// ----------------------------------
    // le canal gauche
    int *data = sound->left;

// calcul des energies instantann�es
// ---------------------------------
    for (int i = 0; i < length / 1024; i++) {
        energie1024[i] = energie(data, 1024 * i, 4096); // 4096 pour lisser un peu la courbe
    }

// calcul des energies moyennes sur 1 seconde
// ------------------------------------------
    energie44100[0] = 0;
    // la moyenne des 43 premiers energies1024 donne l'energie44100 de la premiere seconde
    float somme = 0.f;
    for (int i = 0; i < 43; i++) {
        somme = somme + energie1024[i];
    }
    energie44100[0] = somme / 43;

    for (int i = 1; i < length / 1024; i++) {
        if (i + 42 >= length / 1024) {
            break;
        }
        somme = somme - energie1024[i - 1] + energie1024[i + 42];
        energie44100[i] = somme / 43;
    }

// Ratio energie1024/energie44100
// ------------------------------
    for (int i = 21; i < length / 1024; i++) {
        // -21 pour centrer le energie1024 sur la seconde du energie44100
        if (energie1024[i] > K_ENERGIE_RATIO * energie44100[i - 21]) {
            energie_peak[i] = 1;
        }
    }

// Calcul des BPMs
// ---------------
    // calcul des laps de temps entre chaque energie_peak
    vector<int> T;
    int i_prec = 0;
    for (int i = 1; i < length / 1024; i++) {
        if ((energie_peak[i] == 1) && (energie_peak[i - 1] == 0)) {
            int di = i - i_prec;
            if (di > 5) // en pour les parasites
            {
                T.push_back(di);
                i_prec = i;
            }
        }
    }
    // le tableau T contient tous les laps de temps
    // fait des stats pour savoir quel est le plus fr�quent
    int T_occ_max = 0;
    float T_occ_moy = 0.f;

    // compte les occurence de chaque laps de temps
    int occurences_T[86]; // max 2 paquets de 43 d'�cart (2sec)
    for (int i = 0; i < 86; i++) occurences_T[i] = 0;
    for (int i = 1; i < T.size(); i++) {
        if (T[i] <= 86) occurences_T[T[i]]++;
    }
    int occ_max = 0;
    for (int i = 1; i < 86; i++) {
        if (occurences_T[i] > occ_max) {
            T_occ_max = i;
            occ_max = occurences_T[i];
        }
    }
    // on fait la moyenne du max + son max de voisin pour + de pr�cision
    int voisin = T_occ_max - 1;
    if (occurences_T[T_occ_max + 1] > occurences_T[voisin]) voisin = T_occ_max + 1;
    float div = occurences_T[T_occ_max] + occurences_T[voisin];

    if (div == 0) T_occ_moy = 0;
    else T_occ_moy = (float) (T_occ_max * occurences_T[T_occ_max] + (voisin) * occurences_T[voisin]) / div;

    // clacul du tempo en BPMs
    tempo = (int) 60.f / (T_occ_moy * (1024.f / 44100.f));

// Calcul de la Beat line
// ----------------------
    // cr�ation d'un train d'impulsions (doit valoir 1 tous les T_occ_moy et 0 ailleurs)
    float train_dimp[K_TRAIN_DIMP_SIZE];
    float espace = 0.f;
    train_dimp[0] = 1.f;
    for (int i = 1; i < K_TRAIN_DIMP_SIZE; i++) {
        if (espace >= T_occ_moy) {
            train_dimp[i] = 1;
            espace = espace - T_occ_moy; // on garde le depassement
        }
        else train_dimp[i] = 0;
        espace += 1.f;
    }

    // convolution avec l'�nergir instantann�e de la music
    for (int i = 0; i < length / 1024 - K_TRAIN_DIMP_SIZE; i++) {
        for (int j = 0; j < K_TRAIN_DIMP_SIZE; j++) {
            conv[i] = conv[i] + energie1024[i + j] * train_dimp[j];
        }

    }
    normalize(conv, length / 1024, 1.f);

    // recherche des peak de la conv
    // le max (c'est la plupart du temps un beat (pas tout le temps ...))
    for (int i = 1; i < length / 1024; i++)
        beat[i] = 0;

    float max_conv = 0.f;
    int max_conv_pos = 0;
    for (int i = 1; i < length / 1024; i++) {
        if (conv[i] > max_conv) {
            max_conv = conv[i];
            max_conv_pos = i;
        }
    }
    beat[max_conv_pos] = 1.f;
    found_beats++;

    // les suivants
    // vers la droite
    int i = max_conv_pos + T_occ_max;
    while ((i < length / 1024) && (conv[i] > 0.f)) {
        // on cherche un max dans les parages
        int conv_max_pos_loc = search_max(conv, i, 2);
        beat[conv_max_pos_loc] = 1.f;
        i = conv_max_pos_loc + T_occ_max;
        found_beats++;
    }
    // vers la gauche
    i = max_conv_pos - T_occ_max;
    while (i > 0) {
        // on cherche un max dans les parages
        int conv_max_pos_loc = search_max(conv, i, 2);
        beat[conv_max_pos_loc] = 1.f;
        i = conv_max_pos_loc - T_occ_max;
        found_beats++;

    }

    loading = false;
    if (found_beats >= (int) (float) sound->lengthMS / ((float) 60000 / (float) tempo)-10) {
        std::ofstream output("assets/sounds/beats/"+  songName + ".beats");
        if (output.is_open()) {
            output.clear();
            output << get_tempo() << "\n";
            for (int i = 0; i < length / 1024; i++) {
                output << ((beat[i] == 0) ? 0 : 1);
            }
        }
    }
}

void BeatDetector::update(void) {
    float current_pos = snd_mgr->get_current_time_PCM(sound->type) / 1024.f;
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
        for (auto &b : listeners) {
            b.second->onBeat();
        }
    }
    for (auto &b : listeners) {
        b.second->onPeak(energie1024[(int) current_pos]);
    }

}

float *BeatDetector::get_energie1024(void) {
    return energie1024;
}

float *BeatDetector::get_energie44100(void) {
    return energie44100;
}

float *BeatDetector::get_energie_peak(void) {
    return energie_peak;
}

float *BeatDetector::get_conv() {
    return conv;
}

float *BeatDetector::get_beat() {
    return beat;
}

int BeatDetector::get_tempo(void) {
    return tempo;
}

void BeatDetector::remove_listener(int id) {
    for (auto &b : listeners) {
        if (b.first == id) {
            listeners.erase(listeners.begin() + b.first);
            break;
        }
    }
}

void BeatDetector::add_listener(BeatListener *l) {
    listeners.push_back({listeners.size(), l});
}

bool BeatDetector::getLoading() {
    return loading;
}

