#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>
class ContView
{
public:
    sf::View view ; 
public:
    ContView();
    ContView(sf::Vector2f dimension);
    void setCenter(sf::Vector2f positions);
    void resizeView(float VIEW_WIDTH,float VIEW_HEIGHT,sf::RenderWindow &window , sf::View &view);
};
#endif