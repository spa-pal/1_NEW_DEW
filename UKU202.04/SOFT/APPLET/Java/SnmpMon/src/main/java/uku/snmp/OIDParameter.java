package uku.snmp;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Kriahtunchik on 2/8/14.
 */
public class OIDParameter {

    private String oid;
    private OidType oidType;

    private String displayName;
    private int decimalPlaces;
    private String units;
    private Object value;

    List<OIDParameterChangeListener> changeListeners = new ArrayList<>();
    private boolean noConnection;

    public void addChangeListeners(OIDParameterChangeListener listener) {
        changeListeners.add(listener);
    }

    public String getOid() {
        return oid;
    }

    public void setOid(String oid) {
        this.oid = oid;
    }

    public OidType getOidType() {
        return oidType;
    }

    public void setOidType(OidType oidType) {
        this.oidType = oidType;
    }

    public String getDisplayName() {
        return noConnection ? "Нет связи - " + displayName : displayName;
    }

    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    public int getDecimalPlaces() {
        return decimalPlaces;
    }

    public void setDecimalPlaces(int decimalPlaces) {
        this.decimalPlaces = decimalPlaces;
    }

    public String getUnits() {
        return units;
    }

    public void setUnits(String units) {
        this.units = units;
    }

    public void setValue(Object value) {
        noConnection = false;
        if (value == null && this.value == null || value != null && value.equals(this.value))
            return;

        this.value = value;
        for (OIDParameterChangeListener changeListener : changeListeners) {
            changeListener.onValueChanged(value);
        }
    }

    public Object getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "OIDParameter{" +
                "oid='" + oid + '\'' +
                ", oidType=" + oidType +
                ", displayName='" + displayName + '\'' +
                ", decimalPlaces=" + decimalPlaces +
                ", units='" + units + '\'' +
                ", value=" + value +
                '}';
    }

    public void setNoConnection() {
        noConnection = true;
        for (OIDParameterChangeListener changeListener : changeListeners) {
            changeListener.onValueChanged(null);
        }
    }

    public String getFormattedValue() {
        if (value == null)
            return null;

        Integer intValue = Integer.valueOf(value.toString());
        if (decimalPlaces == 0)
            return intValue + " " + units;

        return  intValue / Math.pow(10, decimalPlaces) + " " + units;
    }
}
