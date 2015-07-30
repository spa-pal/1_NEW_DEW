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
public class ExtIO_Data extends Unit_Data {

    public static final int ON = 1;
    public static final int OFF = 0;
    public Integer_Value io_status = new Integer_Value(0);
    public Integer_Value state_to_switch = new Integer_Value(0);
    public Integer_Value number = new Integer_Value(0);

    public ExtIO_Data() {
    }

    int get_alarm() {
        return 0;
    }

    String get_on_off_status_string(){
        return (io_status.get() == ON)? new String(" Активно"):new String(" Неактивно");
    }

    int get_acknowledged() {
        return this.ACKNOWLEDGED;
    }


    void set_acknowledged(int value) {
    }


}
