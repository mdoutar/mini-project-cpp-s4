#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>


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
    LEVEL_COMPLETE,
    GET_DEUG
};
class Game
{
private:
sf::Font mainFont;
GameState currentState;
int currentLevel = 1;
float deltaTime;
sf::Clock clock;
sf::RenderWindow window;

public : 

    
    
     std::vector<Obstacle> activeObstacles;
     std::vector<Obstacle> defenses;
     std::vector<Obstacle> heals;
     sf::Texture trapTex;
     std::vector<std::vector <Obstacle>> traps;

     
     sf::RectangleShape background;
     sf::RectangleShape gameOver;
     sf::RectangleShape gameFinished;
     
     sf::Music bgMusic;
     sf::Music fightingMusic;
     
     ContView view;
     Menu mainMenu;
     Player student;
     Boss boss;
    
     sf::Text levelText;
     
     sf::Texture healTex;
     
     std::vector<sf::Texture> bgTextures;
     sf::Texture gameOverTex;
     sf::Texture gameFinishedTex;
     
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