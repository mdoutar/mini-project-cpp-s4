#include "../include/Boss.hpp"
Boss::Boss(){}
Boss::Boss( sf::Vector2f size, sf::Vector2f startPosition, int startHealth) {
idleTexture.loadFromFile("../assets/textures/Smile.png");
attackATextureBoss.loadFromFile("../assets/textures/Aggression.png");
attackBTextureBoss.loadFromFile("../assets/textures/Special.png");
attackATexture.loadFromFile("../assets/textures/Sadness.png");
attackBTexture.loadFromFile("../assets/textures/Smile.png");

    if (idleTexture.getSize().x > 0) {
        sprite.setTexture(idleTexture);
    }
    if (idleTexture.getSize().x > 0) {
        sprite.setTexture(idleTexture);
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    if (bounds.width > 0 && bounds.height > 0) {
        sprite.setScale(size.x / bounds.width, size.y / bounds.height);
    }

    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(startPosition);

    health = startHealth;
    speed = 150.f; 
    movingUp = true; 
}

void Boss::update(float deltaTime) {
    throwTimer += deltaTime;
    if (movingUp) {
        sprite.move(0.f, -speed * deltaTime);
        if (sprite.getPosition().y < 250.f) { 
            movingUp = false;
        }
    } else {
        sprite.move(0.f, speed * deltaTime);
        if (sprite.getPosition().y > 550.f) {
            movingUp = true;  
        }
    }
    if (isAttacking) {
        attackAnimTimer += deltaTime;
        if (attackAnimTimer > 0.3f) { 
            isAttacking = false;
            sprite.setTexture(idleTexture); 
        }
    }
}
bool Boss::shouldThrowObstacle() {
    if (throwTimer >= throwInterval) {
        throwTimer = 0.f;
        return true;     
    }
    return false;      
}
void Boss::reset( int newHealth) {
    health = newHealth;
    movingUp = true;
}
void Boss::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Boss::attack(typeAttack type, std::vector<Obstacle>& attackes ) {
    sf::Vector2f spawnPos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getLocalBounds();
    spawnPos.x -= bounds.width;
    throwTimer = 0;
    isAttacking = true;
    attackAnimTimer = 0.f;
    if (type == typeAttack::A) {
        if (attackATexture.getSize().x >0 ) {
            
            sprite.setTexture(attackATextureBoss);
            Obstacle thrownItem(&attackATexture, sf::Vector2f(100.f, 100.f), spawnPos ,10, true, 500);
            attackes.push_back(thrownItem);
        }
    }
    else if (type == typeAttack::B) {
        if (attackBTexture.getSize().x>0) {
            sprite.setTexture(attackBTextureBoss);
            Obstacle thrownItem(&attackBTexture, sf::Vector2f(100.f, 100.f), spawnPos ,10, true, 500);
            attackes.push_back(thrownItem);
        }        
    }
}

int Boss::getHealth() {
    return health;
}
void Boss::takeDamage(int amount){
    health-=amount;
    if (health<=0){
        health =0;
    }
}
sf::Vector2f Boss::getPosition() {
    return sprite.getPosition();
}
