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
public class Jumper_Value extends Integer_Value {


    public Integer_Value number = new Integer_Value(0);
    public Integer_Value status = new Integer_Value(0);
    private String name = new String("Ψλειτ Ή");

    public Jumper_Value(int value) {
        super(value);
    }
    public Jumper_Value(int value, String name) {
        super(value);
        this.name = name;
    }

    public void set_name(String name) {
        this.name = name;
    }

    public String get_name() {
        return name;
    }

}
