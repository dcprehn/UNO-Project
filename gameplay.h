//
// Created by dcpre on 4/20/2021.
//

#ifndef FP_GAMEPLAY_H
#define FP_GAMEPLAY_H

#include "card.h"
#include "deck.h"
#include "player.h"
#include "gamewindow.h"
#include <iostream>
#include <fstream>

class Gameplay {
public:
    /*
     * Gameplay()
     * This constructor is responsible for initializing all of the object's data members. This includes _window
     * (1000 x 750), _gameOver (false), _winner ("None"), _turnNumber (0), _turnIndex (0), and _turnIncrementer (1).
     */
    Gameplay();
    /*
     * addPlayers()
     * Reads game data in from gameInfo.txt, which contains the number of players and each player's name. For each player,
     * the name is read in and used to initialize that Player object. The pointer to this new Player is stored in _players.
     */
    void addPlayers();
    /*
     * dealHands()
     * Deals 7 cards to each player by calling drawCard() for each player 7 times.
     */
    void dealHands();
    /*
     * firstTurn()
     * Special function for starting the game. All of the normal graphics will be displayed on the window with an
     * additional introduction telling the user to click anywhere to continue. Then the function waits for the user to
     * mouse click and handles the top card of the discard pile. If it is a special card, the corresponding function is
     * called. Then the program sleeps for a short amount of time before continuing with the normal game loop.
     */
    void firstTurn();
    /*
     * getNextTurnIndex()
     * Calculates the index of the player whose turn it will be next, by adding _indexIncrementer to _turnIndex. If
     * the result of this sum is negative, the number of players is added (for instance, an index of -1 in a four player
     * game corresponds to it being Player 4's turn next). If the result of the sum is greater than the number of players,
     * we take the remainder of _turnIndex divided by the number of players. Finally, the next turn index is returned.
     */
    int getNextTurnIndex();
    /*
     * specialCard()
     * Called whenever the card being played has a number value greater than 9. This function determines what special
     * card was played, and calls the corresponding function.
     * Parameter: cardPlayed is the card that was just played.
     */
    void specialCard(Card& cardPlayed);
    /*
     * drawTwo()
     * Adds the game logic associated with a Draw Two being played. When someone plays a drawTwo, the next player must
     * draw two cards and their turn is skipped.
     */
    void drawTwo();
    /*
     * reverse()
     * Adds the game logic associated with a Reverse being played. When someone plays a reverse, the order of turns
     * changes. One way to think of this is the turn incrementer changes from positive to negative, or vice versa.
     */
    void reverse();
    /*
     * skip()
     * Adds the game logic associated with a Skip being played. When someone plays a skip, the next player's turn is skipped.
     */
    void skip();
    /*
     * wild()
     * Adds the game logic associated with a Wild being played. If it was played by a bot, botChooseWildColor is called
     * to determine what the chosen color will be. If it is played by the user, wild options will be rendered to the
     * game window and the window's events will be polled until the user clicks. Once they click on one of the four
     * color options, the chosen color becomes the color that they clicked on. Once a color is chosen, the window must
     * also be cleared and redrawn in order to update the turn description with the color that was chosen.
     */
    void wild();
    /*
     * wildDrawFour()
     * Adds the game logic associated with a Wild Draw Four being played. In addition to all that happens with a Wild,
     * the Wild Draw Four makes the next player draw four cards and also skips their turn.
     */
    void wildDrawFour();
    /*
     * renderMainGraphics()
     * This function calls three other functions that are part of the GameWindow class; the first displays the rectangles
     * that represent each player's tablespace. The next displays the game deck (draw pile, discard pile, and number of
     * cards remaining in each). The last displays each player's hand. These functions are grouped together because they
     * are called every time the window is cleared and redrawn.
     */
    void renderMainGraphics();
    /*
     * playUNO()
     * This function incorporates all of the other functions in the Gameplay class. The game is started by addPlayers(),
     * then the game deck is shuffled and dealHands() is called. While the game is not over, the player in _players at
     * index _turnIndex takes their turn. The function checks to see if the current player won (if their hand size is 0)
     * and if they did the game ends. Otherwise, if they played a special card (Draw Two, Skip, Reverse, Wild, or Wild
     * Draw Four), the corresponding function is called. If they played any card at all, _turnIndex is updated with
     * getNextTurnIndex() and the loop repeats.
     */
    void playUNO();
private:
    // _window is the game window where the graphics are displayed.
    RenderWindow _window;
    // _graphics is the GameWindow class that contains all of the graphics methods.
    GameWindow _graphics;
    // _gameDeck is the Deck that the players play with.
    Deck _gameDeck;
    // _players is a vector that contains pointers to all of the players in the game.
    vector<Player*> _players;
    // _gameOver tells whether someone has won.
    bool _gameOver;
    // _winner records the string of the winning Player's name.
    string _winner;
    // _turnNumber records the total number of turns in the game.
    int _turnNumber;
    // _indexIncrementer records which direction the turns are being incremented. +1 is clockwise, -1 is counterclockwise.
    int _indexIncrementer;
    // _turnIndex contains the index of the Player whose turn it currently is.
    int _turnIndex;
    // _wildColorChosen is used to determine whether or not a special wild Sprite should be rendered for the game deck.
    bool _wildColorChosen;
};

#endif //FP_GAMEPLAY_H
