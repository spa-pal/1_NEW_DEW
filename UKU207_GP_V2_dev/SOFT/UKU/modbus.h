
extern unsigned char modbus_buf[20];
extern short modbus_crc16;
extern char modbus_timeout_cnt;
extern char bMODBUS_TIMEOUT;
extern unsigned char modbus_rx_buffer[30];	//�����, ���� ���������� ����������� ������� ���������� ���������� �� ������ �����
extern unsigned char modbus_an_buffer[30];	//�����, ���� ��� ����� ���������� ��� �������
extern unsigned char modbus_rx_buffer_ptr;	//��������� �� ������� ������� ������������ ������
extern unsigned char modbus_rx_counter;		//���������� �������� ����, ������������ ��� ������� ����������� ������� � ��� �����������

extern short modbus_plazma;				//�������
extern short modbus_plazma1;				//�������
extern short modbus_plazma2;				//�������
extern short modbus_plazma3;				//�������

//-----------------------------------------------
unsigned short CRC16_2(char* buf, short len);
//-----------------------------------------------
void modbus_registers_transmit(unsigned char adr,unsigned char func,unsigned short reg_adr,unsigned short reg_quantity);
//-----------------------------------------------
void modbus_hold_registers_transmit(unsigned char adr,unsigned char func,unsigned short reg_adr,unsigned short reg_quantity);
//-----------------------------------------------
void modbus_register_transmit(unsigned char adr,unsigned char func,unsigned short reg_adr);
//-----------------------------------------------
void modbus_hold_register_transmit(unsigned char adr,unsigned char func,unsigned short reg_adr);



