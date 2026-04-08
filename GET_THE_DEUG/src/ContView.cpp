#include "../include/ContView.hpp"
ContView::ContView(){};
ContView::ContView(sf::Vector2f dimension):view(sf::Vector2f(0.f,0.f) ,dimension){
}
void ContView::setCenter(sf::Vector2f positions){
    view.setCenter(positions);
}
void ContView::resizeView(float VIEW_WIDTH,float VIEW_HEIGHT,sf::RenderWindow &window , sf::View &view){
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}