#include <iostream>                             // for standard input/output
using namespace std;                            // using the standard namespace

#include <SFML/Graphics.hpp>                    // include the SFML Graphics Library
using namespace sf;                             // using the sf namespace

#include "card.h"
#include "deck.h"
#include "player.h"
#include "gameplay.h"
#include "gamewindow.h"

void addPlayers() {
    ofstream gameOut;
    gameOut.open("./data/gameInfo.txt");
    if (gameOut.fail()) {
        cerr << "Error: Game Data could not be processed." << endl;
    }
    // Prompt the user for the number of players in the UNO game. No more than 5 players can play.
    cout << "-------------- Welcome To UNO! --------------" << endl << endl;
    cout << "Before we begin playing, the program needs to ask a couple of questions:" << endl << endl;
    int numPlayers;
    cout << "How many players?" << endl << "> ";
    cin >> numPlayers;
    while ((numPlayers > 5) || (numPlayers < 2)) {
        cout << "Sorry, there must be between 2 and 5 players. How many players?" << endl << "> ";
        cin >> numPlayers;
    }
    gameOut << numPlayers << endl;
    // Remove \n from the end of the line.
    string garbage;
    getline(cin, garbage);
    // Add up to 5 Player objects to the vector of players. The first of these will be the user, who will input their name.
    string playerName;
    for (int i = 0; i < numPlayers; i++) {
        if (i == 0) {
            cout << "Enter your Username:" << endl << "> ";
            getline(cin, playerName);
        } else {
            playerName = "Bot " + to_string(i);
        }
        gameOut << playerName << endl;
    }
    cout << endl << "Thank you! Your game will appear on the taskbar at the bottom of your screen!" << endl;
    gameOut.close();
}

int main() {

    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING BELOW HERE
    //********************************************
    srand(time(0));
    Card::LoadAssets();
    GameWindow::LoadAssets();
    addPlayers();

    Gameplay UNO;
    UNO.playUNO();

//    Card::LoadAssets();
//    RenderWindow window(VideoMode(1000, 1000), "test");
//    Deck gameDeck;
//    gameDeck.shuffle();
//    while (window.isOpen()) {
//        window.clear();
//        Card currentCard = gameDeck.getTopCardDiscardPile();
//        Sprite mySprite;
//        if (currentCard.getColor() == "BLACK") {
//            mySprite = currentCard.getWildSprite();
//        }
//        else {
//            mySprite = currentCard.getCardSprite();
//        }
//        mySprite.setPosition(500, 500);
//        window.draw(mySprite);
//        window.display();
//        sleep(Time(seconds(0.5)));
//        window.clear();
//        currentCard.setColorChoice("RED");
////        currentCard = gameDeck.getTopCardDiscardPile();
//        mySprite = currentCard.getWildSprite();
//        mySprite.setPosition(500, 500);
//        window.draw(mySprite);
//        window.display();
//        sleep(Time(seconds(0.5)));
//
//        Card myCard = gameDeck.takeTopCardDrawPile();
//        gameDeck.addTopCardDiscardPile(myCard);
//
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//            else if (event.type == Event::MouseButtonPressed) {
//            }
//        }
//    }

    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING ABOVE HERE
    //********************************************
    return 0;

}