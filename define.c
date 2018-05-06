#define ON                      0
#define OFF                     1

#define btn_enter               !PINA.3
#define btn_back                !PINA.4
#define btn_menu                !PINA.5
#define relay_1                 PORTD.4
#define relay_2                 PORTD.7
#define relay_3                 PORTC.7
#define relay_4                 PORTA.7
#define relay_5                 PORTA.2

#define backlight               PORTC.6

#define CE                      PORTB.4
#define CSN                     PORTB.5
#define SCK                     PORTB.3
#define MOSI                    PORTB.6
#define MISO                    PINB.2
#define IRQ                     PINB.7

#define DATA_REGISTER_EMPTY     (1<<UDRE0)
#define RX_COMPLETE             (1<<RXC0)
#define FRAMING_ERROR           (1<<FE0)
#define PARITY_ERROR            (1<<UPE0)
#define DATA_OVERRUN            (1<<DOR0)

flash char  *name_week_day[]    =   {"\0","SUN","MON","TUE","WED","THU","FRI","SAT"},                                            

            *name_day[]         =   {"\0","01","02","03","04","05","06","07","08","09","10",
                                     "11","12","13","14","15","16","17","18","19","20","21",
                                     "22","23","24","25","26","27","28","29","30","31"},

            *name_month[]       =   {"\0","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"},

            *name_year[]        =   {"2017","2018","2019","2020","2021","2022","2023","2024",
                                     "2025","2026","2027","2028","2029","2030","2031","2032"},


            *name_second[]      =   {"00","01","02","03","04","05","06","07","08","09",
                                     "10","11","12","13","14","15","16","17","18","19",
                                     "20","21","22","23","24","25","26","27","28","29",
                                     "30","31","32","33","34","35","36","37","38","39",
                                     "40","41","42","43","44","45","46","47","48","49",
                                     "50","51","52","53","54","55","56","57","58","59"},

            *name_minute[]      =   {"00","01","02","03","04","05","06","07","08","09",
                                     "10","11","12","13","14","15","16","17","18","19",
                                     "20","21","22","23","24","25","26","27","28","29",
                                     "30","31","32","33","34","35","36","37","38","39",
                                     "40","41","42","43","44","45","46","47","48","49",
                                     "50","51","52","53","54","55","56","57","58","59"},

            *name_hour[]        =   {"00","01","02","03","04","05","06","07","08","09","10","11",
                                     "12","13","14","15","16","17","18","19","20","21","22","23"},


            *name_relay[] =   {"\0","01","02","03","04","05","ALL"};

unsigned long   milisec         =   0;

bool    blink                   =   true,
        is_show_clock           =   false,
        is_sim_init_ok			=	true;
        
int             x               =   10,
                y               =   15;

const int       NEW_LINE        =   8,

                BIG_COLON_X     =   33,
                BIG_COLON_Y     =   13,

                SMALL_COLON_Y   =   30,

                MIN_TO_SEC      =   60;


unsigned char   week_day        =   1,
                day             =   1,
                month           =   1,
                year            =   1,

                hour            =   0,
                minute          =   0,
                second          =   0;
