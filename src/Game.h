#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Player.h"
#include "Deck.h"
#include "HandEvaluator.h"
#include "ai.h"

class Game {
public:
    Game(const std::vector<std::string>& playerNames);
    Game(); //starts game with 4 AI
    Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind);
    Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind, double ante);
    Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind, double ante, double maximumRaise, double money);

    void playRound();
    void endRound();
    void check(Player player);
    void raise(Player player, double raiseAmount);
    void fold(Player player);
    void borrow(Player player, double borrowAmount);
    std::vector<Player>& getPlayers();
    void addPlayer(Player player);
    void removePlayer(Player player);
    void dealFlop();
    void dealTurn();
    void dealRiver();
    void dealCards();
    double getCurrentBet() const;
    double getPreviousRaise() const;
    double getPot() const;
    std::string getPlayerHand(int playerIndex) const;
    const std::vector<Card>& getCommunityCards() const;
    std::vector<string> showHands();
    void displayStats();
    int bigBlindPlayerID();
    double getMinRaise();
    double getMaxRaise();
    std::vector<Player> determineWinner();
    std::vector<Card> getPlayerHandByUsername(const std::string& username) const;
    std::vector<string> getStats();

    // optional
    std::vector<int> getWins();
private:
    void addAIPlayer(const std::string& name);

    std::vector<Player> players;
    Player* smallBlindPlayer;
    Player* bigBlindPlayer;
    Deck deck;
    double smallBlind;
    double bigBlind;
    double ante;
    double maxRaise;
    double money;
    double currentBet;
    double previousRaise;
    double pot;
    double residualPot;
    std::vector<Card> communityCards;
    int numPlayers;

    struct {
        std::vector<double> playerInvestment;
        std::vector<double> playerProfit;
        std::vector<int> playerRounds;
        std::vector<int> playerWins;
        std::vector<int> playerFolds;

        void initialize(int numPlayers) {
            playerInvestment.resize(numPlayers);
            playerProfit.resize(numPlayers);
            playerRounds.resize(numPlayers);
            playerWins.resize(numPlayers);
            playerFolds.resize(numPlayers);
        }
    } gameStats;

    int getPlayerIndex(Player& player);
    void assignBigPlayer(int smallIndex);
};
