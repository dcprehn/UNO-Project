//
// Created by dcpre on 4/19/2021.
//

#ifndef FP_CARD_H
#define FP_CARD_H

#include <string>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>  // For the card sprites.
using namespace sf;

class Card {
public:
    /*
     * LoadAssets()
     * Initializes the static variables _cardTexture and _UNOCardSprite
     */
    static void LoadAssets();
    /*
     * getUNOCardSprite()
     * Getter function which returns the _UNOCardSprite
     */
    static Sprite getUNOCardSprite();
    /*
     * Card()
     * There are three Card constructors, in charge of initializing the _color, _number, _colorChoice, and _cardSprite
     * data members. The default constructor isn't intended to be used and thus initializes them to values that would
     * crash the program. The overloaded constructor initializes the card with a given number and a given color. The
     * copy constructor is used to initialize a new Card object that is a copy of an existing Card object, so it copies
     * all of the data members' values.
     */
    Card();
    Card(string color, int number); // overloaded constructor
    Card(const Card &card);  // copy constructor
    /*
     * getColor()
     * Getter function which returns the _color data member.
     */
    string getColor() const;
    /*
     * getNumber()
     * Getter function which returns the _number data member.
     */
    int getNumber() const;
    /*
     * getCardString()
     * Function which returns a descriptive string of the Card. For instance, if _color = "RED" and _number = 7, the
     * string returned will be "RED 7". Switch statement is used to convert numbers 10-14 into corresponding UNO card
     * actions.
     */
    string getCardString() const;
    /*
     * getColorChoice()
     * Getter function which returns the _colorChoice data member.
     */
    string getColorChoice() const;
    /*
     * getCardSprite();
     * Getter function which returns the _cardSprite data member.
     */
    Sprite getCardSprite() const;
    /*
     * getWildSprite()
     * Getter function which returns the _wildSprite data member. Outputs error if card is not a wild.
     */
    Sprite getWildSprite() const;
    /*
     * setColorChoice()
     * Setter function which sets the value of _colorChoice to the color argument provided. This function is also
     * responsible for setting the _wildSprite attribute of the Card, depending on which color was chosen.
     */
    void setColorChoice(string color);
    /*
     * Setter function which sets the _cardSprite data member to a certain texture depending on what UNO card it is.
     * Every card texture is taken from UNOSprites.png, which means the _cardSprite's texture must be set to a unique
     * rectangle of this png. This function determines which texture rectangle matches which card.
     */
    void findCardSprite();
private:
    // _cardTexture is simply the UNOSprites.png image
    static Texture _cardTexture;
    /*
     * _UNOCardSprite holds the sprite for the back side of every UNO card, which will be the sprite for the draw pile
     * and the bots' hands.
     */
    static Sprite _UNOCardSprite;
    // _HEIGHT and _WIDTH are the height and width of one card texture in UNOSprites.png.
    static const int _HEIGHT = 38;
    static const int _WIDTH = 24;
    // _wildSprites contains 4 special Sprites that will be used to customize the display of normal wild cards.
    static Sprite _wildSprites[4];
    //_wildDrawFourSprites contains 4 special Sprites that will be used to customize the display of wild draw four cards.
    static Sprite _wildDrawFourSprites[4];
    // _color stores the Card's color ("RED", "YELLOW", "GREEN", "BLUE", or "BLACK")
    string _color;
    // _number stores the Card's number (0-9, 10 = Reverse, 11 = Skip, 12 = Draw Two, 13 = Wild, 14 = Wild Draw Four)
    int _number;
    /*
     * _colorChoice is exclusively used for wild cards, as their initial color is BLACK and either the user or the bot
     * can choose which color they want the wild to be.
     */
    string _colorChoice;
     // _cardSprite stores the Card's unique Sprite, which will be used to display the Card on the game window.
    Sprite _cardSprite;
    // _wildSprite is exclusively used for wild cards, to display the color that was chosen by either the user or bots.
    Sprite _wildSprite;
};
#endif //FP_CARD_H
