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
abstract public class Unit_Data {

    public static final int HAS_AN_ALARM = 1;
    public static final int NO_ALARM = 0;

    public static final int ACKNOWLEDGED = 1;
    public static final int NOT_ACKNOWLEDGED = 0;

    public Unit_Data() {
    }

    abstract int get_alarm();
    abstract int get_acknowledged();
    abstract void set_acknowledged(int value);

}
