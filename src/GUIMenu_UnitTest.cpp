#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *entry, *entry1, *entry2;

int ai_num = 0;

static void enter_callback( GtkWidget *widget,
                            GtkWidget *callback_entry )
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (callback_entry));
    printf ("Entry contents: %s\n", entry_text);
}

static void entry_callback(GtkWidget *widget)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    printf ("Username: %s\n", entry_text);
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry1));
    printf ("Password: %s\n", entry_text);
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry2));
    printf ("Room: %s\n", entry_text);
    
    //CALL A FUNCTION IN CLIENT THAT SENDS THIS INFO TO SERVER ALSO SENDS THE NUMBER OF AI
}

static void AI_callback(GtkWidget *widget)
{
    ai_num+=1;
    if (ai_num > 4){
        ai_num = 0;
        printf ("Reset AI to 0");
    }
    else{
        printf ("Added an AI. AI #%i\n", ai_num);
    }
    
}

// static void entry_toggle_editable( GtkWidget *checkbutton,
//                                    GtkWidget *entry )
// {
//   gtk_editable_set_editable (GTK_EDITABLE (entry),
//                              GTK_TOGGLE_BUTTON (checkbutton)->active);
// }

// static void entry_toggle_visibility( GtkWidget *checkbutton,
//                                      GtkWidget *entry )
// {
//   gtk_entry_set_visibility (GTK_ENTRY (entry),
// 			    GTK_TOGGLE_BUTTON (checkbutton)->active);
// }

int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox, *hbox1, *hbox2;
    
    GtkWidget *button, *button1, *button2;
    //GtkWidget *check;
    GtkWidget *frame;
    GtkWidget *label;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 800, 600);
    
    gtk_window_set_title (GTK_WINDOW (window), "Poker Game");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    /*
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (G_OBJECT (window), "delete_event",
                              G_CALLBACK (gtk_widget_destroy), 
                              G_OBJECT (window));
    */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
    G_CALLBACK(gtk_main_quit), NULL);
    
    
    GtkWidget *layout, *background, *image;
    
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add (GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);
    
    background = gtk_image_new_from_file("Assets/PokerMenu.png");
    gtk_layout_put(GTK_LAYOUT(layout), background, 0, 0);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
    
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 100); 

    image = gtk_image_new_from_file("Assets/buttondivider.png");
    //gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), image, FALSE, FALSE, 0);
    
    
    frame = gtk_frame_new ("Welcome to Poker Game");
    label = gtk_label_new ("Please enter your Name, Password, and the Room you want to join below");
    gtk_container_add (GTK_CONTAINER (frame), label);
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    hbox2 = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox2);
    gtk_widget_show (hbox2);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (G_OBJECT (entry), "activate",
		      G_CALLBACK (enter_callback),
		      (gpointer) entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), "Name", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry),
			        0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (hbox2), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);

    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 50);
    g_signal_connect (G_OBJECT (entry1), "activate",
		      G_CALLBACK (enter_callback),
		      (gpointer) entry1);
    gtk_entry_set_text (GTK_ENTRY (entry1), "");
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry1), "Password", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry1),
			        0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (hbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    hbox1 = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox1);
    gtk_widget_show (hbox1);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (G_OBJECT (entry2), "activate",
		      G_CALLBACK (enter_callback),
		      (gpointer) entry2);
    gtk_entry_set_text (GTK_ENTRY (entry2), "");
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry2), "Room", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry2),
			        0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (hbox1), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);
    /*                              
    check = gtk_check_button_new_with_label ("Editable");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (check), "toggled",
	              G_CALLBACK (entry_toggle_editable), (gpointer) entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
    
    check = gtk_check_button_new_with_label ("Visible");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (check), "toggled",
	              G_CALLBACK (entry_toggle_visibility), (gpointer) entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
    */                               
    
    button1 = gtk_button_new_with_label("Enter");
    g_signal_connect(G_OBJECT (button1), "clicked", G_CALLBACK (entry_callback), 0);
    gtk_box_pack_start (GTK_BOX (vbox), button1, TRUE, TRUE, 0);
    GTK_WIDGET_SET_FLAGS (button1, GTK_CAN_DEFAULT);
    gtk_widget_grab_default (button1);
    
    button2 = gtk_button_new_with_label("Add AI Player");
    g_signal_connect(G_OBJECT (button2), "clicked", G_CALLBACK (AI_callback), 0);
    gtk_box_pack_start (GTK_BOX (vbox), button2, TRUE, TRUE, 0);
    
    
    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy),
			      G_OBJECT (window));
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    //gtk_widget_grab_default (button);
    
    
    //gtk_widget_show (window);
    gtk_widget_show_all (window);

    gtk_main();

    return 0;
}