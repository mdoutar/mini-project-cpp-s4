#include "../include/Menu.hpp"
#include <iostream>

Menu::Menu(sf::Vector2f dimension){
    menuBg.setSize(sf::Vector2f(400.f , 500.f));
    menuBg.setPosition(200.f,100.f);
    menuBg.setFillColor(sf::Color(0,0,0,150));

    if (!clickBuffer.loadFromFile("../assets/click.wav")) {
            std::cout << "ERROR: Could not load click sound!\n";
        }

    clickSound.setBuffer(clickBuffer);
    if (!font.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")) { 
            std::cout << "CRITICAL ERROR: Failed to load font!\n";
        }

    if (!btnTex.loadFromFile("../assets/textures/10.png")) {
            std::cout << "ERROR: Could not load button texture!\n";
        }
    
    
    for(int i=0 ; i<MAXSIZE;i++){
        buttons[i].setTexture(&btnTex);
        buttons[i].setSize(sf::Vector2f(200.f, 100.f));
        buttons[i].setPosition((menuBg.getPosition().x )+ (buttons[i].getSize().x/2), menuBg.getPosition().y + (i * 70.f));
        buttons[i].setFillColor(sf::Color::White);

        text_menu[i].setFont(font);
        text_menu[i].setFillColor(sf::Color::Red);
        text_menu[i].setOutlineColor(sf::Color::Yellow);
        text_menu[i].setOutlineThickness(2.f);
        // text_menu[i].setCharacterSize(50);
        text_menu[i].setString(MenuOptions[i]);
        text_menu[i].setPosition(buttons[i].getPosition().x + 50.f, buttons[i].getPosition().y + 10.f);
    }
    
    curSelected = 0;
    
    // focus();



}
void Menu::removeFocus(){
        text_menu[curSelected].setFillColor(sf::Color::Red);
        text_menu[curSelected].setOutlineThickness(0.f);
}
void Menu::focus(){
        text_menu[curSelected].setFillColor(sf::Color::Blue);
        text_menu[curSelected].setOutlineThickness(2.f);
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