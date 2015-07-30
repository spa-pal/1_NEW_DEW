package uku_control;

import java.net.URL;
import java.util.Queue;

/**
 * <p>Title: Ultimate monitor</p>
 *
 * <p>Description: universal monitoring system</p>
 *
 * <p>Copyright: Copyright (c) 2008</p>
 *
 * <p>Company: Lantis</p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Data_Big extends Unit_Data {

    public Integer_Value connection_status = new Integer_Value(0);
    public static final int CONNECTION_FAILED = 0;
    public static final int CONNECTION_OK = 1;

    public Integer_Value current_view = new Integer_Value(DETAILS_VIEW);
    public static final int STATUS_VIEW = 0;
    public static final int DETAILS_VIEW = 1;
    public static final int SPARAMS_VIEW = 2;
    public static final int EXTIO_VIEW = 3;

    public Integer_Value batteries_count = new Integer_Value(0);
    public Integer_Value psus_count = new Integer_Value(0);
    public Integer_Value invertors_count = new Integer_Value(0);
    public Integer_Value external_temperature_count = new Integer_Value(0);
    public Integer_Value external_jumper_count = new Integer_Value(0);
    public Integer_Value extio_count = new Integer_Value(0);
    public Integer_Value extio_status = new Integer_Value(0);
    public static Power_Main_Data power_main = new Power_Main_Data();
    public static Load_Data load = new Load_Data();
    public static PSU_Data psus_array[] = new PSU_Data[255];
    public static Battery_Data batteries_array[] = new Battery_Data[255];
   // public static Temperature_Value external_temperature_array[] = new Temperature_Value[255];
    public static Jumper_Value external_jumper_array[] = new Jumper_Value[255];
    public static Integer_Value specfunctions = new Integer_Value(0);
 //   public static ExtIO_Data extio_data_array[] = new ExtIO_Data[10];
    public static UKU_Info_Data info_data = new UKU_Info_Data();
  //  public static ExtBoardData extBoard = new ExtBoardData();

    public Integer_Value control_byte = new Integer_Value(0);

    public static final int TRUE = 1;
    public static final int FALSE = 0;
    public static int psu_count = 3;
    public static boolean psu_count_updated = false;

    public Integer_Value external_status = new Integer_Value(0);
    public Integer_Value need_correct_interface = new Integer_Value(1);
    public Integer_Value need_correct_interface_status = new Integer_Value(1);
    public Integer_Value need_correct_interface_control = new Integer_Value(1);
    public Integer_Value need_correct_alarm_viewer = new Integer_Value(1);
    public Integer_Value need_correct_sparams_panel = new Integer_Value(1);
    public Integer_Value need_update_extio_panel = new Integer_Value(1);
    public Integer_Value need_update_info_panel = new Integer_Value(1);

    public Integer_Value scroll_pane_position = new Integer_Value(0);

    // true == alarm state
    public static final int ALARM = 1;
    public static final int NORMAL = 0;



    public Integer_Value alarm_is_to_be = new Integer_Value(0);
    public Integer_Value alarm_is_shown = new Integer_Value(0);

    public Integer_Value events_quantity = new Integer_Value(0);
    public Alarm_Event events[] = new Alarm_Event[64];

    public Integer_Value show_primary_bpss = new Integer_Value(0);
    public Integer_Value show_parallel_operation = new Integer_Value(1);
    public Integer_Value show_events_journal = new Integer_Value(0);

    public Integer_Value show_warning_table = new Integer_Value(0);
    public Integer_Value show_warning_table_timeout = new Integer_Value(0);

    public Integer_Value command_set_primary_bps = new Integer_Value(0);
    public Integer_Value command_disable_bps = new Integer_Value(0);
    public Integer_Value command_enable_compensation_charge = new Integer_Value(0);
    public Integer_Value command_enable_capacity_control = new Integer_Value(0);
    public Integer_Value command_disable_special_functions = new Integer_Value(0);
    public Integer_Value command_unlock_bpss = new Integer_Value(0);
    public Integer_Value command_enable_parallel_mode = new Integer_Value(0);
    public Integer_Value command_disable_parallel_mode = new Integer_Value(0);

    public Integer_Value command_get_events_number = new Integer_Value(0);
    public Integer_Value command_get_event = new Integer_Value(0);

    public Integer_Value command_byte = new Integer_Value(0);
    public Integer_Value command_id = new Integer_Value(0);
    public Integer_Value command_parameter = new Integer_Value(0);
    public Integer_Value command_answer = new Integer_Value(0);

    public Integer_Value command_need_to_get_all_events = new Integer_Value(0);
    public Integer_Value command_need_to_get_all_sparams = new Integer_Value(0);



    public Integer_Value get_data_period = new Integer_Value(20);
    public Integer_Value margin_red = new Integer_Value(1);

    public Special_Settings special_settings;

    public UKU_LIFO lifo = new UKU_LIFO();

    private UKU_Data_SNMP snmp;

    public String_Value url = new String_Value("");


    public UKU_Data_Big() {
        special_settings = new Special_Settings();

        for (int i = 0; i < 64; i++)
            events[i] = new Alarm_Event();
        for (int i = 0; i < 255; i++){
            this.batteries_array[i] = new Battery_Data();
            batteries_array[i].number.set(i + 1);
            this.psus_array[i] = new PSU_Data();
            psus_array[i].number.set(i + 1);
            this.external_jumper_array[i] = new Jumper_Value(0, " Шлейф № " + (i + 1));
        //    this.external_temperature_array[i] = new Temperature_Value(0, " Внешняя температура № " + (i + 1));
        }
/*
        this.external_temperature_array[0] = new Temperature_Value(0, " Температура внешнего воздуха");
        this.external_temperature_array[1] = new Temperature_Value(0, " Температура отсека ЭПУ");
        this.external_temperature_array[2] = new Temperature_Value(0, " Температура отсека MSAN");
*/
        this.external_jumper_array[0] = new Jumper_Value(0, " Датчик двери");
        this.external_jumper_array[1] = new Jumper_Value(0, " Датчик дыма");
        this.external_jumper_array[2] = new Jumper_Value(0, " Датчик удара");
        this.external_jumper_array[3] = new Jumper_Value(0, " Датчик переворачивания");


     /*   for (int i = 0; i < 10; i++) {
            this.extio_data_array[i] = new ExtIO_Data();
            this.extio_data_array[i].number.set(i + 1);
        }*/
        this.current_view.set(DETAILS_VIEW);
        snmp = new UKU_Data_SNMP(this);

    }

    public void set_psu_count(int number){
        psu_count = number;
        psu_count_updated = true;
    }


    public static void main(String[] args) {
        UKU_Data_Big iceberg_data = new UKU_Data_Big();
    }

    int get_alarm() {
        int tempik = 0;
                if (this.power_main.get_alarm() != 0)  tempik = 1;
                if (this.psus_count.get() > 0) {
                    for (int i = 0; i < this.psus_count.get(); i++) {
                        if (this.psus_array[i].get_alarm() != 0) {
                            tempik = 1;
                        }
                    }
                }
                if (this.batteries_count.get() > 0) {
                    for (int i = 0; i < this.batteries_count.get(); i++) {
                        if (this.batteries_array[i].get_alarm() != 0) {
                            tempik = 1;
                        }
                    }
                }
                if (this.invertors_count.get() > 0) {
                }
                /*if (this.external_temperature_count.get() > 0) {
                    for (int i = 0; i < this.external_temperature_count.get(); i++) {
                        if (this.external_temperature_array[i].get_alarm() != 0) {
                            tempik = 1;
                        }
                    }

                }*/
                if (this.external_jumper_count.get() > 0) {
                    for (int i = 0; i < this.external_jumper_count.get(); i++) {
                        if (this.external_jumper_array[i].get() != 0) {
                            tempik = 1;
                        }
                    }
                }
        return tempik;
    }

    int get_acknowledged() {
        int tempik = this.ACKNOWLEDGED;
        if (((this.power_main.get_alarm() == this.ALARM)) &
            (this.power_main.get_acknowledged() == NOT_ACKNOWLEDGED))
            tempik = this.NOT_ACKNOWLEDGED;
            if (this.psus_count.get() > 0) {
                     for (int i = 0; i < this.psus_count.get(); i++) {
                         if (this.psus_array[i].get_alarm() != 0)
                             if (this.psus_array[i].get_acknowledged() ==
                                 NOT_ACKNOWLEDGED) {
                                 tempik = this.NOT_ACKNOWLEDGED;
                             }
                     }
                 }
                 if (this.batteries_count.get() > 0) {
                     for (int i = 0; i < this.batteries_count.get(); i++) {
                         if (this.batteries_array[i].get_alarm() != 0)
                             if (this.batteries_array[i].get_acknowledged() ==
                                 NOT_ACKNOWLEDGED) {
                                 tempik = NOT_ACKNOWLEDGED;
                             }
                     }
                 }
        return tempik;
    }

   void set_acknowledged(int value) {
        int tempik = 0;
        this.power_main.set_acknowledged(value);
                 if (this.psus_count.get() > 0) {
                     for (int i = 0; i < this.psus_count.get(); i++) {
                            this.psus_array[i].set_acknowledged(value);
                     }
                 }
                 if (this.batteries_count.get() > 0) {
                     for (int i = 0; i < this.batteries_count.get(); i++) {

                            this.batteries_array[i].set_acknowledged(value);

                     }
                 }
    }
}
