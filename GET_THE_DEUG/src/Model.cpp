#include "../include/Model.hpp"
#include <iostream>

Model::Model(){}

Model::Model(sf::String cont){
    if(!bgTex.loadFromFile("../assets/textures/modelbg.png")){
         std::cout << "Texture of model background not found !!";
    }
    if(!textFont.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")){
         std::cout << "Font of model not found !!";
    }
    modelBg.setTexture(bgTex);

    modelBg.setScale(500.f/bgTex.getSize().x ,500.f/bgTex.getSize().y);
    text.setFont(textFont);

    text.setColor(sf::Color::Black);
    text.setCharacterSize(12);
    text.setString(cont);
    
}
void Model::setPostion(sf::Vector2f position){
    modelBg.setPosition(position);
    text.setPosition(modelBg.getGlobalBounds().left + 90.f ,  modelBg.getGlobalBounds().top +40.f);
}
sf::Vector2f Model::getSize(){
    return sf::Vector2f(modelBg.getGlobalBounds().width , modelBg.getGlobalBounds().height);
}
void Model::draw(sf::RenderWindow &window){
    window.draw(modelBg);
    window.draw(text);
}