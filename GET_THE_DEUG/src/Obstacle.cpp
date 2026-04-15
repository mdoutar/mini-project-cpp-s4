#include "../include/Obstacle.hpp"

Obstacle::Obstacle(){}
Obstacle::Obstacle(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int damage, bool moving, int speed) 
    : damage(damage), moving(moving), speed(speed)
{
    if (texture != nullptr) {
        obstacle.setTexture(*texture);
    }
    sf::FloatRect bounds = obstacle.getLocalBounds();
    if ((bounds.width > 0 && bounds.height > 0) || bounds.width != size.x || bounds.height !=size.y) {
        obstacle.setScale(size.x / bounds.width, size.y / bounds.height);
        
    }
    
    obstacle.setOrigin(bounds.width / 2.f, bounds.height);
    obstacle.setPosition(position);
    isDestroyed = false;
}


Collider Obstacle::getCollider(){return Collider(obstacle);}
void Obstacle::update(float deltaTime){
    if (moving && !isDestroyed) {
        obstacle.move(-speed * deltaTime, 0.f);
        if (obstacle.getPosition().x < -200.f) {
            isDestroyed = true; 
        }
        Collider obstCol = getCollider();
        
    }
}
void Obstacle::destroyObstacle(){
    isDestroyed = true;
    moving = false;
}
sf::Vector2f Obstacle::getPosition() {
    return obstacle.getPosition();
}

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(obstacle);
}