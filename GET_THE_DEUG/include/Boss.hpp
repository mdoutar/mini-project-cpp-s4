#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "Obstacle.hpp"
#include "Bar.hpp"
class Boss {
private:


    sf::Sprite sprite;
    
    float health;
    float speed;
    float throwTimer = 0.f;
    float throwInterval = 1.5f;
    bool movingUp;
    float attackAnimTimer = 0.f;
    public:
    bool isAttacking = false;

    std::vector<std::vector <sf::Texture>> attackesTex;
    sf::Texture idleTexture;
    sf::Texture attackTextureBoss;

    Bar healthBar;


    Boss();
    Boss(  float startHealth);

    sf::FloatRect getBounds();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool shouldThrowObstacle();
     void reset( float newHealth);
    void takeDamage(float amount);
    float getHealth();
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void attack(int level, std::vector<Obstacle>& attackes);
    Collider getCollider() { return Collider(sprite); }
};

#endif