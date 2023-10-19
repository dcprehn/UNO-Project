//
// Created by dcpre on 4/19/2021.
//

#include "deck.h"

Deck::Deck() {
    /*
     * UNO deck contents:
     * 76 number cards (one 0 of each color, two of 1-9 of each color);
     * 8 Draw Two (2 of each color);
     * 8 Reverse (2 of each color);
     * 8 Skip (2 of each color);
     * 4 Wild Cards
     * 4 Wild Draw Fours
     * 108 cards total
     */
    // Add wilds. Normal wild has value of 13, Draw 4 wild has value of 14.
    for (int i = 0; i < 4; i++) {
        this->_drawPile.emplace_back(Card("BLACK", 13));
        this->_drawPile.emplace_back(Card("BLACK", 14));
    }
    // Add the rest of the cards using nested for loop.
    string colors[] = {"RED", "YELLOW", "GREEN", "BLUE"};
    string currentColor;
    string currentNumber;
    for (int i = 0; i < 4; i++) {
        currentColor = colors[i];
        for (int j = 0; j < 13; j++) {
            this->_drawPile.emplace_back(Card(currentColor, j));
            if (j != 0) {  // All cards except for 0's have two of each color.
                this->_drawPile.emplace_back(Card(currentColor, j));
            }
        }
    }
    // Discard pile starts out as one random card from the draw pile.
    int randomIndex;
    randomIndex = rand() % this->_drawPile.size();
    this->_discardPile.push_back(this->_drawPile.at(randomIndex));
    this->_drawPile.erase(this->_drawPile.begin() + randomIndex);
}

int Deck::getDrawPileSize() const {
    return this->_drawPile.size();
}

int Deck::getDiscardPileSize() const {
    return this->_discardPile.size();
}

Card Deck::takeTopCardDrawPile() {
    if (this->_drawPile.size() == 0) {  // If the drawPile is empty, it must be shuffled.
        shuffle();
    }
    // The top card will be defined as the last card in the vector.
    Card topCard = this->_drawPile.at(this->_drawPile.size() - 1);
    this->_drawPile.pop_back();
    return topCard;
}

Card Deck::getTopCardDiscardPile() const {
    // Same as above, top card is the final card in the vector.
    return this->_discardPile.at(this->_discardPile.size() - 1);
}

void Deck::shuffle() {
    // First, all but the top card of the discard pile must be moved to the deck.
    // Store the last card, then remove it.
    Card lastCard = this->_discardPile.at(this->_discardPile.size() - 1);

    this->_discardPile.pop_back();
    // Move every remaining card from the discard pile to the draw pile.
    while (!this->_discardPile.empty()) {
        Card cardToMove = this->_discardPile.at(this->_discardPile.size() - 1);
        this->_drawPile.push_back(cardToMove);
        this->_discardPile.pop_back();
    }
    // Add the last card back in.
    this->_discardPile.push_back(lastCard);

    // Shuffle the cards by filling a new vector of cards with drawPile cards in a random order.
    int cardsToShuffle;
    int randomIndex;
    vector<Card> newDeck;
    cardsToShuffle = this->_drawPile.size();
    while (cardsToShuffle > 0) {
        randomIndex = rand() % cardsToShuffle;
        newDeck.push_back(this->_drawPile.at(randomIndex));
        this->_drawPile.erase(this->_drawPile.begin() + randomIndex);
        --cardsToShuffle;
    }
    this->_drawPile = newDeck;
}

void Deck::addTopCardDiscardPile(const Card cardPlayed) {
    this->_discardPile.push_back(cardPlayed);
}

void Deck::setWildColor(string color) {
//    Card wildCard = this->_discardPile.at(this->_discardPile.size() - 1);
    // Check to make sure the card is a wild card.
//    if (wildCard.getColor() != "BLACK") {
//        cerr << "Something went wrong. Wild color is set on a non-wild card." << endl;
//    }
//    wildCard.setColorChoice(color);
//    this->_discardPile.at(this->_discardPile.size() - 1) = wildCard;
    this->_discardPile.at(this->_discardPile.size() - 1).setColorChoice(color);
}


