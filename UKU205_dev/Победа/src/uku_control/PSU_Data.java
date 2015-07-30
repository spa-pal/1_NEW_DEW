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
public class PSU_Data extends Unit_Data{

    public Integer_Value number = new Integer_Value(0);
    public Integer_Value_0_1 voltage = new Integer_Value_0_1(0);
    public Integer_Value_0_1 current = new Integer_Value_0_1(0);
    public Integer_Value temperature = new Integer_Value(0);
    public Integer_Value status = new Integer_Value(0);
    public Alarm_State alarm_state = new Alarm_State();

    public PSU_Data() {
        alarm_state.set_alarm(0);
        alarm_state.set_acknowledge(0);
        alarm_state.alarm_type.set(0);
    }

    public int get_alarm(){
        if ( alarm_state.alarm_type.get() != (status.get()&0x1E)){
            alarm_state.alarm_type.set(status.get()&0x1E);
            alarm_state.set_alarm(((status.get()&0x1E) != 0)? 1:0);
            alarm_state.set_acknowledge(0);
        }

        return alarm_state.get_alarm();
    }

    public String get_status() {
        String tempik = new String();
        int statusik = status.get();

        if ((statusik & 0x01) == 1)
            tempik = " Активен";
        else {
            statusik = statusik >> 1;
            if ((statusik & 0x01) == 1)
                tempik = " Перегрев";
            else {
                statusik = statusik >> 1;
                if ((statusik & 0x01) == 1)
                    tempik = " Занижено Uвых";
                else {
                    statusik = statusik >> 1;
                    if ((statusik & 0x01) == 1)
                        tempik = " Завышено Uвых";
                    else {
                        statusik = statusik >> 1;
                        if ((statusik & 0x01) == 1)
                            tempik = " Разрыв связи";
                        else {
                            statusik = statusik >> 1;
                            if ((statusik & 0x01) == 1)
                                tempik = " Заблокирован";
                            else {
                                    tempik = " В резерве";
                            }

                        }

                    }
                }

            }
        }


        return tempik;
    }

    public static void main(String[] args) {
        PSU_Data psu_data = new PSU_Data();
    }

    int get_acknowledged() {
        return this.alarm_state.get_acknowledge();
    }

    void set_acknowledged(int value) {
        this.alarm_state.set_acknowledge(value);
    }
}
