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
 * @author Danilov
 * @version 1.0
 */
public class Commands {

    public static final byte NET_ADDRESS_SENDER = 0x00;
    public static final byte NET_ADDRESS_RECEIVER = 0x00;

    private byte[] telemeteria = {
                                 (byte) 0x55,
                                 (byte) 0x61,
                                 NET_ADDRESS_SENDER,
                                 this.NET_ADDRESS_RECEIVER,

    };

}
