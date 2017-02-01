//
// Created by robbie on 17-1-2017.
//

#include "Game.h"

Game::Game(sf::RenderWindow &w) : window(w){
    soundManager = new SoundManager();
    loadResources();
    this->overlay = new DebugOverlay(this);
    this->splashState = new SplashState(this);
    iState = splashState;
    soundManager->play(SOUND_TYPES::SPLASH);
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
    soundManager->insert_sound(SOUND_TYPES::GAME_SOUND, (char *) "./assets/sounds/cyka.mp3");
    soundManager->insert_sound(SOUND_TYPES::BACKGROUND, (char *) "./assets/sounds/song.mp3");
    soundManager->insert_sound(SOUND_TYPES::SPLASH, (char *) "./assets/sounds/song1.mp3");
    fonts.load(Fonts::Default, "./assets/font.ttf");
    textures.load(Textures::SplashScreen, "./assets/images/splashScreen.png");
    textures.load(Textures::SplashName, "./assets/images/splashName.png");
    textures.load(Textures::SplashPresents, "./assets/images/splashPresents.png");
    textures.load(Textures::SplashLoading, "./assets/images/loading.jpg");
    textures.load(Textures::Sniper, "./assets/images/sniper.png");
    textures.load(Textures::Assault, "./assets/images/assault.png");
    textures.load(Textures::Pistol, "./assets/images/pistol.png");
    textures.load(Textures::Sword, "./assets/images/sword.png");
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
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
            overlay->toggleHide();
        }
        iState->input(event);
    }
}

void Game::update(const sf::Time delta) {
    overlay->setPos(view.getCenter()-view.getSize()/2.0f);
    overlay->update(delta);
    iState->update(delta);
    update_debug(delta);
}

void Game::draw() {
    window.clear();
    window.setView(view);
    iState->draw(window);
    overlay->draw(window);
    window.display();
}

void Game::go_to_play() {
    if(playState == nullptr) {
        controlsState = new ControlsState(this);
        playState = new PlayState(this, soundManager, std::string("./assets/Levels/awesomeLevel.txt"));
    }
    soundManager->reset(SOUND_TYPES::BACKGROUND);
    soundManager->reset(SOUND_TYPES::SPLASH);
    soundManager->play(SOUND_TYPES::GAME_SOUND);
    iState = playState;
}

void Game::go_to_level_select() {
    if (levelSelectState == nullptr) {
        levelSelectState = new LevelSelectState(this);
    }
    view.reset(sf::FloatRect(0 ,0 ,window.getSize().x, window.getSize().y));
    iState = levelSelectState;
}

void Game::go_to_menu(bool play) {
    if (menuState == nullptr) {
        menuState = new MenuState(this);
    }
    if(playState != nullptr) {
        delete playState;
        playState = nullptr;
    }
    if(play) {
        soundManager->reset(SOUND_TYPES::GAME_SOUND);
        soundManager->reset(SOUND_TYPES::SPLASH);
        soundManager->play(SOUND_TYPES::BACKGROUND);
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

void Game::go_to_highscore() {
    if (highScoreState == nullptr) {
        highScoreState = new HighScoreState(this);
    }
    highScoreState->load_score();
    iState = highScoreState;
}

void Game::go_to_pause(bool play) {
    if (pauseState == nullptr) {
        pauseState = new PauseState(this);
    }
    if(play) {
        soundManager->pause(SOUND_TYPES::GAME_SOUND);
        soundManager->play(SOUND_TYPES::BACKGROUND);
    }
    view.reset(sf::FloatRect(0 ,0 ,window.getSize().x, window.getSize().y));
    iState = pauseState;
}

void Game::go_to_soon() {
    if (soonState == nullptr) {
        soonState = new SoonState(this);
    }
    iState = soonState;
}

void Game::go_to_game_over(bool dead) {
    gameOverState = new GameOverState(this, dead);
    view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    iState = gameOverState;
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
        overlay->addDebugValue("FPS", std::to_string(mStatisticsNumFrames));
        mStatisticsNumFrames = 0;
    }
}

ControlsState *Game::getControls() {
    return controlsState;
}

void Game::set_level(std::string level_name) {
    window.clear();
    sf::Sprite spriteLoading;
    sf::Texture loading = textures.get(Textures::SplashLoading);
    loading.setSmooth(true);
    spriteLoading.setTexture(loading);
    spriteLoading.setPosition(0,0);
    spriteLoading.setScale(1.0f/(1600.0f/window.getSize().x), 1.0f/(900.0f/window.getSize().y));
    window.draw(spriteLoading);
    window.display();

    std::string map = std::string("./assets/Levels/") + level_name;
    if (playState == nullptr || controlsState == nullptr) {
        controlsState = new ControlsState(this);
        playState = new PlayState(this, soundManager, map);
    } else {
        playState->set_level(map);
    }
}

sf::View* Game::getView() {
    return &view;
}

void Game::setView(sf::View &view) {
    Game::view = view;
}

sf::RenderWindow *Game::get_window() {
    return &window;
}

const TextureHolder &Game::getTextures() const {
    return textures;
}

const FontHolder &Game::getFonts() const {
    return fonts;
}

DebugOverlay *Game::getOverlay() const {
    return overlay;
}

SoundManager *Game::getSoundManager() const {
    return soundManager;
}