//
// Created by dcpre on 4/19/2021.
//

#ifndef FP_DECK_H
#define FP_DECK_H

#include <random>   // For shuffle()
#include <ctime>    // For shuffle()
#include <vector>
#include "card.h"

using namespace std;

class Deck {
public:
    /*
     * Deck()
     * The default constructor initializes the_drawPile and _discardPile data members of the Deck object.
     */
    Deck();
    /*
     * Getter function which returns the size of _drawPile. Used to notify the user how many cards remain in _drawPile.
     */
    int getDrawPileSize() const;
    /*
     * Getter function which returns the size of _discardPile. Used to notify the user how many cards remain in _discardPile.
     */
    int getDiscardPileSize() const;
    /*
     * takeTopCardDrawPile()
     * Returns the top card of _drawPile and also removes this card from _drawPile.
     */
    Card takeTopCardDrawPile();
    /*
     * Getter function which returns the top card (last object) in _discardPile.
     */
    Card getTopCardDiscardPile() const;
    /*
     * shuffle()
     * First moves all but the last Card in _discardPile to _drawPile, then uses <random> to shuffle the contents of
     * _drawPile.
     */
    void shuffle();
    /*
     * addTopCardDiscardPile()
     * Appends a Card to the end of _discardPile.
     * Parameter: cardPlayed is the card added.
     */
    void addTopCardDiscardPile(Card cardPlayed);
    /*
     * setWildColor()
     * This function will be called whenever a player plays a wild card and chooses its color. The function takes the
     * last card of _discardPile (which should be the wild card that was just played), and sets its _colorChoice value
     * to the color argument that was passed into the function.
     */
    void setWildColor(string color);

private:
    // _drawPile holds a vector of Cards that make up the draw pile.
    vector<Card> _drawPile;
    // _discardPile holds a vector of Cards that make up the discard pile.
    vector<Card> _discardPile;
};
#endif //FP_DECK_H
