#include "../include/Boss.hpp"
#include <cstdlib> 
#include <ctime> 

Boss::Boss(){}
Boss::Boss(   float startHealth):healthBar(startHealth) {

    
    try{
        srand(static_cast<unsigned>(time(NULL)));
        if(!idleTexture.loadFromFile("../assets/textures/idleBoss.png")){
             std::cout << "ERROR: Could not load idle boss texture!\n";
        }else{
            sprite.setTexture(idleTexture);
        }

        if(!attackTextureBoss.loadFromFile("../assets/textures/attackBoss.png")){
             std::cout << "ERROR: Could not load boss attacking texture!\n";
        }

        
        
        sf::FloatRect bounds = sprite.getLocalBounds();
        if (bounds.width > 0 && bounds.height > 0) {
            sprite.setScale( 80.f/bounds.width ,120.f/ bounds.height );
        }
    
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
        health = startHealth;
        speed = 150.f; 
        movingUp = true; 


        
        attackesTex.resize(4);
        for(int r =0;r<4;r++){
            attackesTex[r].resize(6);
            for(int c=0;c< 6;c++){
            if (!attackesTex[r][c].loadFromFile("../assets/textures/attackes/lvl" + std::to_string(r + 1) + "/trap"+std::to_string(c + 1)+  ".png")) {
                std::cout << "Error loading trap texture!\n";
            }
        }
    }
    }catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

void Boss::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}

bool Boss::shouldThrowObstacle() {
    if (throwTimer >= throwInterval) {
        throwTimer = 0.f;
        return true;     
    }
    return false;      
}

void Boss::reset( float newHealth) {
    health = newHealth;
    movingUp = true;
}

sf::FloatRect Boss::getBounds() {
    return sprite.getGlobalBounds(); 
}

void Boss::attack(int level, std::vector<Obstacle>& attackes ) {
    sf::Vector2f spawnPos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getLocalBounds();
    spawnPos.x -= bounds.width;
    throwTimer = 0;
    isAttacking = true;
    attackAnimTimer = 0.f;

        int randomAttack = rand() % 6 ;
    if(attackesTex[level-1][randomAttack].getSize().x>0){

Obstacle thrownItem(&attackesTex[level-1][randomAttack], sf::Vector2f(100.f, 100.f), spawnPos, 10.f, true, 550);
        attackes.push_back(thrownItem);
    }
}

float Boss::getHealth() {
    return health;
}

void Boss::takeDamage(float amount){
    health-=amount;
    if (health<=0.f){
        health =0.f;
    }
    healthBar.setHealth(health);
}

sf::Vector2f Boss::getPosition() {
    return sprite.getPosition();
}


void Boss::update(float deltaTime) {
    throwTimer += deltaTime;
    if (movingUp) {
        sprite.move(0.f, -speed * deltaTime);
        if (sprite.getPosition().y < 350.f) { 
            movingUp = false;
        }
    } else {
        sprite.move(0.f, speed * deltaTime);
        if (sprite.getPosition().y > 450.f) {
            movingUp = true;  
        }
    }
    if (isAttacking) {
        attackAnimTimer += deltaTime;
        if (attackAnimTimer > 0.3f) { 
            isAttacking = false;
            sprite.setTexture(idleTexture); 
        }else{
            sprite.setTexture(attackTextureBoss);
        }
    }

    sf::Vector2f barPosition = getPosition() ;
    barPosition.x -= getBounds().width / 2  ; 
    barPosition.y -= getBounds().getSize().y +30.f;
    healthBar.update(getHealth(),barPosition);
}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    healthBar.draw(window);
}