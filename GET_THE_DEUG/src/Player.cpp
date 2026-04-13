#include "../include/Player.hpp"

// Player::Player(){}
Player::Player(float health , int speed):gravity(981.f),health(health) , speed(speed), velocity(0.f, 0.f), rightFace(true), canJump(false), canCrouch(true) ,healthBar(health){
    canDefense = false;
    if (!texture.loadFromFile("../assets/textures/student.png")) {
            std::cout << "ERROR: Could not load player texture!\n";
        }else{
            sprite.setTexture(texture);
        }
    if (!deadTex.loadFromFile("../assets/textures/Smile.png")) {
            std::cout << "ERROR: Could not load dead player texture!\n";
        }
    if(!defenseTexture.loadFromFile("../assets/textures/Smile.png")){
        std::cout << "ERROR: Could not load defense texture!\n";
    }

    animation = Animation(texture, sf::Vector2u(5, 5), 0.1f);
    sprite.setTextureRect(animation.uvRect);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);

    row=0;
}
void Player::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}
void Player::reset( float newHealth, int newSpeed) {
    health = newHealth;
    speed = newSpeed;
    velocity = sf::Vector2f(0.f, 0.f);
    canJump = true;
    canCrouch=true;
    rightFace = true;
    sf::Vector2f barPosition = sprite.getPosition() ;
    barPosition.x -= getBounds().width / 2  ; 
    barPosition.y -= getBounds().getSize().y +30.f;
    healthBar.update(newHealth,barPosition);
}
void Player::update(float deltaTime, sf::Vector2f bossPos){

    velocity.x =0.f;
    float distanceBtwBoss = bossPos.x -getPosition().x;
    throwTimer+= deltaTime;
    
    if(distanceBtwBoss <=1000.f && throwTimer>= throwInterval){
        canDefense = true;
    }else{ canDefense=false;}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) velocity.x -=speed ;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )velocity.x +=speed ; 

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && canJump) {
        canJump = false;
        canCrouch =false;
        velocity.y = -sqrtf(2.f  * gravity * 150.f);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && canCrouch) {
        sprite.setScale(rightFace ? 1.f : -1.f, 0.7f);
    } else {
        sprite.setScale(rightFace ? 1.f : -1.f, 1.f); 
    }
if(velocity.x==0){
     row = 0;

}
    
    velocity.y += gravity * deltaTime;

    if (velocity.x != 0.f) {
        row=2;
        if (velocity.x > 0.0f) {
            rightFace = true;
        } else {
            rightFace = false;
        }
    }
    sprite.move(velocity * deltaTime);

    if (sprite.getPosition().y >= groundHeight) {
        sprite.setPosition(sprite.getPosition().x, groundHeight);
        velocity.y = 0.f;
        canJump = true;  
        canCrouch = true;
    }
    if(!canJump) row=3;

    if (sprite.getPosition().x < 0.f) {
        setPosition(sf::Vector2f(0,groundHeight));
    }else if (sprite.getPosition().x > earthWidth ) {
        setPosition(sf::Vector2f(earthWidth,groundHeight));
    }

    sf::Vector2f barPosition = sprite.getPosition();
    barPosition.x -= getBounds().width / 2  ; 
    barPosition.y -= getBounds().getSize().y +30.f ; 
    healthBar.update(health, barPosition);

    animation.update(row, deltaTime);
    sprite.setTextureRect(animation.uvRect);
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
    if(health >200){
        health =200;
    }
    healthBar.setHealth(health);
}
void Player::defense( std::vector<Obstacle>& defenses , float damage ){
    if(canDefense){
        sf::Vector2f position = sprite.getPosition();
        Obstacle _defense(&defenseTexture,sf::Vector2f(50.f,50.f),position,damage,true,rightFace?-350:350);
        defenses.push_back(_defense);
        throwTimer = 0.f;
        canDefense =false;
    }
}
int Player::getHealth() {
    return health;
}
sf::FloatRect Player::getBounds() {
    return sprite.getGlobalBounds(); 
}