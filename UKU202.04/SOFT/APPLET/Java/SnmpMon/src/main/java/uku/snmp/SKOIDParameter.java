package uku.snmp;

/**
 * Created by Anatoly Danilov on 2/9/14.
 */
public class SKOIDParameter extends OIDParameter {

    private String case0;
    private String case1;
    private String defaultValue = "Не ясно:";

    @Override
    public String getFormattedValue() {

        Object value = getValue();
        if (value == null)
            return "";

        Integer valueAsInt = Integer.valueOf(value.toString());
        switch (valueAsInt){
            case 1:
                setCase1("Замкнут");
                return case1;
            case 0:
                return case0;
            default:
                return defaultValue + valueAsInt;
        }

    }

    public void setCase0(String case0) {
        this.case0 = case0;
    }

    public void setCase1(String case1) {
        this.case1 = case1;
    }

    public void setDefaultValue(String defaultValue) {
        this.defaultValue = defaultValue;
    }
}
