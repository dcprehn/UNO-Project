//
// Created by dcpre on 5/1/2021.
//

#include "gamewindow.h"

Font GameWindow::_font;
Ellipse GameWindow::_UNOLabel(Vector2f(15, 10));
Texture GameWindow::_UNOSprites;

void GameWindow::LoadAssets() {
    if (!_font.loadFromFile("./data/orbitron.ttf")) {
        cerr << "Error: Font could not be loaded." << endl;
    }
    if (!_UNOSprites.loadFromFile("./data/UNOSprites.png")) {
        cerr << "Error: Sprites could not be loaded." << endl;
    }
    _UNOLabel.setTextureRect(IntRect(3, 171, 30, 16));
    _UNOLabel.setTexture(&_UNOSprites);
    _UNOLabel.setScale(2, 2);
}

GameWindow::GameWindow() {
    customizeText(&_title, "Game Board", Color::Cyan, Vector2f(305, 5));

    const Color COLORS[5] = {Color::White, Color::Red, Color::Blue, Color::Yellow, Color::Green};
    const float POSITIONS[5][2] = {{305, 380}, {5, 380}, {5, 5}, {705, 5}, {705, 380}};

    ifstream dataIn;
    dataIn.open("./data/gameInfo.txt");
    if (dataIn.fail()) {
        cerr << "Error: Game Data could not be processed." << endl;
    }
    int numPlayers;
    dataIn >> numPlayers;
    string garbage;
    getline(dataIn, garbage);

    for (int i = 0; i < numPlayers; i++) {
        RectangleShape currentRect;
        currentRect.setPosition(POSITIONS[i][0], POSITIONS[i][1]);
        currentRect.setFillColor(Color::Transparent);
        currentRect.setOutlineThickness(5);
        currentRect.setOutlineColor(COLORS[i]);

        vector<Vector2f> currentCardLocations;
        float cardX = POSITIONS[i][0] + 5;
        float cardY = POSITIONS[i][1] + 50;
        if (i == 0) {
            currentRect.setSize(Vector2f(390, 365));
            /*
             * Every card must be entirely within the _playerWindow and there will be 10 pixels in between each card
             * on all sides. The user's window is 400 pixels wide and the first card position is 5 pixels inside the
             * left edge of the _playerWindow. Once a card is set to overlap the right edge of the _playerWindow,
             * the x position is reset and the y position increases.
             */
            for (int j = 0; j < 15; j++) {
                currentCardLocations.emplace_back(cardX, cardY);
                cardX += _CARD_WIDTH + 10;
                if (cardX > POSITIONS[i][0] + 395 - _CARD_WIDTH) {
                    cardX = POSITIONS[i][0] + 5;
                    cardY += _CARD_HEIGHT + 10;
                }
            }
        }
        else {
            /* The card locations for the bots works very similar, except they have smaller windows of only 300 pixels
             * wide. This also limits the number of displayable cards to 12, instead of 15 for the user.
             */
            currentRect.setSize(Vector2f(290, 365));
            for (int j = 0; j < 12; j++) {
                currentCardLocations.emplace_back(cardX, cardY);
                cardX += _CARD_WIDTH + 10;
                if (cardX > POSITIONS[i][0] + 295 - _CARD_WIDTH) {
                    cardX = POSITIONS[i][0] + 5;
                    cardY += _CARD_HEIGHT + 10;
                }
            }
        }


        Text currentText;
        currentText.setFont(_font);
        string playerName;
        getline(dataIn, playerName);
        currentText.setString(playerName);
        currentText.setFillColor(COLORS[i]);
        currentText.setPosition((POSITIONS[i][0] + 5), (POSITIONS[i][1] + 5));

        _playerData currentPlayerData;
        currentPlayerData._playerWindow = currentRect;
        currentPlayerData._playerText = currentText;
        currentPlayerData._cardLocations = currentCardLocations;

        _playerGraphics.push_back(currentPlayerData);
    }
    _discardLocation = {390, 55};
    _drawLocation = {514, 55};
}

int GameWindow::getPlayerInput(float mouseX, float mouseY) const {
    int cardNumber = -1;
    if ((mouseX >= _drawLocation.x && mouseX <= (_drawLocation.x + 96) ) && (mouseY >= _drawLocation.y && mouseY <= (_drawLocation.y + 152))) {
        cardNumber = 0;
    }
    else {
        const int NUM_ROWS = 3;
        const int NUM_COLS = 5;
        int row = 0, column = 0;
        float xPos = 330;
        float yPos = 430;
        for (int i = 0; i < NUM_COLS; i++) {
            if ((mouseX >= xPos) && (mouseX <= xPos + _CARD_WIDTH)) {
                column = i + 1;
                break;
            }
            xPos += _CARD_WIDTH + 10;
        }
        for (int i = 0; i < NUM_ROWS; i++) {
            if ((mouseY >= yPos) && (mouseY <= yPos + _CARD_HEIGHT)) {
                row = i + 1;
                break;
            }
            yPos += _CARD_HEIGHT + 10;
        }
        if ((row > 0) && (column > 0)) {
            cardNumber = column + (row - 1) * NUM_COLS;
        }
    }
    return cardNumber;
}

void GameWindow::customizeText(Text* text, const string& textToDisplay, Color color, Vector2f position, int fontSize) {
    text->setFont(_font);
    text->setCharacterSize(fontSize);
    text->setString(textToDisplay);
    text->setFillColor(color);
    text->setPosition(position);
}

void GameWindow::customizeSprite(Sprite* sprite, Vector2f position, Vector2f scale) {
    sprite->setPosition(position);
    sprite->setScale(scale);
}

void GameWindow::renderPlayerGraphics(RenderWindow& window) {
    for (int i = 0; i < this->_playerGraphics.size(); i++) {
        window.draw(this->_title);
        window.draw(this->_playerGraphics.at(i)._playerWindow);
        window.draw(this->_playerGraphics.at(i)._playerText);
    }
}

void GameWindow::renderGameDeck(RenderWindow &window, const Deck& gameDeck, bool wildColorChosen) {
    Sprite drawPile = Card::getUNOCardSprite();
    customizeSprite(&drawPile, _drawLocation, Vector2f(4, 4));
    window.draw(drawPile);
    Sprite discardPile;
    if (wildColorChosen) {
        discardPile = gameDeck.getTopCardDiscardPile().getWildSprite();
    }
    else {
        discardPile = gameDeck.getTopCardDiscardPile().getCardSprite();
    }
    customizeSprite(&discardPile, _discardLocation, Vector2f(4, 4));
    window.draw(discardPile);
    Text drawCount;
    customizeText(&drawCount, to_string(gameDeck.getDrawPileSize()), Color::Cyan, Vector2f(514, 212));
    window.draw(drawCount);
    Text discardCount;
    customizeText(&discardCount, to_string(gameDeck.getDiscardPileSize()), Color::Cyan, Vector2f(390, 212));
    window.draw(discardCount);
}


void GameWindow::renderPlayerHand(RenderWindow& window, const vector<Card>& hand, int playerIndex) const {
    if (hand.size() == 1) {
        Ellipse UNO = _UNOLabel;
        Vector2f cardLocation = this->_playerGraphics.at(playerIndex)._cardLocations.at(0);
        UNO.setPosition(cardLocation.x, cardLocation.y + 270);
        window.draw(UNO);
    }
    int numCardsVisible;
    if (playerIndex == 0) {
        numCardsVisible = (hand.size() < 15) ? hand.size() : 15;
        for (int i = 0; i < numCardsVisible; i++){
            Sprite currentSprite = hand.at(i).getCardSprite();
            currentSprite.setPosition(this->_playerGraphics.at(playerIndex)._cardLocations.at(i));
            window.draw(currentSprite);
        }
    }
    else {
        numCardsVisible = (hand.size() < 12) ? hand.size(): 12;
        for (int i = 0; i < numCardsVisible; i++) {
            Sprite currentSprite = Card::getUNOCardSprite();
            currentSprite.setPosition(this->_playerGraphics.at(playerIndex)._cardLocations.at(i));
            window.draw(currentSprite);
        }
    }
}


string GameWindow::renderWildOptions(RenderWindow &window) {
    RectangleShape wildRect;
    wildRect.setPosition(Vector2f(300, 0));
    wildRect.setSize(Vector2f(400, 375));
    wildRect.setFillColor(Color::Black);
    window.draw(wildRect);
    const Color COLORS[4] = {Color::Red, Color::Blue, Color::Yellow, Color::Green};
    const float POSITIONS[4][2] = {{300, 75}, {500, 75}, {300, 225}, {500, 225}};
    float colorSizeX = 200;
    float colorSizeY = 150;
    for (int i = 0; i < 4; i++) {
        RectangleShape colorRect;
        colorRect.setPosition(POSITIONS[i][0], POSITIONS[i][1]);
        colorRect.setFillColor(COLORS[i]);
        colorRect.setSize(Vector2f(colorSizeX, colorSizeY));
        window.draw(colorRect);
    }
    Text colorPrompt;
    customizeText(&colorPrompt, "Choose a color:", Color::Magenta, Vector2f(305, 5), 20);
    window.draw(colorPrompt);
    window.display();
    // Wait for user to choose color by clicking one of the color rectangles.
    Event event;
    string chosenColor;
    while (chosenColor.empty()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonPressed) {
                if ((event.mouseButton.x > POSITIONS[0][0]) && (event.mouseButton.x < POSITIONS[0][0] + colorSizeX) &&
                    (event.mouseButton.y > POSITIONS[0][1]) && (event.mouseButton.y < POSITIONS[0][1] + colorSizeY)) {
                    chosenColor = "RED";
                }
                else if ((event.mouseButton.x > POSITIONS[1][0]) && (event.mouseButton.x < POSITIONS[1][0] + colorSizeX) &&
                         (event.mouseButton.y > POSITIONS[1][1]) && (event.mouseButton.y < POSITIONS[1][1] + colorSizeY)) {
                    chosenColor = "BLUE";
                }
                else if ((event.mouseButton.x > POSITIONS[2][0]) && (event.mouseButton.x < POSITIONS[2][0] + colorSizeX) &&
                         (event.mouseButton.y > POSITIONS[2][1]) && (event.mouseButton.y < POSITIONS[2][1] + colorSizeY)) {
                    chosenColor = "YELLOW";
                }
                else if ((event.mouseButton.x > POSITIONS[3][0]) && (event.mouseButton.x < POSITIONS[3][0] + colorSizeX) &&
                         (event.mouseButton.y > POSITIONS[3][1]) && (event.mouseButton.y < POSITIONS[3][1] + colorSizeY)) {
                    chosenColor = "GREEN";
                }
            }
        }
    }
    return chosenColor;
}

void GameWindow::renderIntro(RenderWindow &window, string name) {
    Text greeting;
    string textToDisplay = "Welcome to UNO, " + name + "!";
    customizeText(&greeting, textToDisplay, Color::Cyan, Vector2f(305, 320), 20);
    window.draw(greeting);
    Text instruction;
    textToDisplay = "Click anywhere to begin!";
    customizeText(&instruction, textToDisplay, Color::Cyan, Vector2f(305, 350), 20);
    window.draw(instruction);
}

void GameWindow::renderMoveDescription(RenderWindow &window, string name) {
    Text moveDescription;
    string textToDisplay = name + " had to draw a card.";
    customizeText(&moveDescription, textToDisplay, Color::Cyan, Vector2f(305, 320), 20);
    window.draw(moveDescription);
}

void GameWindow::renderMoveDescription(RenderWindow &window, string name, const Card &cardPlayed) {
    Text moveDescription;
    string textToDisplay = name + " played a " + cardPlayed.getCardString() + ".";
    customizeText(&moveDescription, textToDisplay, Color::Cyan, Vector2f(305, 320), 20);
    window.draw(moveDescription);
}

void GameWindow::renderMoveDescription(RenderWindow &window, string name, string colorChoice) {
    Text wildChoice;
    string textToDisplay = name + " chose " + colorChoice + "!";
    customizeText(&wildChoice, textToDisplay, Color::Cyan, Vector2f(305, 320), 20);
    window.draw(wildChoice);
}

void GameWindow::renderUserPrompt(RenderWindow &window) {
    Text userPrompt;
    string textToDisplay = "Your turn! Click on a card to play it.";
    customizeText(&userPrompt, textToDisplay, Color::Cyan, Vector2f(305, 350), 20);
    window.draw(userPrompt);
}
