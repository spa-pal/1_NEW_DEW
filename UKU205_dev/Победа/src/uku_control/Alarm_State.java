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
public class Alarm_State {

    public int acknowledge = 0;
    public int alarm = 0;
    public Integer_Value alarm_type = new Integer_Value(0);

    public Alarm_State() {
    }

    public synchronized void set_alarm(int value) {
        alarm = value;
    }

    public synchronized int get_alarm() {
        return alarm;
    }


    public synchronized void set_acknowledge(int value) {
        acknowledge = value;
    }

    public synchronized int get_acknowledge() {
        return acknowledge;
    }


}
