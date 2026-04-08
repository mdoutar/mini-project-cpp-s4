#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "Obstacle.hpp"
enum class typeAttack{
    A,
    B
};
class Boss {
private:
    sf::Sprite sprite;
    int health;
    float speed;
    float throwTimer = 0.f;
    float throwInterval = 2.0f;
    public:
    bool movingUp;
    bool isAttacking = false;
    float attackAnimTimer = 0.f;
    sf::Texture idleTexture;
    sf::Texture attackATextureBoss;
    sf::Texture attackBTextureBoss;
    sf::Texture attackATexture;
    sf::Texture attackBTexture;
    Boss();
    Boss( sf::Vector2f size, sf::Vector2f startPosition, int startHealth);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool shouldThrowObstacle();
     void reset( int newHealth);
    void takeDamage(int amount);
    int getHealth();
    sf::Vector2f getPosition();
    void attack(typeAttack type, std::vector<Obstacle>& attackes);
    Collider getCollider() { return Collider(sprite); }
};

#endif