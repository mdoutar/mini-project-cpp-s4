#include "../include/Animations.hpp"
#include <iostream>

Animation::Animation(){};
Animation::Animation(sf::Texture &texture ,sf::Vector2u imageCount,float switchTime):imageCount(imageCount),switchTime(switchTime){
    totalTime =0.f; 
    curImage.x = 0;
    uvRect.width = texture.getSize().x / imageCount.x;
    uvRect.height = texture.getSize().y / imageCount.y;
}

void Animation::update(int row, float deltatime, bool looping) {
    if (curImage.y != row) {
        curImage.y = row;
        curImage.x = 0;  
        totalTime = 0.f;
    }

    totalTime += deltatime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        curImage.x++;

        if (curImage.x >= imageCount.x) {
            if (looping) {
                curImage.x = 0;
            } else {
                curImage.x = imageCount.x - 1;
            }
        }
    }

    uvRect.top = curImage.y * uvRect.height;
    uvRect.left = curImage.x * uvRect.width;
}