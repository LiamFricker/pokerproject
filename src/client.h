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

//extern int super_socket;
//extern std::string username;


//Called by GUI to send bet to server
void sendBet(int betType, int raise_amount);
void enterUsername(std::string userstring);