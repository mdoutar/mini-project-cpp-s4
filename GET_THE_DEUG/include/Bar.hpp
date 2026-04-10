#ifndef BAR_H
#define BAR_H
#include <SFML/Graphics.hpp> 
#include <iostream>
class Bar{
    private: 
        sf::RectangleShape bar , health;
        sf::Vector2f size ;
        float maxHealth;
    public:
    Bar();
        Bar( float maxHealth,sf::Vector2f size );
        void setHealth(float currHealth);
        void update( float currHealth, sf::Vector2f position);
        void draw(sf::RenderWindow& window);
};
#endif