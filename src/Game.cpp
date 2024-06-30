#include "Game.h"

// Default constructor
Game::Game(const std::vector<std::string>& playerNames) {
    numPlayers = playerNames.size();
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(Player(playerNames[i]));
    }

    // add an AI player using not default constructor
    //addAIPlayer("Bot");

    smallBlindPlayer = &players[0];
    bigBlindPlayer = &players[1];
    smallBlind = 25;
    bigBlind = 50;
    ante = 5;
    currentBet = bigBlind;

    gameStats.initialize(numPlayers);
}

// 4 AI Game constructor
Game::Game() {
    numPlayers = 4;
    /*
    std::string botName;
    for (int i = 0; i < numPlayers; ++i) {
        botName = "Bot" + std::to_string(i);
        addAIPlayer(botName);
    }
    
    */
    smallBlindPlayer = &players[0];
    bigBlindPlayer = &players[1];
    smallBlind = 25;
    bigBlind = 50;
    ante = 5;
    currentBet = bigBlind;

    gameStats.initialize(numPlayers);
}

// Modified constructor
Game::Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind) : Game(playerNames){
    this->smallBlind = smallBlind;
    this->bigBlind = bigBlind;
}

// Modified constructor
Game::Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind, double ante) : Game(playerNames, smallBlind, bigBlind) {
    this->ante = ante;
}

// Modified constructor
Game::Game(const std::vector<std::string>& playerNames, double smallBlind, double bigBlind, double ante, double maximumRaise, double money) : Game(playerNames, smallBlind, bigBlind, ante){
    this->maxRaise = maximumRaise;
    this->money = money;

    for (size_t i = 0; i < players.size(); i++) {
        gameStats.playerInvestment.at(i) = money;
    }
}

// Helper function to return the index of the inputted player from the "players" vector
int Game::getPlayerIndex(Player& player) {
    for (size_t i = 0; i < players.size(); ++i) {
        if ((players.at(i).getName()) == player.getName()) {
            return i;
        }
    }
    return -1;
}

// Function where big player will be assigned depending on where the small player is
void Game::assignBigPlayer(int smallIndex) {
    int bigIndex;

    if (smallIndex == 0) {
        bigIndex = players.size() - 1;
    } else {
        bigIndex = --smallIndex;
    }

    bigBlindPlayer = &(players[bigIndex]);
}

// Shuffles the deck and distribute two cards to each player
void Game::playRound() {
    deck.shuffle();
    for (size_t i = 0; i < players.size(); i++) {
        players[i].modifyBankroll(ante);
        players[i].modifyActive(true);
        players[i].resetBet();

        gameStats.playerRounds.at(i)++;
    }

    // Assigns the position of the big player based on where the small player is
    assignBigPlayer(getPlayerIndex(*smallBlindPlayer));

    // Both small and big players blinds are modified accordingly
    (*smallBlindPlayer).modifyBankroll(smallBlind);
    (*bigBlindPlayer).modifyBankroll(bigBlind);
}

// Moves smallBlindPlayer and bigBlindPlayer to the next player, as appropriate
void Game::endRound() {
    int newSmallIndex;
    // Moves the position of the dealer to the left one position based off of where dealer was last game
    if (getPlayerIndex(*smallBlindPlayer) == 0) {
        newSmallIndex = players.size() - 1;
    } else {
        newSmallIndex = getPlayerIndex(*smallBlindPlayer) - 1;
    }
    smallBlindPlayer = &players[newSmallIndex];
    assignBigPlayer(getPlayerIndex(*smallBlindPlayer));

    deck.shuffle();
    if (pot != 0) {
        residualPot = pot;
        pot = 0;
    }
}

// Subtract the current bet from the player's bankroll
void Game::check(Player player) {
    player.modifyBankroll(player.getBet());
}

// Subtract the current bet from the player's bankroll
void Game::raise(Player player, double raiseAmount) {
    player.modifyBankroll(player.getBet());
    currentBet = raiseAmount;
}

// Modify player bankroll as necessary
void Game::fold(Player player) {
    player.modifyActive(false);

    for (size_t i = 0; i < players.size(); i++) {
        if (player.getName() == players.at(i).getName()) {
            gameStats.playerFolds.at(i)++;
        }
    }
}

// Add money to a player's bankroll
void Game::borrow(Player player, double borrowAmount) {
    // Gets the players index in the "players" vector
    int playerIndex = getPlayerIndex(player);

    // Modifies player's bankroll
    player.modifyBankroll(-1 * borrowAmount);

    // Adds the players stats into the stats struct
    gameStats.playerInvestment[playerIndex] += borrowAmount;
}

std::vector<Player>& Game::getPlayers() {
    return players;
}

void Game::addPlayer(Player player) {
    players.push_back(player);
}

void Game::removePlayer(Player player) {
    int indexToRemove = getPlayerIndex(player);
    players.erase(players.begin() + indexToRemove);
}

// Deal 3 cards on the table
void Game::dealFlop() {
    for (int i = 0; i < 3; i++) {
        communityCards.push_back(deck.dealCard());
    }
}

// Deal 4th card on the table
void Game::dealTurn() {
    communityCards.push_back(deck.dealCard());
}

// Deal 5th card on the table
void Game::dealRiver() {
    communityCards.push_back(deck.dealCard());
}

// Deal 2 cards to each player
void Game::dealCards() {
    deck.shuffle();  // Shuffle the deck before dealing
    // Ensure deck has enough cards to deal to all players
    if (size_t(deck.getTotalCardsLeft()) < players.size() * 2) {
        throw std::out_of_range("Not enough cards to deal to all players");
    }

    // Deal two cards to each player
    for (int j = 0; j < 2; ++j) {
        for (size_t i = 0; i < players.size(); ++i) {
            players[i].hand.push_back(deck.dealCard());
        }
    }
}

double Game::getCurrentBet() const {
    return currentBet;
}

double Game::getPreviousRaise() const {
    return previousRaise;
}

double Game::getPot() const {
    return pot;
}

std::string Game::getPlayerHand(int playerIndex) const {
    std::string hand = "";
    for (const auto& card : players[playerIndex].hand) {
        hand += card.toString() + " ";
    }
    return hand;
}

const std::vector<Card>& Game::getCommunityCards() const {
    return communityCards;
}

std::vector<string> Game::showHands() {
    std::vector<string> playerHandsMsgVector;
    std::string playerHandsMsg;

    for (const auto& player : players) {
        playerHandsMsg += player.getName() + "'s hand: ";
        for (const auto& card : player.getHand()) {
            playerHandsMsg += card.toString() + " ";
        }
        playerHandsMsg += "\n";
        playerHandsMsgVector.push_back(playerHandsMsg);
    }

    return playerHandsMsgVector;
}

void Game::displayStats() {
    for (size_t i = 0; i < players.size(); i++) {
        std::cout << "Stats for " << players.at(i).getName() << ": " << std::endl;
        std::cout << "Rounds played: " << gameStats.playerRounds.at(i) << std::endl;
        std::cout << "Wins: " << gameStats.playerWins.at(i) << std::endl;
        std::cout << "Folds: " << gameStats.playerFolds.at(i) << std::endl;
        std::cout << "Investment: $" << gameStats.playerInvestment.at(i) << std::endl;
        std::cout << "Profit: $" << gameStats.playerProfit.at(i) << std::endl;
        std::cout << std::endl;
    }
}

std::vector<string> Game::getStats() {
    
    std::vector<string> playerHandsMsgVector;
    std::string playerHandsMsg;
    
    //This is buggy
    /*
    for (size_t i = 0; i < players.size(); i++) {
        playerHandsMsg += "Stats for " << std::to_string(players.at(i).getName()) << ": ";
        playerHandsMsg += "\n";
        playerHandsMsg += "Rounds played: " << std::to_string(gameStats.playerRounds.at(i))
        playerHandsMsg += "\n";
        playerHandsMsg += "Wins: " << std::to_string(gameStats.playerWins.at(i))
        playerHandsMsg += "\n";
        playerHandsMsg += "Folds: " << std::to_string(gameStats.playerFolds.at(i))
        playerHandsMsg += "\n";
        playerHandsMsg += "Investment: $" << std::to_string(gameStats.playerInvestment.at(i))
        playerHandsMsg += "\n";
        playerHandsMsg += "Profit: $" << std::to_string(gameStats.playerProfit.at(i))
        playerHandsMsg += "\n";
        playerHandsMsg += 
        playerHandsMsg += "\n";
        playerHandsMsg += "\n";
        playerHandsMsgVector.push_back(playerHandsMsg);
    }
    */

    return playerHandsMsgVector;
}

int Game::bigBlindPlayerID() {
    for (size_t i = 0; i < players.size(); i++) {
        if (bigBlindPlayer->getName() == players.at(i).getName()) {
            return i;
        }
    }
    return -1;
}

double Game::getMinRaise() {
    return currentBet + previousRaise;
}

double Game::getMaxRaise() {
    return currentBet + maxRaise;
}

// Function for determining winner and distributing pot
std::vector<Player> Game::determineWinner() {
    std::vector<Player> activePlayers;
    for (const auto& player : players) {
        if (player.isActive()) {
            activePlayers.push_back(player);
        }
    }

    HandEvaluator handEvaluator;
    std::vector<Player> winners;
    Player bestPlayer = activePlayers.at(0);
    auto bestPlayerHand = activePlayers.at(0).getHand();

    for (size_t i = 1; i < activePlayers.size(); i++) {
        auto tempPlayerHand = activePlayers.at(i).getHand();

        if (HandEvaluator::compareHand(bestPlayerHand, tempPlayerHand, communityCards) == -1) {
            bestPlayerHand = tempPlayerHand;
            bestPlayer = activePlayers.at(i);
        }
    }

    double modifiedPot = pot + residualPot;
    residualPot = 0;

    winners.push_back(bestPlayer);
    for (size_t i = 0; i < activePlayers.size(); i++) {
        auto tempPlayerHand = activePlayers.at(i).getHand();
        if (HandEvaluator::compareHand(bestPlayerHand, tempPlayerHand, communityCards) == 0) {
            winners.push_back(activePlayers.at(i));
        }
    }

    for (size_t i = 0; i < winners.size(); i++) {
        winners.at(i).modifyBankroll(modifiedPot / winners.size());
        pot -= modifiedPot / winners.size();
    }

    for (size_t i = 0; i < winners.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            if (winners.at(i).getName() == players.at(j).getName()) {
                players.at(j).modifyBankroll(modifiedPot / winners.size());
            }
        }
    }

    for (size_t i = 0; i < winners.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            if (winners.at(i).getName() == players.at(j).getName()) {
                gameStats.playerWins.at(j)++;
                gameStats.playerProfit.at(j) = players.at(j).getBankroll() - gameStats.playerInvestment.at(j);
            }
        }
    }

    return winners;
}
std::vector<Card> Game::getPlayerHandByUsername(const std::string& username) const {
    for (const auto& player : players) {
        if (player.getName() == username) {
            return player.getHand();
        }
    }
    return {};
}

// PUT IN GAME.CPP
// returns vector of the number of wins
std::vector<int> Game::getWins() {
    std::vector<int> winsVector;
    for (unsigned int i = 0; i < gameStats.playerWins.size(); i++) {
        winsVector.push_back(gameStats.playerWins.at(i));
    }
    return winsVector;
}

// add AI player
void Game::addAIPlayer(const std::string& name) {
    HandEvaluator* handEvaluator = new HandEvaluator();
    players.push_back(Player(name, 0, 0, true, handEvaluator));
}