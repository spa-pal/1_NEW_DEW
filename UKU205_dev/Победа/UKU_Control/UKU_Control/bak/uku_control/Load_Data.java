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
public class Load_Data extends Unit_Data {

    public Integer_Value_0_1 voltage = new Integer_Value_0_1(0);
    public Integer_Value_0_1 current = new Integer_Value_0_1(0);

    public Load_Data() {
    }

    int get_alarm() {
        return 0;
    }

    int get_acknowledged() {
        return this.ACKNOWLEDGED;
    }


    void set_acknowledged(int value) {
    }


}
