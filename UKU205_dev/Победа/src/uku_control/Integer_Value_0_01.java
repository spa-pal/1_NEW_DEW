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
public class Integer_Value_0_01 extends Integer_Value {
    public Integer_Value_0_01(int value) {
        super(value);
    }

    synchronized String get_textual(){
        return Double.toString(value / 100.0);
    }
}
