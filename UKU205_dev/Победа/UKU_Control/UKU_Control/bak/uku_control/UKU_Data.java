package uku_control;

/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Data {

    public Integer_Value connection_status = new Integer_Value(0);
    public static final int CONNECTION_FAILED = 0;
    public static final int CONNECTION_OK = 1;

    public Integer_Value primary_bps = new Integer_Value(0);
    public static final int PRIMARY_BPS_1 = 0;
    public static final int PRIMARY_BPS_2 = 1;

    public Integer_Value battery_status = new Integer_Value(0);
    public final static int BATTERY_LOST = 0;
    public final static int BATTERY_ENABLED = 1;

    public Integer_Value compensation_charge = new Integer_Value(0);
    public final static int COMPENSATION_ON = 1;
    public final static int COMPENSATION_OFF = 0;

    public Integer_Value capacity_control_status = new Integer_Value(0);
    public final static int CAPACITY_CONTROL_OFF = 0;
    public final static int CAPACITY_CONTROL_ON = 1;

    public Integer_Value voltage_bps_1 = new Integer_Value(0);
    public Integer_Value voltage_bps_2 = new Integer_Value(0);
    public Integer_Value voltage_battery = new Integer_Value(0);
    public Integer_Value voltage_resistor = new Integer_Value(0);

    public Integer_Value current_bps_1 = new Integer_Value(0);
    public Integer_Value current_bps_2 = new Integer_Value(0);
    public Integer_Value current_battery = new Integer_Value(0);

    public Integer_Value temperature_bps_1 = new Integer_Value(0);
    public Integer_Value temperature_bps_2 = new Integer_Value(0);
    public Integer_Value temperature_battery = new Integer_Value(0);

    public Integer_Value voltage_circuit = new Integer_Value(0);
    public Integer_Value frequency_circuit = new Integer_Value(0);

    public Integer_Value battery_capacity = new Integer_Value(0);
    public Integer_Value battery_charge = new Integer_Value(0);

    public Integer_Value safe_delivery = new Integer_Value(0);
    public static final int FAST_DELIVERY = 0;
    public static final int SAFE_DELIVERY = 1;

    public Integer_Value need_to_switch_bps = new Integer_Value(0);
    public Integer_Value need_to_disable_bps = new Integer_Value(0);
    public static final int BPS_1 = 1;
    public static final int BPS_2 = 2;

    public Integer_Value need_to_enable_compensation_charge = new Integer_Value(
            0);
    //int == time to be enabed

    public Integer_Value need_to_enable_capacity_control = new Integer_Value(0);
    public static final int TRUE = 1;

    public Integer_Value need_to_disable_special_function = new Integer_Value(0);

    public Integer_Value external_temperature_count = new Integer_Value(0);
    public Integer_Value external_jumper_count = new Integer_Value(0);

    public Integer_Value external_status = new Integer_Value(0);

    public Integer_Value need_correct_interface = new Integer_Value(0);


    public Temperature_Value external_temperature_1 = new Temperature_Value(0,
            "Внешняя температура № 1");
    public Temperature_Value external_temperature_2 = new Temperature_Value(0,
            "Внешняя температура № 2");
    public Temperature_Value external_temperature_3 = new Temperature_Value(0,
            "Внешняя температура № 3");
    public Temperature_Value external_temperature_array[] = new
            Temperature_Value[3];

    // true == alarm state
    public static final int ALARM = 1;
    public static final int NORMAL = 0;

    public Jumper_Value external_jumper_1 = new Jumper_Value(NORMAL,
            "Шлейф № 1");
    public Jumper_Value external_jumper_2 = new Jumper_Value(NORMAL,
            "Шлейф № 2");
    public Jumper_Value external_jumper_3 = new Jumper_Value(NORMAL,
            "Шлейф № 3");
    public Jumper_Value external_jumper_4 = new Jumper_Value(NORMAL,
            "Шлейф № 4");
    public Jumper_Value external_jumper_array[] = new Jumper_Value[4];

    public Integer_Value alarm_is_to_be = new Integer_Value(0);
    public Integer_Value alarm_is_shown = new Integer_Value(0);

    public Integer_Value events_quantity = new Integer_Value(0);
    public Alarm_Event events[] = new Alarm_Event[64];

    public UKU_Data() {

        for (int i = 0; i < 64; i++) {
            events[i] = new Alarm_Event();
        }

    }


}

