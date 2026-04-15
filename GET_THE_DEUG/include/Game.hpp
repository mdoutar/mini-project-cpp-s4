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

    
    
    std::vector<Obstacle> defenses;

    std::vector<sf::Texture> healsTex;
    std::vector<Obstacle> heals;

    std::vector<std::vector <sf::Texture>> obstaclesTex;
    std::vector<std::vector <Obstacle>> obstacles;

    
    std::vector<Obstacle> bossAttackes;

     
     sf::RectangleShape background;
     sf::RectangleShape gameOver;
     std::vector<sf::Texture>levelCompleteBgTex;
     std::vector<sf::RectangleShape> levelCompleteBg;
     sf::RectangleShape gameFinished;
     
     sf::Music bgMusic;
     sf::Music fightingMusic;
     
     ContView view;
     Menu mainMenu;
     Player student;
     Boss boss;
    
     
     
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