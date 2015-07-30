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
public class Special_Parameters {

    public Integer_Value ID = new Integer_Value(0);
    public String_Value screen_name = new String_Value("");
    public String_Value units = new String_Value("");
    public Integer_Value screen_view = new Integer_Value(0);
    public String_Value tooltip = new String_Value("");
    public Integer_Value value = new Integer_Value(1);
    public Integer_Value multiply_factor = new Integer_Value(1);
    public Integer_Value lowest_value = new Integer_Value(0);
    public Integer_Value highest_value = new Integer_Value(0);
    String OID = new String("1.3.6.1.2.1.1.1.0");

    synchronized void setOID(String value){
        OID = value;
    }

    synchronized String getOID(){
        return OID;
    }

    public Special_Parameters() {
    }
    public Special_Parameters(int id, String name, String unit, int value, int view_type, String tooltip, int mult_factor) {
        ID.set(id);
        screen_name.set(name);
        units.set(unit);
        screen_view.set(view_type);
        this.tooltip.set(tooltip);
        multiply_factor.set(mult_factor);
        this.value.set(value);
    }

    public Special_Parameters(int id, String name, String unit, int value, int view_type, String tooltip, int mult_factor, String oid) {
    ID.set(id);
    screen_name.set(name);
    units.set(unit);
    screen_view.set(view_type);
    this.tooltip.set(tooltip);
    multiply_factor.set(mult_factor);
    this.value.set(value);
    OID = oid;
}


    public Special_Parameters(int id, String name, String unit, int value, int view_type, String tooltip, int mult_factor, int lowest, int highest) {
        ID.set(id);
        screen_name.set(name);
        units.set(unit);
        screen_view.set(view_type);
        this.tooltip.set(tooltip);
        multiply_factor.set(mult_factor);
        this.value.set(value);
        lowest_value.set(lowest);
        highest_value.set(highest);
    }

    public Special_Parameters(int id, String name, String unit, int value,
                              int view_type, String tooltip, int mult_factor,
                              int lowest, int highest, String oid) {
        ID.set(id);
        screen_name.set(name);
        units.set(unit);
        screen_view.set(view_type);
        this.tooltip.set(tooltip);
        multiply_factor.set(mult_factor);
        this.value.set(value);
        lowest_value.set(lowest);
        highest_value.set(highest);
        OID = oid;
    }


}
