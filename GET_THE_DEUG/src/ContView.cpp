#include "../include/ContView.hpp"


ContView::ContView(){};
ContView::ContView(sf::Vector2f dimension ):view(sf::Vector2f(0.f,0.f) ,dimension) {
}
void ContView::setCenter(sf::Vector2f positions){
    view.setCenter(positions);
}
void ContView::resizeView(float VIEW_WIDTH,float VIEW_HEIGHT,sf::RenderWindow &window , sf::View &view){
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}
void ContView::clampToBounds(float worldWidth, float worldHeight) {
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float minX = size.x / 2.f;
    float maxX = worldWidth - (size.x / 2.f);
    
    float minY = size.y / 2.f;
    float maxY = worldHeight - (size.y / 2.f);

    float clampedX = std::clamp(center.x, minX, maxX);
    float clampedY = std::clamp(center.y, minY, maxY);

    view.setCenter(clampedX, clampedY);
}