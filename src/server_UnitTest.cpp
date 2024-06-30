#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"

std::vector<int> clients;
std::map<int, std::string> clientUsernames;
Game* game = nullptr;

void testServer() {
    int server_fd;
    //int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    //int addrlen = sizeof(address);

    // Test socket creation
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return;
    }
    std::cout << "Socket created successfully" << std::endl;

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(10090);

    // Test binding
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return;
    }
    std::cout << "Socket bind successful" << std::endl;

    // Test listening
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return;
    }
    std::cout << "Server listening" << std::endl;

    // Close the socket to end the test
    close(server_fd);
}

int main() {
    testServer();
    return 0;
}
