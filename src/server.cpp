#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"

std::vector<int> clients;
std::map<int, std::string> clientUsernames;
Game* game = nullptr;

//USE THIS TO ALTER ALL NON SPECIFIC MESSAGES
std::string baseMessage = "-1,DO NOT CHOOSE THIS NAME,999,";

void broadcastMessage(const std::string& message) {
    for (int client : clients) {
        send(client, message.c_str(), message.size(), 0);
    }
}


// added code
// helper function
void betting(Game* game, int client_socket) {
    //bool isCheck;
    //bool isRaise;
    //bool isFold;
    bool didSomeoneRaise;
    bool isEndOfBetting = false;
    //double raiseAmount;
    std::string playername;

    while (isEndOfBetting == false) {
         didSomeoneRaise = false; // reset bool
         int i = 4;
         for (auto& player : game->getPlayers() ) { 
            //printf("IN THE LOOP\n"); 
            playername = player.getName();
            //playerNames
            broadcastMessage("8," + playername + "," + to_string(i) + ",Make your bet: " + playername);
            char buffer[1024];
            memset(buffer, 0, 1024);
            //std::cout << "HELP ME" << endl;
            int bytesRead = recv(i, buffer, 1024, 0);
            i++;
            //std::cout << "HELP ME" << endl;
            
            if (bytesRead <= 0) {
                //printf("fsajkfsafafasafsfasafsfas\n");
                std::cerr << "Error reading username from client: " << client_socket << std::endl;
                //close(client_socket);
                //clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
                //return;
            }
            
            //printf("bet received\n");
            //std::cout << "HELP ME" << endl;
            std::string betting_info(buffer);
            int betType = std::stoi(betting_info.substr(0,1));
            int raiseAmount = std::stoi(betting_info.substr(2,10));
         
            //std::cout << "bet type: " << betType << std::endl;
            // reset variables
            
            
            
            switch(betType){
                case(1):
                    game->check(player);
                    broadcastMessage(baseMessage + playername + " has checked\n");
                    break;
                case(0):
                    game->fold(player);
                    broadcastMessage(baseMessage + playername + " has folded\n");
                    break;
                case(2):
                {
                    game->raise(player, raiseAmount);
                    std::string akskfmkf_message = playername + " has raised " + std::to_string(raiseAmount) + "\n";
                    broadcastMessage(baseMessage + akskfmkf_message);
                    didSomeoneRaise = true;
                    break;
                }
                default:
                    game->fold(player);
                    broadcastMessage(baseMessage + playername + " has folded\n");
                    printf("Something went wrong with betting parsing");
            
            }
            
            //printf("switch ended received\n");
            //raiseAmount = raisin;

            

            // wait until the GUI input is received for client
            // update either isCheck, isRaise, or isFold
            // update raiseAmount if isRaise = true

            // for reference
            // void check(Player player);
            // void raise(Player player, double raiseAmount);
            // void fold(Player player);
            /*
                if (isCheck) {
                    
                }
                if (isRaise) {
                    
                }
                if (isFold) {
                    
                }
            */
        }
        if (didSomeoneRaise) {
            isEndOfBetting = false;
            // loop through the players again
        }
        else {
            isEndOfBetting = true;
        }
    }
}

void handleClient(int client_socket) {
    char buffer[1024];
    memset(buffer, 0, 1024);
    int bytesRead = recv(client_socket, buffer, 1024, 0);
    //TODO: AI implementation is needed.
    //TODO: Handle Room/Password
    //TODO: Make this compatible with the Menu GUI
    if (bytesRead <= 0) {
        std::cerr << "Error reading username from client: " << client_socket << std::endl;
        close(client_socket);
        clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
        return;
    }
    std::string username(buffer);
    clientUsernames[client_socket] = username;
    std::cout << username << " has connected. Socket: " << client_socket << std::endl;
    broadcastMessage(baseMessage + username + " has connected\n");

    if (clients.size() == 4) {
        std::vector<std::string> playerNames;
        for (const auto& pair : clientUsernames) {
            playerNames.push_back(pair.second);
        }
        game = new Game(playerNames);

            game->playRound();
            // Added code
            // call playRound to shuffle to deck and assign big blind/small blind

        game->dealCards(); // Deal initial cards
        std::string gameState = "Game started!\n";
        broadcastMessage(baseMessage + gameState);
        for (int client : clients) {
            for (const auto& card : game->getPlayerHandByUsername(clientUsernames[client])) {
                std::string cardMessage = "1,DO NOT CHOOSE THIS NAME,999," + card.toString() + " -1";
                //TODO: Need to send all card information to every client.
                send(client, cardMessage.c_str(), cardMessage.size(), 0);
            }
        }

            // Added code
            // Betting before the flop    
        broadcastMessage(baseMessage + "Place your bets for the preflop\n");
        //cout << "Client socket: " << client_socket << endl;
        betting(game, client_socket);

        // Deal the flop
        game->dealFlop();
        broadcastMessage(baseMessage + "Dealing the flop...\n");
        for (const auto& card : game->getCommunityCards()) {
            //TODO: Need to parse this info at clientside.
            broadcastMessage("2,DO NOT CHOOSE THIS NAME,999," + card.toString() + " -1");
        }

        // Prompt for bets
        //TODO: All betting is bugged.
        //Betting stage needs to send betting info to all players each time.
        broadcastMessage(baseMessage + "Place your bets for the flop\n");

        // Deal the turn
        game->dealTurn();
        broadcastMessage(baseMessage + "Dealing the turn...\n");
        for (const auto& card : game->getCommunityCards()) {
            //TODO: Need to parse this info at clientside.
            broadcastMessage("2,DO NOT CHOOSE THIS NAME,999," + card.toString() + " -1");
        }

        // Prompt for bets
        broadcastMessage(baseMessage + "Place your bets for the turn\n");
        betting(game, client_socket);

        // Deal the river
        game->dealRiver();
        broadcastMessage(baseMessage + "Dealing the river...\n");
        for (const auto& card : game->getCommunityCards()) {
            //TODO: Need to parse this info at clientside.
            broadcastMessage("2,DO NOT CHOOSE THIS NAME,999," + card.toString() + " -1");
        }

        // Prompt for bets
        broadcastMessage(baseMessage + "Place your bets for the river\n");
        betting(game, client_socket);

        game->endRound();
        // Added code
        // call endRound to reassign big and small blind, as well as reset the pot

        // Added code
        // std::vector<Player> determineWinner(); for reference
        std::vector<Player> winners = game->determineWinner();
        std::string winnerMessage;
        for (auto winner : winners) {
            std::string playername = winner.getName();
            winnerMessage += playername + " ";
        }
        winnerMessage += "has won\n";
        broadcastMessage(baseMessage + winnerMessage);

        // the following is for reference. pls delete later.
        /*
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
         */

         // note: playerHandsMsg is in the form of
         // player name + card1 + card2 + newline
         // example: john 3 of heart 4 of spades + newline
        std::vector<string> playerHandsMsgVector = game->showHands();
        for (std::string playerHandsMsg : playerHandsMsgVector) {
            broadcastMessage(baseMessage + playerHandsMsg);
        }
        //The game has no way of handling show hands and calculating score right now.
    }
    int i;
    //printf("in this loop\n");
    while (true) {
        i++;
        
        memset(buffer, 0, 1024);
        int bytesRead = recv(client_socket, buffer, 1024, 0);
        if (bytesRead <= 0) {
            std::cerr << username << " disconnected. Socket: " << client_socket << std::endl;
            close(client_socket);
            clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
            clientUsernames.erase(client_socket);
            return;
        }
        std::string message(buffer);
        broadcastMessage(baseMessage + message);
        
    }
    
}

int main() {    
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(10165);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        clients.push_back(new_socket);
        std::thread(handleClient, new_socket).detach();
    }

    return 0;
}
