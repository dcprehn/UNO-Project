//
// Created by dcpre on 4/19/2021.
//

#include "card.h"

Texture Card::_cardTexture;
Sprite Card::_UNOCardSprite;
Sprite Card::_wildSprites[4];
Sprite Card::_wildDrawFourSprites[4];

void Card::LoadAssets() {
    if (!_cardTexture.loadFromFile("./data/UNOSprites.png")) {
        cerr << "Card Image could not be opened..." << endl;
    }
    _UNOCardSprite.setTexture(_cardTexture);
    _UNOCardSprite.setTextureRect(IntRect(423, 85, _WIDTH, _HEIGHT));
    _UNOCardSprite.setScale(2.5, 2.5);
    // Add the wild sprites to their respective static arrays.
    for (int i = 0; i < 4; i++) {
        Sprite wildSprite;
        wildSprite.setTexture(_cardTexture);
        float xPos = 3 + (_WIDTH + 4) * 13;
        float yPos = 3 + (_HEIGHT + 3) * i;
        wildSprite.setTextureRect(IntRect(xPos, yPos, _WIDTH, _HEIGHT));
        _wildSprites[i] = wildSprite;
        Sprite wildDrawFourSprite;
        wildDrawFourSprite.setTexture(_cardTexture);
        xPos = 3 + (_WIDTH + 4) * 14;
        wildDrawFourSprite.setTextureRect(IntRect(xPos, yPos, _WIDTH, _HEIGHT));
        _wildDrawFourSprites[i] = wildDrawFourSprite;
    }
}

Sprite Card::getUNOCardSprite() {
    return _UNOCardSprite;
}

Card::Card() {
    // These will both be given values that don't exist in UNO, so as to make sure this constructor is not used.
    this->_color = "";
    this->_number = -1;
    this->_colorChoice = "";
}

Card::Card(string color, int number) {
    this->_color = color;
    this->_number = number;
    this->_colorChoice = "";
    findCardSprite();
}

Card::Card(const Card &card) {
    this->_color = card._color;
    this->_number = card._number;
    this->_colorChoice = card._colorChoice;
    this->_cardSprite = card._cardSprite;
    this->_wildSprite = card._wildSprite;
}

string Card::getColor() const {
    return this->_color;
}

int Card::getNumber() const {
    return this->_number;
}

string Card::getCardString() const {
    string cardString;
    if (this->_number < 10) {
        cardString = this->_color + " " + to_string(this->_number);
    }
    else {
        string action;
        switch (this->_number) {
            case 10:
                action = "Reverse";
                break;
            case 11:
                action = "Skip";
                break;
            case 12:
                action = "Draw Two";
                break;
            case 13:
                action = "Wild";
                break;
            case 14:
                action = "Wild Draw Four";
                break;
            default:
                cerr << "Something went wrong..." << endl;
        }
        if (this->_color == "BLACK") {
            cardString = action;
        }
        else {
            cardString = this->_color + " " + action;
        }
    }
    return cardString;
}

string Card::getColorChoice() const {
    return this->_colorChoice;
}

Sprite Card::getCardSprite() const {
    return this->_cardSprite;
}

Sprite Card::getWildSprite() const {
    if (this->_color != "BLACK") {
        cerr << "Error: Wild Sprite requested from non-wild Card." << endl;
    }
    return this->_wildSprite;
}

void Card::setColorChoice(string color) {
    this->_colorChoice = color;
    // Set _wildSprite to be the Sprite associated with the chosen color, using the static arrays of sprites in Card.
    const string colors[4] = {"RED", "GREEN", "YELLOW", "BLUE"};
    for (int i = 0; i < 4; i++) {
        if (color == colors[i]) {
            if (this->_number == 13) {
                this->_wildSprite = _wildSprites[i];
            }
            else if (this->_number == 14) {
                this->_wildSprite = _wildDrawFourSprites[i];
            }
        }
    }

}

void Card::findCardSprite() {
    // Each row in UNOSprites.png has textures for a different color; they are in the same order as the colors array.
    const string colors[4] = {"RED", "GREEN", "YELLOW", "BLUE"};
    // Below are the heights and widths of every UNO card texture in the png.
    // The first UNO texture is located at point (3, 3)
    int left = 3;
    int top = 3;
    /*
     * _color determines which row the texture is located in; _number determines the column. 4 pixels separate each
     * card texture horizontally, and 3 pixels separate each card texture vertically. Wild cards are special cases, as
     * they are located in the first two rows (normal wild is first row, wild draw four is second row) and the 16th
     * column.
     */
    switch (this->_number) {
        case 13:
            left += (_WIDTH + 4) * 15;
            break;
        case 14:
            left += (_WIDTH + 4) * 15;
            top += (_HEIGHT + 3);
            break;
        default:
            for (int i = 0; i < 4; i++) {
                if (this->_color == colors[i]) {
                    top += (_HEIGHT + 3) * i;
                    break;
                }
            }
            left += (_WIDTH + 4) * this->_number;
    }
    this->_cardSprite.setTexture(_cardTexture);
    this->_cardSprite.setTextureRect(IntRect(left, top, _WIDTH, _HEIGHT));
    this->_cardSprite.setScale(2.5, 2.5);
}



