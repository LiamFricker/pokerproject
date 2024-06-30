#include <iostream>
#include <vector>
#include <cassert>
#include "Game.h"

using namespace std;

class GameUnitTest {
public:
    static void testGame() {

        // create test player names
        std::vector<std::string>& testPlayerNames;
        testPlayerNames.push_back("player1");
        testPlayerNames.push_back("player2");

        // test constructors
        Game game(testPlayerNames, 1, 2);
        assert(game.getPlayers().size() == 2);
        Game game(testPlayerNames, 1, 2, 3);
        assert(game.getPlayers().size() == 2);
        Game game(testPlayerNames, 1, 2, 3, 4, 5);
        assert(game.getPlayers().size() == 2);

        // test default constructor
        Game game(testPlayerNames);
        assert(game.getPlayers().size() == 2);

        // store testPlayers
        std::vector<Player>& testPlayers = getPlayers();

        // test game process
        game.playRound();
        game.dealCards();
        assert(testPlayers.at(0).getHand().size() > 0);
        assert(bigBlindPlayerID() != -1);
        game.dealFlop();
        game.dealTurn();
        game.dealRiver();
        assert(game.getCommunityCards().size() >= 5);
        game.endRound();
        assert(bigBlindPlayerID() != -1);

        // test check, raise, fold
        game.check(testPlayers.at(0));
        assert(testPlayers.at(0).getBet() != 0);
        double previousBet = game.getCurrentBet();
        game.raise(testPlayers.at(0), 1000);
        assert(game.getCurrentBet() >= previousBet);
        game.fold(testPlayers.at(0));
        assert(testPlayers.at(0).isActive() == false);

        // test other functions
        assert(game.getMinRaise() >= 0);
        assert(game.getMaxRaise() >= 0);
        assert(game.bigBlindPlayerID() != -1);
        assert(game.getPot() != 0);
        assert(game.getCurrentBet() != 0);
        assert(game.getPreviousRaise() != 0);

        // test winner evaluation
        std::vector<Player> winners = determineWinner();
        assert(winners.size() > 0);

        cout << "All tests passed successfully!" << endl;
    }
};

int main() {
    GameUnitTest::testGame();
    return 0;
}

