/*****************************************************************************/
/* Poll Module :                                                             */
/* * Init the variable-structure and read them from the HW                   */
/* * Wait for input from the power module                                    */
/*****************************************************************************/
/* Version B1.00 Magc7 PowerSrc SNMP Agent                                   */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  PS  Project start                                             */
/* 2002-08-02  ported to CPK450                                              */
/*****************************************************************************/
#include "bldFlags.h"
#include <style.h>
#include <globals.h>
#include <kernel.h>
#include <io.h>
#include <ip.h>    /* defines variables and constants of IP-protocol */
#include <tcp.h>  /* defines variables and constants of TCP-protocol */
#include <string.h>
#include <random.h>
#include <timer.h>
#include "snmpdef.h"
#include "demo.h"

/* external variables ********************************************************/

extern BYTE onbvar3[];
static BYTE Setup5[128];

/* static variables **********************************************************/
static char buf[128];
static WORD srcport;

/* global variables **********************************************************/
GLOBAL BYTE answer[MAX_REQUEST_LENGTH];    //received telemeteria packet
GLOBAL BYTE start_power_main_byte, start_psu_byte, start_battery_byte, start_temper_byte, start_logic_byte, start_ext_io_byte, startExtBoardByte, startClimateControl, currentTelemeteriaNumber;
GLOBAL int prompt, start_packet, i, temp_value, sent_position, rcvd_position;
GLOBAL int table_87[256] = {
    0x00, 0x0E, 0x1C, 0x12, 0x38, 0x36,
    0x24,
    0x2A, 0x70, 0x7E, 0x6C, 0x62, 0x48,
    0x46,
    0x54, 0x5A, 0xE0, 0xEE, 0xFC, 0xF2,
    0xD8,
    0xD6, 0xC4,
    0xCA, 0x90, 0x9E, 0x8C, 0x82, 0xA8,
    0xA6,
    0xB4, 0xBA, 0xCE, 0xC0, 0xD2, 0xDC,
    0xF6,
    0xF8, 0xEA,
    0xE4, 0xBE, 0xB0, 0xA2, 0xAC, 0x86,
    0x88,
    0x9A, 0x94, 0x2E, 0x20, 0x32, 0x3C,
    0x16,
    0x18, 0x0A,
    0x04, 0x5E, 0x50, 0x42, 0x4C, 0x66,
    0x68,
    0x7A, 0x74, 0x92, 0x9C, 0x8E, 0x80,
    0xAA,
    0xA4, 0xB6,
    0xB8, 0xE2, 0xEC, 0xFE, 0xF0, 0xDA,
    0xD4,
    0xC6, 0xC8, 0x72, 0x7C, 0x6E, 0x60,
    0x4A,
    0x44, 0x56,
    0x58, 0x02, 0x0C, 0x1E, 0x10, 0x3A,
    0x34,
    0x26, 0x28, 0x5C, 0x52, 0x40, 0x4E,
    0x64,
    0x6A, 0x78,
    0x76, 0x2C, 0x22, 0x30, 0x3E, 0x14,
    0x1A,
    0x08, 0x06, 0xBC, 0xB2, 0xA0, 0xAE,
    0x84,
    0x8A, 0x98,
    0x96, 0xCC, 0xC2, 0xD0, 0xDE, 0xF4,
    0xFA,
    0xE8, 0xE6, 0x2A, 0x24, 0x36, 0x38,
    0x12,
    0x1C, 0x0E,
    0x00, 0x5A, 0x54, 0x46, 0x48, 0x62,
    0x6C,
    0x7E, 0x70, 0xCA, 0xC4, 0xD6, 0xD8,
    0xF2,
    0xFC, 0xEE,
    0xE0, 0xBA, 0xB4, 0xA6, 0xA8, 0x82,
    0x8C,
    0x9E, 0x90, 0xE4, 0xEA, 0xF8, 0xF6,
    0xDC,
    0xD2, 0xC0,
    0xCE, 0x94, 0x9A, 0x88, 0x86, 0xAC,
    0xA2,
    0xB0, 0xBE, 0x04, 0x0A, 0x18, 0x16,
    0x3C,
    0x32, 0x20,
    0x2E, 0x74, 0x7A, 0x68, 0x66, 0x4C,
    0x42,
    0x50, 0x5E, 0xB8, 0xB6, 0xA4, 0xAA,
    0x80,
    0x8E, 0x9C,
    0x92, 0xC8, 0xC6, 0xD4, 0xDA, 0xF0,
    0xFE,
    0xEC, 0xE2, 0x58, 0x56, 0x44, 0x4A,
    0x60,
    0x6E, 0x7C,
    0x72, 0x28, 0x26, 0x34, 0x3A, 0x10,
    0x1E,
    0x0C, 0x02, 0x76, 0x78, 0x6A, 0x64,
    0x4E,
    0x40, 0x52,
    0x5C, 0x06, 0x08, 0x1A, 0x14, 0x3E,
    0x30,
    0x22, 0x2C, 0x96, 0x98, 0x8A, 0x84,
    0xAE,
    0xA0, 0xB2,
    0xBC, 0xE6, 0xE8, 0xFA, 0xF4, 0xDE,
    0xD0,
    0xC2, 0xCC
};

GLOBAL int table_95[256] = {
    0x00, 0x2A, 0x54, 0x7E, 0xA8, 0x82,
    0xFC,
    0xD6, 0x7A, 0x50, 0x2E, 0x04, 0xD2,
    0xF8,
    0x86, 0xAC,
    0xF4, 0xDE, 0xA0, 0x8A, 0x5C, 0x76,
    0x08,
    0x22, 0x8E, 0xA4, 0xDA, 0xF0, 0x26,
    0x0C,
    0x72, 0x58,
    0xC2, 0xE8, 0x96, 0xBC, 0x6A, 0x40,
    0x3E,
    0x14, 0xB8, 0x92, 0xEC, 0xC6, 0x10,
    0x3A,
    0x44, 0x6E,
    0x36, 0x1C, 0x62, 0x48, 0x9E, 0xB4,
    0xCA,
    0xE0, 0x4C, 0x66, 0x18, 0x32, 0xE4,
    0xCE,
    0xB0, 0x9A,
    0xAE, 0x84, 0xFA, 0xD0, 0x06, 0x2C,
    0x52,
    0x78, 0xD4, 0xFE, 0x80, 0xAA, 0x7C,
    0x56,
    0x28, 0x02,
    0x5A, 0x70, 0x0E, 0x24, 0xF2, 0xD8,
    0xA6,
    0x8C, 0x20, 0x0A, 0x74, 0x5E, 0x88,
    0xA2,
    0xDC, 0xF6,
    0x6C, 0x46, 0x38, 0x12, 0xC4, 0xEE,
    0x90,
    0xBA, 0x16, 0x3C, 0x42, 0x68, 0xBE,
    0x94,
    0xEA, 0xC0,
    0x98, 0xB2, 0xCC, 0xE6, 0x30, 0x1A,
    0x64,
    0x4E, 0xE2, 0xC8, 0xB6, 0x9C, 0x4A,
    0x60,
    0x1E, 0x34,
    0x76, 0x5C, 0x22, 0x08, 0xDE, 0xF4,
    0x8A,
    0xA0, 0x0C, 0x26, 0x58, 0x72, 0xA4,
    0x8E,
    0xF0, 0xDA,
    0x82, 0xA8, 0xD6, 0xFC, 0x2A, 0x00,
    0x7E,
    0x54, 0xF8, 0xD2, 0xAC, 0x86, 0x50,
    0x7A,
    0x04, 0x2E,
    0xB4, 0x9E, 0xE0, 0xCA, 0x1C, 0x36,
    0x48,
    0x62, 0xCE, 0xE4, 0x9A, 0xB0, 0x66,
    0x4C,
    0x32, 0x18,
    0x40, 0x6A, 0x14, 0x3E, 0xE8, 0xC2,
    0xBC,
    0x96, 0x3A, 0x10, 0x6E, 0x44, 0x92,
    0xB8,
    0xC6, 0xEC,
    0xD8, 0xF2, 0x8C, 0xA6, 0x70, 0x5A,
    0x24,
    0x0E, 0xA2, 0x88, 0xF6, 0xDC, 0x0A,
    0x20,
    0x5E, 0x74,
    0x2C, 0x06, 0x78, 0x52, 0x84, 0xAE,
    0xD0,
    0xFA, 0x56, 0x7C, 0x02, 0x28, 0xFE,
    0xD4,
    0xAA, 0x80, 0x1A, 0x30, 0x4E, 0x64,
    0xB2,
    0x98, 0xE6, 0xCC, 0x60, 0x4A, 0x34,
    0x1E,
    0xC8, 0xE2, 0x9C, 0xB6,
    0xEE, 0xC4, 0xBA, 0x90, 0x46, 0x6C,
    0x12,
    0x38, 0x94, 0xBE, 0xC0, 0xEA, 0x3C,
    0x16,
    0x68, 0x42,

};
/* external prototypes *******************************************************/
#if DEBUG
extern void startdebug(void);
extern void stopdebug(void);
#endif
extern void ps_trap(int, int);

/* internal prototypes *******************************************************/
WORD read_data(char *p, int TO);
void show_menu(void);
void make_data(char *p);
void process_data(char *p);
void get_long(BYTE *p, DWORD *l);
void snmpscan(void);
void show_menu();
int val_config(void);
int create_request(BYTE *p, BYTE type, BYTE param1);
void create_crc8(BYTE *user_package, BYTE len);
void process_telemeteria(void);
void processSysParamsList(void);
void proccess_command_reply(void);
void check_if_held(void);

void put_byte_to_sent_buffer(BYTE byte);
void clear_sent_buffer(void);
void put_byte_to_rcvd_buffer(BYTE byte);
void clear_rcvd_buffer(void);
/*****************************************************************************/
/* function snmpscan :                                                       */
/* - jumpin from main-module after HW-init                                   */
/* - init customer-variables                                                 */
/* - check for asynch variable-setting and set them in customer-HW if needed */
/* - poll all the modules and set the variables in memory                    */
/* - trap-handling                                                           */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter  : void                                                         */
/*****************************************************************************/
/* Returncode : void (never returns = program-loop)                          */
/*****************************************************************************/
/* History :                                                                 */
/* 2001.06.26  KK  First version                                             */
/*****************************************************************************/
void demo(void)
{
    WORD    alarmnumber, alarmstate, tonum;
    int     rc, i, n, valid_cmd = 0;
    DWORD   pow;
    BYTE    str[11];

    printf( "*** Let the operation begin ***\r\n" ); /* Prompt to terminal */
    clear_sent_buffer();
    clear_rcvd_buffer();
    PS.counter_packets_output = 0;
    PS.counter_packets_input = 0;
    PS.debugSetVar = 0;
	currentTelemeteriaNumber = 0;
    // init
    PS.load.Automat1State = 0;
    PS.load.Automat2State = 0;
    PS.load.HighVoltage  = 0;
    PS.load.LowVoltage  = 0;
	PS.coldstartBit = 0x80;

    /* Load Location Info */
    val_config();

    memcpy(PS.device_info.Location, Setup5 + 33, STRLEN);
    /* Preset structure */
    memcpy(PS.rd_community, Setup + 34, 14);
    memcpy(PS.wt_community, Setup + 48, 14);
    for (i = 0; i < 3; i++) memcpy(PS.trapadr[i], Setup + 22 + 4*i, 4);
    memset(PS.MessageString, 0, sizeof(PS.MessageString));
    PS.alarmPower = 0;              /* Clear all alarms */
    PS.alarmVoltage = 0;
    PS.alarmTemp = 0;
    /*for(i = 1; i <= PS_HIST ; i++) { 	
        PS.hist[i].volt = 10*i + 500;
        PS.hist[i].amp  = 10*i + 400;
        PS.hist[i].temp = 5*i + 10;
        PS.hist[i].tstamp = (DWORD) (10*i);
        }
    PS.VoltageReading = 500;		    
    PS.CurrentReading = 400;
    PS.TempReading    =  5;
    
    strcpy(PS.MessageString, "The System is started"); ///
    */
    strcpy(PS.MessageString, "The System is started");
    ps_trap(0, 0);                          /* Trap Coldstart */

    /* Program loop */
    while (1) {
        tonum = 3;          /* Set connection error after 3x60 seconds */
        while (tonum > 0) {
            if (valid_cmd == 0) {  /* command waiting to be processed ? */
                memset(buf, 128, 0);
                rc = read_data(buf, 10);    /* Wait 60 sec. for next message */
            }
            if (rc == PS_OK) {
                /* Valid message received */
                tonum = 3;
                valid_cmd = 0;

                /* Green LED always ON */
                BlinkRWord    = PS.command_byte;
                BlinkGWord[0] = 0xFFFF;
                BlinkGWord[1] = 0;
                BlinkReset();

            } else if (rc == PS_TIMEOUT) {
                /* No message from PowerSrc since one minute */
                tonum--;
                PS.command_byte = COMMAND_TIMEOUT;
                /* Yellow LED blinking */
                BlinkGWord[0] = 0;
                BlinkGWord[1] = 0xAAAA;
                BlinkReset();
            }
        }

        if (tonum < 1) {
            /* No message from PowerSrc since 180 seconds */
            strcpy(PS.MessageString, "Alarm serial connection");
            PS.alarmSerial = 1;
            ps_trap(6, 2);

            /* Red LED and yellow LED blinking alternatly */
            BlinkRWord    = 0x5555;
            BlinkGWord[1] = 0xAAAA;
            BlinkReset();

            /* Wait until PowerSrc will be active again */
            while (rc != PS_OK) {
                PS.command_byte = COMMAND_TIMEOUT;
                memset(buf, 128, 0);
                rc = read_data(buf, 20);
            }
            valid_cmd = 1;
            strcpy(PS.MessageString, "Stop alarm serial connection");
            PS.alarmSerial = 0;
            ps_trap(6, 2);

            /* Green LED always ON */
            BlinkRWord    = 0;
            BlinkGWord[0] = 0xFFFF;
            BlinkGWord[1] = 0;
            BlinkReset();
        }
    }
}

/*****************************************************************************/
/* function process_data                                                     */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter:  *p = buffer string to process                                 */
/*****************************************************************************/
/* Returncode:  NONE                                                         */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  KK  First test version                                        */
/*****************************************************************************/
void process_data(char *inp)
{

}

/*****************************************************************************/
/* function read_data                                                        */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter:  *p = buffer to store received string                          */
/*             TO = time out                                                 */
/*****************************************************************************/
/* Returncode:  0 = OK                                                       */
/*             -1 = data error                                               */
/*             -2 = time out occurred                                        */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  KK  First test version                                        */
/*****************************************************************************/
#pragma warn -rch
WORD read_data(p, TO) char *p; int TO;
{

    BYTE cin;
    WORD amp, volt, degr;
    WORD a_tout;
    BYTE request[20];
    BYTE ik = 0;
    int length = 0;
    prompt=0, start_packet = 0, i = 0, temp_value = 0;
/*
request[0] = 0x33;
request[1] = 0x51;
request[2] = 0x01;
request[3] = 0x00;
request[4] = 0x01;
request[5] = 0x37;
request[6] = 0xcb;
request[7] = 0x07;
request[8] = 0x99;
request[9] = 0x0A; //LEAVE FOR TESTS!!!
*/

    a_tout = stime;
    while (1) {
        if (stime - a_tout > 1) break;
        nice();                             //DON't DO THAT AGAIN!!!
    }

    if (PS.reply_ack == REPLY_NEED_TO_CLEAR) {
        clear_sent_buffer();
        clear_rcvd_buffer();
        PS.reply_ack = REPLY_ACKNOWLEDGED;
    }
    if ((PS.command_byte != COMMAND_OK) & (PS.command_byte != COMMAND_INVALID) & (PS.command_byte != COMMAND_TIMEOUT) & (PS.command_byte != COMMAND_FAILED)) {
        PS.reply_ack = REPLY_ACKNOWLEDGED;
        clear_sent_buffer();
        clear_rcvd_buffer();
        switch ((PS.command_byte / 100)) {
        case SET_ACTIVE_BPS:
            length = create_request(request, SET_ACTIVE_BPS, PS.command_byte - SET_ACTIVE_BPS * 100);
            break;
        case ENABLE_COMPENSATION_CHARGE:
            length = create_request(request, ENABLE_COMPENSATION_CHARGE, PS.command_byte - ENABLE_COMPENSATION_CHARGE * 100);
            break;
        case ENABLE_CAPACITY_CONTROL:
            length = create_request(request, ENABLE_CAPACITY_CONTROL, PS.command_byte - ENABLE_CAPACITY_CONTROL * 100);
            break;
        case DISABLE_BPS:
            length = create_request(request, DISABLE_BPS, PS.command_byte - DISABLE_BPS * 100);
            break;
        case DISABLE_SPECIAL_FUNCTIONS:
            length = create_request(request, DISABLE_SPECIAL_FUNCTIONS, 0);
            break;
        case UNLOCK_BPSS:
            length = create_request(request, UNLOCK_BPSS, 0);
            break;
        case ENABLE_PARRALEL_OPERATION:
            length = create_request(request, ENABLE_PARRALEL_OPERATION, 0);
            break;
        case DISABLE_PARRALEL_OPERATION:
            length = create_request(request, DISABLE_PARRALEL_OPERATION, 0);
            break;
        case RESET_ALL_ALARMS:
            length = create_request(request, RESET_ALL_ALARMS, 0);
            break;
        case GET_EVENTS_QUANTITY:
            length = create_request(request, GET_EVENTS_QUANTITY, 0);
            break;
        case GET_EVENT:
            length = create_request(request, GET_EVENT, PS.command_byte - GET_EVENT * 100);
            break;
        case CHECK_CONNECTION:
            length = create_request(request, CHECK_CONNECTION, 0);
            break;
        case GET_SETTINGS_TABLE:
            length = create_request(request, GET_SETTINGS_TABLE, 0);
            break;
        case GET_SETTINGS_PARAMETER:
            length = create_request(request, GET_SETTINGS_PARAMETER, 0);
            break;
        case SET_SETTINGS_PARAMETER:
            length = create_request(request, SET_SETTINGS_PARAMETER, PS.command_byte - SET_SETTINGS_PARAMETER * 100);
            break;
        case SET_EXTERNAL_IO:
            length = create_request(request, SET_EXTERNAL_IO, PS.command_byte - SET_EXTERNAL_IO * 100);
            break;
        case GET_DEVICE_INFO:
            length = create_request(request, GET_DEVICE_INFO, 0);
            break;
        case GET_LOCATION_INFO:
            length = create_request(request, GET_LOCATION_INFO, 0);
            break;
        case SET_LOAD_CTRL_VAR:
            length = create_request(request, SET_LOAD_CTRL_VAR, PS.command_byte - SET_LOAD_CTRL_VAR * 100);
            break;
        case SET_BATTERY_CTRL_VAR:
            length = create_request(request, SET_BATTERY_CTRL_VAR, PS.command_byte - SET_BATTERY_CTRL_VAR * 100);
            break;
        default:
            PS.command_byte = COMMAND_INVALID;
            length = create_request(request, GET_TELEMETERIA, 0);
            break;
        }
    } else{
			if (currentTelemeteriaNumber == 1)
				length = create_request(request, GET_SYS_PARAMS_LIST, 0);
			else
				length = create_request(request, GET_TELEMETERIA, 0);
			currentTelemeteriaNumber = (currentTelemeteriaNumber + 1) & 0x01;
		
		}


    a_tout = stime;
    while (1) {
        if (!prompt) {
            sendblk(request, length);
            prompt++;
            PS.counter_packets_output++;
        }
        if (kbhit()) {
            cin=getch();
            if (start_packet) {
                answer[i] = cin;
                if (PS.reply_ack == REPLY_ACKNOWLEDGED) {
                    put_byte_to_rcvd_buffer(answer[i]);
                }
                i++;
                if ((i >= (answer[2] + 8)) & (cin == 0x0A)) {
                    start_packet = 2;
                    PS.reply_ack = REPLY_NOT_ACKNOWLEDGED;
                    PS.counter_packets_input++;
                    if (answer[1] == 0x61) {
                        if (answer[4] == 0x01) process_telemeteria();
						else if (answer[4] == 0x28) processSysParamsList();
                        else
                            if (((answer[4] == 0x0C)) || ((answer[4] == 0x0D)))
                            proccess_command_reply();
                        else if (((answer[4] == 0x21)) || ((answer[4] == 0x22))) proccess_command_reply();
                        else
                            if (((answer[4] == 0x1F)) || ((answer[4] == 0x20)) || ((answer[4] == 0x1E))) proccess_command_reply();
                        else {
                            PS.command_byte = COMMAND_FAILED;
                            PS.command_answer   = answer[4];
                            PS.command_id       = answer[5];
                        }
                    } else
                        if (answer[1] == 0x62) {
                        proccess_command_reply();
                    }
                }
            }
            if ((cin == 0x33) & (start_packet == 0)) {
                start_packet = 1;
                answer[0] = cin;
                if (PS.reply_ack == REPLY_ACKNOWLEDGED) {
                    clear_rcvd_buffer();
                    put_byte_to_rcvd_buffer(answer[0]);
                }
                i++;
            }
            if (start_packet == 0x02)
                return PS_OK;
        }       /* end if (kbhit())  */

        nice();                   /* obligatory nice() function for multitasking */// NEVER DELETE PLEASE
        if (stime - a_tout > TO)  return PS_TIMEOUT;
    }
    return 0;
}
#pragma warn .rch

void show_menu() {
    printf("\r\n*** Magic7 Power menu ***\r\n");
    printf("1.  send new Voltage reading\r\n");
    printf("2.  send new Current reading\r\n");
    printf("3.  send new Temperature reading\r\n");
    printf("4.  start random data generation\r\n");
    printf("5.  send the Reset command (trap)\r\n");
}

/*****************************************************************************/
/* function make_data  : simulating input with random values                 */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter:  string of data                                                */
/*****************************************************************************/
/* Returncode:  NONE                                                         */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  KK  First test version                                        */
/*****************************************************************************/
void make_data(char *obuf)
{
    int v,a,t;

    v = 400 + ( random(0) & 0xff );                  /* 400 - 655 */
    a = 300 + ( random(0) & 0x7f );                  /* 300 - 427 */
    t =   5 + ( random(0) & 0x3f );                  /*   5 -  68 */
    sprintf(obuf,"V%d A%d T%d\r\n",v,a,t);
    sdelay(1000 + ( random(0) & 0x3ff ));        /* 1000 - 2023 */
}

/*****************************************************************************/
/* Function val_config                                                       */
/* - checks for web configured limits                                        */
/*****************************************************************************/
int val_config(void)
{
    EE_Read(Setup5, (WORD) 512, (WORD) 126);
    if ( !strncmp(Setup5, "M7PS", 4) )  return(1);
    else return(0);
}

/*****************************************************************************/
/* Function getlong                                                          */
/* - retreives long value from 10char. string                                */
/*****************************************************************************/
void get_long(s,l)
BYTE *s;
DWORD *l;
{
    BYTE *p = s;
    DWORD val1, val2, val4;

    val1 = 0L;
    while (*p >= '0' && *p <= '9') {
        val2 = val1 + val1;
        val4 = val2 + val2;
        val1 = (DWORD)(*p++ - '0') + val2 + val4 + val4;
    }
    *l = val1;
}

/*****************************************************************************/
/* Function create_request                                                   */
/* - makes a request byte stream											 */
/* - returns the length of a package		                                 */
/*****************************************************************************/

int create_request(BYTE *request, BYTE type, BYTE param1){
    int i = 0, scan_i = 0;
    switch (type) {
    case GET_TELEMETERIA:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x01;
        request[3] = 0x00;
        request[4] = 0x01;
        create_crc8(request, 5);
        i = 10;
        break;
    case SET_ACTIVE_BPS:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x04;
        request[3] = 0x00;
        request[4] = 0x02;
        request[5] = 0x02;
        request[6] = param1;
        request[7] = param1;
        create_crc8(request, 8);
        i = 13;
        break;
    case ENABLE_COMPENSATION_CHARGE:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x03;
        request[3] = 0x00;
        request[4] = 0x03;
        request[5] = 0x03;
        request[6] = param1;
        create_crc8(request, 7);
        i = 12;
        break;
    case ENABLE_CAPACITY_CONTROL:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x03;
        request[3] = 0x00;
        request[4] = 0x04;
        request[5] = 0x04;
        request[6] = param1;
        create_crc8(request, 7);
        i = 12;
        break;
    case DISABLE_BPS:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x04;
        request[3] = 0x00;
        request[4] = 0x05;
        request[5] = 0x05;
        request[6] = param1;
        request[7] = param1;
        create_crc8(request, 8);
        i = 13;
        break;  
    case DISABLE_SPECIAL_FUNCTIONS:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x07;
        request[5] = 0x07;
        create_crc8(request, 6);
        i = 11;
        break;  
    case UNLOCK_BPSS:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x08;
        request[5] = 0x08;
        create_crc8(request, 6);
        i = 11;
        break;              
    case ENABLE_PARRALEL_OPERATION:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x09;
        request[5] = 0x09;
        create_crc8(request, 6);
        i = 11;
        break;              
    case DISABLE_PARRALEL_OPERATION:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x0A;
        request[5] = 0x0A;
        create_crc8(request, 6);
        i = 11;
        break;  
    case RESET_ALL_ALARMS:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x0B;
        request[5] = 0x0B;
        create_crc8(request, 6);
        i = 11;
        break;  
    case GET_EVENTS_QUANTITY:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x01;
        request[3] = 0x00;
        request[4] = 0x0C;
        request[5] = 0x3a;
        request[6] = 0xc6;
        request[7] = 0x7;
        request[8] = 0x94;
        request[9] = 0xa;
        //create_crc8(request, 5);
        i = 10;
        break;  
    case GET_EVENT:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x0D;
        request[5] = param1;
        create_crc8(request, 6);
        i = 11;
        break;          
    case CHECK_CONNECTION:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x06;
        request[5] = 0x06;
        create_crc8(request, 6);
        i = 11;
        break;
    case GET_SETTINGS_TABLE:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x1E;
        request[5] = 0x1E;
        create_crc8(request, 6);
        i = 11;
        break;          
    case GET_SETTINGS_PARAMETER:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x1F;
        request[5] = PS.command_id & 0xFF;
        create_crc8(request, 6);
        i = 11;
        break;          
    case SET_SETTINGS_PARAMETER:
        request[0] = 0x33;
        request[1] = 0x52;
        switch (param1) {
        case SET_SPARAM_INT:
            request[2] = 0x05;
            request[3] = 0x00;
            request[4] = 0x20;
            request[5] = (PS.command_id) & 0xFF;
            request[6] = 0x22;
            request[7] = ((BYTE)(PS.command_answer ));
            request[8] = ((BYTE)((PS.command_answer >> 8)));
            create_crc8(request, 9);
            i = 14;
            break;
        case SET_SPARAM_INCREMENT:
            request[2] = 0x03;
            request[3] = 0x00;
            request[4] = 0x20;
            request[5] = (PS.command_id) & 0xFF;
            request[6] = 0x33;
            create_crc8(request, 7);
            i = 12;
            break;
        case SET_SPARAM_DECREMENT:
            request[2] = 0x03;
            request[3] = 0x00;
            request[4] = 0x20;
            request[5] = (PS.command_id) & 0xFF;
            request[6] = 0x55;
            create_crc8(request, 7);
            i = 12;
            break;
        }
        break;  
    case SET_EXTERNAL_IO:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x03;
        request[3] = 0x00;
        request[4] = 0x25;
        request[5] = PS.command_id & 0xFF;      //there is no other way. sorry.
        request[6] = param1;
        create_crc8(request, 7);
        i = 12;
        break;
    case GET_DEVICE_INFO:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x21;
        request[5] = 0x21;
        create_crc8(request, 6);
        i = 11;
        break;  
    case GET_LOCATION_INFO:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x02;
        request[3] = 0x00;
        request[4] = 0x22;
        request[5] = 0x22;
        create_crc8(request, 6);
        i = 11;         
        break;
    case SET_LOAD_CTRL_VAR:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x03;
        request[3] = 0x00;
        request[4] = 0x26;
        request[5] = param1;
        request[6] = param1;
        create_crc8(request, 7);
        i = 12;
        break;
    case SET_BATTERY_CTRL_VAR:
        request[0] = 0x33;
        request[1] = 0x52;
        request[2] = 0x03;
        request[3] = 0x00;
        request[4] = 0x27;
        request[5] = param1;
        request[6] = param1;
        create_crc8(request, 7);
        i = 12;
        break;
	case GET_SYS_PARAMS_LIST:
        request[0] = 0x33;
        request[1] = 0x51;
        request[2] = 0x01;
        request[3] = 0x00;
        request[4] = 0x28;
        create_crc8(request, 5);
        i = 10;
        break;

    default:
        i = 0;
        break;

    }
    //nice();
    return i;
}

void create_crc8(BYTE *user_package, BYTE len) {
    int last_byte = len - 1, i;
    int current_crc_1_value = user_package[0];
    int current_crc_2_value = user_package[0];
    BYTE xorred_byte = (BYTE) user_package[0];

    for (i = 1; i <= last_byte; i++) {
        //user_package_final[i] = user_package[i];
        current_crc_1_value = (user_package[i] ^
                               table_87[current_crc_1_value & 0xFF]);
    }
    if (current_crc_1_value == 0)
        current_crc_1_value = 0xFF;

    for (i = 1; i <= last_byte; i++) {
        current_crc_2_value = user_package[i] ^
                              table_95[current_crc_2_value & 0xFF];
    }
    if (current_crc_2_value == 0)
        current_crc_2_value = 0xFF;

    user_package[last_byte + 1] = (BYTE) current_crc_1_value;
    user_package[last_byte + 2] = (BYTE) current_crc_2_value;

    last_byte = last_byte + 2;

    user_package[last_byte + 1] = (BYTE) (last_byte + 1);
    for (i = 1; i < last_byte + 1; i++) {
        xorred_byte = (BYTE) (xorred_byte ^ user_package[i]);
    }
    xorred_byte ^= (BYTE) user_package[last_byte + 1];
    user_package[last_byte + 2] = xorred_byte;
    user_package[last_byte + 3] = (BYTE) 0x0A;


    if (PS.reply_ack == REPLY_ACKNOWLEDGED) {
        clear_sent_buffer();
        for (i = 0; i < last_byte + 4; i++) {
            PS.sent_command[i + 1] = user_package[i];
            put_byte_to_sent_buffer(user_package[i]);
        }
    }
}

//
// This Function will return uint16, when you feed it with array pointer and current position;
//
WORD getInt16Value(BYTE *array, WORD location)
{
	return (int) ((array[location] & 0xFF) |
                        ((array[location + 1] & 0xFF) << 8));
} 

void processSysParamsList(void){
	WORD dataPointer = 6, paramPointer;
	
	PS.sysParamsQuantity = answer[5]; // Save quantity
	
	for (paramPointer = 1; paramPointer <= PS.sysParamsQuantity; paramPointer++)
	{
		PS.sysParams[paramPointer].Code = getInt16Value(answer, dataPointer);
		dataPointer += 2;
		PS.sysParams[paramPointer].Value = getInt16Value(answer, dataPointer);
		dataPointer += 2;
		PS.sysParams[paramPointer].MinValue = getInt16Value(answer, dataPointer);
		dataPointer += 2;
		PS.sysParams[paramPointer].MaxValue = getInt16Value(answer, dataPointer);
		dataPointer += 2;
	}

}

void process_telemeteria(){

    int ik = 0;
    /*===== Control Byte =====*/
    PS.control_byte = answer[3];
	temp_value = PS.control_byte & 0x80; // Cold start bit
	if (((temp_value) != PS.coldstartBit)) {
		PS.coldstartBit = temp_value;
        if ((temp_value) != 0x00) {
            strcpy(PS.MessageString, "Internal state is updating (no-alarm)");
            onbvar3[16] = 13;
            onbvar3[27] = 7;
            onbvar3[28] = 1;
            onbvar3[29] = 0;
            ps_trap(6, 3);
            onbvar3[16] = 15;
			return; // Should return by 12.10 specification
        } else {
            strcpy(PS.MessageString, "Internal state updated (no-alarm)");
            onbvar3[16] = 13;
            onbvar3[27] = 7;
            onbvar3[28] = 1;
            onbvar3[29] = 0;
            ps_trap(6, 3);
            onbvar3[16] = 15;
        }
	}

    start_power_main_byte = answer[14] + 4;
    temp_value = (int) ((answer[answer[16] + 4 + 8] & 0xFF) |
                        ((answer[answer[16] + 1 + 4 + 8] & 0xFF) << 8));
    PS.CurrentReading = answer[2];
    PS.VoltageReading = start_power_main_byte;
    temp_value = (int) ((answer[start_power_main_byte] & 0xFF) |
                        ((answer[start_power_main_byte + 1] & 0xFF) << 8));
    PS.mains.Voltage = temp_value;
    temp_value = (int) ((answer[start_power_main_byte + 2] & 0xFF) |
                        ((answer[start_power_main_byte + 3] & 0xFF) << 8));
    PS.mains.Frequency = temp_value;
    temp_value = answer[start_power_main_byte + 6]  & 0xFF;
    PS.mains.Status = temp_value;

    if (((temp_value & 0x01) != PS.mains.Alarm)) {
        if ((temp_value & 0x01) == 0x01) {
            strcpy(PS.MessageString, "Alarm Input Power System");
            PS.mains.Alarm = 1;
            onbvar3[16] = 13;
            onbvar3[27] = 1;
            onbvar3[28] = 4;
            onbvar3[29] = 0;
            ps_trap(6, 3);
            onbvar3[16] = 15;
        } else {
            strcpy(PS.MessageString, "Clear Alarm Input Power System");
            PS.mains.Alarm = 0;
            onbvar3[16] = 13;
            onbvar3[27] = 1;
            onbvar3[28] = 4;
            onbvar3[29] = 0;
            ps_trap(6, 3);
            onbvar3[16] = 15;
        }
    }

    /*==== LOAD BLOCK ===*/
    start_power_main_byte = answer[15] + 4;
    temp_value = (int) ((answer[start_power_main_byte] & 0xFF) |
                        ((answer[start_power_main_byte + 1] & 0xFF) << 8));
    PS.load.Voltage = temp_value;
    temp_value = (int) ((answer[start_power_main_byte + 2] & 0xFF) |
                        ((answer[start_power_main_byte + 3] & 0xFF) << 8));
    PS.load.Current = temp_value;

    // Блок информации об Автоматах
    temp_value = answer[start_power_main_byte + 4] & 0x01;
    if (temp_value != PS.load.Automat1State) {
        PS.load.Automat1State = temp_value;
        if ((temp_value & 0x01) == 0x01) {
            strcpy(PS.MessageString, "Alarm Load - Automat 1 switched off");
        } else {
            strcpy(PS.MessageString, "Clear Alarm Load - Automat 1");
        }
        onbvar3[16] = 13;
        onbvar3[27] = 2;
        onbvar3[28] = 3;
        onbvar3[29] = 0;
        ps_trap(6, 3);
        onbvar3[16] = 15;
    }

    temp_value = (answer[start_power_main_byte + 4] >> 1) & 0x01;
    if (temp_value != PS.load.Automat2State) {
        PS.load.Automat2State = temp_value;
        if ((temp_value & 0x01) == 0x01) {
            strcpy(PS.MessageString, "Alarm Load - Automat 2 switched off");
        } else {
            strcpy(PS.MessageString, "Clear Alarm Load - Automat 2");
        }
        onbvar3[16] = 13;
        onbvar3[27] = 2;
        onbvar3[28] = 4;
        onbvar3[29] = 0;
        ps_trap(6, 3);
        onbvar3[16] = 15;
    }

    // Блок информации об авариях напряжения
    temp_value = answer[start_power_main_byte + 5] & 0x01;
    if (temp_value != PS.load.LowVoltage) {
        PS.load.LowVoltage = temp_value;
        if ((temp_value & 0x01) == 0x01) {
            strcpy(PS.MessageString, "Alarm Load - Low Voltage");
        } else {
            strcpy(PS.MessageString, "Clear Load - Low Voltage alarm");
        }
        onbvar3[16] = 13;
        onbvar3[27] = 2;
        onbvar3[28] = 5;
        onbvar3[29] = 0;
        ps_trap(6, 3);
        onbvar3[16] = 15;
    }

    temp_value = (answer[start_power_main_byte + 5] >> 1) & 0x01;
    if (temp_value != PS.load.HighVoltage) {
        PS.load.HighVoltage = temp_value;
        if ((temp_value & 0x01) == 0x01) {
            strcpy(PS.MessageString, "Alarm Load - High Voltage");
        } else {
            strcpy(PS.MessageString, "Clear Alarm Load - High Voltage");
        }
        onbvar3[16] = 13;
        onbvar3[27] = 2;
        onbvar3[28] = 6;
        onbvar3[29] = 0;
        ps_trap(6, 3);
        onbvar3[16] = 15;
    }
    /*==== LOAD BLOCK END===*/
    /*==== QUANTITY BLOCK ====*/

    PS.batteries_count = answer[1 + 4];
    PS.psus_count = answer[2 + 4];
    PS.invertors_count = answer[3 + 4];
    PS.temperatures_count = answer[4 + 4];
    PS.logics_count = answer[5 + 4];
    PS.ext_io.quantityIO = answer[6 + 4];
	PS.extBoardExistence = answer[7 + 4];
    PS.climateControl.ClimateControlExists = answer[8 + 4]; // Indicates the availability of climate control parameters

    /*===== Batteries BLOCK ===*/
    start_battery_byte = answer[16] + 4;
    if (start_battery_byte != 0xFF) {
        for (ik = 0; ik < PS.batteries_count; ik++) {
            PS.battery[ik + 1].sequence_numberBat = answer[start_battery_byte + ik * 13];
            temp_value = (int) ((answer[start_battery_byte + 1 + ik * 13]  & 0xFF ) |
                                ((answer[start_battery_byte + 2 + ik * 13]  & 0xFF ) <<
                                 8));
            PS.battery[ik + 1].VoltageBat = temp_value;
            temp_value = ((answer[start_battery_byte + 3 + ik * 13]  & 0xFF ) |
                          ((answer[start_battery_byte + 4 + ik * 13]  & 0xFF ) <<
                           8));
            PS.battery[ik + 1].CurrentBat = temp_value;
            temp_value = ((answer[start_battery_byte + 5 + ik * 13]  & 0xFF ) |
                          ((answer[start_battery_byte + 6 + ik * 13]  & 0xFF ) <<
                           8));
            PS.battery[ik + 1].TemperatureBat = temp_value;
            temp_value = answer[start_battery_byte + 7 + ik * 13];
            PS.battery[ik + 1].StatusBat = temp_value; 

            if (((temp_value & 0x01) != PS.battery[ik + 1].Battery_AlarmBat)) {
                if ((temp_value & 0x01) == 0x01) {
                    strcpy(PS.MessageString, "Alarm Battery  ");
                    PS.MessageString[14] = 0x30 + ik + 1;
                    PS.battery[ik + 1].Battery_AlarmBat = (temp_value & 0x01);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm Battery  ");
                    PS.battery[ik + 1].Battery_AlarmBat = (temp_value & 0x01);
                    PS.MessageString[20] = 0x30 + ik + 1;
                }
                    onbvar3[27] = 4;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 7;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
            }

            if ((( (temp_value & 0x02) >> 1) != PS.battery[ik + 1].Is_chargingBat)) {
                if (( (temp_value & 0x02) >> 1) == 0x01) {
                    strcpy(PS.MessageString, "Battery   is charging");
                    PS.MessageString[8] = 0x30 + ik + 1;
                    PS.battery[ik + 1].Is_chargingBat =  (temp_value & 0x02) >> 1;
                    onbvar3[27] = 4;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 8;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Battery   is not charging");
                    PS.MessageString[8] = 0x30 + ik + 1;
                    PS.battery[ik + 1].Is_chargingBat =  (temp_value & 0x02) >> 1;
                    onbvar3[27] = 4;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 8;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

               // temp_value keeps Status value. Let's examine it for ASimmetry alarm
            if (((temp_value & 0x04) >> 2) != (PS.battery[ik + 1].BatteryAsimmetryAlarm)) {
                if (( (temp_value & 0x04) >> 2) == 0x01) {
                    strcpy(PS.MessageString, "Battery   asimmetry alarm");
                    
                } else {
                    strcpy(PS.MessageString, "Battery   no asimetry alarm");
                }
                PS.MessageString[8] = 0x30 + ik + 1; // Inserts battery number to the message string
                PS.battery[ik + 1].BatteryAsimmetryAlarm =  (temp_value & 0x04) >> 2;
                onbvar3[27] = 4;
                onbvar3[28] = 2;
                onbvar3[29] = 1;
                onbvar3[30] = 10; // pointer to correct OID of variable transmitted with trap
                onbvar3[31] = ik + 1;

                ps_trap(6, 3);
            }
                // temp_value keeps Status value. Let's examine it for Deep discharge alarm
            if (((temp_value & 0x08) >> 3) != (PS.battery[ik + 1].BatteryDeepDischargeAlarm)) {
                if (( (temp_value & 0x08) >> 3) == 0x01) {
                    strcpy(PS.MessageString, "Battery   deep discharge alarm");
                } else {
                    strcpy(PS.MessageString, "Battery   no deep discharge alarm");
                }
                PS.MessageString[8] = 0x30 + ik + 1;
                PS.battery[ik + 1].BatteryDeepDischargeAlarm =  (temp_value & 0x08) >> 3;
                onbvar3[27] = 4;
                onbvar3[28] = 2;
                onbvar3[29] = 1;
                onbvar3[30] = 11; // pointer to correct OID of variable transmitted with trap
                onbvar3[31] = ik + 1;

                ps_trap(6, 3);
            }

            temp_value = ((answer[start_battery_byte + 8 + ik * 13]  & 0xFF ) |
                          ((answer[start_battery_byte + 9 + ik * 13]  & 0xFF ) << 8));
            PS.battery[ik + 1].CapacityBat = temp_value;
            temp_value = ((answer[start_battery_byte + 10 + ik * 13]  & 0xFF ));
            PS.battery[ik + 1].ChargeBat = temp_value;
        }
    }

    /*===== Batteries BLOCK END ===*/

    /*===== PSUs BLOCK ===*/
    start_psu_byte = answer[17] + 4;
    if (start_psu_byte != 0xFF) {
        for (ik = 0; ik < PS.psus_count; ik++) {
            PS.psu[ik + 1].sequence_number = answer[start_psu_byte + ik * 10];
            temp_value = (int) ((answer[start_psu_byte + 1 + ik * 10]  & 0xFF ) |
                                ((answer[start_psu_byte + 2 + ik * 10]  & 0xFF ) <<
                                 8));
            PS.psu[ik + 1].Voltage = temp_value;
            temp_value = ((answer[start_psu_byte + 3 + ik * 10]  & 0xFF ) |
                          ((answer[start_psu_byte + 4 + ik * 10]  & 0xFF ) <<
                           8));
            PS.psu[ik + 1].Current = temp_value;
            temp_value = ((answer[start_psu_byte + 5 + ik * 10]  & 0xFF ) |
                          ((answer[start_psu_byte + 6 + ik * 10]  & 0xFF ) <<
                           8));
            PS.psu[ik + 1].Temperature = temp_value;
            temp_value = answer[start_psu_byte + 7 + ik * 10];
            PS.psu[ik + 1].Status = temp_value;

            if (((((temp_value & 0x02) >> 1)) != PS.psu[ik + 1].Heat_Alarm)) {
                if (( (temp_value & 0x02) >> 1) == 0x01) {
                    strcpy(PS.MessageString, "Alarm Overheat PSU  ");
                    PS.MessageString[19] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Heat_Alarm = ((temp_value & 0x02) >> 1);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 5;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm Overheat PSU  ");
                    PS.MessageString[25] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Heat_Alarm = ((temp_value & 0x02) >> 1);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 5;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }
            if ((((temp_value & 0x04) >> 2) != PS.psu[ik + 1].Low_Voltage)) {
                if (( ((temp_value & 0x04) >> 2)) == 0x01) {
                    strcpy(PS.MessageString, "Alarm Low Voltage PSU  ");
                    PS.MessageString[22] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Low_Voltage = ((temp_value & 0x04) >> 2);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 6;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm Low Voltage PSU  ");
                    PS.MessageString[28] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Low_Voltage = ((temp_value & 0x04) >> 2);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 6;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

            if ((((temp_value & 0x08) >> 3) != PS.psu[ik + 1].High_Voltage)) {
                if (( ((temp_value & 0x08) >> 3)) == 0x01) {
                    strcpy(PS.MessageString, "Alarm High Voltage PSU  ");
                    PS.MessageString[23] = 0x30 + ik + 1;
                    PS.psu[ik + 1].High_Voltage = ((temp_value & 0x08) >> 3);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 7;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm High Voltage PSU  ");
                    PS.MessageString[29] = 0x30 + ik + 1;
                    PS.psu[ik + 1].High_Voltage = ((temp_value & 0x08) >> 3);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 7;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

            if ((((temp_value & 0x10) >> 4) != PS.psu[ik + 1].Connection_Lost)) {
                if (( ((temp_value & 0x10) >> 4)) == 0x01) {
                    strcpy(PS.MessageString, "Alarm No Connection PSU ");
                    PS.MessageString[23] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Connection_Lost = ((temp_value & 0x10) >> 4);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 8;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm No Connection PSU ");
                    PS.MessageString[29] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Connection_Lost = ((temp_value & 0x10) >> 4);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 8;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

            if ((((temp_value & 0x20) >> 5) != PS.psu[ik + 1].External_Lock)) {
                if (( ((temp_value & 0x20) >> 5)) == 0x01) {
                    strcpy(PS.MessageString, "PSU   Locked");
                    PS.MessageString[4] = 0x30 + ik + 1;
                    PS.psu[ik + 1].External_Lock = ((temp_value & 0x20) >> 5);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 9;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "PSU   Unlocked");
                    PS.MessageString[4] = 0x30 + ik + 1;
                    PS.psu[ik + 1].External_Lock = ((temp_value & 0x20) >> 5);
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 9;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

            temp_value = temp_value & 0x1F;
            if (temp_value == 0x00)
                temp_value = 0x01;
            else
                temp_value = 0x00;
            if (((temp_value ) != PS.psu[ik + 1].Reserved)) {
                if ( (temp_value ) == 0x01) {
                    strcpy(PS.MessageString, "PSU   In Reserve");
                    PS.MessageString[4] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Reserved = (temp_value );
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 10;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "PSU   Not In Reserve");
                    PS.MessageString[4] = 0x30 + ik + 1;
                    PS.psu[ik + 1].Reserved = (temp_value );
                    onbvar3[27] = 3;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 10;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }
        }
    }
    /*=====  BLOCK END ===*/

    /*===== Temperatures BLOCK ===*/

    start_temper_byte = answer[19] + 4;
    if (start_temper_byte != 0xFF) {
        for (ik = 0; ik < PS.temperatures_count; ik++) {
            PS.temp_sensor[ik + 1].sequence_numberTemp = answer[start_temper_byte + ik * 4];
            temp_value = (int) ((answer[start_temper_byte + 1 + ik * 4]  & 0xFF ) |
                                ((answer[start_temper_byte + 2 + ik * 4]  & 0xFF ) <<
                                 8));
            PS.temp_sensor[ik + 1].TemperatureTemp = temp_value;
            temp_value = answer[start_temper_byte + 3 + ik * 4];
            PS.temp_sensor[ik + 1].StatusTemp = temp_value;
            if ((((temp_value & 0x01)) != PS.temp_sensor[ik + 1].OutoforderTemp)) {
                if (( ((temp_value & 0x01))) == 0x01) {
                    strcpy(PS.MessageString, "TempSensor   is Invalid");
                    PS.MessageString[11] = 0x30 + ik + 1;
                    PS.temp_sensor[ik + 1].OutoforderTemp = (temp_value & 0x01);
                    onbvar3[27] = 5;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 4;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "TempSensor   is Valid");
                    PS.MessageString[11] = 0x30 + ik + 1;
                    PS.temp_sensor[ik + 1].OutoforderTemp = (temp_value & 0x01);
                    onbvar3[27] = 5;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 4;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }

            if (((((temp_value & 0x02) >> 1)) != PS.temp_sensor[ik + 1].Temp_alarmTemp)) {
                if (( (((temp_value & 0x02) >> 1))) == 0x01) {
                    strcpy(PS.MessageString, "Alarm TempSensor  ");
                    PS.MessageString[17] = 0x30 + ik + 1;
                    PS.temp_sensor[ik + 1].Temp_alarmTemp = ((temp_value & 0x02) >> 1);
                    onbvar3[27] = 5;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 5;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                } else {
                    strcpy(PS.MessageString, "Clear Alarm TempSensor  ");
                    PS.MessageString[23] = 0x30 + ik + 1;
                    PS.temp_sensor[ik + 1].Temp_alarmTemp = ((temp_value & 0x02) >> 1);
                    onbvar3[27] = 5;
                    onbvar3[28] = 2;
                    onbvar3[29] = 1;
                    onbvar3[30] = 5;
                    onbvar3[31] = ik + 1;
                    ps_trap(6, 3);
                }
            }
        }
    }
    /*=====  BLOCK END ===*/

    /*===== Logic BLOCK ===*/
    start_logic_byte = answer[20] + 4;
    if (start_logic_byte != 0xFF) {
        for (ik = 0; ik < PS.logics_count; ik++) {
            PS.logic_input[ik + 1].sequence_numberLogic = answer[start_logic_byte + ik * 2];
            temp_value = answer[start_logic_byte + 1 + ik * 2];
            PS.logic_input[ik + 1].StatusLogic = temp_value;
            if ((((temp_value & 0x01)) != PS.logic_input[ik + 1].Active)) {
                if (temp_value & 0x01) {
                    strcpy(PS.MessageString, "Logic Input   is Active");
                } else {
                    strcpy(PS.MessageString, "Logic Input   is Inactive");
                }
                PS.MessageString[12] = 0x30 + ik + 1;
                PS.logic_input[ik + 1].Active = (temp_value & 0x01);
                onbvar3[27] = 6;
                onbvar3[28] = 2;
                onbvar3[29] = 1;
                onbvar3[30] = 2;
                onbvar3[31] = ik + 1;
                ps_trap(6, 3);
            }

            if (((temp_value & 0x02) >> 1) != PS.logic_input[ik + 1].Alarm) {
                if ((temp_value & 0x02) >> 1) {
                    switch (ik){
                    case 0:
                        strcpy(PS.MessageString, "Door opening alarm");
                        break;
                    case 1:
                        strcpy(PS.MessageString, "Fire/Smoke alarm");
                        break;
					case 2:
                        strcpy(PS.MessageString, "Shock sensor alarm");
                        break;
                    default:
                        strcpy(PS.MessageString, "Alarm Logic Input  ");
                        PS.MessageString[18] = 0x30 + ik + 1;
                        break;
                    }
                } else {
                    switch (ik){
                    case 0:
                        strcpy(PS.MessageString, "Clear Door opening alarm");
                        break;
					case 1:
                        strcpy(PS.MessageString, "Clear Fire/Smoke alarm");
                        break;
                    case 2:
                        strcpy(PS.MessageString, "Clear Shock sensor alarm");
                        break;
                    default:
                        strcpy(PS.MessageString, "Clear Alarm Logic Input  ");
                        PS.MessageString[24] = 0x30 + ik + 1;
                        break;
                    }
                }
                PS.logic_input[ik + 1].Alarm = ((temp_value & 0x02) >> 1);
                onbvar3[27] = 6;
                onbvar3[28] = 2;
                onbvar3[29] = 1;
                onbvar3[30] = 3;
                onbvar3[31] = ik + 1;
                ps_trap(6, 3);
            }
        }
    }

    /*=====  BLOCK END ===*/

    /*===== Special functions BLOCK ===*/
    temp_value = answer[answer[21] + 4];
    if (PS.special_functions != temp_value) {
        PS.special_functions = temp_value;
		PS.specFuncCapacityControl = temp_value & 0x03;
		PS.specFuncCompensationCharge = (temp_value == 10)?0x01:0x00;
        if (temp_value == 10) {
            strcpy(PS.MessageString, "Compensation Charge Activated");

        } else if ((temp_value > 0 ) & (temp_value < 10)) {
            strcpy(PS.MessageString, "Battery   Capacity Control");
            PS.MessageString[7] = 0x30 + temp_value;
        } else
            strcpy(PS.MessageString, "Special Functions Disabled");

        onbvar3[16] = 13;
        onbvar3[27] = 7;
        onbvar3[28] = 2;
        onbvar3[29] = 0;
        ps_trap(6, 3);
        onbvar3[16] = 15;
    }
    /*=====  BLOCK END ===*/

    /*===== EXT IO BLOCK ===*/
    start_ext_io_byte = answer[22] + 4;
    if (start_ext_io_byte != 0xFF) {
        PS.ext_io.StatusExtIO = answer[start_ext_io_byte];
    }
    /*=====  BLOCK END ===*/
	/*===== EXTENSION BOARD INFO ===*/
	startExtBoardByte = answer[23] + 4;
	if (PS.extBoardExistence == 10){
		temp_value = (int) ((answer[startExtBoardByte] & 0xFF) |
							((answer[startExtBoardByte + 1] & 0xFF) << 8));
		PS.extVoltageInput1 = temp_value;
		temp_value = (int) ((answer[startExtBoardByte + 2] & 0xFF) |
							((answer[startExtBoardByte + 3] & 0xFF) << 8));
		PS.extVoltageInput2 = temp_value;
		temp_value = (int) ((answer[startExtBoardByte + 4] & 0xFF) |
							((answer[startExtBoardByte + 5] & 0xFF) << 8));
		PS.extVoltagePES = temp_value;
		temp_value = (int) ((answer[startExtBoardByte + 6] & 0xFF) |
							((answer[startExtBoardByte + 7] & 0xFF) << 8));
		PS.extCurrentPower = temp_value;
		temp_value = (int) ((answer[startExtBoardByte + 10] & 0xFF) |
							((answer[startExtBoardByte + 11] & 0xFF) << 8));
		PS.extTotalEnergy = ((DWORD)temp_value) & 0xFFFF;       
		temp_value = (int) ((answer[startExtBoardByte + 8] & 0xFF) |
							((answer[startExtBoardByte + 9] & 0xFF) << 8));		
		PS.extTotalEnergy = (DWORD)(PS.extTotalEnergy << 16) | (((DWORD)temp_value)& 0xFFFF);       
		temp_value = (int) (answer[startExtBoardByte + 12] & 0xFF);
		PS.extFanSpeed = temp_value;
		temp_value = (int) (answer[startExtBoardByte + 13] & 0xFF);
		PS.extActiveInput = temp_value;
	}
	/*=====  BLOCK END ===*/

    /*===== CLIMATE CONTROL  ===*/
    startClimateControl = answer[24] + 4;
    if (PS.climateControl.ClimateControlExists == 10) {
        temp_value = (int) ((answer[startClimateControl] & 0xFF) |
                            ((answer[startClimateControl + 1] & 0xFF) << 8));
        PS.climateControl.BoxTemperature = temp_value; // Temperature of the Box added
        temp_value = (int) (answer[startClimateControl + 2] & 0xFF);

        // temp_value keeps Status value. Let's examine it for Deep discharge alarm
        if ((temp_value & 0x01) != PS.climateControl.BoxAlarm) {
            if (temp_value & 0x01) {
                strcpy(PS.MessageString, "Enclosure Temperature Alarm");
            } else {
                strcpy(PS.MessageString, "Clear Enclosure Temperature Alarm");
            }

            PS.climateControl.BoxAlarm = temp_value; // Alarm for Box Added
            onbvar3[16] = 13;
            onbvar3[27] = 14;
            onbvar3[28] = 3;
            onbvar3[29] = 0;
            ps_trap(6, 3);
            onbvar3[16] = 15;
        }
        temp_value = (int) (answer[startClimateControl + 3] & 0xFF);
        PS.climateControl.LoadOffState = temp_value;  // Load Off State added
        temp_value = (int) (answer[startClimateControl + 4] & 0xFF);
        PS.climateControl.LoadControlVar = temp_value; // Load Control Variable indication added
        temp_value = (int) (answer[startClimateControl + 5] & 0xFF);
        PS.climateControl.BatteryOffState = temp_value; // Battery Off State added
        temp_value = (int) (answer[startClimateControl + 6] & 0xFF);
        PS.climateControl.BatteryControlVar = temp_value; // Battery Control Variable indication added
        temp_value = (int) (answer[startClimateControl + 7] & 0xFF);
        PS.climateControl.FanPositionVar = temp_value; // Battery Control Variable indication added
    }
    /*=====  BLOCK END ===*/
}



void check_if_held(){
    if ((answer[5] == 0xFF))
        PS.command_byte = COMMAND_OK;
    else if ((answer[5] == 0x01)) PS.command_byte = COMMAND_FAILED;
    else PS.command_byte = COMMAND_INVALID;
}

void proccess_command_reply(){
    int ik_char = 0;

    switch (answer[4]) {
    case SET_ACTIVE_BPS:
        if ((answer[5] == SET_ACTIVE_BPS) & (answer[6] == answer[7]) & (answer[7] == ((BYTE)(PS.command_byte - SET_ACTIVE_BPS * 100))))
            PS.command_byte = COMMAND_OK;
        else PS.command_byte = COMMAND_FAILED;
        break;
    case ENABLE_COMPENSATION_CHARGE:
        check_if_held();
        break;
    case ENABLE_CAPACITY_CONTROL:
        check_if_held();
        break;
    case DISABLE_BPS:
        if ((answer[5] == DISABLE_BPS) & (answer[6] == answer[7]) & (answer[7] == ((BYTE)(PS.command_byte - DISABLE_BPS * 100))))
            PS.command_byte = COMMAND_OK;
        else PS.command_byte = COMMAND_FAILED;      
        break;
    case CHECK_CONNECTION:
        if ((answer[5] == CHECK_CONNECTION))
            PS.command_byte = COMMAND_OK;
        else PS.command_byte = COMMAND_FAILED;              
        break;
    case DISABLE_SPECIAL_FUNCTIONS:
        check_if_held();
        break;
    case UNLOCK_BPSS:
        check_if_held();
        break;
    case ENABLE_PARRALEL_OPERATION:
        check_if_held();
        break;
    case DISABLE_PARRALEL_OPERATION:
        check_if_held();
        break;
    case RESET_ALL_ALARMS:
        check_if_held();
        break;
    case GET_EVENTS_QUANTITY:
        if (answer[5] < 65) {
            PS.events_count = answer[5];
            PS.command_byte = COMMAND_OK;
        } else PS.command_byte = COMMAND_FAILED;
        break;
    case GET_EVENT:
        if (answer[5] == ((BYTE)(PS.command_byte - GET_EVENT * 100))) {
            PS.event[answer[5]].sequence_numberEvent = answer[5];
            PS.event[answer[5]].Device_Type = answer[6];
            PS.event[answer[5]].Device_Number = answer[7];
            PS.event[answer[5]].Event_Type = answer[8];
            PS.event[answer[5]].Event_Year_Start = answer[14];
            PS.event[answer[5]].Event_Month_Start = answer[15];
            PS.event[answer[5]].Event_Day_Start = answer[16];
            PS.event[answer[5]].Event_Hour_Start = answer[18];
            PS.event[answer[5]].Event_Minute_Start = answer[19];
            PS.event[answer[5]].Event_Second_Start = answer[20];
            PS.event[answer[5]].Event_Year_Finished = answer[22];
            PS.event[answer[5]].Event_Month_Finished = answer[23];
            PS.event[answer[5]].Event_Day_Finished = answer[24];
            PS.event[answer[5]].Event_Hour_Finished = answer[26];
            PS.event[answer[5]].Event_Minute_Finished = answer[27];
            PS.event[answer[5]].Event_Second_Finished = answer[28];
            PS.command_byte = COMMAND_OK;
        } else PS.command_byte = COMMAND_FAILED;
        break;
    case GET_SETTINGS_TABLE:
        PS.command_answer   = answer[7];
        PS.sparam_type      = answer[5];
        PS.command_id       = answer[5];
        PS.command_byte     = COMMAND_OK;
        break;
    case GET_SETTINGS_PARAMETER:
        temp_value = (int) ((answer[6] & 0xFF) |
                            ((answer[7] & 0xFF) << 8));
        PS.command_answer   = temp_value;
        PS.command_id       = answer[5];
        PS.command_byte     = COMMAND_OK;
        break;
    case SET_SETTINGS_PARAMETER:
        PS.command_id       = answer[5];
        if ((answer[6] == 0xFF))
            PS.command_byte     = COMMAND_OK;
        else if ((answer[6] == 0x01))
            PS.command_byte     = COMMAND_FAILED;
        else PS.command_byte    = COMMAND_INVALID;
        break;
    case SET_EXTERNAL_IO:
        PS.command_id       =answer[5];
        if ((answer[6] == 0xFF))
            PS.command_byte     = COMMAND_OK;
        else if ((answer[6] == 0x01))
            PS.command_byte     = COMMAND_FAILED;
    case GET_DEVICE_INFO:
        PS.device_info.Device_Code = answer[5];
        temp_value = (int) ((answer[6] & 0xFF) |
                            ((answer[7] & 0xFF) << 8));
        PS.device_info.Serial_Number_LSB = temp_value;
        temp_value = (int) ((answer[8] & 0xFF) |
                            ((answer[9] & 0xFF) << 8));
        PS.device_info.Serial_Number_MSB = temp_value;
        PS.command_byte     = COMMAND_OK;
        break;
    case GET_LOCATION_INFO:
        PS.device_info.Serial_Number_MSB = answer[5];
        for (ik_char = 0; ik_char < PS.device_info.Serial_Number_MSB; ik_char++)
            PS.device_info.Location[ik_char] = answer[6 + ik_char];
        PS.device_info.Location[PS.device_info.Serial_Number_MSB] = 0x00;
        PS.command_byte     = COMMAND_OK;
        break;
    case SET_LOAD_CTRL_VAR:
        check_if_held();
        break;
    case SET_BATTERY_CTRL_VAR:
        check_if_held();
        break;
		default:
        PS.command_byte = COMMAND_INVALID;
        break;
    }
}


void put_byte_to_sent_buffer(BYTE byte){
    BYTE slave_byte;
    slave_byte = ((byte&0xF0) >> 4);
    slave_byte = slave_byte&0x0F;

    if (slave_byte > 9) slave_byte = slave_byte + 0x37;
    else  slave_byte = slave_byte + 0x30;

    PS.sent_string[sent_position++] = slave_byte;
    slave_byte = ((byte&0x0F));

    if (slave_byte > 0x09) slave_byte = slave_byte + 0x37;
    else  slave_byte = slave_byte + 0x30;

    PS.sent_string[sent_position++] = slave_byte;
    PS.sent_string[sent_position] = 0x00;
}

void clear_sent_buffer(void){
    sent_position = 0;
    PS.sent_string[0] = 0x00;
}

void put_byte_to_rcvd_buffer(BYTE byte){
    BYTE slave_byte;
    slave_byte = ((byte&0xF0) >> 4);
    slave_byte = slave_byte&0x0F;

    if (slave_byte > 9) slave_byte = slave_byte + 0x37;
    else  slave_byte = slave_byte + 0x30;

    PS.rcvd_string[rcvd_position++] = slave_byte;
    slave_byte = ((byte&0x0F));

    if (slave_byte > 0x09) slave_byte = slave_byte + 0x37;
    else  slave_byte = slave_byte + 0x30;

    PS.rcvd_string[rcvd_position++] = slave_byte;
    PS.rcvd_string[rcvd_position] = 0x00;
}

void clear_rcvd_buffer(void){
    rcvd_position = 0;
    PS.rcvd_string[0] = 0x00;
}
