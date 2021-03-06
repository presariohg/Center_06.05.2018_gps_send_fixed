void clrscr                     (); //clear glcd and default setfont
void gui_init                   (); //main screen include menu, time, SIM signal, relay status        
void gui_print_time             (); //display time, date in main screen
void gui_colon_blink            (); //blinking second dot
void gui_set_choice             (int co_y, unsigned char *s);   //dich chuyen con tro khi bam phim back trong luc chon menu
void gui_choose_relay           (); //display relay menu
void gui_current_time           (); //display time menu
void exe_main_menu              (int command);  //execute commands from main menu 
void gui_cursor_move            (int erase_position);   //move cursor function
void gui_main_menu              (); //display main menu
void node_info_examine          (station_info station_receive); //auto proccess over data receiver
void get_relay_status           (); //get relay status and display on main screen
void gui_set_title              (unsigned char *s); //set title menu
void gui_gprs_read              ();



void clrscr() {
    glcd_clear();
    glcd_moveto(0,0);
    glcd_setfont(font5x7);
}
void gui_init() {
    int i = 0;
    clrscr();
    glcd_rectangle(0,0,84,48);                      // hinh chu nhat bao quanh man hinh
    glcd_rectangle(0,0,84,11);                      // hinh chu nhat bao quanh title
    glcd_rectangle(0,37,26,48);                     // hinh chu nhat bao quanh menu
    glcd_setfont(font5x7);
    glcd_outtextxy(18,2,"SPRINKLE");
    glcd_outtextxy(2,39,"Menu");
    get_relay_status();                             //lay status cua cac role de hien thi
    glcd_setfont(relay_icon_7x7);
        for (i = 1; i <= 5; i++) {
            glcd_putcharxy(27 + i * 8, 39, node[i].status); //8: width cua font
        }
    glcd_setfont(phone_signal_10x5);                //cot song cua SIM 
    //trong file phone_signal_10x5.c co du 6 moc signal strength nhung luc code dong nay sim dang bi loi phan cung nen chua test duoc
	//co the dung lenh AT+CSQ de check signal strength
	if (is_sim_init_ok)                             //binh thuong trong ham init_sms co put_command va doi modul SIM tra ve OK
	    glcd_outtextxy(72, 3, "5");                 //khong co song
	else 
        glcd_outtextxy(72, 3, "0");                 //co song
}
void gui_print_time() {
    int i = 0;
    rtc_get_time(&hour, &minute, &second);
    rtc_get_date(&week_day, &day, &month, &year);
    glcd_setfont(big_letter_10x14);     //font chu to de hien thi gio + phut
    glcd_outtextxyf(11, BIG_COLON_Y, name_hour[hour]);      //hien thi gio bang so to giua man hinh
    glcd_outtextxyf(44, BIG_COLON_Y, name_minute[minute]);  //hien thi phut bang so to giua man hinh
    glcd_setfont(tiny_letter);          //font chu nho de hien thi ngay - thang - nam
    glcd_outtextxyf(66, BIG_COLON_Y, name_second[second]);
    glcd_outtextxyf(66,22,name_week_day[week_day]);
    glcd_outtextxyf(2, SMALL_COLON_Y, name_month[month]);
    glcd_outtext(" ");
    glcd_outtextf(name_day[day]);
    glcd_outtext(" ");
    glcd_outtextf(name_year[year]);
    get_relay_status();
    glcd_setfont(relay_icon_7x7);
        for (i = 1; i <= 5; i++) {
            glcd_putcharxy(27 + i * 8, 39, node[i].status); //8: width cua font
        }
}
void gui_colon_blink() {
    if (blink) {
        glcd_setfont(big_letter_10x14);
        glcd_outtextxy(BIG_COLON_X, BIG_COLON_Y, ":");
    } else {
        glcd_setfont(big_letter_10x14);
        glcd_outtextxy(BIG_COLON_X, BIG_COLON_Y, "="); //vi luc ve font quen ve dau space nen dung tam dau = :v
    }
    blink = !blink;
}
void gui_set_choice(int co_y, unsigned char *s) {
    char text[14];
    int i = 0;
    memset(text,'\0',14);    //sao chep ky tu '\0' vao 14 ky tu dau tien cua chuoi text
    while (*s) {             //de khong anh huong den cac chu trong menu dang sau
        text[i] = *s;
        i++;
        s++;
    }
    glcd_outtextxy(x, co_y, text); //dich chuyen dong chon tiep theo cua menu
}
void exe_main_menu(int command) {
    switch (command) {
    case 1:
        gui_current_time();
        return;
    case 2:
        gui_choose_relay(); 
        return;
    case 3:
       // is_sim_init_ok = true;
     //   init_sms();
      //  init_gprs();
        return;
    case 4:
        gui_gprs_read();
        return;
    }
}
void gui_cursor_move(int erase_position) {
    if (erase_position == 0) {
        glcd_putcharxy(x - 7,y - NEW_LINE,' ');
    } else {
        glcd_putcharxy(x - 7,15 + NEW_LINE * (erase_position - 1), ' ');
    }
    glcd_putcharxy(x - 7, y, '>');
}
void gui_main_menu() {
    int erase_position = 0;
    int command;
     while (1) {
        clrscr();
        gui_set_title("MENU");
        gui_set_choice(y + NEW_LINE * 0, "Set Time");   //NEW_LINE =8, lan luot cac hang menu cach nhau 8 hang
        gui_set_choice(y + NEW_LINE * 1, "Set Node");
        gui_set_choice(y + NEW_LINE * 2, "Sim Init");
        gui_set_choice(y + NEW_LINE * 3, "Get GPRS");
        command = 1;
         while (1) {
            if (btn_enter) {
                while(btn_enter);
                exe_main_menu(command);
                break;
            }
            if (btn_back) {     //next menu when press back button 
                while(btn_back);
                command++;                  //increase command
                y += NEW_LINE;              //next menu
                if (command > 4) {          //total 4 command, if lager 4 will return first command
                    erase_position  =   4;
                    command         =   1;
                    y               =   15;
                }
                gui_cursor_move(erase_position);  //move cursor when press back button 
                erase_position      =   0;
            }    
            if (btn_menu) {      //show start screen when press menu button
                while (btn_menu);
                gui_init();
                is_show_clock = true;

                return;
            }
         }
     }
}
void gui_set_title(unsigned char *s) {
    char title[14];
    int i = 0, co_x;
    memset(title,'\0',14);
    while (*s) {
        title[i] = *s;
        i++;
        s++;
    }
    co_x = (84 - i*6)/2;
    glcd_outtextxy(co_x, 2, title);
    glcd_line(0,10,84,10);
    glcd_rectangle(0,0,84,48);
    y = 15;
    x = 10;
    glcd_putcharxy(x - 7,y,'>');
}

void gui_gprs_read() {
    clrscr();
    gui_set_title("Website CMD ");
    glcd_putcharxy(x - 7,y,' '); //xoa dau > 
   //gprs_read();
    while (1) {
        if (btn_menu) {
            while (btn_menu);
            return;
        }
    }
}

void node_info_examine(station_info station_receive) {
if ((station_receive.light < 70) && (station_receive.sm < 20)) {
		switch (station_receive.flag) {
			case 1:
	            relay_1                 =   ON;
	            node[1].status          =   ON;
	            node[1].alarm_time_s    =   1 * MIN_TO_SEC;
        	break;
	        case 2:
	            relay_2                 =   ON;
	            node[2].status          =   ON;
	            node[2].alarm_time_s    =   1 * MIN_TO_SEC;
	        break;
	        case 3:
	            relay_3                 =   ON;
	            node[3].status          =   ON;
	            node[3].alarm_time_s    =   1 * MIN_TO_SEC;
	        break;
	        case 4:
	            relay_4                 =   ON;
	            node[4].status          =   ON;
	            node[4].alarm_time_s    =   1 * MIN_TO_SEC;
	        break;
	        case 5:
	            relay_5                 =   ON;
	            node[5].status          =   ON;
	            node[5].alarm_time_s    =   1 * MIN_TO_SEC;
	        break; 
		}
	}
}
