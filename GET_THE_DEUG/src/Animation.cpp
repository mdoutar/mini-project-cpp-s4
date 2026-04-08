#include "../include/Animations.hpp"
Animation::Animation(){};
Animation::Animation(sf::Texture &texture ,sf::Vector2u imageCount,float switchTime):imageCount(imageCount),switchTime(switchTime){
    totalTime =0.f; 
    curImage.x = 0;
    uvRect.width = texture.getSize().x / float(imageCount.x);
    uvRect.height = texture.getSize().y /float(imageCount.y);
}

void Animation::update(int row,float deltatime){
    curImage.y = row;
    totalTime += deltatime;
    if(totalTime >=switchTime){
        totalTime-=switchTime;
        curImage.x++;
        if(curImage.x>=imageCount.x) curImage.x =0;
    }
    uvRect.top = curImage.y*uvRect.height;
    uvRect.width = abs(uvRect.width);
    uvRect.left = (curImage.x)*abs(uvRect.width);   
}