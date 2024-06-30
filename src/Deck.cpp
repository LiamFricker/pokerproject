#include "Deck.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

Deck::Deck() {
    // Initialize deck with 52 cards
    for (int value = 1; value <= 13; ++value) {
        for (int suit = HEARTS; suit <= SPADES; ++suit) {
            cards.push_back(Card(value, static_cast<Suit>(suit)));
        }
    }

    totalCardsLeft = 52;
    currentCard = 0;
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    totalCardsLeft = 52;
    currentCard = 0;
}

Card Deck::dealCard() {
    if (size_t(currentCard) < cards.size()) {
        totalCardsLeft--;
        return cards[currentCard++];
    } else {
        throw std::out_of_range("No more cards in the deck");
    }
}

int Deck::getTotalCardsLeft() const {
    return totalCardsLeft;
}
