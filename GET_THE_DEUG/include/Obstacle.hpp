#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>
#include "../include/Collider.hpp"
class Obstacle
{
public :
    sf::Sprite obstacle;
    int damage;
    bool moving;
    int speed;
    bool isDestroyed ;
    
public:
Collider getCollider();
Obstacle();
    Obstacle(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int damage, bool moving, int speed);
    
    
    sf::Vector2f getPosition();
    void draw(sf::RenderWindow &window);
    void destroyObstacle();
    void update(float deltaTime);

};

#endif