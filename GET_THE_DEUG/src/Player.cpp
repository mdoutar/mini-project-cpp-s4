#include "../include/Player.hpp"

// Player::Player(){}
Player::Player(float health , int speed):gravity(981.f),health(health) , speed(speed), velocity(0.f, 0.f), rightFace(true), canJump(false), canCrouch(true) ,healthBar(health){
    try{
        canDefense = false;
        if(!texture.loadFromFile("../assets/textures/student.png")){
            std::cout << "ERROR: Could not load student texture!\n";
        }else{
            sprite.setTexture(texture);
        }
        defensesTex.resize(4);
        for(int i(0) ; i<defensesTex.size();i++){
            if(!defensesTex[i].loadFromFile("../assets/textures/defenses/defenseLvl"+std::to_string(i+1)+".png")){
                std::cout << "ERROR: Could not load defense "<< i <<" student texture!\n";
            }
            std::cout << i ;
        }
        
        row=0;
        animation = Animation(texture, sf::Vector2u(5, 3), 0.1f);
        sprite.setTextureRect(animation.uvRect);

        sf::FloatRect bounds = sprite.getGlobalBounds();
        //  if (bounds.width > 0 && bounds.height > 0) {
        //     sprite.setScale( 150.f/bounds.width ,150.f/ bounds.height );
        // }
        sprite.setOrigin(bounds.width / 2.f, bounds.height);
    }catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Player::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}

void Player::reset( float newHealth, int newSpeed) {
    row=0;
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


// void Player::onCollision(sf::Vector2f direction){
//     if(direction.x !=0.f){
//         velocity.x =0.f;
//     }
//     if(direction.y>0.f){
//         velocity.y =0.f;
//     }
//     else if(direction.y <0.f){
//         velocity.y =0.f;
//         canJump=true;
//         canCrouch=true;
//     }
// }
    
void Player::takeDamage(float damage) {
    health -= damage;
    if (health < 0) {
        health = 0; 
        // sprite.setTexture(deadTex);
        
    }
    if(health >200){
        health =200;
    }
    healthBar.setHealth(health);
}
void Player::defense( std::vector<Obstacle>& defenses , float damage,int level ){
    if(canDefense){
        sf::Vector2f position = sprite.getPosition();
        // set player damage *10 just for testing the levels fast
        Obstacle _defense(&defensesTex[level-1],sf::Vector2f(150.f,150.f),position,damage * 10,true,rightFace?-1000:1000);
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

    float desiredWidth = 80.f;
    float desiredHeight = 120.f;
    float scaleX = desiredWidth / sprite.getLocalBounds().width;
    float scaleY = desiredHeight / sprite.getLocalBounds().height;

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && canCrouch) {
        sprite.setScale(rightFace ? scaleX : -scaleX, scaleY * 0.6f);
      
    } else {
        sprite.setScale(rightFace ? scaleX : -scaleX, scaleY);
    }
    

    if(velocity.x==0){
        row = 0;
    }
    
    velocity.y += gravity * deltaTime;

    if (velocity.x != 0.f) {
        row=1;
        if (velocity.x > 0.0f) {
            rightFace = true;
        } else {
            rightFace = false;
        }
    }

    sprite.move(velocity * deltaTime);

    if (getPosition().y >= groundHeight) {
        sprite.setPosition(getPosition().x, groundHeight);
        velocity.y = 0.f;
        canJump = true;  
        canCrouch = true;
    }
    if(!canJump) row=2;

    if (getPosition().x < 0.f) {
        setPosition(sf::Vector2f(0,getPosition().y));
    }else if (getPosition().x > earthWidth ) {
        setPosition(sf::Vector2f(earthWidth,getPosition().y));
    }

    sf::Vector2f barPosition = getPosition();
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