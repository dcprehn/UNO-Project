# UNO
## TITLE:
My name is Devin Prehn, and the title of my project is UNO.

## PROBLEM DESCRIPTION:
My original goal was to create a virtual version of one of my favorite card games, Uno. The game involves building and shuffling a deck, dealing out a certain number of cards to each player, and creating gameflow logic that each player abides by on their turn. I was unable to create both a single-player and multi-player game mode, and also didn’t think this would work very well because multiple people would have to play locally (I don’t know how to set up a network) and they would be able to see each other’s cards. Instead, I took on a much greater focus with the graphics aspect of my project, and created a display that is visually appealing with every unique UNO card having its own texture. I also added….well, you’ll see it when you play it :).

## PROGRAM DOCUMENTATION:
This program uses the SFML graphics library and thus this library must be installed on the machine attempting to run this program.
Aside from this, the program is extremely simple to run:
Execute the `Makefile` and then run the `main.cpp`.
The program will start by asking you for the number of players and your preferred username. Between 2 and 5 players are able to play, and it will only accept a number in that range (if you input a number outside of that range it will ask again; if you input a letter or special character, it will probably get stuck in an infinite loop and will have to be terminated). I would recommend playing with five players, as I designed the graphics specifically for this number and it has the best look.
Then the program will create a window. You might have to open it yourself as it will start off minimized.
From there, the normal rules of UNO apply. Click on one of your cards to play it, click on the draw pile to draw a card, etc.

I struggled a lot with the graphics and only recently got them working correctly. Because of this, there are a handful of things that I wasn’t able to get to. The list includes:
Creating some sort of “draw” animation that shows a card going from the draw pile to your hand. This would be a method of the GameWindow class and would be called in the playUNO() method of GamePlay, whenever a player draws a card.
Fixing a couple of bugs and limitations of the game. For instance, the maximum number of cards that the user is capable of seeing in their hand is 15, because of the size of the card and the table space. This number is only 12 for the bots, which have smaller table spaces. In addition, if the discard pile is initialized with a wild card, you will not be able to play anything except another wild card (this is because the colorChoice attribute of the wild card has not been defined, as it is normally determined by the player/bot).
Making it so that other special cards that start as the first discard have immediate effect; for example, if the first discard is a skip, in a typical UNO game that would skip the player to the left of the dealer who normally gets to take their turn first.
Implementing other graphics that visually depict what is happening in the game. For instance, if someone plays a reverse, a reverse sprite would be displayed in their table space.
When the game is finished, outputting a text file full of data from the game, including but not limited to the number of turns, who took the most turns, the frequency of each card that was played, the frequency of wild colors, etc.

## TESTS:
The first test encountered in the program is when the user is prompted to enter the number of players. Although I did not handle the case where the user doesn’t enter a number at all, if it can pass as an integer value then the question will be asked until it receives a valid input (between 2 and 5 inclusive).
Next, the player is only able to click on and play cards that are currently playable. For example, clicking on a RED 6 when the discard is a GREEN 8 will have no effect on the program. Clicking just slightly to the left of a card, or in between two cards, will also have no effect; the click must occur when the cursor is hovered over a playable card.
The bots are capable of playing completely by themselves. This isn’t super impressive because UNO is a fairly simple game; however, this does handle all cases that will arise in-game. If a bot plays a wild, then they will also choose the color that appears most frequently in their hand. If a bot has a draw two played on them, they will immediately draw two cards.
The Deck will automatically be shuffled when it runs out of cards. I programmed this to happen even when it occurs in the middle of a turn. Furthermore, I programmed the game to remove all but the top card of the discard pile and shuffle this into the draw pile, as well.
A special graphic is displayed whenever a player gets down to one card in hand. This graphic will remain for as long as the player only has one card in hand, and will disappear as soon as the player draws a card. Multiple of these graphics will be displayed if multiple players are at UNO.
The user has almost complete control over how they play. They are not required to play a card if they are able to, and they will be prompted with which color they would like whenever playing a wild card. The only case that they do not control is having Draw Twos or Draw Fours played against them, in which case the corresponding number of cards will be automatically added to their hand.

## REFLECTIONS:
Looking back on this project, I am honestly amazed that it all ended up working out. I grossly underestimated how difficult it would be to implement graphics into the game, and (shocker) didn’t start the project early enough so I put myself in a real time crunch to finish. I also now recognize the extreme importance of thinking deeply about the structure of the program, and methodically planning out as much of it as you can before writing even one line of code. I eagerly jumped right into the project, which unfortunately led to a lot of mistakes that I had to account for later on. Similarly, I understand how important it is to use an incremental programming approach; Again, I wanted to write as much code as possible and wedge it all together and cross my fingers to see if everything worked, rather than methodically working through and checking each method of each class, and checking edge cases to prevent bugs before they happened. With regards to future projects, I will make sure to take a more organized and planned out approach, which I think will ultimately make the final product much better.
