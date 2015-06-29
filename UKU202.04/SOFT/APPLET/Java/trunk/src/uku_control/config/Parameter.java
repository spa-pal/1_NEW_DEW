package uku_control.config;

import uku_control.Type;
import uku_control.Util;

import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 */
@XmlRootElement
public class Parameter<T> implements Comparable<Parameter> {

    private String name;
    private String oid;
    private Type type;
    private T value;

    private String key;
    private double multiplier = 1.0;
    private List<StatusMapping> statusMappings = new ArrayList<StatusMapping>();

    private List<ChangeListener> changeListeners = new ArrayList<ChangeListener>();


    public String getOid() {
        return oid;
    }

    @XmlAttribute
    public void setOid(String oid) {
        this.oid = oid;
    }

    public Type getType() {
        return type;
    }

    @XmlAttribute
    public void setType(Type type) {
        this.type = type;
    }

    public T getValue() {
        return value;
    }

    @XmlElement
    public void setValue(T value) {
        if (Util.isSame(this.value, value))
            return;

        this.value = value;

        for (ChangeListener listener : changeListeners)
            listener.stateChanged(new ChangeEvent(this));

    }

    public String getName() {
        return name;
    }

    @XmlAttribute
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Parameter{" +
                "name='" + name + '\'' +
                ", oid='" + oid + '\'' +
                ", type=" + type +
                ", value=" + value +
                ", key='" + getKey() + '\'' +
                '}';
    }

    public String getKey() {
        return key;
    }

    @XmlAttribute
    public void setKey(String key) {
        this.key = key;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Parameter parameter = (Parameter) o;

        if (!oid.equals(parameter.oid)) return false;
        if (type != parameter.type) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = oid.hashCode();
        result = 31 * result + type.hashCode();
        return result;
    }

    @Override
    public int compareTo(Parameter o) {
        return oid.compareTo(o.oid);
    }

    public String getTextValue() {
        if (value == null)
            return "N/A";
        switch (type) {
            case OCTET_STRING:
                return (String) value;
            case INTEGER:
                return String.valueOf(value);
            case DOUBLE:
                double roundedValue = Math.round(((Integer) this.value) * getMultiplier() * 10000) / 10000.0;

                return String.valueOf(roundedValue);
            case STATUS:
                Integer statusBit = (Integer) value;
                for (StatusMapping statusMapping : statusMappings) {
                    if (statusMapping.getMask() == statusBit || (statusBit & statusMapping.getMask()) != 0)
                        return statusMapping.getValue();
                }
                return "Не опознан " + value;
            default:
                return String.valueOf(this.value);
        }

    }

    public double getMultiplier() {
        return multiplier;
    }

    @XmlAttribute
    public void setMultiplier(double multiplier) {
        this.multiplier = multiplier;
    }

    public void addChangeListener(ChangeListener changeListener) {
        changeListeners.add(changeListener);
    }

    public List<ChangeListener> getChangeListeners() {
        return changeListeners;
    }

    public void addChangeListeners(List<ChangeListener> changeListeners) {
        this.changeListeners.addAll(changeListeners);
    }

    @XmlElement(name = "status")
    public List<StatusMapping> getStatusMappings() {
        return statusMappings;
    }

    public void setStatusMappings(List<StatusMapping> statusMappings) {
        this.statusMappings = statusMappings;
    }

    public boolean isAlarmStatus() {
        if (value == null)
            return true;

        Integer statusBit = (Integer) value;
        for (StatusMapping statusMapping : statusMappings)
            if (statusMapping.getMask() == statusBit || (statusBit & statusMapping.getMask()) != 0)
                return statusMapping.isAlarm();

        //not found mapping is alarm
        return true;
    }
}
