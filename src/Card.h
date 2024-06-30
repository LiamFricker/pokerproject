#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

class Card {
public:
    Card(int value, Suit suit);
    string toString() const;

    // returns value of the card 1-13
    int getValue() const;
    // returns the suit of the card
    Suit getSuit() const;

private:
    int value;
    Suit suit;
};

bool operator>(const Card& lhs, const Card& rhs);
bool operator<(const Card& lhs, const Card& rhs);
bool operator==(const Card& lhs, const Card& rhs);

#endif
