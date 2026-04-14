#include "../include/Game.hpp"
#include <cstdlib> 
#include <ctime>   

static const float WINDOW_WIDTH = 800.f , WINDOW_HEIGHT=600.f;



Game::Game( ): window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT) ,"GET THE DEUG" , sf::Style::Close |sf::Style::Resize )   , mainMenu(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT)),view(sf::Vector2f(WINDOW_WIDTH , WINDOW_HEIGHT) ) ,student( 200, 300),boss( sf::Vector2f(100.f,100.f),200 ){
    window.setFramerateLimit(60);

    if (!mainFont.loadFromFile("../assets/fonts/OpenSans-Bold.ttf")) {
        std::cout << "ERROR: Could not load font!\n";
    }else{
        levelText.setFont(mainFont);
        levelText.setCharacterSize(40);
        levelText.setFillColor(sf::Color::Green);

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
    if(!gameOverTex.loadFromFile("../assets/textures/game-over.png")){}else{
        gameOver.setTexture(&gameOverTex);
        gameOver.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    }
    bgTextures.resize(4);
    for (int i = 0; i < 4; i++) {
        if (!bgTextures[i].loadFromFile("../assets/textures/levelBackgrounds/School S" + std::to_string(i + 1) + ".png")) {
            std::cout << "ERROR: Could not load background texture " << (i + 1) << "!\n";
        } 
    }

        background.setTexture(&bgTextures[0]);
        background.setSize(sf::Vector2f(bgTextures[0].getSize().x, window.getSize().y));

    if(!gameFinishedTex.loadFromFile("../assets/textures/finished.png") ){
        std::cout << "ERROR: Could not load win texture " << std::endl;
    }else{
        gameFinished.setTexture(&gameFinishedTex);
        gameFinished.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    }
    obstacles.resize(4);

    

        student.groundHeight = 500.f;
        student.setPosition(sf::Vector2f(100.f, student.groundHeight));
        student.earthWidth = background.getLocalBounds().width;

        boss.setPosition(sf::Vector2f(background.getSize().x - 200.f,student.groundHeight));
        


    // not add textures yet
    //     srand(static_cast<unsigned>(time(NULL)));
    //     obstaclesTex.resize(4);
    //     for(int r =0;r<4;r++){
    //         obstaclesTex[r].resize(6);
    //         for(int c=0;c< 6;c++){
    //         if (!obstaclesTex[r][c].loadFromFile("../assets/textures/obstackes/lvl" + std::to_string(r + 1) + "/trap"+std::to_string(c + 1)+  ".png")) {
    //             // std::cout << "Error loading trap texture!\n";
    //         }else{

    //             // float randX = rand() % (700 -200 + 1) + 200 ;
                
    //             int maxY = static_cast<int>(student.groundHeight);
    //             int minY = static_cast<int>(student.groundHeight) - 200;
    //             float randY = rand() % (maxY - minY + 1) + minY;
                
    //             Obstacle trap(&obstaclesTex[r][c], sf::Vector2f(80.f,80.f ),sf::Vector2f(250.f + c* 250.f , randY), 0, false, 0);
                
    //             obstacles[r].push_back(trap);
    //         }
    //     }
    // }

    float randHealPosX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 500) - 300 +1) + 300;
    if (!healTex.loadFromFile("../assets/textures/attackes/lvl4/trap3.png")) {
        std::cout << "ERROR: Could not load heal texture!\n";
    }else{
        Obstacle heal(&healTex,sf::Vector2f(50.f,50.f),sf::Vector2f(randHealPosX,student.groundHeight), -150,false , 0 );
        heals.push_back(heal);
        currentState = GameState::MENU;
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
                mainMenu.clickSound.play();
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mainMenu.handleHover(mousePos);
                break;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mainMenu.clickSound.play();
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                int clickedItem = mainMenu.checkMouseClick(mousePos);
                
                if (clickedItem != -1) {
                    mainMenu.clickSound.play();
                }

                if (clickedItem == 0) { 
                    currentState = GameState::PLAYING;
                } else if(clickedItem ==1){
                    currentLevel = 1;
                    resetGame();
                    currentState = GameState::PLAYING;
                }
                else if (clickedItem == 2) { 
                    window.close();
                }
                break;
            }

            if (event.type == sf::Event::KeyPressed) {
                mainMenu.clickSound.play();
                if (event.key.code == sf::Keyboard::Up ) mainMenu.moveUP();
                else if (event.key.code == sf::Keyboard::Down) mainMenu.moveDOWN();
                else if (event.key.code == sf::Keyboard::Escape) {
                    // currentState = GameState::PLAYING;
                    break;
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = mainMenu.getMenuPressed();
                    if(selected==0 ){
                        currentState = GameState::PLAYING;
                    }
                    else if (selected == 1) {
                        currentLevel =1;
                        resetGame();
                        currentState = GameState::PLAYING;
                    }
                    else if (selected == 2) window.close();
                }
            }
        }
        else if (currentState==GameState::GET_DEUG&& event.key.code == sf::Keyboard::Escape) {
            mainMenu.clickSound.play();
            currentLevel=1;
                    resetGame();
                    currentState = GameState::MENU;
                }
        else if (currentState == GameState::GAME_OVER) {
            mainMenu.clickSound.play();
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


    background.setTexture(&bgTextures[currentLevel-1]);

    bossAttackes.clear();
    defenses.clear();
    heals.clear();

    float randHealPosX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 500) - 300 +1) + 300;
    Obstacle heal(&healTex,sf::Vector2f(50.f,50.f),sf::Vector2f(randHealPosX,student.groundHeight), -150,false , 0 );
    heals.push_back(heal);
    std::cout << healTex.getSize().y;

    int newBossHealth = float(100 + (currentLevel * 100));
    boss.healthBar.setMaxHealth(newBossHealth);
    boss.reset(newBossHealth);
    
    student.reset(200.f,300);
    student.setPosition(sf::Vector2f(100.f, student.groundHeight));
    
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

        sf::Vector2f direction;
        
        student.update(deltaTime,boss.getPosition());
        boss.update(deltaTime);
     
        Collider bossCol = boss.getCollider();
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
        
        //     int r = currentLevel - 1;

        //     if (r >= 0 && r < obstacles.size()) {
        //     for (int c = 0; c < obstacles[r].size(); c++) {
        //             Collider trapCol = obstacles[r][c].getCollider();
        //             if (studentCol.checkCollider(trapCol, direction, 0.f)) {
        //                 student.takeDamage(obstacles[r][c].damage);
        //                 if(direction.y ==1.f){
        //                     student.canJump =true;
        //                 }
        //             }
        //         }
        // }

        for (int i=0 ;i< bossAttackes.size();){
            bossAttackes.at(i).update(deltaTime);
            sf::Vector2f direction;
            Collider obstCol = bossAttackes[i].getCollider();
            if (!bossAttackes[i].isDestroyed && studentCol.checkCollider(obstCol, direction, 0.0f)) {
                bossAttackes[i].destroyObstacle();
                student.takeDamage(bossAttackes[i].damage*currentLevel+10);
            }else if (bossAttackes[i].isDestroyed) {
                bossAttackes.erase(bossAttackes.begin() + i);
            } else {
                i++; 
            }
        }

        for(int i=0;i<defenses.size();){
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

        if(boss.shouldThrowObstacle()){
            boss.attack(currentLevel, bossAttackes );
        }



        if(student.getCollider().checkCollider(  bossCol,direction,0.f)){
            if (direction.y == 1.f || direction.y == -1.f ) {
                student.takeDamage(5);
            } 
        }



        if(student.getHealth() <=0){
            currentLevel =1;
            currentState = GameState::GAME_OVER;
        }


        if(boss.getHealth() <=0){
            currentState = GameState::LEVEL_COMPLETE;
            transitionTimer = 0.f;
            levelText.setString("Level " + std::to_string(currentLevel) + " Complete!\nLoading Level " + std::to_string(currentLevel + 1) + "...");
            currentLevel++;
            levelText.setPosition(250.f, 250.f);
                if (currentLevel <= 4) {
                resetGame();
            } else {
                currentState = GameState::GET_DEUG;
            }
        }
        // if(student.canDefense){
        //      if(bgMusic.getStatus() == bgMusic.Playing){
        //          bgMusic.pause();
        //      }
        //     fightingMusic.play();
        // }else if(fightingMusic.getStatus() == fightingMusic.Playing){
        //     fightingMusic.pause();
        //     bgMusic.play();
        // }

        
        view.setCenter(student.getPosition());
        view.clampToBounds(background.getGlobalBounds().width,background.getGlobalBounds().height);
    }

    if(currentState ==GameState::MENU){
        mainMenu.update();
    }

    if (currentState == GameState::LEVEL_COMPLETE) {
        transitionTimer += deltaTime;
        if (transitionTimer > 3.0f) { 
            resetGame();
            currentState = GameState::PLAYING;
        }
    }
}

void Game::render() {
    
    if (currentState == GameState::MENU) {
        window.clear(sf::Color::Black);
        window.setView(window.getDefaultView());
        mainMenu.draw(window);
    } 
    else if (currentState == GameState::PLAYING) {
        

        window.clear(sf::Color::Black);
        window.setView(view.view); 
        window.draw(background);
        student.draw(window);
        boss.draw(window);
        for (int i = 0; i < bossAttackes.size(); i++) {
            bossAttackes[i].draw(window);
        }
        for (int i = 0; i < heals.size(); i++) {
            heals[i].draw(window);
        }
        for(int i=0;i<defenses.size();i++){
            defenses[i].draw(window);
        }

        // int r = currentLevel - 1;

        // if (r >= 0 && r < obstacles.size()) {
        //     for (int i = 0; i < obstacles[r].size(); i++) {
        //         obstacles[r][i].draw(window);
        //     }
        // }

    }
    else if (currentState == GameState::LEVEL_COMPLETE) {
        window.clear(sf::Color::Yellow);
        window.setView(window.getDefaultView());
        window.draw(levelText);
    }
      else if (currentState == 
        GameState::GAME_OVER){
            window.clear(sf::Color::Black);
            window.setView(window.getDefaultView());
            window.draw(gameOver);
        }
        else if(currentState == GameState::GET_DEUG){
            window.clear(sf::Color::Black);
            window.setView(window.getDefaultView());
            window.draw(gameFinished);
        }

    window.display();
}