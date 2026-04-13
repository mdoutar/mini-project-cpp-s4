#include "../include/Menu.hpp"
#include <iostream>

Menu::Menu(sf::Vector2f dimension){
            if(!menuTex.loadFromFile("../assets/textures/menuBg.png")){
            std::cout << "ERROR: Could not load menu background texture!\n";
        }else{
            
            menuBg.setTexture(&menuTex);
        }
        menuBg.setSize(dimension);

    if (!clickBuffer.loadFromFile("../assets/click.wav")) {
            std::cout << "ERROR: Could not load click sound!\n";
        }

    clickSound.setBuffer(clickBuffer);
    if (!font.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")) { 
            std::cout << "CRITICAL ERROR: Failed to load font!\n";
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
        text_menu[i].setPosition(buttons[i].getPosition().x  , buttons[i].getPosition().y );
        buttons[i].setSize(sf::Vector2f(text_menu[i].getGlobalBounds().width, text_menu[i].getGlobalBounds().height));
    }

    curSelected = 0;
    



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
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            if (curSelected != i) {
                removeFocus();
                curSelected = i;
                focus();
            }
            break;
        }
    }
}
int Menu::checkMouseClick(sf::Vector2f mousePos) {
    for (int i = 0; i < MAXSIZE; i++) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
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
void Menu::draw(sf::RenderWindow & window){
    
    window.draw(menuBg);
   for (int i = 0; i < MAXSIZE; i++) {
        window.draw(buttons[i]);
        window.draw(text_menu[i]);
    }
}