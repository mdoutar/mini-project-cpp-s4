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
    int currentLevel = 1;
    float deltaTime;
    float optShake = 0.f ;
    float shakeTime;
    bool muted=false;

    GameState currentState;

    std::vector<float> reservedSpacesX;

    sf::Texture gameOverTex;
    std::vector<sf::Texture> bgTextures;
     sf::Texture gameFinishedTex;
     std::vector<sf::Texture> healsTex;
    
     sf::Font mainFont;
    sf::Clock clock;
    sf::RenderWindow window;
    
    
    std::vector<Obstacle> defenses;
    
    std::vector<Obstacle> heals;

    std::vector<std::vector <sf::Texture>> obstaclesTex;
    std::vector<std::vector <Obstacle>> obstacles;
    
    
    std::vector<Obstacle> bossAttackes;
    
    
    
    
     sf::RectangleShape background;
     sf::RectangleShape gameOver;
     sf::RectangleShape gameFinished;
     sf::Text muteButton;

     std::vector<sf::Texture>levelCompleteBgTex;
     std::vector<sf::RectangleShape> levelCompleteBg;
     
     sf::Music bgMusic;
     sf::Music fightingMusic;
     
     ContView view;
     Player student;
     Boss boss;
     Menu mainMenu;
    
     

     
     float transitionTimer = 0.f;
     
     void resetGame();
     void shakeView();
     void processEvent();
     void update();
     void render();
     
     public:     
     
     Game();
    void run();

};

#endif