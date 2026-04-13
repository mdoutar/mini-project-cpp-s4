#include "../include/Bar.hpp"

Bar::Bar(){};

Bar::Bar(float maxHealth) : maxHealth(maxHealth) {
    size.x = 100.f; 
    size.y = 5.f;   

    bar.setSize(size);
    bar.setFillColor(sf::Color::Red);
    bar.setOutlineThickness(2.f);
    bar.setOutlineColor(sf::Color::Black);

    health.setSize(size);
    health.setFillColor(sf::Color::Green);
}

void Bar::update(float currHealth, sf::Vector2f position) {
    if (currHealth < 0.f) currHealth = 0.f;
    
    float healthPercent = currHealth / maxHealth;
    
    health.setSize(sf::Vector2f(size.x * healthPercent, size.y));
    
    bar.setPosition(position);
    health.setPosition(position);
    

    bar.setSize(size);  
}

void Bar::setMaxHealth(float maxHealth) {
    this->maxHealth = maxHealth;   
}

void Bar::setHealth(float currHealth) {
    if (currHealth < 0.f) currHealth = 0.f;
    
    float healthPercent = currHealth / maxHealth;
    health.setSize(sf::Vector2f(size.x * healthPercent, size.y));
}

void Bar::draw(sf::RenderWindow &window) {
    window.draw(bar);
    window.draw(health);
}