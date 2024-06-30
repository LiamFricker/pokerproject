#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>
#include "ai.h"

using namespace std;

PokerAI::PokerAI(HandEvaluator& handEvaluator) : handEvaluator(handEvaluator) {
    // Initialize baseline strength values for hand types weaker than Straight
    handValue[HIGH_CARD] = 2;
    handValue[ONE_PAIR] = 3;
    handValue[TWO_PAIR] = 7;
    handValue[THREE_OF_A_KIND] = 12;
}

// Helper function to guess the potential of your hand
double PokerAI::estimateHandPotential(const vector<Card>& holeCards, const vector<Card>& communityCards, int handType) {
    // create vector of all cards available
    std::vector<Card> combinedCards = holeCards;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    // Sort combinedCards
    std::sort(combinedCards.begin(), combinedCards.end(), [](const Card &a, const Card &b) {
        return a.getValue() < b.getValue();
    });

    // initialize potential with values from handValue array
    double potential = handValue[handType];

    // increase potential if game is on flop
    if (communityCards.size() == 3) potential += 2;

    // if hand type is currently high card, check if it's a good high card or not
    int highestVal = 0;
    if (handType == HIGH_CARD) {
        for (auto combinedCard : combinedCards) {
            if (combinedCard.getValue() > highestVal) highestVal = combinedCard.getValue();
            if (combinedCard.getValue() == 1) { highestVal = 1; break; } // check for ace
        }
        if (highestVal != 1) potential = potential + (highestVal - 10)*0.75; // increase potential for high card over 10
        else potential += 4; // ace buff
    }

    // if pair in hole cards, potential increase
    if (holeCards[0].getValue() == holeCards[1].getValue()) potential += 2.1;

    // if hole cards same suit, potential increase
    if (holeCards[0].getSuit() == holeCards[1].getSuit()) potential += 1.1;

    // if pair in community cards, potential decrease b/c everyone has access to it
    bool pairInCommunity = false;
    std::vector<Card> sortedCommunityCards = communityCards;
    std::sort(sortedCommunityCards.begin(), sortedCommunityCards.end(), [](const Card &a, const Card &b) {
        return a.getValue() < b.getValue();
    });
    for (size_t i = 1; i < sortedCommunityCards.size(); i++) {
        if (sortedCommunityCards[i].getValue() == sortedCommunityCards[i - 1].getValue()) {
            pairInCommunity = true;
            break;
        }
    }
    if (pairInCommunity && (handType == ONE_PAIR)) potential -= 3;

    // if hand is one pair and no pair in community, check how strong of a pair it is
    int pair = 0;
    if (!pairInCommunity && (handType == ONE_PAIR)) {
        for (size_t i = 1; i < combinedCards.size(); i++) {
            if (combinedCards[i].getValue() == combinedCards[i - 1].getValue()) {
                pair = combinedCards[i].getValue();
                break;
            }
        }
        if (pair >= 10) potential = potential + (pair - 9)*1.05; // increase potential for pair over 9
        else if (pair == 1) potential += 5; // ace buff
    }

    // check suit similarities
    int spade = 0;
    int club = 0;
    int heart = 0;
    int diamond = 0;

    for (auto combinedCard : combinedCards) {
        if (combinedCard.getSuit() == HEARTS) heart++;
        else if (combinedCard.getSuit() == SPADES) spade++;
        else if (combinedCard.getSuit() == CLUBS) club++;
        else if (combinedCard.getSuit() == DIAMONDS) diamond++;
    }
    if ((communityCards.size() <= 4) && ((heart >= 4) || (spade >= 4) || (club >= 4) || (diamond >= 4)))
        potential += 5; // give big buff if close to flush

    return potential;
}

// Make a decision based on hand type
string PokerAI::makeDecision(const vector<Card>& holeCards, const vector<Card>& communityCards) {
    // Use HandEvaluator instance to determine hand type
    int handType = handEvaluator.evaluateHand(holeCards, communityCards);

    // Wait for 2 seconds before making a decision
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Always check on pre-flop
    if (communityCards.size() < 3) return "Check";

    // Always raise if hand is straight or better
    if (handType == STRAIGHT || handType == FLUSH || handType == FULL_HOUSE || handType == FOUR_OF_A_KIND
        || handType == STRAIGHT_FLUSH || handType == ROYAL_FLUSH)
        return "Raise";

    double potential = estimateHandPotential(holeCards, communityCards, handType);

    if (potential > 7) return "Raise";
    else if (potential > 4) return "Check";
    else return "Fold";
}
