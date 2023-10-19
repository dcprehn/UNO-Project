//
// Created by dcpre on 4/20/2021.
//

#ifndef FP_PLAYER_H
#define FP_PLAYER_H

#include <vector>
#include "deck.h"
#include "gamewindow.h"

class Player {
public:
    /*
     * Player() constructor initializes the _name data member.
     */
    Player(string name);
    /*
     * getName()
     * Getter function which returns the _name of the Player.
     */
    string getName() const;
    /*
     * getHandSize()
     * Getter function which returns the number of Cards in the Player's _hand.
     */
    int getHandSize() const;
    /*
     * getHand()
     * Getter function which returns the Player's entire _hand.
     */
    vector<Card> getHand() const;
    /*
     * canPlay()
     * Determines whether cardToPlay can be played by comparing cardToPlay's color and number to the color and number of
     * cardLastPlayed. If the colors or numbers are the same, or if cardToPlay is a wild card,
     * this function returns true.
     * Parameters:
     * cardToPlay is the Card being tested to see if it can be played.
     * cardLastPlayed is the top card of the discard pile, which cardToPlay would be played on.
     */
    bool canPlay(const Card& cardToPlay, const Card& cardLastPlayed);
    /*
     * drawCard()
     * This function takes the top card of the draw pile of the game deck and appends this Card to the player's _hand.
     * Parameter: gameDeck is the Deck that Player draws from.
     */
    void drawCard(Deck& gameDeck);
    /*
     * playCard()
     * Removes the Card being played from _hand, and adds this card to the gameDeck's top of _discardPile.
     * Parameters:
     * cardToPlay is the Card being played. The function searches the player's hand until this card is found in the hand.
     * gameDeck is the Deck that the Card being played is added to.
     */
    void playCard(const Card& cardToPlay, Deck& gameDeck);
    /*
     * botTakeTurn()
     * First, the card that was played last is determined by accessing the top card of the _discardPile of gameDeck.
     * Then, the function iterates through every Card in the bot's _hand and calls canPlay() to see if the Card can be
     * played. If canPlay() returns true, playCard() is called, the bot's turn is over, and the function returns true.
     * If every card is tested and none can be played, drawCard() is called and the function returns false. The return
     * value of the function determines whether the bot's turn is over or not.
     */
    bool botTakeTurn(Deck& gameDeck);
    /*
     * userTakeTurn()
     * First, the card that was played last is determined by accessing the top card of the _discardPile of gameDeck.
     * Then, the function waits for user input which involves polling the events of the window and seeing if the player
     * mouse clicked. Once this happens, a separate function in gamewindow.cpp is called which returns the number of the
     * card that the user clicked on. If the user clicked on the drawPile, drawCard() is called and the function returns
     * false. If the user clicked on one of the cards in their _hand, canPlay() is called to determine if that card can
     * be played. If it can't, nothing happens. If it can, playCard() is called and the function returns true.
     */
    bool userTakeTurn(RenderWindow& window, Deck& gameDeck, GameWindow &graphics);
    /*
     * botChooseWildColor()
     * this function returns the color that the bot "chooses" for the wild card they previously played. The wild color
     * is chosen by iterating through the bot's _hand and keeping a tally of the number of each Card color that the
     * _hand contains. After this, the color with the most occurrences is chosen and returned.
     */
    string botChooseWildColor() const;
private:
    // _hand stores the vector of Cards that make up the Player's hand.
    vector<Card> _hand;
    // _name stores the string representing the Player's name.
    string _name;
};

#endif //FP_PLAYER_H
