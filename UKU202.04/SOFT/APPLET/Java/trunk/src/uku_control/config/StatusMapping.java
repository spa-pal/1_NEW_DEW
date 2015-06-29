package uku_control.config;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlValue;

/**
 * Created by Anatoly Danilov on 11/22/2014.
 * For the pleasure
 */
@XmlRootElement
public class StatusMapping {
    private int mask;
    private String value;
    private boolean isAlarm;

    @XmlAttribute
    public int getMask() {
        return mask;
    }

    public void setMask(int mask) {
        this.mask = mask;
    }

    @XmlValue
    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    @XmlAttribute(name = "isAlarm")
    public boolean isAlarm() {
        return isAlarm;
    }

    public void setAlarm(boolean isAlarm) {
        this.isAlarm = isAlarm;
    }
}
