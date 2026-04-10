#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
class Collider{
    private:
        sf::Sprite& spirite;
    public:
        Collider(sf::Sprite &spirite );
        bool checkCollider(Collider &other ,sf::Vector2f& direction,float push );
        void move(float dx,float dy){spirite.move(dx,dy);};
        sf::Vector2f getPosition();
        sf::Vector2f getHalfSize();

};
#endif