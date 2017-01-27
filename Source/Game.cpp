//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w) : window(w){
    loadResources();
    this->splashState = new SplashState(this);
    iState = splashState;
    soundManager = new SoundManager();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    view.reset(sf::FloatRect(0 ,0 ,window.getSize().x, window.getSize().y));
    window.setView(view);

    while (window.isOpen()) {
        input();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            input();
            update(TimePerFrame);

        }
        update_debug(elapsedTime);
        draw();
    }
}

Game::~Game() {
    delete playState;
    delete menuState;
    delete settingsState;
}

void Game::loadResources() {
    fonts.load(Fonts::Default, "./assets/font.ttf");
    textures.load(Textures::SplashScreen, "./assets/images/splashScreen.png");
    textures.load(Textures::SplashName, "./assets/images/splashName.png");
    textures.load(Textures::SplashPresents, "./assets/images/splashPresents.png");
    textures.load(Textures::Sniper, "./assets/images/sniper.png");
    textures.load(Textures::Assault, "./assets/images/assault.png");
    textures.load(Textures::Pistol, "./assets/images/pistol.png");
    textures.load(Textures::Floor, "./assets/images/floor.png");
    textures.load(Textures::Floor2, "./assets/images/floor2.png");
    textures.load(Textures::Floor3, "./assets/images/floor3.png");
    textures.load(Textures::Floor4, "./assets/images/floor4.png");
    textures.load(Textures::Finish, "./assets/images/end.png");
    textures.load(Textures::Cyber, "./assets/images/Nuken.png");
    textures.load(Textures::Loot, "./assets/images/loot.png");
    textures.load(Textures::LootUsed, "./assets/images/loot2.png");
}

void Game::input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        iState->input(event);
    }
}

void Game::update(const sf::Time delta) {
    iState->update(delta);
}

void Game::draw() {
    window.clear();
    iState->draw(window);
    window.display();
}

void Game::go_to_play() {
    if(playState == nullptr) {
        controlsState = new ControlsState(this);
        playState = new PlayState(this, soundManager);
    }
    iState = playState;
}

void Game::go_to_level_select() {
    if (levelSelectState == nullptr) {
        levelSelectState = new LevelSelectState(this);
    }
    iState = levelSelectState;
}

void Game::go_to_menu() {
    if (menuState == nullptr) {
        menuState = new MenuState(this);
    }
    iState = menuState;
}

void Game::go_to_options() {
    if (settingsState == nullptr) {
        settingsState = new SettingsState(this);
    }
    if (iState == pauseState) {
        settingsState->setBack([&]() { go_to_pause(); });
    } else if (iState == menuState) {
        settingsState->setBack([&]() { go_to_menu(); });
    }
    iState = settingsState;
}

void Game::go_to_test() {
    if (soundTestState == nullptr) {
        soundTestState = new SoundTestState(this, soundManager);
    }
    iState = soundTestState;
}

void Game::go_to_controls() {
    if (controlsState == nullptr) {
        controlsState = new ControlsState(this);
    }
    iState = controlsState;
}

void Game::go_to_pause() {
    if (pauseState == nullptr) {
        pauseState = new PauseState(this);
    }
    window.setView(view);
    iState = pauseState;
}

void Game::go_to_soon() {
    if (soonState == nullptr) {
        soonState = new SoonState(this);
    }
    iState = soonState;
}

void Game::quit() {
    window.close();
}

sf::Vector2i Game::get_Mouse_Position() {
    return sf::Mouse::getPosition(window);
}


void Game::update_debug(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

ControlsState *Game::getControls() {
    return controlsState;
}

void Game::set_level(std::string string) {
    if (playState == nullptr) {
        playState = new PlayState(this, soundManager);
    }
    playState->set_level(string);
}
