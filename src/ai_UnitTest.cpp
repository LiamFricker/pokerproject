#include <iostream>
#include <cmath>
#include <cassert>
#include "ai.h"

using namespace std;

class PokerAITest {
public:
    void runTests() {
        testMakeDecision();
        cout << "All tests passed!" << endl;
    }

private:
    void testMakeDecision() {
        HandEvaluator handEvaluator;
        PokerAI ai(handEvaluator);

        // test straight flush hand on flop
        vector<Card> holeCards = {Card(13, SPADES), Card(12, SPADES)};
        vector<Card> communityCards = {Card(11, SPADES), Card(10, SPADES), Card(9, SPADES)};
        assert(ai.makeDecision(holeCards, communityCards) == "Raise");
        std::cout << "Straight Flush Raise on Flop Test Success\n";

        // test one pair hand on turn
        holeCards = {Card(11, DIAMONDS), Card(3, SPADES)};
        communityCards = {Card(4, HEARTS), Card(2, DIAMONDS), Card(11, HEARTS), Card(7, CLUBS)};
        assert(ai.makeDecision(holeCards, communityCards) == "Check");
        std::cout << "One Pair Check on Turn Test Success\n";

        // test one pair when pair is in community cards (weaker potential)
        holeCards = {Card(7, DIAMONDS), Card(8, CLUBS)};
        communityCards = {Card(11, SPADES), Card(11, DIAMONDS), Card(10, HEARTS), Card(2, CLUBS)};
        assert(ai.makeDecision(holeCards, communityCards) == "Fold");
        std::cout << "One Pair Fold in Pool Test Success\n";

        // test high card ace
        holeCards = {Card(7, DIAMONDS), Card(1, CLUBS)};
        communityCards = {Card(9, SPADES), Card(10, DIAMONDS), Card(11, HEARTS)};
        assert(ai.makeDecision(holeCards, communityCards) == "Raise");
        std::cout << "High Card Ace Raise Test Success\n";
    }
};

int main() {
    PokerAITest test;
    test.runTests();
    return 0;
}