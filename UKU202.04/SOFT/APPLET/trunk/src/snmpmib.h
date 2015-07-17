/*****************************************************************************/
/* Module Private MIB                                                        */
/* Description of a private mib                                              */
/* Changes in this are should only be made if you are definitely sure about  */
/* what you do. If you add another Field under one label, you have to        */
/* increase the number of fields for this label in the "dw 1,n"-statement    */
/* for this label.                                                           */
/* The following Type-descriptors exist:                                     */
/* S_SEQU  : Sequence, directs to another label                              */
/* S_LEER  : empty fields                                                    */
/* S_RAM   : field is stored in RAM                                          */
/* S_ROM   : field is stored in ROM                                          */
/* S_SET   : field is changable                                              */
/* S_OCTSTR: field is a 0-terminated string                                  */
/* S_INT   : field is an integer-value                                       */
/* S_LONG  : field is a long-value                                           */
/* S_TIPADR: field is an IP-address                                          */
/* S_TCTR  : field is a counter                                              */
/* S_TGAUGE: field is a gauge                                                */
/* S_TTICK : field is a timer                                                */
/* S_AFUN  : field will be handled by following function (put '_' in front)  */
/*****************************************************************************/
/* Version 1.00                                                              */
/*****************************************************************************/
/*****************************************************************************/
/* History :                                                                 */
/* 2002-08-02  ported to CPK450, added S_SET                                 */
/* 2012-02-16  made new Automat1State and 2 states                           */
/*****************************************************************************/

#pragma inline
void m_wc() {
	asm public data_priv_mib
		asm data_priv_mib:
		asm dw 1, 37820
		asm dw S_LEER, 37819
		asm dw S_SEQU, Magic7Root

		asm Magic7Root:
		asm dw 1, 1
		asm dw S_SEQU, Magic7Products

		asm Magic7Products:
		asm dw 1, 2
		asm dw S_LEER, 1
		asm dw S_SEQU, Magic7PSMIB

		asm Magic7PSMIB:
		asm dw 1, 15
		asm dw S_SEQU, displayMains
		asm dw S_SEQU, displayLoad
		asm dw S_SEQU, displayPSU
		asm dw S_SEQU, displayBatTable
		asm dw S_SEQU, displayTempTable
		asm dw S_SEQU, displayLogicTable
		asm dw S_SEQU, displaySpecial
		asm dw S_SEQU, commands
		asm dw S_SEQU, displayEventsTable
		asm dw S_SEQU, displayExtIO
		asm dw S_SEQU, displayDeviceInfo
        asm dw S_SEQU, displayDebugInfo
		asm dw S_SEQU, displayExtensionBoard
        asm dw S_SEQU, displayClimateControl
        asm dw S_SEQU, systemParameters

		asm displayMains:
		asm dw 1, 4
		asm dw S_INT+ S_RAM		, PS.mains.Voltage
		asm dw S_INT+ S_RAM		, PS.mains.Frequency
		asm dw S_INT+ S_RAM		, PS.mains.Status
		asm dw S_INT+ S_RAM		, PS.mains.Alarm

		asm displayLoad:
		asm dw 1, 6
		asm dw S_INT+ S_RAM		, PS.load.Voltage
		asm dw S_INT+ S_RAM		, PS.load.Current
        asm dw S_INT+ S_RAM     , PS.load.Automat1State
        asm dw S_INT+ S_RAM     , PS.load.Automat2State
        asm dw S_INT+ S_RAM     , PS.load.LowVoltage
        asm dw S_INT+ S_RAM     , PS.load.HighVoltage

		asm displayPSU:	
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.psus_count
		asm dw S_SEQU				, psu_table 
		
		asm psu_table:
		asm dw 0, 1
		asm dw S_SEQU, psu_table_entry
	
		asm psu_table_entry:
		asm dw 2, 13
		asm dw S_AFUN, _psus_table
		
		asm displayBatTable:	
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.batteries_count
		asm dw S_SEQU				, batteries_table
		
		asm batteries_table:
		asm dw 0, 1
		asm dw S_SEQU, batteries_entry
		
		asm batteries_entry:
		asm dw 2, 11
		asm dw S_AFUN, _batt_table
		
		asm displayTempTable:
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.temperatures_count
		asm dw S_SEQU				, sensores_table
		
		asm sensores_table:
		asm dw 0, 1
		asm dw S_SEQU, sensors_entry
		
		asm sensors_entry:
		asm dw 2, 5
		asm dw S_AFUN, _sensors_table
		
		asm displayLogicTable:
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.logics_count
		asm dw S_SEQU				, logics_table
		
		asm logics_table:
		asm dw 0, 1
		asm dw S_SEQU, logics_entry
		
		asm logics_entry:
		asm dw 2, 4
		asm dw S_AFUN, _logic_table
		
		asm displaySpecial:
		asm dw 1, 7
		asm dw S_INT+ S_RAM			, PS.control_byte
		asm dw S_INT+ S_RAM			, PS.special_functions
		asm dw S_INT+ S_RAM			, PS.sparam_type
		asm dw S_OCTSTR	+ S_RAM		, PS.MessageString
		asm dw S_INT+ S_RAM			, PS.trap_value
		asm dw S_AFUN				, _specialFunctionsCapacityControl
		asm dw S_AFUN				, _specialFunctionsCompensationCharge

		
		asm commands:
		asm dw 1, 3
		asm dw S_INT+ S_SET+ S_RAM  , PS.command_byte
		asm dw S_INT+ S_SET+ S_RAM  , PS.command_answer
		asm dw S_INT+ S_SET+ S_RAM  , PS.command_id
		
		asm displayEventsTable:
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.events_count
		asm dw S_SEQU				, eventy_table
		
		asm eventy_table:
		asm dw 0, 1
		asm dw S_SEQU, events_entry
		
		asm events_entry:
		asm dw 2, 16
		asm dw S_AFUN, _events_table
		
		
		asm displayExtIO:
		asm dw 1, 2
		asm dw S_INT+ S_RAM			, PS.ext_io.quantityIO
		asm dw S_INT+ S_RAM			, PS.ext_io.StatusExtIO
		
		asm displayDeviceInfo:
		asm dw 1, 4
		asm dw S_INT+ S_RAM			, PS.device_info.Device_Code
		asm dw S_INT+ S_RAM			, PS.device_info.Serial_Number_LSB
		asm dw S_INT+ S_RAM			, PS.device_info.Serial_Number_MSB
		asm dw S_OCTSTR	+ S_RAM 	, PS.device_info.Location

        asm displayDebugInfo:
        asm dw 1, 6
        asm dw S_INT+ S_RAM + S_SET , PS.reply_ack
        asm dw S_OCTSTR + S_RAM     , PS.sent_string
        asm dw S_OCTSTR + S_RAM     , PS.rcvd_string
        asm dw S_INT + S_RAM        , PS.counter_packets_output
        asm dw S_INT + S_RAM        , PS.counter_packets_input
        asm dw S_INT + S_RAM + S_SET, PS.debugSetVar
		
		asm displayExtensionBoard:
		asm dw 1, 8
		asm dw S_INT+ S_RAM			, PS.extBoardExistence
		asm dw S_INT+ S_RAM			, PS.extVoltageInput1
		asm dw S_INT+ S_RAM			, PS.extVoltageInput2
		asm dw S_INT+ S_RAM			, PS.extVoltagePES
		asm dw S_INT+ S_RAM + S_LONG, PS.extTotalEnergy
		asm dw S_INT+ S_RAM			, PS.extCurrentPower
		asm dw S_INT+ S_RAM			, PS.extActiveInput
		asm dw S_AFUN				, _funcExtFanSpeed
		
		asm displayClimateControl:
        asm dw 1, 8
        asm dw S_INT+ S_RAM         , PS.climateControl.ClimateControlExists
        asm dw S_INT+ S_RAM         , PS.climateControl.BoxTemperature
        asm dw S_INT+ S_RAM         , PS.climateControl.BoxAlarm
        asm dw S_INT+ S_RAM         , PS.climateControl.LoadOffState
        asm dw S_AFUN               , _monitoringLoadControlVariable
        asm dw S_INT+ S_RAM         , PS.climateControl.BatteryOffState
        asm dw S_AFUN               , _monitoringBatteryControlVariable
        asm dw S_INT+ S_RAM         , PS.climateControl.FanPositionVar

        asm systemParameters:
        asm dw 1, 2
        asm dw S_INT+ S_RAM         , PS.sysParamsQuantity
        asm dw S_SEQU               , systemParametersTable1

        asm systemParametersTable1:
		asm dw 0, 1
		asm dw S_SEQU               , systemParametersTable

        asm systemParametersTable:
        asm dw 2, 4
        asm dw S_AFUN               , _sysParamTable

/*
        asm dw S_SEQU               , debuggg_table
                                                   
                                                   
        asm debuggg_table:                         
        asm dw 0, 1                                
        asm dw S_SEQU, debug_entry                 
                                                   
        asm debug_entry:                           
        asm dw 2, 2                                
        asm dw S_AFUN,  _debug_table               
*/
                                    

		
}
