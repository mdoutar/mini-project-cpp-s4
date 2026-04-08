#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <math.h>
#include "Collider.hpp"
#include "Obstacle.hpp"
class Player {
private:

sf::Vector2f velocity;
bool canJump;
bool canCrouch;
bool rightFace;
float gravity;
float groundHeight;
int health;
int speed;
public:
    bool canDefense;
    sf::Texture defensePlayerTexture;
    sf::Texture defenseTexture;
    

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture deadTex;    

    Player(sf::Vector2f startPosition,int health , int speed);

    void update(float deltaTime,sf::Vector2f bossPos);
    void draw(sf::RenderWindow& window);
    
    void onCollision(sf::Vector2f direction);
     Collider getCollider() { return Collider(sprite); }
    void takeDamage(int damage);
    int getHealth();
    sf::Vector2f getPosition() { return sprite.getPosition(); }
    void reset(sf::Vector2f startPosition, int newHealth, int newSpeed);
    sf::FloatRect getBounds(); 
    void defense(  std::vector<Obstacle>& defenses, int damage);
};

#endif