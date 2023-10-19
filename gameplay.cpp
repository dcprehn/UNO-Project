//
// Created by dcpre on 4/20/2021.
//

#include "gameplay.h"

Gameplay::Gameplay() {
    this->_window.create(VideoMode(1000, 750), "UNO!");
    this->_window.setFramerateLimit(60);
    this->_gameOver = false;
    this->_winner = "None";
    this->_turnNumber = 0;
    this->_turnIndex = 0;
    this->_indexIncrementer = 1;
    this->_wildColorChosen = false;
}

void Gameplay::addPlayers() {
    ifstream gameIn;
    gameIn.open("./data/gameInfo.txt");
    if (gameIn.fail()) {
        cerr << "Error: Game Data could not be processed." << endl;
    }
    int numPlayers;
    gameIn >> numPlayers;
    string garbage;
    getline(gameIn, garbage);
    // Add up to 5 Player objects to the vector of players. The first of these will be the user, who will input their name.
    string playerName;
    for (int i = 0; i < numPlayers; i++) {
        getline(gameIn, playerName);
        this->_players.emplace_back(new Player(playerName));
    }
    gameIn.close();
}

void Gameplay::dealHands() {
    // A standard game of UNO starts with each player being dealt 7 cards.
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < this->_players.size(); j++) {
            (this->_players.at(j))->drawCard(this->_gameDeck);
        }
    }
}

void Gameplay::firstTurn() {
    // Render main graphics along with intro.
    this->_window.clear(Color::Black);
    renderMainGraphics();
    this->_graphics.renderIntro(this->_window, this->_players.at(0)->getName());
    this->_window.display();
    // Wait for user to open window and read the introduction.
    Event event;
    while (this->_window.waitEvent(event)) {
        if (event.type == Event::MouseButtonPressed) {
            cout << "Good Luck!" << endl;
            break;
        }
    }
    // Refresh window.
    this->_window.clear(Color::Black);
    renderMainGraphics();
    // Check to see if the top card of the discard pile is a special card.
    Card firstCard = this->_gameDeck.getTopCardDiscardPile();
    if (firstCard.getNumber() > 9) {
        // If so, it will be treated as though Bot 4 played it, meaning _turnIndex is modified.
        this->_turnIndex = this->_players.size() - 1;
        // Determine what special card was played.
        specialCard(firstCard);
        // Increment _turnIndex.
        this->_turnIndex = getNextTurnIndex();
    }
    this->_graphics.renderMoveDescription(this->_window, "The Dealer", this->_gameDeck.getTopCardDiscardPile());
    this->_window.display();
//    sleep(Time(seconds(1)));
}
void Gameplay::specialCard(Card& cardPlayed) {
    switch (cardPlayed.getNumber()) {
        case 10:
            reverse();
            break;
        case 11:
            skip();
            break;
        case 12:
            drawTwo();
            break;
        case 13:
            wild();
            break;
        case 14:
            wildDrawFour();
            break;
        default:
            cerr << "Something went wrong. Card value is greater than 14.";
    }
}

void Gameplay::drawTwo() {
    // Make the next player draw two cards. i is the affected player's index.
    int i = getNextTurnIndex();
    (this->_players.at(i))->drawCard(this->_gameDeck);
    (this->_players.at(i))->drawCard(this->_gameDeck);
    // Skip the player's turn.
    this->_turnIndex = getNextTurnIndex();
}

void Gameplay::reverse() {
    this->_indexIncrementer *= -1;
}

void Gameplay::skip() {
    // Skip the affected player's turn.
    this->_turnIndex = getNextTurnIndex();
}

void Gameplay::wild() {
    // Display the wild card description and pause for a few seconds before determining the chosen color.
    this->_graphics.renderMoveDescription(this->_window, this->_players.at(this->_turnIndex)->getName(), this->_gameDeck.getTopCardDiscardPile());
    this->_window.display();
//    sleep(Time(seconds(1)));
    // Clear the window and render the main graphics again.
    this->_window.clear();
    renderMainGraphics();
    // The player who plays the wild gets to choose what color they want.
    string chosenColor;
    if (this->_turnIndex == 0) {
        chosenColor = this->_graphics.renderWildOptions(this->_window);
    }
    else {
        chosenColor = (this->_players.at(this->_turnIndex))->botChooseWildColor();
    }
    // Set the wild card color and reset the window again, rendering the move description of the color chosen.
    this->_gameDeck.setWildColor(chosenColor);
    this->_wildColorChosen = true;
    this->_window.clear();
    renderMainGraphics();
    this->_graphics.renderMoveDescription(this->_window, this->_players.at(this->_turnIndex)->getName(), chosenColor);
}

void Gameplay::wildDrawFour() {
    // In addition to a normal wild, the next player must draw four cards and their turn is skipped.
    wild();
    int i = getNextTurnIndex();
    for (int j = 0; j < 4; j++) {
        (this->_players.at(i))->drawCard(this->_gameDeck);
    }
    this->_turnIndex = getNextTurnIndex();
}

int Gameplay::getNextTurnIndex() {
    int i; // Next turn index
    i = (this->_turnIndex + this->_indexIncrementer);
    if (i < 0) {  // Turn index could become negative due to reverses.
        i += this->_players.size();
    }
    i %= this->_players.size();
    return i;
}



void Gameplay::playUNO() {
    addPlayers();
    this->_gameDeck.shuffle();
    dealHands();
    Event event;
    // Game loop continues until _gameOver is true.
    while (!this->_gameOver) {
        // At the start of the game, the user is notified that it is their turn, and that they play a card by clicking it.
        if (this->_turnNumber == 0) {
            firstTurn();
        }
        this->_window.clear(Color::Black);
        renderMainGraphics();
        // If it's the user turn, notify them that it is their turn.
        if (this->_turnIndex == 0)
            this->_graphics.renderUserPrompt(this->_window);
        this->_window.display();
        // currentPlayer is determined based on what _turnIndex is.
        Player* currentPlayer = this->_players.at(this->_turnIndex);
        // currentPlayer takes their turn, either playing or drawing a card.
        bool cardWasPlayed;
        if (this->_turnIndex != 0) {
            cardWasPlayed = currentPlayer->botTakeTurn(this->_gameDeck);
        }
        else {
            cardWasPlayed = currentPlayer->userTakeTurn(this->_window, this->_gameDeck, this->_graphics);
        }

        // Check to see if the player who took their turn just won.
        if (currentPlayer->getHandSize() == 0) {
            this->_gameOver = true;
            this->_winner = currentPlayer->getName();
        }
        /*
         * If they played a card, the card number is determined and checked to see if a special card was played (Reverse,
         * Draw Two, Wild, etc). If so, then the corresponding function is called.
         */
        if (cardWasPlayed) {
            this->_wildColorChosen = false;
            this->_window.clear();
            renderMainGraphics();
            Card cardPlayed = this->_gameDeck.getTopCardDiscardPile();
            // Check to see if a special card was played, ie if the top of the discard pile has a value greater than 9.
            if (cardPlayed.getNumber() > 9) {
                specialCard(cardPlayed);
            }
            // the wild() function renders its own description, whereas every other card does not.
            if ((cardPlayed.getNumber() != 13) && (cardPlayed.getNumber() != 14)) {
                this->_graphics.renderMoveDescription(this->_window, currentPlayer->getName(), this->_gameDeck.getTopCardDiscardPile());
            }
        }
        else {
            this->_window.clear();
            renderMainGraphics();
            this->_graphics.renderMoveDescription(this->_window, currentPlayer->getName());
        }
        this->_window.display();
//        sleep(Time(seconds(1)));
        // Increment turn Index and turn Number.
        if (cardWasPlayed) {
            this->_turnIndex = getNextTurnIndex();
            this->_turnNumber++;
        }
        // Check to see if window was closed.
        while (this->_window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                this->_window.close();
            }
        }
    }
    cout << "What an amazing game of UNO!" << endl;
    cout << "Congratulations, " << this->_winner << ", you WON!!!" << endl;

}

void Gameplay::renderMainGraphics() {
    this->_graphics.renderPlayerGraphics(this->_window);
    this->_graphics.renderGameDeck(this->_window, this->_gameDeck, this->_wildColorChosen);
    for (int i = 0; i < this->_players.size(); i++) {
        this->_graphics.renderPlayerHand(this->_window, this->_players.at(i)->getHand(), i);
    }
}
