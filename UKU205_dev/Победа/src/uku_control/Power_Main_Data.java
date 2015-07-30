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
 * @author not attributable
 * @version 1.0
 */
public class Power_Main_Data extends Unit_Data{

    public Integer_Value voltage = new Integer_Value(0);
    public Integer_Value_0_1 frequency = new Integer_Value_0_1(0);
    public Integer_Value status = new Integer_Value(0);
    public Alarm_State alarm_state = new Alarm_State();

    public Power_Main_Data() {
        alarm_state.set_acknowledge(0);
        alarm_state.set_alarm(0);
    }
    public int get_alarm(){
        if (alarm_state.get_alarm() != (status.get() & 0x01)){
            alarm_state.set_alarm(status.get() & 0x01);
            alarm_state.set_acknowledge(0);
        }
        return alarm_state.get_alarm();
    }

    int get_acknowledged() {
        return this.alarm_state.get_acknowledge();
    }

    void set_acknowledged(int value) {
        this.alarm_state.set_acknowledge(value);
    }

}
