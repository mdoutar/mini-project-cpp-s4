#include "../include/Game.hpp"
#include <cstdlib> 
#include <ctime>   

static const float WINDOW_WIDTH = 800.f , WINDOW_HEIGHT=600.f, MUSIC_VOLUME = 20.f,STUDENT_HEALTH = 200.f ,STUDENT_STARTED_POSX =100.f , DISTANCE_BTN_OBTSCLS = 50.F ;
static const int   STUDENT_SPEED =300, BOSS_STARTED_HEALTH = 200; 


Game::Game( ): window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT) ,"GET THE DEUG" , sf::Style::Close |sf::Style::Resize )   , mainMenu(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT)),view(sf::Vector2f(WINDOW_WIDTH , WINDOW_HEIGHT) ) ,student( STUDENT_HEALTH,STUDENT_SPEED),boss( BOSS_STARTED_HEALTH   ){
    window.setFramerateLimit(60);
    bool positionOccupied;
    reservedSpacesX.reserve(15);

    if (  !bgMusic.openFromFile("../assets/audios/background_music.mp3") ) {
            std::cout << "ERROR: Could not load background music!\n";
    }else{
            bgMusic.setLoop(true);
            bgMusic.setVolume(MUSIC_VOLUME);
            bgMusic.play(); 
    }
    if (  !fightingMusic.openFromFile("../assets/fighting_theme.ogg") ) {
            std::cout << "ERROR: Could not load fighting music!\n";
    }else{
            fightingMusic.setLoop(true);
            fightingMusic.setVolume(MUSIC_VOLUME);
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

    if(!gameFinishedTex.loadFromFile("../assets/textures/levelComplete/finished.png") ){
        std::cout << "ERROR: Could not load win texture " << std::endl;
    }else{
        gameFinished.setTexture(&gameFinishedTex);
        gameFinished.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    }
    student.groundHeight = 500.f;
    student.setPosition(sf::Vector2f(STUDENT_STARTED_POSX, student.groundHeight));
    student.earthWidth = background.getLocalBounds().width;
    
    boss.setPosition(sf::Vector2f(background.getSize().x - 200.f,student.groundHeight));
    
    
        obstacles.resize(4);
        srand(static_cast<unsigned>(time(NULL)));
        obstaclesTex.resize(4);
        float randX;
        for(int r =0;r<4;r++){
            obstaclesTex[r].resize(1);
            for(int c=0;c< obstaclesTex[r].size();c++){
            if (!obstaclesTex[r][c].loadFromFile("../assets/textures/obstacles/lvl" + std::to_string(r + 1) + "/obstacle"+std::to_string(c + 1)+  ".png")) {
                std::cout << "Error loading obstacle " << r << c <<" texture!\n";
            }else{
                do{
                    positionOccupied = false;
                    randX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 1000) - 300 +1) + 300;
                    for (float reservedSpace : reservedSpacesX){
                    if (std::abs(randX - reservedSpace) < DISTANCE_BTN_OBTSCLS) {
                        positionOccupied = true;
                        break;
                    }
                }
                }while(positionOccupied);
                Obstacle obstacle(&obstaclesTex[r][c], sf::Vector2f(200.f,150.f ),sf::Vector2f(randX , student.groundHeight), 0, false, 0);
                obstacles[r].push_back(obstacle);
                reservedSpacesX.push_back(randX );
            }
        }
    }
    float randHealPosX;
    
    healsTex.resize(4);
    for(int i(0); i<healsTex.size() ;i++ ){
        if (!healsTex[i].loadFromFile("../assets/textures/heals/heal"+std::to_string(i+1)+".png")) {
            std::cout << "ERROR: Could not load heal" << i+1 <<"texture!\n";
        }else{
            do{
                positionOccupied = false;
                randHealPosX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 500) - 300 +1) + 300;
                for (float reservedSpace : reservedSpacesX){
                   if (std::abs(randHealPosX  - reservedSpace) < DISTANCE_BTN_OBTSCLS) {
                    positionOccupied = true;
                    break;
                   }
               }
            }while(positionOccupied);
            Obstacle heal(&healsTex[i],sf::Vector2f(healsTex[i].getSize().x/2,healsTex[i].getSize().y/2),sf::Vector2f(randHealPosX,student.groundHeight), -150,false , 0 );
            heals.push_back(heal);
            reservedSpacesX.push_back(randHealPosX) ;
        }
    }
    levelCompleteBg.resize(3);
    levelCompleteBgTex.resize(3);
    for(int i(0); i<levelCompleteBgTex.size();i++){
        if(!levelCompleteBgTex[i].loadFromFile("../assets/textures/levelComplete/level"+std::to_string(i+1)+"Passed.png")){
            std::cout << "Error loading level complete background" << i+1 <<" texture!\n";
        }else{
            levelCompleteBg[i].setTexture(&levelCompleteBgTex[i]);
            levelCompleteBg[i].setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
        }
    }
    currentState = GameState::MENU;

    if(!muteOffTex.loadFromFile("../assets/textures/music_off.png")){
        std::cout << "Could not load mute off texture" ;
    }
    if(!muteOnTex.loadFromFile("../assets/textures/music_on.png")){
        std::cout << "Could not load mute on texture" ;
    }
    muteButton.setTexture(muteOnTex);
    muteButton.setPosition(sf::Vector2f(10.f,50.f));
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
            if (event.type == sf::Event::KeyPressed){

                if( event.key.code == sf::Keyboard::Escape ) {
                    mainMenu.clickSound.play();
                    currentState= GameState::MENU;
                }
                else if( student.canDefense &&((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) ||  (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right))){
                    student.defense(defenses ,float((5-currentLevel)*10) , currentLevel);
                }
            }
        }
        else if (currentState == GameState::MENU) {
            
            if (event.type == sf::Event::MouseMoved) {
                // mainMenu.clickSound.play();
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mainMenu.handleHover(mousePos);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
                if (event.key.code == sf::Keyboard::Up ) mainMenu.moveUP();
                else if (event.key.code == sf::Keyboard::Down) mainMenu.moveDOWN();
                else if (event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::PLAYING;
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
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (muteButton.getGlobalBounds().contains(mousePos)) {
            muted =!muted;
        }
        if(student.canDefense){
              if(bgMusic.getStatus() == bgMusic.Playing){
                  bgMusic.pause();
              }
             fightingMusic.play();
         }else if(fightingMusic.getStatus() == fightingMusic.Playing){
             fightingMusic.pause();
             bgMusic.play();
         }
     if(muted){
         bgMusic.pause();
         muteButton.setTexture(muteOffTex);
     }else{
         bgMusic.play();
         muteButton.setTexture(muteOnTex);
     }
    }
}


void Game::resetGame(){


    background.setTexture(&bgTextures[currentLevel-1]);

    bossAttackes.clear();
    defenses.clear();
    // heals.clear();
    reservedSpacesX.clear();
    reservedSpacesX.reserve(15);
    bool  positionOccupied;
    float randHealPosX;
    for(int i(0); i < heals.size() ;i++ ){
          do{
                positionOccupied = false;
                randHealPosX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 500) - 300 +1) + 300;
                for (float reservedSpace : reservedSpacesX){
                   if (std::abs(randHealPosX  - reservedSpace) < DISTANCE_BTN_OBTSCLS) {
                    positionOccupied = true;
                    break;
                   }
               }
            }while(positionOccupied);
        heals[i].isDestroyed = false;
        heals[i].obstacle.setPosition(sf::Vector2f(randHealPosX,student.groundHeight));
        reservedSpacesX.push_back(randHealPosX );
    }

    int newBossHealth = float(100 + (currentLevel * 100));
    boss.healthBar.setMaxHealth(newBossHealth);
    boss.reset(newBossHealth);
    float randX;
    for(int r(0); r<obstacles.size(); r++){
        for(int c(0) ; c<obstacles[r].size(); c++){
              do{
                positionOccupied = false;
                randX = rand() % ((static_cast<int>(background.getGlobalBounds().width) - 1000) - 300 +1) + 300;
                for (float reservedSpace : reservedSpacesX){
                   if (std::abs(randX - reservedSpace) < DISTANCE_BTN_OBTSCLS) {
                    positionOccupied = true;
                    break;
                   }
               }
            }while(positionOccupied);
            obstacles[r][c].obstacle.setPosition(sf::Vector2f(randX , student.groundHeight));
            reservedSpacesX.push_back(randX );
        }
    }
    
    student.reset(STUDENT_HEALTH,STUDENT_SPEED);
    student.setPosition(sf::Vector2f(STUDENT_STARTED_POSX, student.groundHeight));
    
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
     
 
        

        int r = currentLevel - 1;

            if (r >= 0 && r < obstacles.size()) {
            for (int c = 0; c < obstacles[r].size(); c++) {
                    Collider obstacleCol = obstacles[r][c].getCollider();
                    
                     if (studentCol.checkCollider(obstacleCol, direction, -1.f)) {
                         student.takeDamage(obstacles[r][c].damage);
                         if(direction.y ==1.f){
                             student.canJump =true;
                             student.canCrouch=true;
                             student.velocity.y = 0.f;
                             optShake = obstacleCol.getPosition().x;
                            }
                        }
                        if (direction.y == 0.f && std::abs(optShake - obstacleCol.getPosition().x) < 3.f && std::abs(student.groundHeight - student.getPosition().y) < 3.f ) {
                            optShake = 1.f; 
                        }
                }
            }
        
            if (r >= 0 && r < heals.size()) {
                Collider healCol = heals.at(r).getCollider();
                if(!heals[r].isDestroyed && studentCol.checkCollider(healCol ,direction, 0.0f)){
                    student.takeDamage(heals[r].damage);
                    student.canJump = true;
                    heals[r].destroyObstacle();
                }else if(heals[r].isDestroyed){
                    heals[r].obstacle.setPosition(-1000.f,-1000.0f);
                }
            }
        for (int i=0 ;i< bossAttackes.size();){
            bossAttackes.at(i).update(deltaTime);
            sf::Vector2f direction;
            Collider attackCol = bossAttackes[i].getCollider();
                        if (r >= 0 && r < obstacles.size()) {
                            for (int c = 0; c < obstacles[r].size(); c++) {
                                Collider curObsCol = obstacles[r][c].getCollider();
                                if(!bossAttackes[i].isDestroyed && curObsCol.checkCollider(attackCol, direction, 1.f)){
                                    bossAttackes[i].destroyObstacle();
                                    
                                }
                            }
                        }
            if (!bossAttackes[i].isDestroyed && studentCol.checkCollider(attackCol, direction, 0.0f)) {
                bossAttackes[i].destroyObstacle();
                student.takeDamage(bossAttackes[i].damage*currentLevel+10);
                // shakeTime = 0.3f;
            }
            else if (bossAttackes[i].isDestroyed) {
                bossAttackes.erase(bossAttackes.begin() + i);
            } else {
                i++; 
            }
        }
        for(int i=0; i < defenses.size(); ){
            defenses[i].update(deltaTime);
            sf::Vector2f direction;
            Collider defenseCol = defenses[i].getCollider();
            
            for (int c = 0; c < obstacles[r].size(); c++){
                Collider obstCol = obstacles[r][c].getCollider();
                if(!defenses[i].isDestroyed && obstCol.checkCollider(defenseCol, direction, 1.f)){
                    defenses[i].destroyObstacle(); 
                    // obstacles[r][c].destroyObstacle();
                }
            }
            
            if(!defenses[i].isDestroyed && bossCol.checkCollider(defenseCol, direction, 0.f)){
                defenses[i].destroyObstacle();
                boss.takeDamage(defenses[i].damage);
            }

            if (defenses[i].isDestroyed) {
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
            if(currentLevel == 4){
            currentState = GameState::GET_DEUG;
            }else{
                currentState = GameState::LEVEL_COMPLETE;
                transitionTimer = 0.f;                    
            }
        }
 

        
        view.setCenter(student.getPosition());
        view.clampToBounds(background.getGlobalBounds().width,background.getGlobalBounds().height);
        if(optShake ==1.f){
            shakeTime = 0.3f;
            optShake = 0.f;
        }
        shakeView();

    }

    if(currentState ==GameState::MENU){
        mainMenu.update();
    }

    if (currentState == GameState::LEVEL_COMPLETE) {
        
        transitionTimer += deltaTime;
        if (transitionTimer > 3.0f) { 
            if (currentLevel < 4) {
                currentLevel++;
                resetGame();
                currentState = GameState::PLAYING;
            } else {
                currentState = GameState::GET_DEUG;
            }
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
        
        
        for(int i=0;i<defenses.size();i++){
            defenses[i].draw(window);
        }
        
        int r = currentLevel - 1;
        
        if (r >= 0 && r < obstacles.size()) {
            for (int i = 0; i < obstacles[r].size(); i++) {
                if(obstacles[r][i].obstacle.getGlobalBounds().width > 0){
                    obstacles[r][i].draw(window);
                }
            }
        }
        if (r >= 0 && r < heals.size()) {
            heals[r].draw(window);
        }

    }
    else if (currentState == GameState::LEVEL_COMPLETE) {
        window.clear(sf::Color::Black);
        window.setView(window.getDefaultView());
        
        int bgIndex = currentLevel - 1;
        if(bgIndex >= 0 && bgIndex < levelCompleteBg.size()){
            window.draw(levelCompleteBg[bgIndex]);
        }
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
        window.setView(window.getDefaultView());
    window.draw(muteButton);
    window.display();
}

void Game::shakeView(){
    if (shakeTime <= 0.f) {
        return; 
    }
    float shakeX = static_cast<float>((rand() % 7) - 5);
    float shakeY = static_cast<float>((rand() % 7) - 5);

    view.view.move(shakeX, shakeY);
    shakeTime -= deltaTime;
}