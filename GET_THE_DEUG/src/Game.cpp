#include "../include/Game.hpp"
static const float WINDOW_WIDTH = 800.f , WINDOW_HEIGHT=600.f; 
Game::Game( ): window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT) ,"GET THE DEUG" , sf::Style::Close |sf::Style::Resize )  ,background(sf::Vector2f(3000.f,600.f)) ,view(sf::Vector2f(WINDOW_WIDTH , WINDOW_HEIGHT)), mainMenu(sf::Vector2f(800.f, 400.f)) ,student(sf::Vector2f(100.f, 600.f), 200, 300),boss( sf::Vector2f(100.f,100.f),sf::Vector2f(2950.f,600.f),200 ){
    window.setFramerateLimit(60);
    if (!healTex.loadFromFile("")) {
        std::cout << "ERROR: Could not heal texture!\n";
    }
    Obstacle heal(&healTex,sf::Vector2f(10.f,10.f),sf::Vector2f(1000.f,700.f), -100,false , 0 );
    heals.push_back(heal);
    currentState = GameState::MENU;
    if (!mainFont.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")) {
        std::cout << "ERROR: Could not load font!\n";
    }else{
        levelText.setFont(mainFont);
        levelText.setCharacterSize(40);
        levelText.setFillColor(sf::Color::Green);

        gameOverMessage.setCharacterSize(40);
        gameOverMessage.setFont(mainFont);
        gameOverMessage.setFillColor(sf::Color::Red);
    }    
        if (  !bgMusic.openFromFile("../assets/background_theme.ogg") ) {
            std::cout << "ERROR: Could not load background music!\n";
        }else{
            bgMusic.setLoop(true);
            bgMusic.setVolume(50.f);
            bgMusic.play(); 
        }
        if (  !bgMusic.openFromFile("../assets/fighting_theme.ogg") ) {
            std::cout << "ERROR: Could not load fighting music!\n";
        }else{
            fightingMusic.setLoop(true);
            fightingMusic.setVolume(50.f);
        }
    
    if (!bgTexture.loadFromFile("../assets/orig.png")) {
            std::cout << "ERROR: Could not load background texture!\n";
        } else {
            background.setTexture(&bgTexture);
        }
}


void Game::processEvent(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::Resized) {
            view.resizeView(WINDOW_WIDTH, WINDOW_HEIGHT, window, view.view);
        }
        if (currentState == GameState::PLAYING) {
            if( event.key.code == sf::Keyboard::Escape ) {
                    mainMenu.clickSound.play();
                    currentState= GameState::MENU;
                }
                else if( student.canDefense &&(event.key.code ==sf::Keyboard::E || event.mouseButton.button ==sf::Mouse::Right)){
                    student.defense(defenses ,float((5-currentLevel)*10));
                }
                }
        else if (currentState == GameState::MENU) {
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mainMenu.handleHover(mousePos);
                break;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                int clickedItem = mainMenu.checkMouseClick(mousePos);
                
                if (clickedItem != -1) {
                    mainMenu.clickSound.play();
                }

                if (clickedItem == 0) { 
                    currentState = GameState::PLAYING;
                } else if(clickedItem ==2){
                    resetGame();
                    currentState = GameState::PLAYING;
                }
                else if (clickedItem == 3) { 
                    window.close();
                }
                break;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up ) mainMenu.moveUP();
                else if (event.key.code == sf::Keyboard::Down) mainMenu.moveDOWN();
                else if (event.key.code == sf::Keyboard::Escape) {
                    mainMenu.clickSound.play();
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    mainMenu.clickSound.play();
                    int selected = mainMenu.getMenuPressed();
                    if(selected==0 ){
                        currentState = GameState::PLAYING;
                    }
                    else if (selected == 2) {
                        resetGame();
                        currentState = GameState::PLAYING;
                    }
                    else if (selected == 3) window.close();
                }
            }
        }
        else if (currentState == GameState::GAME_OVER) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    currentState = GameState::PLAYING;
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    resetGame();
                    currentState = GameState::MENU;
                }
            }
        }
    }
       
}


void Game::resetGame(){
    activeObstacles.clear();
    defenses.clear();
    heals.clear();
    Obstacle heal(&healTex,sf::Vector2f(10.f,10.f),sf::Vector2f(1000.f,700.f), -100.f,false , 0 );
    heals.push_back(heal);
    int newBossHealth = float(100 + (currentLevel * 100));
    student =Player(sf::Vector2f(100.f, 600.f), 200.f, 300);
    student.texture.loadFromFile("../assets/textures/Sadness.png");
    student.sprite.setTexture(student.texture);

    // boss = Boss(sf::Vector2f(100.f,100.f),sf::Vector2f(2950.f,500.f),newBossHealth );
    boss.reset(newBossHealth);
    render();
};  

void Game::run(){
while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        processEvent();
        update();
        render();
    }
    

}
void Game::update(){
 if (currentState == GameState::PLAYING) {
        Collider bossCol = boss.getCollider();
        sf::Vector2f direction;
        student.update(deltaTime,boss.getPosition());
        boss.update(deltaTime);
        Collider studentCol = student.getCollider();
        for(int i =0 ; i<heals.size();){
            Collider healCol = heals.at(i).getCollider();
            if(!heals[i].isDestroyed && studentCol.checkCollider(healCol ,direction, 0.0f)){
                heals[i].destroyObstacle();
                student.takeDamage(heals[i].damage);
            }else if(heals[i].isDestroyed){
                heals.erase(heals.begin()+i);
            }
            else{
                i++;
            }
        }
        if(boss.shouldThrowObstacle()){
            boss.attack(typeAttack::A , activeObstacles );
        }
        for (int i=0 ;i< activeObstacles.size();){
            activeObstacles.at(i).update(deltaTime);
            sf::Vector2f direction;
            Collider obstCol = activeObstacles[i].getCollider();
            if (!activeObstacles[i].isDestroyed && studentCol.checkCollider(obstCol, direction, 0.0f)) {
                activeObstacles[i].destroyObstacle();
                student.takeDamage(activeObstacles[i].damage);
                
            }else if (activeObstacles[i].isDestroyed) {
                activeObstacles.erase(activeObstacles.begin() + i);
            } else {
                i++; 
            }
        }for(int i=0;i<defenses.size();){
            defenses[i].update(deltaTime);
            sf::Vector2f direction;
            Collider obstCol = defenses[i].getCollider();
            if(!defenses[i].isDestroyed && bossCol.checkCollider(obstCol,direction,0.f)){
                defenses[i].destroyObstacle();
                boss.takeDamage(defenses[i].damage);

            }if (defenses[i].isDestroyed) {
                defenses.erase(defenses.begin() + i);
            } else {
                i++; 
            }
        }
        if(student.getCollider().checkCollider(  bossCol,direction,0.f)){
            if (direction.y == 1.f || direction.y == -1.f ) {
                boss.movingUp = false;
                student.takeDamage(10);
            } 
        }
        if(student.getHealth() <=0){
            currentState = GameState::GAME_OVER;
            gameOverMessage.setString("press enter to restart");
            gameOverMessage.setPosition(view.view.getCenter().x + 200.f, view.view.getCenter().y + 50.f);
        }
        if(boss.getHealth() <=0){
            currentState = GameState::LEVEL_COMPLETE;
            transitionTimer = 0.f;
            levelText.setString("Level " + std::to_string(currentLevel) + " Complete!\nLoading Level " + std::to_string(currentLevel + 1) + "...");
            levelText.setPosition(view.view.getCenter().x + 200.f, view.view.getCenter().y + 50.f);
                currentLevel++;
                resetGame();
        }
        if(student.canDefense){
            bgMusic.pause();
            fightingMusic.play();
        }else if(bgMusic.getStatus() == bgMusic.Playing){
            fightingMusic.pause();
            bgMusic.play();
        }
        view.setCenter(student.getPosition()); 
    }
    if (currentState == GameState::LEVEL_COMPLETE) {
        transitionTimer += deltaTime;
        if (transitionTimer > 3.0f) { 
            currentLevel++;
            resetGame();
            currentState = GameState::PLAYING;
        }
    }
}
void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(background); 
    if (currentState == GameState::MENU) {
        mainMenu.draw(window);
         window.setView(window.getDefaultView());
    } 
    else if (currentState == GameState::PLAYING) {
        window.setView(view.view); 
        student.draw(window);
        boss.draw(window);
        for (int i = 0; i < activeObstacles.size(); i++) {
            activeObstacles[i].draw(window);
        }
        for(int i=0;i<defenses.size();i++){
            defenses[i].draw(window);
        }
    }
    else if (currentState == GameState::LEVEL_COMPLETE) {
        window.clear(sf::Color::Black);
        window.setView(window.getDefaultView());
        window.draw(levelText);
    }
      else if (currentState == 
        GameState::GAME_OVER){
            window.clear(sf::Color::Black);
            window.setView(window.getDefaultView());
            window.draw(gameOverMessage);
        }

    window.display();
}