#ifndef AI_H
#define AI_H

#include "HandEvaluator.h"
#include <string>
#include <unordered_map>

class PokerAI {
public:
    // Constructor to initialize hand odds
    PokerAI(HandEvaluator& handEvaluator);

    // Function to make a decision based on cards in hand/board
    std::string makeDecision(const std::vector<Card>& holeCards, const std::vector<Card>& communityCards);

private:
    // handEvaluator instance to let AI make decisions by evaluating the hand it has
    HandEvaluator& handEvaluator;

    // Map to store handValue base strengths
    std::unordered_map<int, double> handValue;

    double estimateHandPotential(const std::vector<Card>& holeCards, const std::vector<Card>& communityCards, int handType);
};


#endif
