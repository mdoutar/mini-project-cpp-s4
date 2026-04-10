#include "../include/Collider.hpp"
#include <iostream>
Collider::Collider(sf::Sprite &spirite):spirite(spirite){}
bool Collider::checkCollider(Collider &other ,sf::Vector2f& direction,float push ){
    sf::Vector2f thisPos = getPosition();
    sf::Vector2f thisHalSize = getHalfSize();
    sf::Vector2f otherPos = other.getPosition();
    sf::Vector2f otherHalSize = other.getHalfSize();

    float deltaX = thisPos.x - otherPos.x;
    float deltaY = thisPos.y - otherPos.y;

    float intersectX = std::abs(deltaX) - (thisHalSize.x + otherHalSize.x);
    float intersectY = std::abs(deltaY) - (thisHalSize.y + otherHalSize.y);
    if(intersectX < 0.f &&  intersectY <0.f){
        push = std::max(std::min(push,1.f),0.f);
        if(intersectX> intersectY){
            if(deltaX > 0.f){
                move(-intersectX * (1.f - push) ,0.f);
                other.move( intersectX *  push,0.f);
                direction.x = 1.f;direction.y = 0.f;
            }
            else if(deltaX < 0.f){
                move( intersectX * (1.f - push) ,0.f);
                other.move( -intersectX *  push,0.f);
                direction.x = -1.f;direction.y = 0.f;
            }
        }else {
            if(deltaY > 0.f){
                move(0.f,-intersectY * (1.f - push) );
                other.move(0.f, intersectY *  push);
                direction.x = 0.f;direction.y = -1.f;
                
            }
                else if(deltaY < 0.f){
                    move( 0.f,intersectY * (1.f - push));
                    other.move( 0.f , -intersectY *  push);
                    direction.x = 0.f;direction.y = 1.f;
            }
        }
        return true;
    }
    return false;
}

sf::Vector2f Collider::getPosition() {
    sf::FloatRect bounds = spirite.getGlobalBounds();
    return sf::Vector2f(bounds.left + (bounds.width/2), bounds.top + (bounds.height/2));
}

sf::Vector2f Collider::getHalfSize() {
    sf::FloatRect bounds = spirite.getGlobalBounds();
    return sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f);
}