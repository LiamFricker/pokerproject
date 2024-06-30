#ifndef HANDEVALUATOR_H
#define HANDEVALUATOR_H

#include "Card.h"
#include <vector>

using namespace std;

enum HandRank {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

class HandEvaluator {
public:

    HandEvaluator();

    // evaluate one hand
    // integer values returns rank of hand
    static int evaluateHand(const vector<Card>& hand, const std::vector<Card>& communityCards);

    // compares hand 1 and hand 2
    // returns 0 if tied
    // returns 1 if hand1 is winning
    // returns 2 if hand2 is winning
    static int compareHand(const vector<Card>& hand1, const std::vector<Card>& hand2, const std::vector<Card>& communityCards);


        // evaluation functions
    static int isRoyalFlush(const vector<Card>& hand, const std::vector<Card>& communityCards);
    static int isStraightFlush(const vector<Card>& hand, const std::vector<Card>& communityCards);
    static int isFlush(const vector<Card>& hand, const std::vector<Card>& communityCards);

    static int isFullHouse(const vector<Card>& hand, const std::vector<Card>& communityCards);
    static int isStraight(const std::vector<Card>& hand, const std::vector<Card>& communityCards);

    static int isPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards);

    static int isTwoPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards);
    static int isThreeOfAKind(const std::vector<Card>& hand, const std::vector<Card>& communityCards);
    static int isFourOfAKind(const std::vector<Card>& hand, const std::vector<Card>& communityCards);


    // helper functions
    static int highCardComparison(const vector<Card>& hand1, const std::vector<Card>& hand2, const std::vector<Card>& communityCards, unsigned int numCards, unsigned int comboValue);
    static int secondPairInTwoPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards);

private:
};

#endif
