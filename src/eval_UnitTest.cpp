#include <iostream>
#include <vector>
#include <cassert>
#include "HandEvaluator.h"

using namespace std;

class UnitTest {
public:
    static void testHandEvaluator() {
        // Royal flush test case
        vector<Card> RFholeCards = {Card(13, SPADES), Card(12, SPADES)};
        vector<Card> RFcommunityCards = {Card(11, SPADES), Card(10, SPADES), Card(1, SPADES)};

        // Straight flush test case
        vector<Card> SFholeCards = {Card(13, SPADES), Card(9, SPADES)};
        vector<Card> SFcommunityCards = {Card(11, SPADES), Card(10, SPADES), Card(12, SPADES)};

        // 4 of a kind test case
        vector<Card> FKholeCards = {Card(13, SPADES), Card(13, HEARTS)};
        vector<Card> FKcommunityCards = {Card(13, DIAMONDS), Card(13, CLUBS), Card(9, HEARTS)};

        // Full house test case
        vector<Card> FHholeCards = {Card(13, SPADES), Card(13, HEARTS)};
        vector<Card> FHcommunityCards = {Card(13, DIAMONDS), Card(9, CLUBS), Card(9, HEARTS)};

        // Flush test case
        vector<Card> FholeCards = {Card(13, SPADES), Card(12, SPADES)};
        vector<Card> FcommunityCards = {Card(11, SPADES), Card(10, SPADES), Card(2, SPADES)};

        // Straight test case
        vector<Card> SholeCards = {Card(13, SPADES), Card(12, CLUBS)};
        vector<Card> ScommunityCards = {Card(11, SPADES), Card(10, SPADES), Card(9, HEARTS)};

        // 3 of a kind test case
        vector<Card> TKholeCards = {Card(13, SPADES), Card(13, HEARTS)};
        vector<Card> TKcommunityCards = {Card(13, DIAMONDS), Card(2, CLUBS), Card(9, HEARTS)};

        // Two pair test case
        vector<Card> TPholeCards = {Card(13, SPADES), Card(13, HEARTS)};
        vector<Card> TPcommunityCards = {Card(2, DIAMONDS), Card(2, CLUBS), Card(9, HEARTS)};

        // One pair test case
        vector<Card> OPholeCards = {Card(13, SPADES), Card(13, HEARTS)};
        vector<Card> OPcommunityCards = {Card(3, DIAMONDS), Card(2, CLUBS), Card(9, HEARTS)};

        // High card test case
        vector<Card> HCholeCards = {Card(13, SPADES), Card(6, HEARTS)};
        vector<Card> HCcommunityCards = {Card(3, DIAMONDS), Card(2, CLUBS), Card(9, HEARTS)};

        // Instantiate hand evaluator
        HandEvaluator handEvaluator;

        // Test royal flush
        assert(handEvaluator.evaluateHand(RFholeCards, RFcommunityCards) == ROYAL_FLUSH);

        // Test straight flush
        assert(handEvaluator.evaluateHand(SFholeCards, SFcommunityCards) == STRAIGHT_FLUSH);

        // Test four of a kind
        assert(handEvaluator.evaluateHand(FKholeCards, FKcommunityCards) == FOUR_OF_A_KIND);

        // Test full house
        assert(handEvaluator.evaluateHand(FHholeCards, FHcommunityCards) == FULL_HOUSE);

        // Test flush
        assert(handEvaluator.evaluateHand(FholeCards, FcommunityCards) == FLUSH);

        // Test straight
        assert(handEvaluator.evaluateHand(SholeCards, ScommunityCards) == STRAIGHT);

        // Test three of a kind
        assert(handEvaluator.evaluateHand(TKholeCards, TKcommunityCards) == THREE_OF_A_KIND);

        // Test two pair
        assert(handEvaluator.evaluateHand(TPholeCards, TPcommunityCards) == TWO_PAIR);

        // Test one pair
        assert(handEvaluator.evaluateHand(OPholeCards, OPcommunityCards) == ONE_PAIR);

        // Test high card
        assert(handEvaluator.evaluateHand(HCholeCards, HCcommunityCards) == HIGH_CARD);

        cout << "All tests passed successfully!" << endl;
    }
};

int main() {
    UnitTest::testHandEvaluator();
    return 0;
}
