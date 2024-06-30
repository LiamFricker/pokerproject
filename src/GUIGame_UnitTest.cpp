#include <gtk/gtk.h>
#include <stdio.h>
#include "GameGUI.h"
#include <stdlib.h> 
#include <time.h> 

GtkWidget *window;
GtkWidget *card1, *card2, *card3, *card4, *card5, *left_card1, *left_card2, 
        *right_card1, *right_card2, *top_card1, *top_card2, *bottom_card1, *bottom_card2;
GtkWidget *label_main, *label_left, *label_top, *label_right, *label_bottom,
        *label_left1, *label_top1, *label_right1, *label_bottom1, 
        *label_left2, *label_top2, *label_right2, *label_bottom2;
GtkWidget *call_button, *fold_button, *raise_button;
GtkWidget *raise_slider;

int game_state = 0;

void hide_buttons(){
    gtk_widget_hide(call_button);
    gtk_widget_hide(fold_button);
    gtk_widget_hide(raise_button);
    gtk_widget_hide(raise_slider);
}

static void call_callback(GtkWidget *widget)
{
    g_print ("Call was pressed\n");
    //check(player);
    hide_buttons();
}

static void fold_callback(GtkWidget *widget)
{
    g_print ("Fold was pressed\n");
    //fold(player);
    hide_buttons();
}

static void raise_callback( GtkWidget *widget, GtkRange* data)
{
    g_print ("Raise was pressed. Raise amount: %i\n", (int) gtk_range_get_value(data));
    //raise(player, (int) gtk_range_get_value(data));
    hide_buttons();
}

/* another callback */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}



/*
static gboolean button_press_callback (GtkWidget      *event_box,
                         GdkEventButton *event,
                         gpointer        data)
{
    g_print ("Event box clicked at coordinates %f,%f\n",
             event->x, event->y);

    // Returning TRUE means we handled the event, so the signal
    // emission should be stopped (don’t call any further callbacks
    // that may be connected). Return FALSE to continue invoking callbacks.
    return TRUE;
}

static GtkWidget* create_image(void)
{
    GtkWidget *image, *image1;
    GtkWidget *main_event_box, *event_box, *event_box1;

    image = gtk_image_new_from_file ("Assets/CardDistribution.png");
    image1 = gtk_image_new_from_file ("Assets/cardback.png");

    event_box = gtk_event_box_new ();
    event_box1 = gtk_event_box_new ();
    main_event_box = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (event_box), image);
    gtk_container_add (GTK_CONTAINER (event_box1), image1);
    gtk_container_add (GTK_CONTAINER (main_event_box), event_box);
    gtk_container_add (GTK_CONTAINER (main_event_box), event_box1);

    g_signal_connect (G_OBJECT (event_box),
                      "button_press_event",
                      G_CALLBACK (button_press_callback),
                      image);
    g_signal_connect (G_OBJECT (event_box1),
                      "button_press_event",
                      G_CALLBACK (button_press_callback),
                      image1);
    gtk_widget_show (image);
    gtk_widget_show (image1);
    gtk_widget_show (main_event_box);
    return main_event_box;
}
*/
//returns a widget with the specified cardtype
//You may have to change this so it sets the card rather than overwrites it
static GtkWidget* get_card(int cardnum, int suit){
    GtkWidget *card;
    char* card_string;
    switch(suit){
        case 1:
            asprintf(&card_string, "Assets/spades%i.png", cardnum);
            break;
        case 2:
            asprintf(&card_string, "Assets/clubs%i.png", cardnum);
            break;
        case 3:
            asprintf(&card_string, "Assets/hearts%i.png", cardnum);
            break;
        case 4:
            asprintf(&card_string, "Assets/diamonds%i.png", cardnum);
            break;
        case -1:
            asprintf(&card_string, "Assets/fakespacing.png");
            break;
        default:
            asprintf(&card_string, "Assets/cardback.png");
    }
    card = gtk_image_new_from_file(card_string);
    return card;
}

static void set_card(int suit, int cardnum, GtkWidget *card){
    char* card_string;
    g_print ("Suit: %i Num: %i \n", cardnum, suit);
    switch(suit){
        case 1:
            asprintf(&card_string, "Assets/spades%i.png", cardnum);
            break;
        case 2:
            asprintf(&card_string, "Assets/clubs%i.png", cardnum);
            break;
        case 3:
            asprintf(&card_string, "Assets/hearts%i.png", cardnum);
            break;
        case 4:
            asprintf(&card_string, "Assets/diamonds%i.png", cardnum);
            break;
        case -1:
            asprintf(&card_string, "Assets/fakespacing.png");
            break;
        default:
            asprintf(&card_string, "Assets/cardback.png");
    }
    gtk_image_set_from_file(GTK_IMAGE(card), card_string);
}



//Shows the call/raise/fold buttons 
void show_buttons(){
    gtk_widget_show(call_button);
    gtk_widget_show(fold_button);
    gtk_widget_show(raise_button);
    gtk_widget_show(raise_slider);
}

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

void set_cards(int type, int cardnum1, int suit1, int cardnum2, int suit2, int cardnum3, int suit3){
    switch(type){
        case 0:
            set_card(cardnum1, suit1, bottom_card1);
            set_card(cardnum2, suit2, bottom_card2);
            break;
        case 1:
            set_card(cardnum1, suit1, left_card1);
            set_card(cardnum2, suit2, left_card2);
            break;
        case 2:
            set_card(cardnum1, suit1, top_card1);
            set_card(cardnum2, suit2, top_card2);
            break;
        case 3:
            set_card(cardnum1, suit1, right_card1);
            set_card(cardnum2, suit2, right_card2);
            break;
        case 4:
            set_card(cardnum1, suit1, card1);
            set_card(cardnum2, suit2, card2);
            set_card(cardnum3, suit3, card3);
            break;
        case 5:
            set_card(cardnum1, suit1, card4);
            break;
        case 6:
            set_card(cardnum1, suit1, card5);
            break;
        default:
            set_card(0, 0, bottom_card1);
            set_card(0, 0, bottom_card2);
            set_card(0, 0, left_card1);
            set_card(0, 0, left_card2);
            set_card(0, 0, top_card1);
            set_card(0, 0, top_card2);
            set_card(0, 0, right_card1);
            set_card(0, 0, right_card2);
            set_card(0, 0, card1);
            set_card(0, 0, card2);
            set_card(0, 0, card3);
            set_card(0, 0, card4);
            set_card(0, 0, card5);
            break;
    }
}

void deal_callback(){
    g_print ("Test Deal was pressed Game State %i\n", game_state);
    //fold(player);
    switch(game_state){
        case (0):
            set_cards(0, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            set_cards(1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            set_cards(2, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            set_cards(3, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            break;
        case (1):
            set_cards(4, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1,
                rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            break;
        case (2):
            set_cards(5, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            break;
        case (3):
            set_cards(6, rand() % (4 + 1 - 1) + 1, rand() % (13 + 1 - 1) + 1);
            break;
        default:
            set_cards(7);
    }
    game_state+=1;
    if (game_state == 5){
        game_state = 0;
    }
}

/*
void game_end(char* ending_message) {
    gtk_widget_hide(window);
    GtkWidget *window2;
    window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window2), 500, 500); 
    gtk_window_set_title (GTK_WINDOW (window2), "Poker Game");
    g_signal_connect (G_OBJECT (window2), "delete_event", G_CALLBACK (delete_event), NULL);
    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
    
}    
*/    
//Implement this later
//getEventText()



int main( int   argc,
          char *argv[] )
{
    //Left, right, top, bottom is all from the player's perspective. We will refer to them as such since the GUI doesn't care
    //who they actually are. An ID for each player can be assigned at a later point based on the development of the engine.
    GtkWidget *layout;
    GtkWidget *vbox_main, *vbox_left, *vbox_top, *vbox_right, *vbox_bottom, *vbox_center, *vbox_options_left, *vbox_options_right;
    GtkWidget *hbox_main, *hbox_left, *hbox_top, *hbox_right, *hbox_bottom, *hbox_center;// *hbox_options;
    GtkWidget *spacer_top, *spacer_bottom, *spacer_left, *spacer_right, *raise_spacer, *call_spacer;
    
    //Test Widgets
    GtkWidget *window1, *deal_button;
    
    //GtkAdjustment *raise_adjustment;
    //GtkObject *raise_adjustment;
    /*
    GtkWidget *label_main, *label_left, *label_top, *label_right, *label_bottom,
        *label_left1, *label_top1, *label_right1, *label_bottom1, 
        *label_left2, *label_top2, *label_right2, *label_bottom2;
    */
    //Incase you want to do this with two+ labels per player
    //GtkWidget *card1, *card2, *card3, *card4, *card5, *left_card1, *left_card2, 
    //    *right_card1, *right_card2, *top_card1, *top_card2, *bottom_card1, *bottom_card2;
    GtkWidget *background;//, background0, *dealer_chip, *label_main2; Can be added later 

    //Placeholder since the other guys haven't started yet on their parts yet
    //This is goofy but Player 4 is index 0 and the rest are 1, 2, 3
    int PlayerBets[4] = {0,0,0,0};
    int PlayerMoney[4] = {1000,1000,1000,1000};
    //int Player1_Bet = 0, Player2_Bet = 0, Player3_Bet = 0, Player4_Bet = 0, 
    //  Player1_Money = 1000, Player2_Money = 1000, Player3_Money = 1000, Player4_Money = 1000; 

    //Your Player ID (1-4)
    int PlayerID = 1;
    //Current Dealer ID
    int DealerID = 1;
    //The Minimum Raise
    int MinRaise = 100;
    //Current Bet
    int CurrentBet = 100;
    //The Maximum Raise
    int MaxRaise = 10000;
    //All in 0 false 1 true
    //int AllIn = 0;
    //Helper Var used in functions
    int PlayerNum;
    //Helper String used in functions
    char* label_string;
    //Card Hidden Image
    //GtkWidget *hiddenCard = gtk_image_new_from_file ("Assets/cardback.png");;

    /* Misc code to help me later. Delete after done.
    GtkWidget *image;
    image = create_image();
    gtk_widget_show (image);
    GtkWidget *image1 = gtk_image_new_from_file ("Assets/cardback.png");
    GtkWidget *image2 = gtk_image_new_from_file ("Assets/CardDistribution.png");

    //label
    label = gtk_label_new("This is my label");

    gtk_label_set_text(GTK_LABEL (label), "I cannot use this func");

    label.set_angle(90)
    button1.get_child().set_angle(90) # assuming it's not a stock button
    button2.get_child().set_angle(90)
    vbox.set_orientation(gtk.ORIENTATION_HORIZONTAL)

    gtk_box_pack_start()
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    */

    gtk_init (&argc, &argv);

    //The window that displays the game
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 1050, 900); //1030,900 without buttons
    gtk_window_set_title (GTK_WINDOW (window), "Poker Game");
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //Test Code
    srand(time(0)); 
    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window1), 100, 100); 
    gtk_window_set_title (GTK_WINDOW (window1), "Deal Cards");
    g_signal_connect (G_OBJECT (window1), "delete_event", G_CALLBACK (delete_event), NULL);
    deal_button = gtk_button_new_with_label("Deal");
    g_signal_connect(G_OBJECT (deal_button), "clicked", G_CALLBACK (deal_callback), 0);
    gtk_container_add (GTK_CONTAINER (window1), deal_button);
    
    

    

    //The Overall Layout
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add (GTK_CONTAINER (window), layout);
    
    background = gtk_image_new_from_file("Assets/PokerBoard.png");
    gtk_layout_put(GTK_LAYOUT(layout), background, 0, 0);
    
    
    GtkWidget *temp_vbox;
    temp_vbox = gtk_vbox_new(FALSE, 0);
    gtk_layout_put(GTK_LAYOUT(layout), temp_vbox, 0, 0);
    
    gtk_container_set_border_width (GTK_CONTAINER (temp_vbox), 60); 
    
    //The Box Covering Left, Center, Right columns
    hbox_main = gtk_hbox_new(FALSE, 75);
    gtk_container_add(GTK_CONTAINER(temp_vbox), hbox_main);
    //gtk_box_pack_start (GTK_BOX (temp_vbox), hbox_main, FALSE, FALSE, 0);
    

    //HBox_main elements:
    //The VBox containing the left player's elements
    vbox_left = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start (GTK_BOX (hbox_main), vbox_left, FALSE, FALSE, 0);    

    //The VBox containing all the elements in the middle
    //layout = gtk_box_new(NULL, NULL);
    //gtk_container_add (GTK_CONTAINER (hbox_main), layout);
    vbox_main = gtk_vbox_new(FALSE, 75);
    gtk_box_pack_start (GTK_BOX (hbox_main), vbox_main, FALSE, FALSE, 0);    

    //The VBox containing the right player's elements
    vbox_right = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start (GTK_BOX (hbox_main), vbox_right, FALSE, FALSE, 0);

    //VBox_main elements:
    //The VBox containing the top player's elements
    vbox_top = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox_main), vbox_top, FALSE, FALSE, 0);
    //gtk_container_add (GTK_CONTAINER (vbox_main), vbox_left);

    //The VBox containing all the center elements
    vbox_center = gtk_vbox_new(FALSE, 50);
    gtk_box_pack_start (GTK_BOX (vbox_main), vbox_center, FALSE, FALSE, 0);
    //gtk_container_add (GTK_CONTAINER (vbox_main), vbox_center);

    //The VBox containing the bottom player's elements
    //hbox_options = gtk_hbox_new(FALSE, 10);
    //gtk_box_pack_start (GTK_BOX (vbox_main), hbox_options, FALSE, FALSE, 0);
    vbox_bottom = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start (GTK_BOX (vbox_main), vbox_bottom, FALSE, FALSE, 0);
    //gtk_container_add (GTK_CONTAINER (vbox_main), vbox_bottom);

    //vbox_left (Left Player) Elements:
    //The Top Label for the Left Player
    spacer_left = gtk_image_new_from_file("Assets/fakealigning.png");
    gtk_box_pack_start (GTK_BOX (vbox_left), spacer_left, FALSE, FALSE, 0);
    //If using the Dealer Chip (WIP), remove this if clause. 
    //I can also do these without the brackets or a ternary but just incase I need to add more later
    PlayerNum = (PlayerID + 3) % 4;
    if (DealerID == PlayerNum){
        asprintf(&label_string, "Player %i   Dealer", DealerID);    
    } 
    else{
        if (PlayerNum == 0)
            asprintf(&label_string, "Player 4");
        else
            asprintf(&label_string, "Player %i", PlayerNum);
    }
    label_left = gtk_label_new(label_string);
    asprintf(&label_string, "Money: ¥%i", PlayerMoney[PlayerNum]);
    label_left1 = gtk_label_new(label_string);
    gtk_box_pack_start (GTK_BOX (vbox_left), label_left, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox_left), label_left1, FALSE, FALSE, 0);
    //hbox_left: The Image Hbox for the left player
    hbox_left = gtk_hbox_new(FALSE, 15);
    gtk_box_pack_start (GTK_BOX (vbox_left), hbox_left, FALSE, FALSE, 10);
    //The Bottom Label for the Left Player
    if (PlayerBets[PlayerNum] < 0){
        label_left2 = gtk_label_new("Bet: None");
    } 
    else{
        asprintf(&label_string, "Bet: ¥%i", PlayerBets[PlayerNum]);
        label_left2 = gtk_label_new(label_string);
    }
    gtk_box_pack_start (GTK_BOX (vbox_left), label_left2, FALSE, FALSE, 0);

    //vbox_top (Top Player) Elements:
    //The Top Label for the Top Player
    //If using the Dealer Chip (WIP), remove this if clause. 
    //I can also do these without the brackets or a ternary but just incase I need to add more later
    PlayerNum = (PlayerID + 2) % 4;
    if (DealerID == PlayerNum){
        asprintf(&label_string, "Player %i   Dealer", DealerID);    
    } 
    else{
        if (PlayerNum == 0)
            asprintf(&label_string, "Player 4");
        else
            asprintf(&label_string, "Player %i", PlayerNum);
    }
    label_top = gtk_label_new(label_string);
    asprintf(&label_string, "Money: ¥%i", PlayerMoney[PlayerNum]);
    label_top1 = gtk_label_new(label_string);
    gtk_box_pack_start (GTK_BOX (vbox_top), label_top, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox_top), label_top1, FALSE, FALSE, 0);
    //hbox_top: The Image Hbox for the top player
    hbox_top = gtk_hbox_new(FALSE, 15);
    gtk_box_pack_start (GTK_BOX (vbox_top), hbox_top, TRUE, TRUE, 10);
    //The Bottom Label for the Top Player
    if (PlayerBets[PlayerNum] < 0){
        label_top2 = gtk_label_new("Bet: None");
    } 
    else{
        asprintf(&label_string, "Bet: ¥%i", PlayerBets[PlayerNum]);
        label_top2 = gtk_label_new(label_string);
    }
    gtk_box_pack_start (GTK_BOX (vbox_top), label_top2, FALSE, FALSE, 0);

    //vbox_right (Right Player) Elements:
    spacer_right = gtk_image_new_from_file("Assets/fakealigning.png");
    gtk_box_pack_start (GTK_BOX (vbox_right), spacer_right, FALSE, FALSE, 0);
    //The Top Label for the Right Player
    //If using the Dealer Chip (WIP), remove this if clause. 
    //I can also do these without the brackets or a ternary but just incase I need to add more later
    PlayerNum = (PlayerID + 1) % 4;
    if (DealerID == PlayerNum){
        asprintf(&label_string, "Player %i   Dealer", DealerID);    
    } 
    else{
        if (PlayerNum == 0)
            asprintf(&label_string, "Player 4");
        else
            asprintf(&label_string, "Player %i", PlayerNum);
    }
    label_right = gtk_label_new(label_string);
    asprintf(&label_string, "Money: ¥%i", PlayerMoney[PlayerNum]);
    label_right1 = gtk_label_new(label_string);
    gtk_box_pack_start (GTK_BOX (vbox_right), label_right, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox_right), label_right1, FALSE, FALSE, 0);
    //hbox_right: The Image Hbox for the right player
    hbox_right = gtk_hbox_new(FALSE, 15);
    gtk_box_pack_start (GTK_BOX (vbox_right), hbox_right, FALSE, FALSE, 10);
    //The Bottom Label for the right Player
    if (PlayerBets[PlayerNum] < 0){
        label_right2 = gtk_label_new("Bet: None");
    } 
    else{
        asprintf(&label_string, "Bet: ¥%i", PlayerBets[PlayerNum]);
        label_right2 = gtk_label_new(label_string);
    }
    gtk_box_pack_start (GTK_BOX (vbox_right), label_right2, FALSE, FALSE, 0);

    //vbox_bottom (Bottom Player) Elements:
    //The Top Label for the Bottom Player
    //If using the Dealer Chip (WIP), remove this if clause. 
    //I can also do these without the brackets or a ternary but just incase I need to add more later
    PlayerNum = PlayerID - 1;
    if (DealerID == PlayerNum){
        asprintf(&label_string, "Player %i   Dealer", DealerID);    
    } 
    else{
        if (PlayerNum == 0)
            asprintf(&label_string, "Player 4");
        else
            asprintf(&label_string, "Player %i", PlayerNum);
    }
    label_bottom = gtk_label_new(label_string);
    asprintf(&label_string, "Money: ¥%i", PlayerMoney[PlayerNum]);
    label_bottom1 = gtk_label_new(label_string);
    gtk_box_pack_start (GTK_BOX (vbox_bottom), label_bottom, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox_bottom), label_bottom1, FALSE, FALSE, 0);
    //hbox_bottom: The Image Hbox for the bottom player
    hbox_bottom = gtk_hbox_new(FALSE, 15);
    gtk_box_pack_start (GTK_BOX (vbox_bottom), hbox_bottom, TRUE, TRUE, 10);
    //The Bottom Label for the bottom Player
    if (PlayerBets[PlayerID] < 0){
        label_bottom2 = gtk_label_new("Bet: None");
    } 
    else{
        asprintf(&label_string, "Bet: ¥%i", PlayerBets[PlayerNum]);
        label_bottom2 = gtk_label_new(label_string);
    }
    gtk_box_pack_start (GTK_BOX (vbox_bottom), label_bottom2, FALSE, FALSE, 0);

    //vbox_center (center cards) Elements:
    //The Top Label for the Center. This label will declare changes in events such as hands, bets, wins etc. 
    label_main = gtk_label_new(NULL);
    //asprintf(&label_string, "[PLACEHOLDER] Player 1 reveals a Five of a Kind!");
    gtk_label_set_markup(GTK_LABEL (label_main), "<span size=\"large\">[PLACEHOLDER] Player 1 reveals a Five of a Kind!</span>");
    gtk_box_pack_start (GTK_BOX (vbox_center), label_main, FALSE, FALSE, 0);
    //hbox_center: The Image Hbox for the center cards
    hbox_center = gtk_hbox_new(FALSE, 15);
    gtk_box_pack_start (GTK_BOX (vbox_center), hbox_center, FALSE, FALSE, 0);

    //hbox_left (Left Player's cards) images:
    left_card1 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_left), left_card1, FALSE, FALSE, 0);
    left_card2 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_left), left_card2, FALSE, FALSE, 0);

    //hbox_top (Top Player's cards) images:
    spacer_top = get_card(-1,-1);
    gtk_box_pack_start (GTK_BOX (hbox_top), spacer_top, FALSE, FALSE, 0);
    top_card1 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_top), top_card1, FALSE, FALSE, 0);
    top_card2 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_top), top_card2, FALSE, FALSE, 0);

    //hbox_right (Right Player's cards) images:
    right_card1 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_right), right_card1, FALSE, FALSE, 0);
    right_card2 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_right), right_card2, FALSE, FALSE, 0);

    //hbox_bottom (Bottom Player's cards) images:
    spacer_bottom = get_card(-1,-1);
    gtk_box_pack_start (GTK_BOX (hbox_bottom), spacer_bottom, FALSE, FALSE, 0);
    bottom_card1 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_bottom), bottom_card1, FALSE, FALSE, 0);
    //gtk_image_set_from_file(GTK_IMAGE(spacer_bottom), "Assets/spades1.png");
    bottom_card2 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_bottom), bottom_card2, FALSE, FALSE, 0);

    //hbox_center (Center cards) images:
    card1 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_center), card1, FALSE, FALSE, 0);
    card2 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_center), card2, FALSE, FALSE, 0);
    card3 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_center), card3, FALSE, FALSE, 0);
    card4 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_center), card4, FALSE, FALSE, 0);
    card5 = get_card(0,0);//*hiddenCard;
    gtk_box_pack_start (GTK_BOX (hbox_center), card5, FALSE, FALSE, 0);

    //Call, Raise, Fold buttons
    if (CurrentBet <= PlayerMoney[PlayerID])    
        call_button = gtk_button_new_with_label("Call");
    else{
        call_button = gtk_label_new("Unable to Call");
    }
    fold_button = gtk_button_new_with_label("Fold");
    raise_spacer = gtk_image_new_from_file("Assets/fakebar.png");
    call_spacer = gtk_image_new_from_file("Assets/fakebar.png");
    //Add "All in" later
    //Add to check for Max raise as well as if MinRaise + Current is more than MaxRaise
    if (MinRaise+CurrentBet < PlayerMoney[PlayerID] && MinRaise+CurrentBet < MaxRaise){
        if(MaxRaise > PlayerMoney[PlayerID]){
            //raise_adjustment = gtk_adjustment_new(MinRaise, MinRaise, PlayerMoney[PlayerID], 1, 10, 100);
            raise_slider = gtk_hscale_new_with_range(MinRaise+CurrentBet, PlayerMoney[PlayerID], 1);
        }
        else{
            //raise_adjustment = gtk_adjustment_new(MinRaise, MinRaise, MaxRaise, 1, 10, 100);
            raise_slider = gtk_hscale_new_with_range(MinRaise+CurrentBet, MaxRaise, 1);
        }
        raise_button = gtk_button_new_with_label("Raise");
    }
    else{
        raise_button = gtk_label_new("Unable to Raise");
        raise_slider = gtk_label_new("");
    }
    //raise_slider = gtk_hscale_new(GTK_ADJUSTMENT(raise_adjustment));
    //raise_slider = gtk_hscale_new_with_range(MinRaise, PlayerMoney[PlayerID], 1);
    //int argument = 1;
    g_signal_connect(G_OBJECT (call_button), "clicked", G_CALLBACK (call_callback), 0);
    //argument = 2;
    g_signal_connect(G_OBJECT (fold_button), "clicked", G_CALLBACK (fold_callback), 0);
    //argument = (int) gtk_range_get_value(GTK_RANGE(raise_slider));
    g_signal_connect(G_OBJECT (raise_button), "clicked", G_CALLBACK (raise_callback), (gpointer) raise_slider);
    

    vbox_options_left = gtk_vbox_new(FALSE, 25);
    gtk_layout_put(GTK_LAYOUT(layout), vbox_options_left, 120, 550);
    gtk_box_pack_start(GTK_BOX (vbox_options_left), raise_spacer, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX (vbox_options_left), raise_slider, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX (vbox_options_left), raise_button, FALSE, FALSE, 0);  
    
    vbox_options_right = gtk_vbox_new(FALSE, 25);
    gtk_layout_put(GTK_LAYOUT(layout), vbox_options_right, 660, 550);
    gtk_box_pack_start(GTK_BOX (vbox_options_right), call_spacer, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX (vbox_options_right), call_button, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX (vbox_options_right), fold_button, FALSE, FALSE, 0);  
    
    //gtk_layout_put(GTK_LAYOUT(layout), call_button, 600, 600);
    //gtk_layout_put(GTK_LAYOUT(layout), fold_button, 600, 650);
    //gtk_layout_put(GTK_LAYOUT(layout), raise_button, 250, 600);
    //gtk_layout_put(GTK_LAYOUT(layout), raise_slider, 250, 650);
    //Handle Call/Raise/Fold Buttons/Sliders here:
    /*
    Creates a new button with the label "Button 1". 
    button = gtk_button_new_with_label ("Button 1");
    
    Now when the button is clicked, we call the "callback" function
    with a pointer to "button 1" as its argument 
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), (gpointer) "button 1");

    Instead of gtk_container_add, we pack this button into the invisible
    box, which has been packed into the window. 
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);

     Always remember this step, this tells GTK that our preparation for
     this button is complete, and it can now be displayed. *
    gtk_widget_show (button);

    Do these same steps again to create a second button 
    button = gtk_button_new_with_label ("Button 2");

    Call the same callback function with a different argument,
     passing a pointer to "button 2" instead. *
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), (gpointer) "button 2");

    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (box1), image1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (box1), image2, TRUE, TRUE, 0);
    */
   
   
   
    gtk_widget_show_all (window);
    gtk_widget_show_all (window1);

    gtk_main ();

    return 0;
    
}
