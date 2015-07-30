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
public class ExtBoardData  extends Unit_Data{

    public static final int EXTENSION_BOARD_EXISTS = 10;

    public Integer_Value boardExists = new Integer_Value(0);

    public Integer_Value voltageInput1 = new Integer_Value(0);
    public Integer_Value voltageInput2 = new Integer_Value(0);
    public Integer_Value voltagePES = new Integer_Value(0);

    public Integer_Value_0_01 totalPower = new Integer_Value_0_01(0);
    public Integer_Value currentPower = new Integer_Value(0);
    public Integer_Value fanSpeed = new Integer_Value(0);
    public Integer_Value activeInput = new Integer_Value(0);



    public ExtBoardData() {
    }

    int get_alarm() {
        return 0;
    }

    int get_acknowledged() {
        return 0;
    }

    void set_acknowledged(int value) {
    }
}
