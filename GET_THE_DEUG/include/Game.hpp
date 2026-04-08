#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ContView.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "Obstacle.hpp"
#include <vector>
enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    LEVEL_COMPLETE
};
class Game
{
private:
sf::Font mainFont;
public : 
    int currentLevel = 1;
    GameState currentState;
    float deltaTime;
    std::vector<Obstacle> activeObstacles;
     std::vector<Obstacle> defenses;
     std::vector<Obstacle> heals;
     sf::Texture healTex;
    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape background;
    sf::Texture bgTexture;
    sf::Music bgMusic;
    sf::Music fightingMusic;
    ContView view;
    Menu mainMenu;
    Player student;
    Boss boss;
    sf::Text levelText;
    sf::Text gameOverMessage;
    float transitionTimer = 0.f;

public:
    Game();
    void resetGame();
    void update();
    void run();
    void processEvent();
    void render();

};

#endif