#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <math.h>
#include "Collider.hpp"
#include "Obstacle.hpp"
#include "Bar.hpp"
#include "Animations.hpp"

class Player {
private:

bool rightFace;
float gravity;
float health;
int speed; 
sf::Sprite sprite;

public:
Animation animation;
Bar healthBar;

bool canDefense;
bool canCrouch;
bool canJump;
int row;
float throwTimer = 0.f;
float throwInterval = .3f;
float earthWidth;
float groundHeight;

sf::Vector2f velocity;
    sf::Texture defensePlayerTexture;
    std::vector <sf::Texture> defensesTex;
    sf::Texture texture;    


    Player(float health , int speed);

    void update(float deltaTime, sf::Vector2f bossPos);
    void draw(sf::RenderWindow& window);
    
    // void onCollision(sf::Vector2f direction);
     Collider getCollider() { return Collider(sprite); }
    void takeDamage(float damage);
    int getHealth();
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    void reset( float newHealth, int newSpeed);
    sf::FloatRect getBounds(); 
    void defense(  std::vector<Obstacle>& defenses, float damage,int level);
    void setPosition(sf::Vector2f pos);
};

#endif