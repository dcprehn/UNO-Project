//
// Created by dcpre on 5/1/2021.
//

#ifndef FP_GAMEWINDOW_H
#define FP_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
#include <fstream>
#include <vector>
using namespace std;
#include "card.h"
#include "deck.h"
#include "ellipse.h"

class GameWindow {
public:
    /*
     * LoadAssets()
     * This static method initializes the static data members of the GameWindow class, including _font, _UNOLabel, and
     * _UNOSprites.
     */
    static void LoadAssets();
    /*
     * GameWindow()
     * The constructor initializes the values of several private data members of the class. First, it customizes the
     * title sprite. Then, it reads in data from gameInfo.txt, using a for loop for the number of players and
     * determining the rectangle that acts as the player's tablespace as well as the text that renders the player's name.
     * Both of these are added to the _playerData struct, to be used in other class methods. Finally, _drawLocation and
     * _discardLocation are hardcoded.
     */
    GameWindow();
    /*
     * getPlayerInput()
     * Determines what the user just clicked on, given the x- and y- coordinates of the mouse. The function first checks
     * to see if the user clicked on the draw pile, in which case it returns 0. Then it checks to see if the user
     * clicked on one of their own cards. This is checked by dividing the user's tablespace into rows and columns based
     * on where the cards are rendered. Then, if the mouse was located in both a viable row and column, the card number
     * is determined by: colNum + (rowNum * numCardsPerRow). The card number is then returned.
     * Parameters:
     * mouseX: x-coordinate of the mouse when the mouse button was clicked.
     * mouseY: y-coordinate of the mouse when the mouse button was clicked.
     */
    int getPlayerInput(float mouseX, float mouseY) const;
    /*
     * customizeText()
     * This function is designed to clean up the code so that text can be customized in one line. The text object's
     * properties are assigned the values that are passed into the function.
     * Parameters:
     * text: The text object that is being customized.
     * textToDisplay: a string that is to be displayed by the text object.
     * color: the desired color of the text.
     * position: the location of the text on the window.
     * fontSize: the size of the text, defaulted to 30px.
     */
    static void customizeText(Text* text, const string& textToDisplay, Color color, Vector2f position, int fontSize = 30);
    /*
     * customizeSprite()
     * This function is also designed to clean up the code so that certain sprites can be customized in one line. The
     * sprite's properties are assigned to the values passed into the function.
     * Parameters:
     * sprite: the sprite object that is being customized.
     * position: the location of the sprite on the window.
     * scale: the size of the sprite relative to its texture, defaulted to 2.5 which is the typical size of an UNO card.
     */
    static void customizeSprite(Sprite* sprite, Vector2f position, Vector2f scale = Vector2f(2.5, 2.5));
    /*
     * renderPlayerGraphics()
     * This function uses the RectangleShape and Text objects in _playerData and draws these on the window for each
     * player.
     * Parameter: "window" is the window being drawn on.
     */
    void renderPlayerGraphics(RenderWindow& window);
    /*
     * renderGameDeck()
     * This function renders the draw and discard piles to the screen, as well as the card counts for each. In other
     * words, the sprite for the top card of the discard pile is rendered, the _UNOCardSprite is rendered for the draw
     * pile, and the sizes of the gameDeck _drawPile and _discardPile are displayed. If the top card of the discard pile
     * is a wild and the color has been chosen, this function will draw the customized Card _wildSprite.
     * Parameters:
     * window: the window being drawn on.
     * gameDeck: the deck that is being rendered.
     * wildCardChosen: a Boolean value determining whether or not the function should draw a customized wild sprite.
     */
    void renderGameDeck(RenderWindow& window, const Deck& gameDeck, bool wildCardChosen = false);
    /*
     * renderPlayerHand()
     * Draws the sprite associated with each card in the hand passed into the function. If the user's hand is being
     * rendered, the card will be drawn face up, meaning the Card sprite is used. If a bot's hand is being rendered,
     * _UNOCardSprite will be used for every Card. This function also takes care of the spacing of each card. Because of
     * limited space, only the first 12 cards in hand can be displayed for bots, and only the first 15 cards in hand can
     * be displayed for the user. This function also draws the _UNOLabel if the player's hand size is one.
     * Parameters:
     * window: the window being drawn on.
     * hand: the vector of Cards that is being drawn.
     * playerIndex: the index of the player whose hand is being rendered.
     */
    void renderPlayerHand(RenderWindow& window, const vector<Card>& hand, int playerIndex) const;
    /*
     * renderWildOptions()
     * This function, called whenever the user plays a Wild, draws over the user's tablespace with a black rectangle
     * and white border, then draws a prompt asking the user to click the color they wish to choose followed by four
     * colored rectangles, one for each color in UNO. The function then waits for user input in the form of a mouse
     * click, checking to see where the user clicked and if they click on one of the four colored rectangles the
     * function returns the chosen color.
     * Parameter: window is the window being drawn on.
     */
    static string renderWildOptions(RenderWindow& window);
    /*
     * renderIntro()
     * This function is only called at the beginning of the game, rendering a font object that welcomes the user to the
     * game and notifies them that clicking a card will play it.
     * Parameters:
     * window: the window being drawn on.
     * name: the name of the user.
     */
    static void renderIntro(RenderWindow& window, string name);
    /*
     * renderMoveDescription()
     * This overloaded function draws a string to the window that describes the turn that was just taken. This
     * description includes the name of the player that just went, as well as the action they took. If they drew a card,
     * only the window and name parameters will be passed to the function. If they played a card, a Card object will
     * also be passed. If they chose a wild color, the color choice will be passed.
     * Parameters:
     * window: the window being drawn on.
     * name: the name of the player who just took their turn.
     * cardPlayed, the Card that the player just played.
     * colorChoice: the wild color chosen by the user/bots.
     */
    static void renderMoveDescription(RenderWindow& window, string name);
    static void renderMoveDescription(RenderWindow& window, string name, const Card& cardPlayed);
    static void renderMoveDescription(RenderWindow& window, string name, string colorChoice);
    /*
     * renderUserPrompt()
     * This function is called at the beginning of each of the user's turns, to remind notify them that it is their turn.
     * The notification is located in the same place as the move description normally is.
     */
    static void renderUserPrompt(RenderWindow& window);
private:
    // The Card's width and height are constant values used to help render the cards.
    const float _CARD_HEIGHT = 95;
    const float _CARD_WIDTH = 60;
    // _UNOLabel is a shape with a special texture that is outputted whenever a player only has one card left.
    static Ellipse _UNOLabel;
    // _UNOSprites is The PNG where the sprites are getting their textures from.
    static Texture _UNOSprites;
    // _font is a special font included in the data file.
    static Font _font;
    // _playerData holds the info for each player's window object and text object which will be displayed every turn.
    struct _playerData {
        RectangleShape _playerWindow;
        Text _playerText;
        vector<Vector2f> _cardLocations;
    };
    // _playerGraphics is simply a vector containing all of the _playerData.
    vector<_playerData> _playerGraphics;
    // _discardLocation stores the position of the discard pile.
    Vector2f _discardLocation;
    // _drawLocation stores the position of the draw pile.
    Vector2f _drawLocation;
    // _title is a Text object that displays the title of the game.
    Text _title;
};

#endif //FP_GAMEWINDOW_H
