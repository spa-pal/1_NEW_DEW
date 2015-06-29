package uku_control.config;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/23/2014.
 * For the pleasure
 */
@XmlRootElement
public class Settings {
    private List<SettingParameter> parameters = new ArrayList<SettingParameter>();

    private PowerSupplyUnit psu;
    private Battery battery;


    @XmlElement(name = "parameter")
    public List<SettingParameter> getParameters() {
        return parameters;
    }

    public void setParameters(List<SettingParameter> parameters) {
        this.parameters = parameters;
    }

    @XmlElement
    public PowerSupplyUnit getPsu() {
        return psu;
    }

    public void setPsu(PowerSupplyUnit psu) {
        this.psu = psu;
    }

    @XmlElement
    public Battery getBattery() {
        return battery;
    }

    public void setBattery(Battery battery) {
        this.battery = battery;
    }

    public Collection<? extends Parameter> getAllParameters() {
        List<Parameter> parameters = new ArrayList<Parameter>(this.parameters);
        if (psu != null)
            parameters.add(psu.getQuantityPsu());
        if (battery != null)
            parameters.add(battery.getQuantityBatteries());

        return parameters;
    }
}
