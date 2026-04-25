#include "../include/Menu.hpp"
#include <iostream>
#include <math.h>

Menu::Menu(sf::Vector2f dimension){
MenuOptions[0] = "Play";
    MenuOptions[1] = "Restart";
    MenuOptions[2] = "Control";
    MenuOptions[3] = "Quit";

            if(!menuTex.loadFromFile("../assets/textures/menuBg.png")){
            std::cout << "ERROR: Could not load menu background texture!\n";
        }else{
            
            menuBg.setTexture(&menuTex);
        }
        menuBg.setSize(dimension);

    if (!clickBuffer.loadFromFile("../assets/audios/mouse-click.mp3")) {
            std::cout << "ERROR: Could not load click sound!\n";
        }

    clickSound.setBuffer(clickBuffer);
    if (!font.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")) { 
            std::cout << "CRITICAL ERROR: Failed to load menu font!\n";
        }

    if (!btnTex.loadFromFile("../assets/texures/10.png")) {
            std::cout << "ERROR: Could not load button texture!\n";
        }
    float centerX = menuBg.getPosition().x + (menuBg.getSize().x / 2.f);
    float buttonX = centerX -(btnTex.getSize().x/2);
    
    
    for(int i=0 ; i<MAXSIZE;i++){
        buttons[i].setFillColor(sf::Color(0, 0, 0, 100));
        buttons[i].setPosition(buttonX,   250.f + float(i *60));
        
        
        text_menu[i].setFont(font);
        text_menu[i].setFillColor(sf::Color::Red);
        text_menu[i].setOutlineColor(sf::Color::Yellow);
        text_menu[i].setOutlineThickness(2.f);
        text_menu[i].setString(MenuOptions[i]);
        
        sf::FloatRect textBounds = text_menu[i].getLocalBounds();
        text_menu[i].setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        
        text_menu[i].setPosition(
            buttons[i].getPosition().x + (buttons[i].getSize().x / 2.0f), 
            buttons[i].getPosition().y + (buttons[i].getSize().y / 2.0f)
        );;
    }

    curSelected = 0;
    focus();
    



}
void Menu::removeFocus(){
        text_menu[curSelected].setFillColor(sf::Color::Red);
        text_menu[curSelected].setOutlineColor(sf::Color::Yellow);
}
void Menu::focus(){
        text_menu[curSelected].setFillColor(sf::Color::Yellow);
        text_menu[curSelected].setOutlineColor(sf::Color::Red);
}
void Menu::handleHover(sf::Vector2f mousePos){
    for (int i = 0; i < MAXSIZE; i++) {
        if (text_menu[i].getGlobalBounds().contains(mousePos)) {
            if (curSelected != i) {
                removeFocus();
                std::cout << mousePos.x;
                curSelected = i;
                focus();
            }
            break;
        }
    }
}
int Menu::checkMouseClick(sf::Vector2f mousePos) {
    for (int i = 0; i < MAXSIZE; i++) {
        if (text_menu[i].getGlobalBounds().contains(mousePos)) {
            removeFocus();
            curSelected = i;
            focus();
            return i; 
        }
    }
    return -1;
}


void Menu::moveUP(){
        removeFocus();
        curSelected--;
        if(curSelected<=-1){
            curSelected =MAXSIZE-1;
        }
        focus();
    
}
void Menu::moveDOWN(){
        removeFocus();
        curSelected++;
        if(curSelected>=MAXSIZE){
            curSelected =0;
        }
        focus();
}

void Menu::update(){

    float time = pulseClock.getElapsedTime().asSeconds();
    float pulseScale = 1.0f + 0.15f * std::sin(time * 5.0f);
    for(int i(0); i< MAXSIZE;i++){

        if (i == curSelected) {
            text_menu[i].setScale(pulseScale, pulseScale);
        } else {
            text_menu[i].setScale(1.0f, 1.0f);
        }
    }

} 

void Menu::draw(sf::RenderWindow & window){
    
    window.draw(menuBg);
    for (int i = 0; i < MAXSIZE; i++) {
         window.draw(buttons[i]);

        window.draw(text_menu[i]);
    }
}