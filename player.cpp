//
// Created by dcpre on 4/20/2021.
//

#include "player.h"

Player::Player(string name) {
    this->_name = name;
}

string Player::getName() const {
    return this->_name;
}

int Player::getHandSize() const {
    return this->_hand.size();
}

vector<Card> Player::getHand() const {
    return this->_hand;
}

bool Player::canPlay(const Card& cardToPlay, const Card& cardLastPlayed) {
    if (cardLastPlayed.getColor() == "BLACK") {
        if (cardToPlay.getColor() == "BLACK") return true;
        if (cardToPlay.getColor() == cardLastPlayed.getColorChoice()) return true;
    }
    else {
        if (cardToPlay.getColor() == "BLACK") return true;
        if (cardToPlay.getColor() == cardLastPlayed.getColor()) return true;
        if (cardToPlay.getNumber() == cardLastPlayed.getNumber()) return true;
    }
    return false;
}

void Player::drawCard(Deck& gameDeck) {
    Card cardToDraw = gameDeck.takeTopCardDrawPile();
    this->_hand.push_back(cardToDraw);
}

void Player::playCard(const Card& cardToPlay, Deck& gameDeck) {
    // Remove card from Player's hand.
    for (int i = 0; i < this->_hand.size(); i++) {
        Card currentCard = this->_hand.at(i);
        // Here we are searching for the card that is being played.
        if ((currentCard.getColor() == cardToPlay.getColor()) && (currentCard.getNumber() == cardToPlay.getNumber())) {

            // Add card to the end of discardPile.
            gameDeck.addTopCardDiscardPile(currentCard);
            this->_hand.erase(this->_hand.begin() + i);
            break;
        }
    }
}

bool Player::botTakeTurn(Deck &gameDeck) {
    Card lastCard = gameDeck.getTopCardDiscardPile();
    bool cardPlayed = false;
    // Iterate through _hand and test each card to see if it is playable. If so, play the card.
    for (int i = 0; i < this->_hand.size(); i++) {
        Card currentCard = this->_hand.at(i);
        if (canPlay(currentCard, lastCard)) {
            playCard(currentCard, gameDeck);
            cardPlayed = true;
            break;
        }
    }
    // If every card in the hand was checked and couldn't be played, the player must draw cards until they can play.
    if (!cardPlayed) {
        drawCard(gameDeck);
    }
    return cardPlayed;
}

bool Player::userTakeTurn(RenderWindow &window, Deck &gameDeck, GameWindow &graphics) {
    Card lastCard = gameDeck.getTopCardDiscardPile();
    bool cardPlayed = false;
    bool cardDrawn = false;
    Event event;
    //
    while ((!cardPlayed) && (!cardDrawn)) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                int cardNum = graphics.getPlayerInput(event.mouseButton.x, event.mouseButton.y);
                if (cardNum <= this->_hand.size()) {
                    switch (cardNum) {
                        case 0:
                            drawCard(gameDeck);
                            cardDrawn = true;
                            break;
                        case -1:
                            break;
                        default:
                            Card chosenCard = this->_hand.at(cardNum - 1);
                            if (canPlay(chosenCard, lastCard)) {
                                playCard(chosenCard, gameDeck);
                                cardPlayed = true;
                            }
                    }
                    if ((cardPlayed) || (cardDrawn)) break;
                }
            }
        }
    }
    return cardPlayed;
}

string Player::botChooseWildColor() const {
    // The wild card will be chosen based on which color appears the most in the player's hand.
    string colors[4] = {"RED", "YELLOW", "GREEN", "BLUE"};
    int cardsPerColor[4] = {0};
    for (int i = 0; i < this->_hand.size(); i++) {
        Card currentCard = this->_hand.at(i);
        if (currentCard.getColor() == "RED") cardsPerColor[0]++;
        else if (currentCard.getColor() == "YELLOW") cardsPerColor[1]++;
        else if (currentCard.getColor() == "GREEN") cardsPerColor[2]++;
        else if (currentCard.getColor() == "BLUE") cardsPerColor[3]++;
    }
    // Now we find the max value in cardsPerColor, and return the corresponding color.
    int mostCardsPerColor = cardsPerColor[0];
    int colorIndex = 0;
    for (int i = 1; i < 4; i++) {
        if (cardsPerColor[i] > mostCardsPerColor) {
            mostCardsPerColor = cardsPerColor[i];
            colorIndex = i;
        }
    }
    return colors[colorIndex];
}