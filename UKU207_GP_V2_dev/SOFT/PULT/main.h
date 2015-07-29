typedef enum {tsOFF=0,tsU=1,tsI=2} enum_tmblr_state;
extern enum_tmblr_state tmblr_state;
typedef enum {bsOFF,bsON} enum_but_state;
extern enum_but_state but_state;


//Телеметрия и телеуправление
extern signed short out_U, out_I, out_I_;
extern signed short ust_I, ust_I_;
extern signed short ust_Iloc, ust_I_loc;
typedef enum {wmI,wmI_} enum_wrk_mode;
extern enum_wrk_mode wrk_mode;

//Время
extern unsigned short time;
extern unsigned short time_set;
//unsigned short ust_time;

//Индикация
extern short ind_U;
extern short ind_I;
extern short ind_U_set;
extern short ind_I_set;

//Управление процессом
typedef enum {wsOFF,wsGS,wsPS} enum_work_stat;
extern enum_work_stat work_stat;

void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7);


