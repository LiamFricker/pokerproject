#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "ai.h"
#include <vector>
#include <string>

using namespace std;

class Player {
public:
    // default Player() constructor, let bankroll = 0 and bet = 0
    Player(const string name);

    // modified Player() constructor
    Player(const string name1, double bankroll1, double bet1, bool isAI = false, HandEvaluator* handEvaluator = nullptr);

    // returns the player's name
    string getName() const;

    // adds amount to the current bet value
    // removes money from the bankroll
    void placeBet(int amount);

    // gets the bet
    int getBet() const;

    //sets bet amount
    void setBet(int bet);

    // resets bet to 0
    void resetBet();

    // gets the bankroll
    int getBankroll() const;

    // resets bankroll to 0
    void resetBankroll();

    // subtracts the amount from the bankroll
    // if the function returns 0, bankroll is positive
    // if the function returns 1, bankroll is negative aka bet invalid
    int modifyBankroll(int amount);

    // adds a card to a hand
    void receiveCard(const Card& card);

    // displays the current hand
    void showHand() const;

    // returns whether or not player is active
    // aka the player has not folded
    bool isActive() const;

    // sets player's active status to isPlayerActive
    void modifyActive(bool isPlayerActive);

    // checks if player is AI
    bool isAI() const;

    // returns the hand
    vector<Card> getHand() const;

    // the player's hand
    vector<Card> hand;

    // AI decision making method
    string makeDecision(const vector<Card>& communityCards);

private:

    // amount of money the player is betting in the current round
    double bet;

    // amount of money the player has
    double bankroll;

    // name of the player
    string name;

    bool m_isActive;
    bool m_isAI;
    PokerAI* pokerAI; // AI instance
};

#endif
