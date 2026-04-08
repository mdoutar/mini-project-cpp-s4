#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
static const int MAXSIZE = 4;
static std::string MenuOptions[MAXSIZE] = {
    "Play",
    "Levels",
    "Restart",
    "Quit",
};

class Menu
{
private:
    int curSelected ; 
    
    sf::RectangleShape menuBg;
    sf::Texture btnTex;
    
    sf::SoundBuffer clickBuffer;
    sf::Text text_menu[MAXSIZE];
    
    public:
    sf::Sound clickSound;
    sf::RectangleShape buttons[MAXSIZE];
    sf::Font font;  

public:
    Menu(sf::Vector2f size); 
    int getMenuPressed(){
        return curSelected;
    }
    int checkMouseClick(sf::Vector2f mousePos);
    void handleHover(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);
    void moveUP();
    void moveDOWN();
    void focus();
    void removeFocus();
};
#endif