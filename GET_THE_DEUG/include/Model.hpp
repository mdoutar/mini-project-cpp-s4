#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
class Model
{
private:
    sf::Sprite modelBg ; 
    sf::Texture bgTex ; 
    sf::Font textFont;
    sf::Text text;
    sf::Text cont;
public:
    bool open  =false; 
public:
    Model();
    Model(sf::String cont);
    void setPostion(sf::Vector2f position);
    sf::Vector2f getSize();
    void draw(sf::RenderWindow& window);
};

#endif