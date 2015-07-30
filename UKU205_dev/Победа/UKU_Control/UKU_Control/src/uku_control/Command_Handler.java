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
public class Command_Handler {

    public static final int  GET_TELEMETERIA  = 1;
    public static final int  SET_ACTIVE_BPS  = 2;
    public static final int  ENABLE_COMPENSATION_CHARGE  = 3;
    public static final int  ENABLE_CAPACITY_CONTROL  = 4;
    public static final int  DISABLE_BPS =  5;
    public static final int  CHECK_CONNECTION = 6;
    public static final int  DISABLE_SPECIAL_FUNCTIONS = 7;
    public static final int  UNLOCK_BPSS =   8;
    public static final int  ENABLE_PARRALEL_OPERATION = 9;
    public static final int  DISABLE_PARRALEL_OPERATION = 10;
    public static final int  RESET_ALL_ALARMS = 11;
    public static final int  GET_EVENTS_QUANTITY = 12;
    public static final int  GET_EVENT = 13;
    public static final int  GET_SETTINGS_TABLE = 30;
    public static final int  SEND_COMMAND_1_BYTE = 21;
    public static final int  SEND_COMMAND_2_BYTES =  22;
    public static final int  SEND_COMMAND_3_BYTES = 23;
    public static final int  SEND_COMMAND_4_BYTES = 24;
    public static final int  SET_EXTERNAL_IO = 37;
    public static final int  COMMAND_OK =  0x5555;
    public static final int  COMMAND_INVALID = 0xEEEE;
    public static final int  WRONG_PARAMETER = 0xEEEF;
    public static final int  COMMAND_FAILED = 0xAAAA;
    public static final int  COMMAND_TIMEOUT = 55;

    /*   Special Settings Commands  */
    public static final int  GET_SPECIAL_SETTINGS_SET = 0x1E;
    public static final int  GET_SPECIAL_PARAMETER = 0x1F;
    public static final int  SET_SPECIAL_PARAMETER = 0x20;

    public static final int SET_SPARAM_INT = 1;
    public static final int SET_SPARAM_INCREMENT = 2;
    public static final int SET_SPARAM_DECREMENT = 3;

    /*   Device Information Get Command   */
    public static final int  GET_DEVICE_INFO = 0x21;

    public Command_Handler() {
    }

}
