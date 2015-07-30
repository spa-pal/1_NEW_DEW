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
public class Temperature_Value extends Integer_Value {

    public Integer_Value number = new Integer_Value(0);
    public Integer_Value status = new Integer_Value(0);

    private String name = new String("Внешняя температура");
    private int alarm = 0;

    public Temperature_Value(int value) {
        super(value);
    }

    public Temperature_Value(int value, String name) {
        super(value);
        this.name = name;

    }


    public synchronized void set_alarm(int alarm) {
        this.alarm = alarm;
    }

    public synchronized int get_alarm() {
        return ((status.get() & 0x03) != 0)?1:0;//2do
    }

    public void set_name(String name) {
        this.name = name;
    }

    public String get_name() {
        return name;
    }

}
