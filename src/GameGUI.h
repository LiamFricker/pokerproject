
#ifndef GAMEGUI_H
#define GAMEGUI_H
#include <stdio.h>
#include <gtk/gtk.h>
#include "client.h"

// Declare global variables as extern
extern GtkWidget *card1, *card2, *card3, *card4, *card5, *left_card1, *left_card2, 
                 *right_card1, *right_card2, *top_card1, *top_card2, *bottom_card1, *bottom_card2;
extern GtkWidget *label_main, *label_left, *label_top, *label_right, *label_bottom,
                 *label_left1, *label_top1, *label_right1, *label_bottom1,
                 *label_left2, *label_top2, *label_right2, *label_bottom2;
extern GtkWidget *call_button, *fold_button, *raise_button;
extern GtkWidget *raise_slider;
extern int game_state;


//This needs to be called everytime a player's turn starts.
//Shows the call/raise/fold buttons 
void show_buttons();
void hide_buttons();

void set_label(std::string setlabel);
void set_time(int clocktime);

//Type. Defaults to -1
    //0 Player Flip
    //1 Left Flip
    //2 Top Flip
    //3 Right Flip
    //4 Community 3 Card Flip
    //5 Community 4th Card Flip
    //6 Community 5th Card Flip
    //Else Resets everything to unflipped.
//CardNum. Defaults to 0
    //1 Spaces, 2 Clubs, 3 Hearts, 4 Diamonds, Else Covered, (-1 Invalid)
//Suit. Defaults to 0
    //1 Ace, 2-10 Card Num, 11 Jack, 12 Queen, 13 King
//CardNum/Suit1
    //Always fill this out if you want to set a card to certain value. 
//CardNum/Suit2
    //Fill this out for 0-4 Types. 
//CardNum/Suit3
    //Fill this out for 4 Types.

void set_cards(int type = -1, int cardnum1 = 0, int suit1 = 0, int cardnum2 = 0, int suit2 = 0, int cardnum3 = 0, int suit3 = 0);

//Event Type:
    //0 The Game has begun
    //1 Round X has begun where X is playerID
    //2 Your cards are Y suit, Z cardnum and [3] suit, [4] cardnum where y,z,[3],[4] is num amount 1,2,3,4 respectively. 
    //3 The community cards are X suit, Y cardnum, Z suit, [3] cardnum, [4] suit, [5] cardnum
    //where x is playerID and y,z,[3],[4] is num amount 1,2,3,4,5 respectively.
    //4 Player X bets $Y. where X is PlayerID and Y is num_amount1
    //5 Player X calls the $Y bet! where X is PlayerID and Y is the num_amount1
    //6 Player X folds. where X is PlayerID
    //7 Player X raises the bet $Y and the total is now $X+Y. where X is PlayerID, Y is the num_amount1, Z is the num_amount2
    //8 The Turn card is X suit Y cardnum where X is playerID and Y is num_amount1. 
    //9 The River card is X suit Y cardnum where X is playerID and Y is num_amount1 
    //10 Player X reveals his hand to be Y Z [3] with a Z [3][4][5] kicker. X is playerID, Y specifies hand Z,[3] specifiy card type. 
    //Z,[3],[4],[5] specify kicker. Z,[3],[4],[5],[6] are num_amount 1,2,3,4,5,6 respectively
        //Below is the specs for Y
        //0 High Card Z with a [3], [4], [5], [6] kicker.
        //1 Pair Z with a [3], [4] kicker
        //2 Two Pair Z (higher), [3] with a [4] kicker
        //3 Three of a Kind Z, with a [3], [4] kicker
        //4 Straight of highest Z
        //5 Flush of highest Z, Kicker [3], [4], [5], [6]
        //6 Full House of Z (triple), [3] (pair)
        //7 Four of a Kind of Z, with a [3] kicker
        //8 Straight Flush of highest Z
            //Royal Flush if Z is 13 (King)
        //9 Five of a Kind of Z
        //Default: Invalid Hand.
    //11 Player X has won and has claimed $Y where X is PlayerID Y is numamount1
    //12 Player X, Y have tied and claims $Z each X is PlayerID Y is numamount1, Z is numamount2
    //13 Player X, Y, Z have tied and claims $[3] each X is PlayerID Y, Z, [3] are numamount 1, 2, 3 respectively
    //14 Player X, Y, Z, [3] have tied and claims $[4] each X is PlayerID Y, Z, [3], [4] are numamount 1, 2, 3, 4 respectively
    //Default: An Invalid Move has been made.  
void event_handler(int event_type, int playerID = 1, int num_amount1 = 1, int num_amount2 = 1, int num_amount3 = 1, 
    int num_amount4 = 1, int num_amount5 = 1, int num_amount6 = 1);
    
void GameGUIInit();

void deal_callback();

#endif // GAMEGUI_H