/*****************************************************************************/
/*****************************************************************************/
/* SNMP Module :                                                             */
/* - init the variables for SNMP-interface                                   */
/* - functions called by snmp-interface for read-write-variables and table   */
/*****************************************************************************/
/* Version B1.00 Magic7 SNMP Agent                                           */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  as  first testversion with all functionality                  */
/* 2002-08-02  ported to CPK450                                              */
/*****************************************************************************/
#include "bldFlags.h"
#include <kernel.h>
#include <io.h>
#include <string.h>
#include <ip.h>
#include <udp.h>
#include <globals.h>
#include <snmp\snmp.h>
#include "snmpdef.h"
#include "demo.h"


/* external variables ********************************************************/
extern struct snmp_context scon;
struct PS_def PS;

/* static variables **********************************************************/
/* Calculation of enterprise id: ( 7777 is taken as an example )
   Given number: 7777 = 1E61(hex) = 0001 1110  0110 0001
   Use 7 bits, fill with 0:       = 0011 1100  0110 0001
   Set first bit to 1:            = 1011 1100  0110 0001 = BC61(hex)
   = 188, 97
*/
BYTE enterpriset[] = { 6, 8, 0x2b, 6, 1, 4, 1, 130, 167, 60};
                  /* 1st char is always 6; 2nd length of objid excl length */

BYTE onbvar[] = {/* 1st char is always 6; 2nd length of objid excl. length */
	6, 8, 0x2b, 6, 1, 2, 1, 1, 1, 0,                 /* System Description */
	6, 8, 0x2b, 6, 1, 2, 1, 1, 3, 0                  /* SysUpTime */
}; /* object-id for standard-traps */

BYTE onbvar2[] = {/* 1st char is always 6; 2nd length of objid excl. length */
      6, 13, 0x2b, 6, 1, 4, 1, 130, 167, 60, 1, 2, 7, 4, 0   /*Trap-Error-String */
}; /* object-id for customer specific Trap 2 */

BYTE onbvar3[] = {/* 1st char is always 6; 2nd length of objid excl. length */
      6, 13, 0x2b, 6, 1, 4, 1, 130, 167, 60, 1, 2, 7, 4, 0,  /*Trap-Error-String */
      6, 15, 0x2b, 6, 1, 4, 1, 130, 167, 60, 1, 2, 7, 5, 0, 0, 0   /*Trap-Error-Value */
/* This byte should be set to passed variable ---^      */
}; /* object-id for customer specific Trap 3 */



/* global variables **********************************************************/
/* char S_name[60] = "Magic7 Power Snr:  xxx-xxx By.yy"; */
			/* "xxx-xxx By.yy" must be the last part of the string */
/* GLOBAL BYTE S_obj[]={ 9,0x2b,6,1,4,1,188,97,1,2 }; */


/* external prototypes *******************************************************/
extern int snmp_trap ( BYTE *enterprise,int typ, int spec );
extern int snmp_leaf (WORD typ, WORD par);

/* internal prototypes *******************************************************/
void ps_trap(int a, int b);
//voltage_Lower(WORD *op);
//send_command(WORD *op);
//history_table(WORD *op);
batt_table(WORD *op);
psus_table(WORD *op);
sensors_table(WORD *op);
logic_table(WORD *op);
events_table(WORD *op);
specialFunctionsCapacityControl(WORD *op);
specialFunctionsCompensationCharge(WORD *op);
monitoringLoadControlVariable(WORD *op);
monitoringBatteryControlVariable(WORD *op);
sysParamTable(WORD *op);
funcExtFanSpeed(WORD *op);
#include "snmpmib.h" /* definition of private mib */


/*****************************************************************************/
/* function ps_trap :                                                        */
/* - creating traps, standard or customer specific                           */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/* Parameter  : int typ = Trap-type                                          */
/*              int spec= if typ==6 the customer-trap can be specified here  */
/*****************************************************************************/
/* Returncode : void                                                         */
/*****************************************************************************/
/* History :                                                                 */
/* 2001-06-26  KK  Project start                                             */
/*****************************************************************************/
void ps_trap(int typ, int spec) {
/*
    typ :
        0 = Cold start
        1 = Warm start
        2 = Link down port
        3 = Link port
        4 = Authentication failure
        5 = Neighbour loss
        6 = Private trap

    spec: can be used to classify private trap
        2 = Errorcode detected
*/
    int rc;

    if (!*((DWORD*) (Setup + 22))) return;		/* check for snmp-mgr IP */
    else {
        if(typ < 6) {
            /* Standard Traps */
            scon.inpptr = onbvar;
            scon.inpend = onbvar + sizeof(onbvar);
        }
        else {
            /* Customer specific Trap */
            switch(spec) {
                case 2:					/* serial comm */
                    scon.inpptr = onbvar2;
                    scon.inpend = onbvar2 + sizeof(onbvar2);
                    break;
                case 3:					/* out of limit */
                    scon.inpptr = onbvar3;
                    scon.inpend = onbvar3 + sizeof(onbvar3) - (15 - onbvar3[16]);
                    break;
                default:
                    scon.inpptr = onbvar;
                    scon.inpend = onbvar + sizeof(onbvar);
                    break;
            }
        }
	}

	rc = snmp_trap(enterpriset, typ, spec);    /* create trap message */

	if(rc > 0) {
		if(Setup[22]) udp_send(Setup + 22, 162, 162, outbuf, rc);
		if(Setup[26]) udp_send(Setup + 26, 162, 162, outbuf, rc);
		if(Setup[30]) udp_send(Setup + 30, 162, 162, outbuf, rc);
	}
}


debug_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;

	if ( i > MAX_REQUEST_LENGTH) { op[-1]++; i=*op=1;}

	switch(op[-1]) {

	case 1:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.sent_command[i]);
		break;
	case 2:/* Amp */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.rcvd_command[i]);
		break;
	case 3:/* Temp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.logic_input[i].Alarm);
		break;
	case 4:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.logic_input[i].StatusLogic);
		break;
	default:
		return S_noSuchName;
	}

    return 0;
}


events_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;

	if (PS.events_count != 0){
		if ( i > PS.events_count) { op[-1]++; i=*op=1;}}
	else {
	if ( i > 1) { op[-1]++; i=*op=1;}
		return snmp_leaf(S_INT  + S_RAM, (WORD)&PS.events_count);
	}
	
	switch(op[-1]) {

	case 1:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].sequence_numberEvent);
		break;
	case 2:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Device_Type);
		break;
	case 3:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Device_Number);
		break;
	case 4:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Type);
		break;
	case 5:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Year_Start);
		break;
	case 6:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Month_Start);
		break;
	case 7:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Day_Start);
		break;
	case 8:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Hour_Start);
		break;
	case 9:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Minute_Start);
		break;
	case 10:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Second_Start);
		break;
	case 11:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Year_Finished);
		break;
	case 12:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Month_Finished);
		break;
	case 13:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Day_Finished);
		break;
	case 14:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Hour_Finished);
		break;
	case 15:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Minute_Finished);
		break;
	case 16:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.event[i].Event_Second_Finished);
		break;
	default:
		return S_noSuchName;
	}

    return 0;
}

logic_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;

	if (PS.logics_count != 0){
		if ( i > PS.logics_count) { op[-1]++; i=*op=1;}}
	else {
	if ( i > 1) { op[-1]++; i=*op=1;}
		return snmp_leaf(S_INT  + S_RAM, (WORD)&PS.logics_count);
	}
	
	switch(op[-1]) {

	case 1:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.logic_input[i].sequence_numberLogic);
		break;
	case 2:/* Amp */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.logic_input[i].Active);
		break;
	case 3:/* Temp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.logic_input[i].Alarm);
		break;
	case 4:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.logic_input[i].StatusLogic);
		break;
	default:
		return S_noSuchName;
	}

    return 0;
}

sensors_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;

	if (PS.temperatures_count != 0){
		if ( i > PS.temperatures_count) { op[-1]++; i=*op=1;}}
	else {
	if ( i > 1) { op[-1]++; i=*op=1;}
	return snmp_leaf(S_INT  + S_RAM, (WORD)&PS.temperatures_count);
	}

	
	
	switch(op[-1]) {

	case 1:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.temp_sensor[i].sequence_numberTemp);
		break;
	case 2:/* Amp */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.temp_sensor[i].TemperatureTemp);
		break;
	case 3:/* Temp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.temp_sensor[i].Temp_alarmTemp);
		break;
	case 4:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.temp_sensor[i].OutoforderTemp);
		break;
	case 5: /* 89p */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.temp_sensor[i].StatusTemp);
		break;
	case 6: /* 89p */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.temp_sensor[i].StatusTemp);
		break;		
	default:
		return S_noSuchName;
	}

    return 0; //snmp_leaf(S_INT  + S_RAM, (WORD)&PS.temperatures_count);
}


batt_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;
	
	if (PS.batteries_count != 0){
		if ( i > PS.batteries_count) { op[-1]++; i=*op=1;}}
	else {
	if ( i > 1) { op[-1]++; i=*op=1;}
		return snmp_leaf(S_INT  + S_RAM, (WORD)&PS.batteries_count);
	}	
	
	switch(op[-1]) {

	case 1:
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.battery[i].sequence_numberBat);
		break;
	case 2:
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.battery[i].VoltageBat);
		break;
	case 3:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].CurrentBat);
		break;
	case 4:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].TemperatureBat);
		break;
	case 5:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].CapacityBat);
		break;
	case 6:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].ChargeBat);
		break;
	case 7:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].Battery_AlarmBat);
		break;
	case 8:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].Is_chargingBat);
		break;
	case 9:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].StatusBat);
		break;
	case 10:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].BatteryAsimmetryAlarm);
		break;
	case 11:
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.battery[i].BatteryDeepDischargeAlarm);
		break;
	default:
		return S_noSuchName;
	}

    return 0;
}

psus_table(op) WORD *op;
{
	WORD i;

	if((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

	if(scon.flags & FLAG_INCR) { 	/* if increment */
		if(scon.objend == op) {
			i = *op = 1; scon.objend++;
			}
		else {
			i = *op + 1;
			}

		*op = i;
		}
	else {				/* non incremental */
		i = *op;
		}


	scon.objend = op + 1;
	if (( i > PS.psus_count) | ( i > 14 )) { op[-1]++; i=*op=1; }

	switch(op[-1]) {

	case 1:/* Volt */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.psu[i].sequence_number);
		break;
	case 2:/* Amp */
		snmp_leaf(S_INT  + S_RAM, (WORD)&PS.psu[i].Voltage);
		break;
	case 3:/* Temp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Current);
		break;
	case 4:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Temperature);
		break;
	case 5:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Heat_Alarm);
		break;
	case 6:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Low_Voltage);
		break;
	case 7:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].High_Voltage);
		break;
	case 8:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Connection_Lost);
		break;
	case 9:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].External_Lock);
		break;
	case 10:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Reserved);
		break;
	case 11:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Status);
		break;
	case 12:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Status);//(WORD)&PS.psu[i].Temperature);
		break;
	case 13:/* TimeStamp */
		snmp_leaf(S_INT + S_RAM, (WORD)&PS.psu[i].Status);//(WORD)&PS.psu[i].Temperature);
		break;
	
	default:
		return S_noSuchName;
	}

    return 0;
}


/*****************************************************************************/
/* function Fan Speed     :                                                  */
/* - called from SNMP for reading, writing and checking of integer value     */
/*   in the data structure.                                                  */
/*****************************************************************************/
funcExtFanSpeed(op) WORD *op;
{
    if ( ( scon.flags & FLAG_SET ) )                 /* Setting ? */
    {
        /* to check for a 16 bit integer value                            */
        /*      if ( ( scon.intval < -32767) || (scon.intval > 32768 ) )  */
        /* to check for reasonable 'lower voltage' valus                  */
        /* here we check for value between 300 and 500                    */
        if ( ( scon.intval >12) || (scon.intval < 1 ) )
        {
            return S_badValue;
        }
        if( scon.flags & FLAG_PASS )             /* just checking */
        {
            return 0;
        }
        else                                         /* now do it */
        {
            PS.command_answer = (WORD) scon.intval;
			PS.command_id = 0x50; // ID for FAN CHANGE!
			PS.command_byte = SET_SETTINGS_PARAMETER * 100 + SET_SPARAM_INT;
            return 0;
        }
    }
    else
    {
        if (scon.flags & FLAG_INCR)
        {
            if (scon.objend == op )
            {
                *scon.objend++ = 0;
            }
        }
        if (scon.objend != op + 1 || op[0] != 0)
        {
            return S_NextEntry;
        }
        return (snmp_leaf(S_INT + S_RAM, (WORD)&(PS.extFanSpeed)));
    }
}

/*****************************************************************************/
/* function Special Functions:                                               */
/* - called from SNMP for reading, writing and checking of integer value     */
/*   in the data structure.                                                  */
/*   0 - for disable all;
/*   
/*****************************************************************************/
specialFunctionsCapacityControl(op) WORD *op;
{
    if ( ( scon.flags & FLAG_SET ) )                 /* Setting ? */
    {
        if ( ( scon.intval > 2) || (scon.intval < 0 ) )
        {
            return S_badValue;
        }
        if( scon.flags & FLAG_PASS )             /* just checking */
        {
            return 0;
        }
        else                                         /* now do it */
        {
			if (scon.intval != 0){ 
				PS.command_byte = ENABLE_CAPACITY_CONTROL * 100 + (WORD) scon.intval;
			}
			else
			{
				PS.command_byte = DISABLE_SPECIAL_FUNCTIONS * 100;
			}
            return 0;
        }
    }
    else
    {
        if (scon.flags & FLAG_INCR)
        {
            if (scon.objend == op )
            {
                *scon.objend++ = 0;
            }
        }
        if (scon.objend != op + 1 || op[0] != 0)
        {
            return S_NextEntry;
        }
        return (snmp_leaf(S_INT + S_RAM, (WORD)&(PS.specFuncCapacityControl)));
    }
}

specialFunctionsCompensationCharge(op) WORD *op;
{
    if ( ( scon.flags & FLAG_SET ) )                 /* Setting ? */
    {
        if ( ( scon.intval > 24) || (scon.intval < 0 ) )
        {
            return S_badValue;
        }
        if( scon.flags & FLAG_PASS )             /* just checking */
        {
            return 0;
        }
        else                                         /* now do it */
        {
			if (scon.intval != 0){ 
				PS.command_byte = ENABLE_COMPENSATION_CHARGE * 100 + (WORD) scon.intval;
			}
			else
			{
				PS.command_byte = DISABLE_SPECIAL_FUNCTIONS * 100;
			}
            return 0;
        }
    }
    else
    {
        if (scon.flags & FLAG_INCR)
        {
            if (scon.objend == op )
            {
                *scon.objend++ = 0;
            }
        }
        if (scon.objend != op + 1 || op[0] != 0)
        {
            return S_NextEntry;
        }
        return (snmp_leaf(S_INT + S_RAM, (WORD)&(PS.specFuncCompensationCharge)));
    }
}

/* monitoring control variables*/

monitoringLoadControlVariable(op) WORD *op;
{
    if ( ( scon.flags & FLAG_SET ) )                 /* Setting ? */
    {
	    if ( ( scon.intval > 99) || (scon.intval < 0 ) )
        {
            return S_badValue;
        }
	
        if( scon.flags & FLAG_PASS )             /* just checking */
        {
            return 0;
        }
        else                                         /* now do it */
        {
			PS.command_byte = SET_LOAD_CTRL_VAR * 100 + (WORD) scon.intval;
            return 0;
        }
    }
    else
    {
        if (scon.flags & FLAG_INCR)
        {
            if (scon.objend == op )
            {
                *scon.objend++ = 0;
            }
        }
        if (scon.objend != op + 1 || op[0] != 0)
        {
            return S_NextEntry;
        }
        return (snmp_leaf(S_INT + S_RAM, (WORD)&(PS.climateControl.LoadControlVar)));
    }
}

monitoringBatteryControlVariable(op) WORD *op;
{
    if ( ( scon.flags & FLAG_SET ) )                 /* Setting ? */
    {
	    if ( ( scon.intval > 99) || (scon.intval < 0 ) )
        {
            return S_badValue;
        }

        if( scon.flags & FLAG_PASS )             /* just checking */
        {
            return 0;
        }
        else                                         /* now do it */
        {
			PS.command_byte = SET_BATTERY_CTRL_VAR * 100 + (WORD) scon.intval;
            return 0;
        }
    }
    else
    {
        if (scon.flags & FLAG_INCR)
        {
            if (scon.objend == op )
            {
                *scon.objend++ = 0;
            }
        }
        if (scon.objend != op + 1 || op[0] != 0)
        {
            return S_NextEntry;
        }
        return (snmp_leaf(S_INT + S_RAM, (WORD)&(PS.climateControl.BatteryControlVar)));
    }
}



/* UNIQUE IN HISTORY TABLE MIT EINE SET KOMMAND */
sysParamTable(op) WORD *op;
{
    WORD i;
    if ( ( scon.flags & FLAG_SET ) ) {                 
        if (op[-1] != 2) {
            return S_readOnly; // Return read Only if it is not a Value assignment
        } else {
            i = *op;

            if ( ( scon.intval >PS.sysParams[i].MaxValue) || (scon.intval < PS.sysParams[i].MinValue ) ) {
                return S_badValue;
            }
            if ( scon.flags & FLAG_PASS ) {             
                return 0;
            } else {
                
                PS.command_answer = (WORD) scon.intval;
                PS.command_id = PS.sysParams[i].Code; // ID for anything
                PS.command_byte = SET_SETTINGS_PARAMETER * 100 + SET_SPARAM_INT;
                return 0;

            }
        }
    } else {
   // if ((scon.flags & FLAG_SET) && (!(scon.flags & FLAG_PASS))) return S_readOnly;

        if (scon.flags & FLAG_INCR) {    /* if increment */
            if (scon.objend == op) {
                i = *op = 1; scon.objend++;
            } else {
                i = *op + 1;
            }

            *op = i;
        } else {              /* non incremental */
            i = *op;
        }


        scon.objend = op + 1;
        if (PS.sysParamsQuantity != 0) {
            if ( i > PS.sysParamsQuantity) {
                op[-1]++; i=*op=1;
            }
        } else {
            if ( i > 1) {
                op[-1]++; i=*op=1;
            }
            return snmp_leaf(S_INT  + S_RAM, (WORD)&PS.sysParamsQuantity);
        }

        switch (op[-1]) {
        
        case 1:/* Volt */
            snmp_leaf(S_INT  + S_RAM, (WORD)&PS.sysParams[i].Code);
            break;
        case 2:/* Amp */
            snmp_leaf(S_INT  + S_RAM, (WORD)&PS.sysParams[i].Value);
            break;
        case 3:/* Temp */
            snmp_leaf(S_INT + S_RAM, (WORD)&PS.sysParams[i].MinValue);
            break;
        case 4:/* TimeStamp */
            snmp_leaf(S_INT + S_RAM, (WORD)&PS.sysParams[i].MaxValue);
            break;
        default:
            return S_noSuchName;
        }
    return 0;
    }
}
/*************************************************************************************************/
/* Function snmp_acheck                                                                          */
/* Called by kernel or user routine for checking access rights                                   */
/* The IP Address is checked to see if it an approved SNMP Manager, then the Community is checked*/
/*************************************************************************************************/
/* Version 1.00                                                                                  */
/*************************************************************************************************/
/* Parameter:  DWORD *ip        = IP address of calling station                                  */
/*             char  *community = Name of calling community                                      */
/*             WORD  comlen     = Number of characters to check                                  */
/*************************************************************************************************/
/* Returncode:  0 = access OK                                                                    */
/*              1 = no access                                                                    */
/*              2 = read-only access                                                             */
/*************************************************************************************************/
/* History :                                                                                     */
/* 2001-06-26  KK  First test version                                                            */
/* 2002-07-20  JC  Added IP check and Write community                                            */
/*************************************************************************************************/
int snmp_acheck(unsigned char *ip, char *community, WORD comlen)
{
  int i;
  BYTE IPflag=0;     /* flag to indicate that the IP address is one of the defined SNMP managers */


  /***********************************************************************************************/
  /* Check IP address to be one of the defined SNMP managers,                                    */
  /* continue and check SNMP community name otherwise exit with no access                        */
  /***********************************************************************************************/

  IPflag = 0;                                                        /* set IP flag to false     */
  for(i=0 ; i<3; i++) {
    if ( PS.trapadr[i][0] != 0 )
      if ((memcmp( ip, PS.trapadr[i], 4)) == 0) {
        IPflag=1;                                                    /* set IP Flag to true      */
      }
  }
  #if 0
  printf("IP-call:%s, IP-man:%s\r\n",IPaddCall, IPaddMan );
  #endif

  if (IPflag == 0)                                                   /* all tests failed?        */
  {
    return(1);                                                       /* access denied            */
  }

  /***********************************************************************************************/
  /* Check SNMP Community                                                                        */
  /* if community is Write Community - read and write access    - return (0)                     */
  /* if community is Read  Community - read only access         - return (2)                     */
  /* if community not known - no access                         - return (1)                     */
  /* we need to check the write community first, this is because if the read and the write       */
  /* communities have the same name and read is checked first, write requests are blocked as     */
  /* a read only access is returned                                                              */
  /***********************************************************************************************/

  #if 0
  printf("\r\ncommunity: %s,  setup (rd/wt): %s / %s",community ,PS.rd_community, PS.wt_community );
  #endif
  
	return(0);
	/*
  if ( (strncmp(community, PS.wt_community, comlen) == 0) &&         /* is it write ?                 */
	   /*(strlen(PS.wt_community ) == comlen ) )
  /*{
    return(0);                                                  /* read-write access             */
 /* }
  else
  {
    if ( (strncmp(community, PS.rd_community, comlen) == 0) &&       /* is it read ?                  */
	   /*  (strlen(PS.rd_community ) == comlen ) )

    /*{
      return(2);                                                 /* read-only access             */
  /*  }
    else                                                         /* then: not known              */
   /* {
      return(1);                                                  /* access denied               */
   /* }
  }*/
}
