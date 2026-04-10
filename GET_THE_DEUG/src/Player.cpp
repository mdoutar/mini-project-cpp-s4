#include "../include/Player.hpp"

// Player::Player(){}
Player::Player(sf::Vector2f startPosition ,float health , int speed):gravity(981.f),health(health) , speed(speed), velocity(0.f, 0.f), rightFace(true), canJump(false), canCrouch(true) ,healthBar(health,sf::Vector2f(100.f, 10.f)){
    canDefense = false;
    if (!texture.loadFromFile("../assets/textures/Sadness.png")) {
            std::cout << "ERROR: Could not load player texture!\n";
        }
    if (!deadTex.loadFromFile("../assets/textures/Smile.png")) {
            std::cout << "ERROR: Could not load dead player texture!\n";
        }
    if (!defenseTexture.loadFromFile("../assets/textures/Smile.png")) {
            std::cout << "ERROR: Could not load defense texture!\n";
        }
    
    sprite.setTexture(texture);
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);

    sprite.setPosition(startPosition);

    
}
void Player::reset(sf::Vector2f startPosition, float newHealth, int newSpeed) {
    sprite.setPosition(startPosition);
    health = newHealth;
    speed = newSpeed;
    velocity = sf::Vector2f(0.f, 0.f);
    canJump = true;
    canCrouch=true;
    rightFace = true;
    sf::Vector2f barPosition = startPosition ;
     barPosition.x -= getBounds().width / 2  ; 
    barPosition.y -= getBounds().getSize().y +30.f;
    healthBar.update(newHealth,barPosition);
}
void Player::update(float deltaTime, sf::Vector2f bossPos){
    velocity.x =0.f;
    float distanceBtwBoss = bossPos.x -getPosition().x;
    if(distanceBtwBoss <=1000.f){
        canDefense = true;
    }else{ canDefense=false;}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) velocity.x -=speed ; 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )velocity.x +=speed ; 

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && canJump) {
        canJump = false;
        // canCrouch =false;
        velocity.y = -sqrtf(2.f  * gravity * 150.f);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && canCrouch) {
        sprite.setScale(rightFace ? 1.f : -1.f, 0.5f);
    } else {
        sprite.setScale(rightFace ? 1.f : -1.f, 1.f); 
    }

    velocity.y += gravity * deltaTime;

    if (velocity.x != 0.f) {
        if (velocity.x > 0.0f) {
            rightFace = true;
        } else {
            rightFace = false;
        }
    }
    sprite.move(velocity * deltaTime);

    float groundHeight = 500.f;
    if (sprite.getPosition().y >= groundHeight) {
        sprite.setPosition(sprite.getPosition().x, groundHeight);
        velocity.y = 0.f;
        canJump = true;  
        canCrouch = true;
    }
    if (sprite.getPosition().x < 0.f) {
        sprite.move(10.f,0);
    }
    float playerWidth = sprite.getGlobalBounds().width;
    float earthWidth = 3000.f;
    
    if (sprite.getPosition().x > earthWidth ) {
        sprite.move(-10.f,0);
    }
    sf::Vector2f barPosition = sprite.getPosition();
    barPosition.x -= getBounds().width / 2  ; 
    barPosition.y -= getBounds().getSize().y +30.f ; 
    healthBar.update(health, barPosition);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    healthBar.draw(window );
}
void Player::onCollision(sf::Vector2f direction){
    if(direction.x !=0.f){
        velocity.x =0.f;
    }
    if(direction.y>0.f){
        velocity.y =0.f;
    }
    else if(direction.y <0.f){
        velocity.y =0.f;
        canJump=true;
        canCrouch=true;
    }
}
    
void Player::takeDamage(float damage) {
    health -= damage;
    if (health < 0) {
        health = 0; 
        sprite.setTexture(deadTex);
    }
    healthBar.setHealth(damage);
}
void Player::defense( std::vector<Obstacle>& defenses , float damage ){
    sf::Vector2f position = sprite.getPosition();
    Obstacle _defense(&defenseTexture,sf::Vector2f(50.f,50.f),position,damage,true,-250);
    defenses.push_back(_defense);
}
int Player::getHealth() {
    return health;
}
sf::FloatRect Player::getBounds() {
    return sprite.getGlobalBounds(); 
}