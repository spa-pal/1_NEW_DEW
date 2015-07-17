#define DEBUG 0


#define SPA_ENTERPRISE_ID			130, 131, 31
#define TELECORE_ENTERPRISE_ID		130, 167, 60	

#define CURRENT_ENTERPRISE_ID	TELECORE_ENTERPRISE_ID

#define STX 0x02
#define CR  0x0d
#define ACK 0x06
#define NAK 0x15

#define DEVICE_INFO_EEPROM 1

/* read_data() return value */
#define PS_OK           0
#define PS_DATAERROR    -1
#define PS_TIMEOUT      -2

#define PS_MAXALARM	 4	/* Maximal possible alarm number */
#define PS_HIST		10	/* Number of history rows        */
#define STRLEN      69
#define MAX_REQUEST_LENGTH      300
#define MAX_STRLEN          255

typedef struct Hist_table {
    WORD    volt;
    WORD    amp;
    WORD    temp;
    DWORD   tstamp;
} HIST;

typedef struct Main_Circuit {
	WORD Voltage;
	WORD Frequency;
	WORD Status;
	WORD  Alarm;
} MainC;

typedef struct Device_Info {
	WORD Device_Code;
	WORD Serial_Number_LSB;
	WORD Serial_Number_MSB;
	WORD Location_Length;
	BYTE Location[STRLEN];
}  D_Info;
	
	
typedef struct Events {
	WORD sequence_numberEvent;
	WORD Device_Type;
	WORD Device_Number;
	WORD Event_Type;
	WORD Event_Year_Start;
	WORD Event_Month_Start;
	WORD Event_Day_Start;
	WORD Event_Hour_Start;
	WORD Event_Minute_Start;
	WORD Event_Second_Start;
	WORD Event_Year_Finished;
	WORD Event_Month_Finished;
	WORD Event_Day_Finished;
	WORD Event_Hour_Finished;
	WORD Event_Minute_Finished;
	WORD Event_Second_Finished;
	} EventStruct;

typedef struct Load_type {
	WORD Voltage;
	WORD Current;
	WORD Status;
    WORD Automat1State; // 0 - Normal, 1 - Alarm
    WORD Automat2State; // 0 - Normal, 1 - Alarm
    WORD LowVoltage; // 0 - Normal, 1 - Alarm
    WORD HighVoltage; // 0 - Normal, 1 - Alarm
} Load_Var;

typedef struct PSU_type{
	WORD sequence_number;
	WORD Voltage;
	WORD Current;
	WORD Temperature;
	WORD Status;
	WORD Heat_Alarm;
	WORD Low_Voltage;
	WORD High_Voltage;
	WORD Connection_Lost;
	WORD External_Lock;
	WORD Reserved;
} PSU_block;

typedef struct Battery_type{
	WORD sequence_numberBat;
	WORD VoltageBat;
	WORD CurrentBat;
	WORD TemperatureBat;
	WORD CapacityBat;
	WORD ChargeBat;
	WORD StatusBat;
	WORD Is_chargingBat;
	WORD Battery_AlarmBat;
    WORD BatteryAsimmetryAlarm;
    WORD BatteryDeepDischargeAlarm;
} Bat_type;

typedef struct Temperature_type{
	WORD sequence_numberTemp;
	WORD TemperatureTemp;
	WORD StatusTemp;
	WORD OutoforderTemp;
	WORD Temp_alarmTemp;
} temp_type;

typedef struct Logic_Input_type{
	WORD sequence_numberLogic;
	WORD StatusLogic;
	WORD Active;
	WORD Alarm;
} logic_type;

typedef struct EXT_IO_type{
	WORD quantityIO;
	WORD StatusExtIO;
} ext_io_type;

typedef struct ClimateControlType{
    WORD ClimateControlExists;
    WORD BoxTemperature;
    WORD BoxAlarm;
    WORD LoadOffState;
    WORD LoadControlVar;
    WORD BatteryOffState;
    WORD BatteryControlVar;
    WORD FanPositionVar;
    WORD StuffingVar;
} climateControlType;

typedef struct SysParamType{
    WORD Code;
    WORD Value;
    WORD MinValue;
    WORD MaxValue;
    WORD OneMoreStuffing;
} sysParamType;


typedef struct PS_def {
	WORD 	coldstartBit;
    BYTE    trapadr[3][4];
    BYTE    rd_community[14];
    BYTE    wt_community[14];
    WORD    sent_command[MAX_REQUEST_LENGTH];
    WORD    rcvd_command[MAX_REQUEST_LENGTH];
    BYTE    sent_string[MAX_STRLEN];
    BYTE    rcvd_string[MAX_STRLEN];
    WORD    counter_packets_output;
    WORD    counter_packets_input;
    WORD    reply_ack;
    DWORD   PowerReading;
    WORD    VoltageReading;
    WORD    CurrentReading;
    WORD    TempReading;
    DWORD   PowerUpperLimit;
    DWORD   PowerLowerLimit;
    WORD    VoltageUpperLimit;
    WORD    VoltageLowerLimit;
    WORD    TempUpperLimit;
    WORD    TempLowerLimit;
    BYTE    CommandString[STRLEN];
    BYTE    MessageString[STRLEN];
    WORD    alarmPower;
    WORD    alarmVoltage;
    WORD    alarmTemp;
    WORD    alarmSerial;
	WORD 	psus_count;
	WORD 	batteries_count;
	WORD 	temperatures_count;
	WORD 	events_count;
	WORD	logics_count;
	WORD 	invertors_count;
	WORD 	control_byte;
	WORD	special_functions;
	WORD	command_byte;
	WORD  	command_answer;
	WORD	command_id;
	WORD	sparam_type;
	WORD	trap_value;
	WORD	extBoardExistence;
	WORD 	extVoltageInput1;
	WORD 	extVoltageInput2;
	WORD 	extVoltagePES;
	DWORD 	extTotalEnergy;
	WORD 	extCurrentPower;
	WORD	extActiveInput;
	WORD	extFanSpeed;
	WORD	specFuncCapacityControl;
	WORD	specFuncCompensationCharge;
    WORD    debugSetVar;
    WORD    sysParamsQuantity; // Quantity of system parameters. Derived from telemeteria 2
    struct  SysParamType sysParams[50];
    struct  ClimateControlType climateControl;
	struct  EXT_IO_type ext_io;
    struct	Hist_table hist[PS_HIST+1];
	struct 	Main_Circuit mains;
	struct	Load_type load;
	struct	PSU_type psu[10];
	struct 	Battery_type battery[3];
	struct 	Battery_type battery1;
	struct 	Temperature_type temp_sensor[5];
	struct	Logic_Input_type logic_input[5];
	struct 	Events event[65];
	struct 	Device_Info device_info;
} PowerSrc;










