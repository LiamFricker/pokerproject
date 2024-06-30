#include "Player.h"
#include <iostream>

Player::Player(const string name) : bet(0), bankroll(0), name(name), m_isActive(true), m_isAI(false), pokerAI(nullptr) {}

Player::Player(const string name, double bankroll, double bet, bool isAI, HandEvaluator* handEvaluator) :
    bet(bet), bankroll(bankroll), name(name), m_isActive(true), m_isAI(isAI) {
    if (isAI && handEvaluator != nullptr) {
        pokerAI = nullptr;//new PokerAI(*handEvaluator);
    } else {
        pokerAI = nullptr;
    }
}

void Player::receiveCard(const Card& card) {
    hand.push_back(card);
}

void Player::showHand() const {
    for (const auto& card : hand) {
        cout << card.toString() << endl;
    }
}

vector<Card> Player::getHand() const {
    return hand;
}

void Player::placeBet(int amount) {
    bet += amount;
}

int Player::getBet() const {
    return bet;
}

//sets bet amount
void Player::setBet(int bet) {
    this->bet = bet;
}

void Player::resetBet() {
    bet = 0;
}

int Player::getBankroll() const {
    return bankroll;
}

void Player::resetBankroll() {
    bankroll = 0;
}

int Player::modifyBankroll(int amount) {
    bankroll -= amount;
    if (bankroll < 0) {
        return 1;
    } else {
        return 0;
    }
}

string Player::getName() const {
    return name;
}

bool Player::isActive() const {
    return m_isActive;
}

void Player::modifyActive(bool isPlayerActive) {
    m_isActive = isPlayerActive;
}

bool Player::isAI() const {
    return m_isAI;
}

std::string Player::makeDecision(const std::vector<Card>& communityCards) {
    if (m_isAI && pokerAI) {
        return "boom";//pokerAI->makeDecision(hand, communityCards);
    }
    return "";
}
