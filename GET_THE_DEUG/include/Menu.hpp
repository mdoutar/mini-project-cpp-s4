#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
static const int MAXSIZE = 4;


class Menu
{
private:
    std::string MenuOptions[MAXSIZE];
    int curSelected =0 ; 
    
    sf::Texture btnTex;
    
    sf::SoundBuffer clickBuffer;
    sf::Text text_menu[MAXSIZE];
    
        sf::RectangleShape menuBg;
        
        sf::Clock pulseClock;
        void focus();
        void removeFocus();
        
        public:
        sf::Texture menuTex;
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
    void moveUP();
    void moveDOWN();
    void update();
    void draw(sf::RenderWindow& window);
};
#endif