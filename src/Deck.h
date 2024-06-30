#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

using namespace std;

class Deck {
public:
    Deck(); //constructor
    void shuffle();
    Card dealCard();
    int getTotalCardsLeft() const; // Add this line
    
    void resetDeck();

private:
    vector<Card> cards;
    int totalCardsLeft;
    int currentCard;
    void swapCards(int i, int j);
};

#endif
