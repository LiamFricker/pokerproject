#include "HandEvaluator.h"
#include <algorithm>
#include <iostream>

    /*
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
    */

HandEvaluator::HandEvaluator() {}

// evaluate one hand
// integer values returns rank of hand
int HandEvaluator::evaluateHand(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    int rank = -1;

    try {
        if (isRoyalFlush(hand, communityCards) != 0) {
            rank = ROYAL_FLUSH;
            return rank;
        } else if (isStraightFlush(hand, communityCards) != 0) {
            rank = STRAIGHT_FLUSH;
            return rank;
        } else if (isFourOfAKind(hand, communityCards) != 0) {
            rank = FOUR_OF_A_KIND;
            return rank;
        } else if (isFullHouse(hand, communityCards) != 0) {
            rank = FULL_HOUSE;
            return rank;
        } else if (isFlush(hand, communityCards) != 0) {
            rank = FLUSH;
            return rank;
        } else if (isStraight(hand, communityCards) != 0) {
            rank = STRAIGHT;
            return rank;
        } else if (isThreeOfAKind(hand, communityCards) != 0) {
            rank = THREE_OF_A_KIND;
            return rank;
        } else if (isTwoPair(hand, communityCards) != 0) {
            rank = TWO_PAIR;
            return rank;
        } else if (isPair(hand, communityCards) != 0) {
            rank = ONE_PAIR;
            return rank;
        } else {
            rank = HIGH_CARD;
            return rank;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in evaluateHand: " << e.what() << "\n";
    }

    return rank;
}

// compares hand 1 and hand 2
// returns 0 if tied
// returns 1 if hand1 is winning
// returns 2 if hand2 is winning
int HandEvaluator:: compareHand(const std::vector<Card>& hand1, const std::vector<Card>& hand2, const std::vector<Card>& communityCards) {

    int hand1rank = evaluateHand(hand1, communityCards);
    int hand2rank = evaluateHand(hand2, communityCards);

    int hand1_tiebreak;
    int hand2_tiebreak;

    if (hand1rank > hand2rank) {
        return 1;
    }
    if (hand1rank < hand2rank) {
        return 2;
    }
    if (hand1rank == hand2rank) {
        // begin comparing who has the "better hand"
        // example: straight with 10 high is better than straight with 8 high
        switch(hand1rank) {
            case HIGH_CARD:
                return highCardComparison(hand1, hand2, communityCards, static_cast<unsigned int> (5), static_cast<unsigned int> (0));
                break;
            case ONE_PAIR:
                hand1_tiebreak = HandEvaluator::isPair(hand1, communityCards);
                hand2_tiebreak = HandEvaluator::isPair(hand2, communityCards);
                if (hand1_tiebreak == hand2_tiebreak) {
                    return highCardComparison(hand1, hand2, communityCards, static_cast<unsigned int> (3), static_cast<unsigned int> (hand1_tiebreak));
                }
                break;
            case TWO_PAIR:
                hand1_tiebreak = isTwoPair(hand1, communityCards);
                hand2_tiebreak = isTwoPair(hand2, communityCards);
                if (hand1_tiebreak == hand2_tiebreak) {
                    return highCardComparison(hand1, hand2, communityCards, static_cast<unsigned int> (1), static_cast<unsigned int> (hand1_tiebreak));
                }
                break;
            case THREE_OF_A_KIND:
                hand1_tiebreak = isThreeOfAKind(hand1, communityCards);
                hand2_tiebreak = isThreeOfAKind(hand2, communityCards);
                if (hand1_tiebreak == hand2_tiebreak) {
                    return highCardComparison(hand1, hand2, communityCards,static_cast<unsigned int> (2), static_cast<unsigned int> (hand1_tiebreak));
                }
                break;
            case STRAIGHT:
                hand1_tiebreak = isStraight(hand1, communityCards);
                hand2_tiebreak = isStraight(hand2, communityCards);
                break;
            case FLUSH:
                hand1_tiebreak = isFlush(hand1, communityCards);
                hand2_tiebreak = isFlush(hand2, communityCards);
                break;
            case FULL_HOUSE:
                hand1_tiebreak = isFullHouse(hand1, communityCards);
                hand2_tiebreak = isFullHouse(hand2, communityCards);
                if (hand1_tiebreak == hand2_tiebreak) {
                    hand1_tiebreak = isPair(hand1, communityCards);
                    hand2_tiebreak = isPair(hand2, communityCards);
                }
                break;
            case FOUR_OF_A_KIND:
                hand1_tiebreak = isFourOfAKind(hand1, communityCards);
                hand2_tiebreak = isFourOfAKind(hand2, communityCards);
                break;
            case STRAIGHT_FLUSH:
                hand1_tiebreak = isStraightFlush(hand1, communityCards);
                hand2_tiebreak = isStraightFlush(hand2, communityCards);
                break;
            case ROYAL_FLUSH:
                hand1_tiebreak = isRoyalFlush(hand1, communityCards);
                hand2_tiebreak = isRoyalFlush(hand2, communityCards);
                break;
        }

        // modify ace so it is easier to compute (1 becomes 14)
        hand1_tiebreak = hand1_tiebreak == 1 ? 14 : hand1_tiebreak;
        hand2_tiebreak = hand2_tiebreak == 1 ? 14 : hand2_tiebreak;

        if (hand1_tiebreak > hand2_tiebreak) {
            return 1;
        }
        if (hand1_tiebreak < hand2_tiebreak) {
            return 2;
        }
        if (hand1_tiebreak == hand2_tiebreak) {
            return 0;
        }
    }
    return 0;
}

// compares numCards from hand 1 and hand 2
// returns 0 if tied
// returns 1 if hand1 is winning
// returns 2 if hand2 is winning
int HandEvaluator::highCardComparison(const vector<Card>& hand1, const std::vector<Card>& hand2, const std::vector<Card>& communityCards, unsigned int numCards, unsigned int comboValue) {

    std::vector<int> array1;
    std::vector<int> array2;
    unsigned int numCardsToCompare = 5;

    // Adding values from hand1 and communityCards to array1
    for (const auto& card : hand1) {
        array1.push_back(card.getValue());
    }
    for (const auto& card : communityCards) {
        array1.push_back(card.getValue());
    }
    // Adding values from hand2 and communityCards to array2
    for (const auto& card : hand2) {
        array2.push_back(card.getValue());
    }
    for (const auto& card : communityCards) {
        array2.push_back(card.getValue());
    }

    if (numCards == 3) { // pair case
        numCardsToCompare = numCards;
        // Remove all instances of comboValue in array1
        array1.erase(std::remove(array1.begin(), array1.end(), comboValue), array1.end());
        // Remove all instances of comboValue in array2
        array2.erase(std::remove(array2.begin(), array2.end(), comboValue), array2.end());
    }
    if (numCards == 1) { // two pair case
        numCardsToCompare = numCards;
        if (secondPairInTwoPair(hand1, communityCards) > secondPairInTwoPair(hand2, communityCards) ) {
            return 1;
        }
        if (secondPairInTwoPair(hand1, communityCards) < secondPairInTwoPair(hand2, communityCards) ) {
            return 2;
        }

        // handle exceptions
        if (secondPairInTwoPair(hand1, communityCards) == secondPairInTwoPair(hand2, communityCards) ) {
            // Remove all instances of comboValue in array1
            array1.erase(std::remove(array1.begin(), array1.end(), comboValue), array1.end());
            // Remove all instances of comboValue in array2
            array2.erase(std::remove(array2.begin(), array2.end(), comboValue), array2.end());

            int secondPair = secondPairInTwoPair(hand1, communityCards);
            // Remove all instances of secondPair in array1
            array1.erase(std::remove(array1.begin(), array1.end(), secondPair), array1.end());
            // Remove all instances of secondPair in array2
            array2.erase(std::remove(array2.begin(), array2.end(), secondPair), array2.end());
        }
    }
    if (numCards == 2) { // three of a kind case
        numCardsToCompare = numCards;
        // Remove all instances of comboValue in array1
        array1.erase(std::remove(array1.begin(), array1.end(), comboValue), array1.end());
        // Remove all instances of comboValue in array2
        array2.erase(std::remove(array2.begin(), array2.end(), comboValue), array2.end());
    }

    // Sort array1 in descending order
    std::sort(array1.begin(), array1.end(), [](int a, int b) {
        return a > b;
    });
    // Sort array2 in descending order
    std::sort(array2.begin(), array2.end(), [](int a, int b) {
        return a > b;
    });

    unsigned int i = 0;
    while (i < numCardsToCompare) {
        while (i < array1.size() && i < array2.size() ) {
            if (array1.at(i) > array2.at(i)) {
                return 1; // hand1 wins
            }
            if (array1.at(i) < array2.at(i)) {
                return 2; // hand2 wins
            }
            i++;
        }
    }

    return 0; // it's tied
}

int HandEvaluator:: secondPairInTwoPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0, num11 = 0, num12 = 0, num13 = 0;
    int numPairs = 0;
    // the value of the largest pair, aka if I have a two pair of 10 and 8, numLargestPair would be 8
    int numLargestPair;
    int secondLargestPair = 0;

    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getValue()) {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            case 7:
                num7++;
                break;
            case 8:
                num8++;
                break;
            case 9:
                num9++;
                break;
            case 10:
                num10++;
                break;
            case 11:
                num11++;
                break;
            case 12:
                num12++;
                break;
            case 13:
                num13++;
                break;
        }
    }

    // check for pairs
    if (num2 == 2){
        numPairs++;
        numLargestPair = 2;
    }
    if (num3 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 3;
    }
    if (num4 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 4;
    }
    if (num5 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 5;
    }
    if (num6 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 6;
    }
    if (num7 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 7;
    }
    if (num8 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 8;
    }
    if (num9 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 9;
    }
    if (num10 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 10;
    }
    if (num11 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 11;
    }
    if (num12 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 12;
    }
    if (num13 == 2){
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 13;
    }
    if (num1 == 2) {
        numPairs++;
        secondLargestPair = numLargestPair;
        numLargestPair = 1;
    }

    // if there are at least two pairs, return numLargestPair
    // note that the biggest is the ACE
    // 1, 13, 12, 11, ... 3, 2
    if (numPairs >= 2) {
        return secondLargestPair;
    }
    else {
        // no second largest pair
        return 0;
    }
}

int HandEvaluator:: isRoyalFlush(const std::vector<Card>& hand, const std::vector<Card>& communityCards){
    int straightNum = isStraight(hand, communityCards);
    int flushNum = isFlush(hand, communityCards);

    if (flushNum > 0) {
        if (straightNum == 1) {
            // note Royal Flush means 10, 11, 12, 13, 1
            // which means that the highest card is 1, or Ace
            return straightNum;
        }
    }

    // otherwise no royal flush found, return 0
    return 0;
}
int HandEvaluator:: isStraightFlush(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    int straightNum = isStraight(hand, communityCards);
    int flushNum = isFlush(hand, communityCards);

    if (flushNum > 0) {
        if (straightNum > 0) {
            return straightNum;
        }
    }

    // otherwise no straight flush found, return 0
    return 0;
}

int HandEvaluator:: isFlush(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    int numHearts = 0;
    int numDiamonds = 0;
    int numSpades = 0;
    int numClubs = 0;

    // int holding largest value in a potential flush
    int largestHearts = 0;
    int largestDiamonds = 0;
    int largestSpades = 0;
    int largestClubs = 0;

    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    // count the card suits
    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getSuit()) {
            case HEARTS:
                numHearts++;
                // assign the largest value in the flush
                if (combinedCards.at(i).getValue() > largestHearts) {
                    // handle ace high
                    if (largestHearts != 1) {
                        largestHearts = combinedCards.at(i).getValue();
                    }
                }
                break;
            case DIAMONDS:
                numDiamonds++;
                // assign the largest value in the flush
                if (combinedCards.at(i).getValue() > largestDiamonds) {
                    // handle ace high
                    if (largestDiamonds != 1) {
                        largestDiamonds = combinedCards.at(i).getValue();
                    }
                }
                break;
            case CLUBS:
                numClubs++;
                // assign the largest value in the flush
                if (combinedCards.at(i).getValue() > largestClubs) {
                    // handle ace high
                    if (largestClubs != 1) {
                        largestClubs = combinedCards.at(i).getValue();
                    }
                }
                break;
            case SPADES:
                numSpades++;
                // assign the largest value in the flush
                if (combinedCards.at(i).getValue() > largestSpades) {
                    // handle ace high
                    if (largestSpades != 1) {
                        largestSpades = combinedCards.at(i).getValue();
                    }
                }
            break;
        }
    }

    // check if there are 5 cards
    if (numSpades >= 5) {
        return largestSpades;
    }
    if (numHearts >= 5) {
        return largestHearts;
    }
    if (numDiamonds >= 5) {
        return largestDiamonds;
    }
    if (numClubs >= 5) {
        return largestClubs;
    }

    // if no flush is found, return 0
    return 0;
}

int HandEvaluator:: isFullHouse(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {

    int pairNum = isPair(hand, communityCards);
    int tripletNum = isThreeOfAKind(hand, communityCards);

    if (tripletNum > 0 && pairNum > 0) {
        // full house found
        return tripletNum;
    }

    // no full house found
    return 0;
}

int HandEvaluator:: isStraight(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    // create a new vector with cards from the hand and the table
    std::vector <Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    int straightHigh = 0;
    int straightLength = 1;
    int aceHighStraightLength = 1;
    //int aceLowStraightLength = 1;

    // Sort combinedCards
    std::sort(combinedCards.begin(), combinedCards.end(), [](const Card &a, const Card &b) {
        return a.getValue() < b.getValue();
    });

    // Remove duplicate ranks
    auto last = std::unique(combinedCards.begin(), combinedCards.end(), [](const Card &a, const Card &b) {
        return a.getValue() == b.getValue();
    });
    combinedCards.erase(last, combinedCards.end());

    // Regular straight check (ace high and ace low will be handled separately)
    if (combinedCards.at(0).getValue() != 1) {
        for (size_t i = 1; i < combinedCards.size(); ++i) {
            if (combinedCards[i].getValue() == combinedCards[i - 1].getValue() + 1) { // Check if consecutive
                straightLength++;
                if (straightLength >= 5) {
                    straightHigh = combinedCards[i].getValue(); // Update highest card in straight (will be returned)
                }
            } else if (combinedCards[i].getValue() != combinedCards[i - 1].getValue()) {
                straightLength = 1; // Reset straight length if not consecutive
            }
        }
    }

    // note: ace = 1, two = 2, ... king = 13
    // Handle Ace High (10, J, Q, K, A)
    // since combinedCards is sorted, if the first card is 1 and last is 13, then handle ace high exception
    else if (combinedCards.back().getValue() == 13 && combinedCards[0].getValue() == 1) {
        for (size_t i = 1; i < combinedCards.size(); ++i) {
            if (combinedCards[i].getValue() == 10) {
                aceHighStraightLength++;
                for (size_t j = i + 1; j < combinedCards.size(); ++j) {
                    if (combinedCards[j].getValue() == combinedCards[j-1].getValue() + 1) {
                        aceHighStraightLength++;
                        if (aceHighStraightLength >= 5) {
                            return 1; // Return 1 for Ace High
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // Handle Ace Low (A, 2, 3, 4, 5)
    else if (combinedCards.back().getValue() == 5 && combinedCards[0].getValue() == 1) {
        int aceLowStraightLength = 1;
        for (size_t i = 1; i < combinedCards.size(); ++i) {
            if (combinedCards[i].getValue() == 2) { // Look for 2 to start Ace-low straight check
                aceLowStraightLength++;
                for (size_t j = i + 1; j < combinedCards.size(); ++j) {
                    if (combinedCards[j].getValue() == combinedCards[j-1].getValue() + 1) {
                        aceLowStraightLength++;
                        if (aceLowStraightLength >= 5) {
                            return 5; // Return 5 for Ace Low
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // if straight found, return highest card value. Otherwise, return 0
    return (straightLength >= 5) ? straightHigh : 0;
}



int HandEvaluator:: isPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0, num11 = 0, num12 = 0, num13 = 0;

    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getValue()) {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            case 7:
                num7++;
                break;
            case 8:
                num8++;
                break;
            case 9:
                num9++;
                break;
            case 10:
                num10++;
                break;
            case 11:
                num11++;
                break;
            case 12:
                num12++;
                break;
            case 13:
                num13++;
                break;
        }
    }

    // Check each counter for a Pair (Two of a Kind)
    if (num1 == 2) return 1;
    if (num13 == 2) return 13;
    if (num12 == 2) return 12;
    if (num11 == 2) return 11;
    if (num10 == 2) return 10;
    if (num9 == 2) return 9;
    if (num8 == 2) return 8;
    if (num7 == 2) return 7;
    if (num6 == 2) return 6;
    if (num5 == 2) return 5;
    if (num4 == 2) return 4;
    if (num3 == 2) return 3;
    if (num2 == 2) return 2;

    // If no Pair is found, return 0
    return 0;
}

int HandEvaluator:: isTwoPair(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {
    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0, num11 = 0, num12 = 0, num13 = 0;
    int numPairs = 0;
    // the value of the largest pair, aka if I have a two pair of 10 and 8, numLargestPair would be 8
    int numLargestPair;

    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getValue()) {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            case 7:
                num7++;
                break;
            case 8:
                num8++;
                break;
            case 9:
                num9++;
                break;
            case 10:
                num10++;
                break;
            case 11:
                num11++;
                break;
            case 12:
                num12++;
                break;
            case 13:
                num13++;
                break;
        }
    }

    // check for pairs
    if (num2 == 2){
        numPairs++;
        numLargestPair = 2;
    }
    if (num3 == 2){
        numPairs++;
        numLargestPair = 3;
    }
    if (num4 == 2){
        numPairs++;
        numLargestPair = 4;
    }
    if (num5 == 2){
        numPairs++;
        numLargestPair = 5;
    }
    if (num6 == 2){
        numPairs++;
        numLargestPair = 6;
    }
    if (num7 == 2){
        numPairs++;
        numLargestPair = 7;
    }
    if (num8 == 2){
        numPairs++;
        numLargestPair = 8;
    }
    if (num9 == 2){
        numPairs++;
        numLargestPair = 9;
    }
    if (num10 == 2){
        numPairs++;
        numLargestPair = 10;
    }
    if (num11 == 2){
        numPairs++;
        numLargestPair = 11;
    }
    if (num12 == 2){
        numPairs++;
        numLargestPair = 12;
    }
    if (num13 == 2){
        numPairs++;
        numLargestPair = 13;
    }
    if (num1 == 2) {
        numPairs++;
        numLargestPair = 1;
    }

    // if there are at least two pairs, return numLargestPair
    // note that the biggest is the ACE
    // 1, 13, 12, 11, ... 3, 2
    if (numPairs >= 2) {
        return numLargestPair;
    }
    else {
        // no two pair
        return 0;
    }
}

int HandEvaluator::isThreeOfAKind(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {

    int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0, num11 = 0, num12 = 0, num13 = 0;

    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getValue()) {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            case 7:
                num7++;
                break;
            case 8:
                num8++;
                break;
            case 9:
                num9++;
                break;
            case 10:
                num10++;
                break;
            case 11:
                num11++;
                break;
            case 12:
                num12++;
                break;
            case 13:
                num13++;
                break;
        }
    }

    // Check each counter for a count of 3
    if (num1 == 3) return 1;
    if (num2 == 3) return 2;
    if (num3 == 3) return 3;
    if (num4 == 3) return 4;
    if (num5 == 3) return 5;
    if (num6 == 3) return 6;
    if (num7 == 3) return 7;
    if (num8 == 3) return 8;
    if (num9 == 3) return 9;
    if (num10 == 3) return 10;
    if (num11 == 3) return 11;
    if (num12 == 3) return 12;
    if (num13 == 3) return 13;

    // If no Three of a Kind is found, return 0
    return 0;
}

int HandEvaluator:: isFourOfAKind(const std::vector<Card>& hand, const std::vector<Card>& communityCards) {

    int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0, num11 = 0, num12 = 0, num13 = 0;

    // create a new vector with cards from the hand and the table
    std::vector<Card> combinedCards = hand;
    combinedCards.insert(combinedCards.end(), communityCards.begin(), communityCards.end());

    for (int i = 0; i < static_cast<int>(combinedCards.size()); i++) {
        switch(combinedCards.at(i).getValue()) {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            case 7:
                num7++;
                break;
            case 8:
                num8++;
                break;
            case 9:
                num9++;
                break;
            case 10:
                num10++;
                break;
            case 11:
                num11++;
                break;
            case 12:
                num12++;
                break;
            case 13:
                num13++;
                break;
        }
    }

    // Check each counter for a count of 4
    if (num1 == 4) return 1;
    if (num2 == 4) return 2;
    if (num3 == 4) return 3;
    if (num4 == 4) return 4;
    if (num5 == 4) return 5;
    if (num6 == 4) return 6;
    if (num7 == 4) return 7;
    if (num8 == 4) return 8;
    if (num9 == 4) return 9;
    if (num10 == 4) return 10;
    if (num11 == 4) return 11;
    if (num12 == 4) return 12;
    if (num13 == 4) return 13;

    // If no Four of a Kind is found, return 0
    return 0;
}
