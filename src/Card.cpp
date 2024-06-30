#include "Card.h"
#include <sstream>

Card::Card(int value, Suit suit) : value(value), suit(suit) {}

std::string Card::toString() const {
    std::ostringstream oss;
    oss << value << " of ";
    switch (suit) {
        case HEARTS: oss << "Hearts"; break;
        case DIAMONDS: oss << "Diamonds"; break;
        case CLUBS: oss << "Clubs"; break;
        case SPADES: oss << "Spades"; break;
    }
    return oss.str();
}

int Card::getValue() const {
    return value;
}

Suit Card::getSuit() const {
    return suit;
}

// Custom comparison operators
bool operator>(const Card& lhs, const Card& rhs) {
    if (lhs.getValue() > rhs.getValue()) {
        return true;
    }
    return false;
}

bool operator<(const Card& lhs, const Card& rhs) {
    if (lhs.getValue() < rhs.getValue()) {
        return true;
    }
    return false;
}

bool operator==(const Card& lhs, const Card& rhs) {
    if (lhs.getValue() == rhs.getValue()) {
        return true;
    }
    return false;
}