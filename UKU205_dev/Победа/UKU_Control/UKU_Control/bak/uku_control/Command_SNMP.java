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
public class Command_SNMP {

    public int command_name = 0;
    public int attached_parameter = 0;
    public int attached_parameter_2 = 0;
    public int attached_parameter_3 = 0;

    public int make() {
        return (command_name * 100 + attached_parameter);
    }
    
    public Command_SNMP() {
    }

    public Command_SNMP(int a) {
        command_name = (a);
    }

    public Command_SNMP(int a, int b) {
        command_name = (a);
        attached_parameter = (b);
    }

    public Command_SNMP(int a, int b, int c) {
        command_name = (a);
        attached_parameter = (b);
        attached_parameter_2 = (c);
    }

    public Command_SNMP(int a, int b, int c, int d) {
        command_name = (a);
        attached_parameter = (b);
        attached_parameter_2 = (c);
        attached_parameter_3 = (d);
    }

    public int get_attached_parameter() {
        return attached_parameter;
    }

    public int get_attached_parameter_2() {
        return attached_parameter_2;
    }

    public int get_attached_parameter_3() {
        return attached_parameter_3;
    }

}
