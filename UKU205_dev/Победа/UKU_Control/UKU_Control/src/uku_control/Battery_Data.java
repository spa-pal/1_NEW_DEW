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
public class Battery_Data extends Unit_Data{

    public Integer_Value number = new Integer_Value(0);
    public Integer_Value_0_1 voltage = new Integer_Value_0_1(0);
    public Integer_Value_0_01 current = new Integer_Value_0_01(0);
    public Integer_Value temperature = new Integer_Value(0);
    public Integer_Value status = new Integer_Value(0);
    public Integer_Value_0_1 capacity = new Integer_Value_0_1(0);
    public Integer_Value charge = new Integer_Value(0);
    public Alarm_State alarm_state = new Alarm_State();

    public Battery_Data() {
    }
    public int get_alarm() {
        if (alarm_state.get_alarm() != (status.get() & 0x01)){
            alarm_state.set_alarm((status.get() & 0x01));
            alarm_state.set_acknowledge(this.NOT_ACKNOWLEDGED);
        }
        return ((alarm_state.get_alarm()));
    }
    public int get_as_alarm() {
    if (alarm_state.get_alarm() != (status.get() & 0x01)){
        alarm_state.set_alarm((status.get() & 0x01));
        alarm_state.set_acknowledge(this.NOT_ACKNOWLEDGED);
    }
    return ((alarm_state.get_alarm()));
}

    public String get_status() {
           String tempik = new String();
           int statusik = status.get();

           if ((statusik & 0x01) == 1)
               tempik = " Авария";
           else {
               statusik = statusik >> 1;
               if ((statusik & 0x01) == 1)
                   tempik = " Заряд";
               else tempik = " Разряд";
           }


           return tempik;
    }

    public String get_charge(){
        String tempik = new String();
        if (this.charge.get() == 255)
            return " не измер.";
        else return this.charge.get_textual();
    }

    int get_acknowledged() {
        return alarm_state.get_acknowledge();
    }

    void set_acknowledged(int value) {
        alarm_state.set_acknowledge(value);
    }

}
