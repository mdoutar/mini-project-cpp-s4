#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>
#include <algorithm>

class ContView
{

public:
    sf::View view ; 
public:
    ContView();
    ContView(sf::Vector2f dimension );
    void setCenter(sf::Vector2f positions);
    void resizeView(float VIEW_WIDTH,float VIEW_HEIGHT,sf::RenderWindow &window , sf::View &view);
    void clampToBounds(float worldWidth, float worldHeight);
};
#endif