#include <iostream>
#include <pthread.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "Menu.h"
#include "GameGUI.h"

void* receiveMessages(void* sock_ptr) {
    int sock = *((int*)sock_ptr);
    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int bytesRead = recv(sock, buffer, 1024, 0);
        if (bytesRead <= 0) {
            std::cerr << "Connection closed by server" << std::endl;
            close(sock);
            exit(EXIT_FAILURE);
        }
        std::cout << buffer << std::endl;
    }
    return nullptr;
}

void testClient() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    //char buffer[1024] = {0};

    // Test socket creation
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }
    std::cout << "Socket created successfully" << std::endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10090);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    // Test connection establishment
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Ended" << std::endl;
        return;
    }
    std::cout << "Connected to server successfully" << std::endl;

    // Test message sending
    std::string message = "Test message from client";
    send(sock, message.c_str(), message.size(), 0);
    std::cout << "Message sent successfully" << std::endl;

    // Test message receiving (by starting a separate thread)
    pthread_t receiveThread;
    pthread_create(&receiveThread, nullptr, receiveMessages, &sock);

    // Sleep for a while to allow message receiving
    sleep(2);

    // Close socket to end the test
    close(sock);
}

int main(int argc, char *argv[]) {
    // temporarily disabled GUI from unit test
    /* first test GUI menu
    gtk_init (&argc, &argv);
    gui_menu();
    GameGUIInit();
    gtk_main();
    std::cout << "GUI loaded successfully" << std::endl;
*/
    testClient();

    return 0;
}
