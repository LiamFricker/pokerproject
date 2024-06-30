#include "client.h"
#include<unistd.h> 

//global var cause I cba
int super_socket;
int socket_tries;
std::string username;
bool username_entered;
int t = 300;
int findSuit(std::string suitstring){
    suitstring = suitstring.substr(0, suitstring.find("-1")-1);
    //std::cout << "suitstring name: " << suitstring << std::endl;
    if (suitstring == "Spades"){
        return 1;
    }
    else if (suitstring == "Clubs"){
        return 2;
    }
    else if (suitstring == "Hearts"){
        return 3;
    }
    else if (suitstring == "Diamonds"){
        return 4;
    }
    else {
        printf("BAD CARD\n");
        return 0;
    }
    
}

void enterUsername(std::string userstring){
    username = userstring;
    username_entered = true;
}

void* receiveMessages(void* sock_ptr) {
    int sock = *((int*)sock_ptr);
    int card_tally = 0;
    int temp_card[6] = {0,0,0};
    int temp_suit[6] = {0,0,0};
    while (true) {
        char buffer[1024];
        memset(buffer, 0, 1024);
        int bytesRead = recv(sock, buffer, 1024, 0);
        if (bytesRead <= 0) {
            std::cerr << "Connection closed by server" << std::endl;
            close(sock);
            exit(EXIT_FAILURE);
        }
        
        
        // Message Type, Player Name (0 if none), ..., message
        std::string messageParser(buffer);
        int messageType = std::stoi(messageParser.substr(0,messageParser.find(",")));
        //std::cout << "Message type: " << messageType << " end" << std::endl;
        messageParser = messageParser.substr(messageParser.find(",")+1, 1024);
        std::string playerName = messageParser.substr(0,messageParser.find(","));
        //std::cout << "Player name: " << playerName << std::endl;
        messageParser = messageParser.substr(messageParser.find(",")+1, 1024);
        int messageSocket = std::stoi(messageParser.substr(0,messageParser.find(",")));
        //std::cout << "Message sock: " << messageSocket << " end" << std::endl;
        messageParser = messageParser.substr(messageParser.find(",")+1, 1024);
        
        
        switch (messageType){
            //Unused
            case (0):
                printf("End of the world");
                break;
            //Player's cards
            case (1):
                if (card_tally == 0){
                    temp_card[0] = 0;
                    temp_suit[0] = 0;
                    temp_card[1] = 0;
                    temp_suit[1] = 0;
                    temp_card[2] = 0;
                    temp_suit[2] = 0;
                }
                
                temp_card[card_tally] = std::stoi(messageParser.substr(0,messageParser.find("o")));
                //std::cout << "Card num: " << temp_card[card_tally] << std::endl;
                //std::cout << "Card num: " << messageParser.find("-1") << std::endl;
                temp_suit[card_tally] = findSuit(messageParser.substr(messageParser.find("o")+3,messageParser.find("-1")-1));
                //std::cout << temp_suit[card_tally] << std::endl;
                
                card_tally++;
                if (card_tally == 2){
                    set_cards(0, temp_suit[0], temp_card[0], temp_suit[1], temp_card[1], 0, 0);
                    //set_cards(4, 1, 1, 1, 1, 1, 1);
                    //set_cards(5, 1, 1, 1, 1, 1, 1);
                    //set_cards(6, 1, 1, 1, 1, 1, 1);
                    card_tally = 0;
                }
                
                break;
            //Community cards 3.
            case (2):
                t += 100;
                if (card_tally == 0){
                    temp_card[0] = 0;
                    temp_suit[0] = 0;
                    temp_card[1] = 0;
                    temp_suit[1] = 0;
                    temp_card[2] = 0;
                    temp_suit[2] = 0;
                }
                if (card_tally < 3){
                  temp_card[card_tally] = std::stoi(messageParser.substr(0,messageParser.find("o")));
                  //std::cout << "Card num: " << temp_card[card_tally] << std::endl;
                  temp_suit[card_tally] = findSuit(messageParser.substr(messageParser.find("o")+3,messageParser.find("-1")-1));
                  //std::cout << temp_suit[card_tally] << std::endl;
                  
                  card_tally++;
                  if (card_tally == 3){
                      //std::cout << "Card num: " << temp_card[0] << std::endl;
                      set_cards(4, temp_suit[0], temp_card[0], temp_suit[1], temp_card[1], temp_suit[2], temp_suit[2]);
                      //set_cards(4, 1, 1, 1, 1, 1, 1);
                  }
                }
                else {
                    temp_card[card_tally-3] = std::stoi(messageParser.substr(0,messageParser.find("o")));
                    //std::cout << "Card num: " << temp_card[card_tally] << std::endl;
                    temp_suit[card_tally-3] = findSuit(messageParser.substr(messageParser.find("o")+3,messageParser.find("-1")-1));
                    //std::cout << temp_suit[card_tally] << std::endl;
                    set_cards(card_tally+2, temp_suit[card_tally-3], temp_card[card_tally-3], 0, 0, 0, 0);
                    card_tally++;
                    if (card_tally == 5){
                        card_tally = 0;
                    }
                }
                
                break;     
            //Betting
            case (8):
                if (playerName == username){
                    //printf("SHOW BUTTONS\n");
                    super_socket = messageSocket;
                    socket_tries = 0;
                    show_buttons();
                }
                break;
            //Non Message Messages
            case (-1):
                //printf("BM");
                std::cout << messageParser << std::endl;            
                break;
            default:
                printf("End of the world");
        
        }
        
        
    }
    return nullptr;
}

//int g = 0; 



void *GTKThread(void *vargp) 
{ 
    gtk_main();
    return nullptr;
    
} 

void *TimerThread(void *vargp) 
{ 
    t = 300;
    while(true){
        sleep(1);
        t--;
        set_time(t);
    }
    return nullptr;
    
} 

void sendBet(int betType, int raise_amount){
    //Info sent as example: 1,100
    //0 fold, 1 call, 2 raise 
    //std::cout << "bet sent called on soecket " << super_socket << std::endl;
    std::string fullMessage = std::to_string(betType) + "," + std::to_string(raise_amount);
    //send(3, fullMessage.c_str(), fullMessage.size(), 0);
    send(super_socket, fullMessage.c_str(), fullMessage.size(), 0);
    socket_tries++;
    if (socket_tries > 3){
        std::cout << "Too many failures. Flooding. " << std::endl;
        send(4, fullMessage.c_str(), fullMessage.size(), 0);
        send(5, fullMessage.c_str(), fullMessage.size(), 0);
        send(6, fullMessage.c_str(), fullMessage.size(), 0);
        send(7, fullMessage.c_str(), fullMessage.size(), 0);
        socket_tries = 0;
    }
    
    //printf("bet sent\n");
}

int main(int argc, char *argv[]) {
    gtk_init (&argc, &argv);
    gui_menu();
    GameGUIInit();
    //gtk_main();
    
    //GTK Main thread
    pthread_t tid; 
    pthread_create(&tid, NULL, GTKThread, (void *)&tid); 
    
    username_entered = false;
    //static std::string username;
    std::cout << "Enter your username: ";
    //std::getline(std::cin, username);
    int j;
    while (username_entered == false){
        j++;
        //std::getline(std::cin, username);
    }
    
    /*
    int i;
    while (true) {
        i++;
    }
    */
    //int super_socket = 0;
    struct sockaddr_in serv_addr;
    //char buffer[1024] = {0};

    if ((super_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10165);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(super_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Ended" << std::endl;
        return -1;
    }

    
    
    std::string connectMessage = username;// + " has connected";
    //std::cout << "username sent on soecket " << super_socket << std::endl;    
    send(super_socket, connectMessage.c_str(), connectMessage.size(), 0);
    //super_socket = sock;
    std::cout << "Connected to the server as " << username << std::endl;
    
    set_label("Name: " + username);
    
    pthread_t timer; 
    pthread_create(&timer, NULL, TimerThread, (void *)&timer); 
    
    pthread_t receiveThread;
    pthread_create(&receiveThread, nullptr, receiveMessages, &super_socket);
    
    
    //std::cout << "Passed: ";
    //Client needs to be able to send bet info to server
    int i;        
    while (true) {
        i++;
        /*
        std::string message;
        std::getline(std::cin, message);
        std::string fullMessage = username + ": " + message;
        send(super_socket, fullMessage.c_str(), fullMessage.size(), 0);
        */        
    }

    return 0;
}
