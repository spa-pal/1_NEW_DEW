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
/*****************************************************************************/

#pragma inline
void m_wc() {
	asm public data_priv_mib
		asm data_priv_mib:
		asm dw 1, 7777
		asm dw S_LEER, 7776
		asm dw S_SEQU, Magic7Root

		asm Magic7Root:
		asm dw 1, 1
		asm dw S_SEQU, Magic7Products

		asm Magic7Products:
		asm dw 1, 2
		asm dw S_LEER, 1
		asm dw S_SEQU, Magic7PSMIB

		asm Magic7PSMIB:
		asm dw 1, 4
		asm dw S_SEQU, Readings
		asm dw S_SEQU, Settings
		asm dw S_SEQU, Traps
		asm dw S_SEQU, Tables

		asm Readings:
		asm dw 1, 5
		asm dw S_INT+ S_LONG + S_RAM	, PS.PowerReading
		asm dw S_INT+ S_RAM		, PS.mains.Voltage
		asm dw S_INT+ S_RAM		, PS.CurrentReading
		asm dw S_INT+ S_RAM		, PS.TempReading
		asm dw S_INT+ S_RAM		, PS.VoltageReading

		asm Settings:
		asm dw 1, 7
		asm dw S_INT + S_LONG + S_RAM + S_SET   , PS.PowerUpperLimit
		asm dw S_INT + S_LONG + S_RAM + S_SET   , PS.PowerLowerLimit
		asm dw S_INT + S_RAM + S_SET			, PS.VoltageUpperLimit
		asm dw S_AFUN                           , _voltage_Lower
		asm dw S_INT + S_RAM + S_SET            , PS.TempUpperLimit
		asm dw S_INT + S_RAM + S_SET            , PS.TempLowerLimit
		asm dw S_AFUN                           , _send_command

		asm Traps:
		asm dw 1, 5
		asm dw S_OCTSTR	+ S_RAM + S_SET	, PS.MessageString
		asm dw S_INT 	+ S_RAM		, PS.alarmPower
		asm dw S_INT 	+ S_RAM		, PS.alarmVoltage
		asm dw S_INT 	+ S_RAM		, PS.alarmTemp
		asm dw S_INT 	+ S_RAM		, PS.alarmSerial

		asm Tables:
		asm dw 1, 1
		asm dw S_SEQU,	historyTable

		asm historyTable:
		asm dw 0, 1
		asm dw S_SEQU, historyEntry

		asm historyEntry:
		asm dw 2, 4
		asm dw S_AFUN, _history_table
}
