#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
class Animation
{

private:
    float deltatime,totalTime,switchTime;
    
    int loopCounter; 

    sf::Vector2u imageCount;
    sf::Vector2u curImage;
    
    public:
    sf::IntRect uvRect;
    Animation();
    Animation(sf::Texture &texture ,sf::Vector2u imageCount,float switchTime );
    void update(int row,float deltatime, bool looping= true);
};




#endif