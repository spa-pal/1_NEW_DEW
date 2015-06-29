package uku_control.config;

import javax.xml.bind.annotation.XmlElement;

/**
 * Created by Anatoly Danilov on 1/20/2015.
 * For the pleasure
 */
public class Battery {
    private Parameter<Integer> quantityBatteries;
    private SettingParameter compensationCharge;
    private SettingParameter capacityControl;
    private SettingParameter disableSpecials;

    @XmlElement(name = "quantity-batteries")
    public Parameter<Integer> getQuantityBatteries() {
        return quantityBatteries;
    }

    public void setQuantityBatteries(Parameter<Integer> quantityBatteries) {
        this.quantityBatteries = quantityBatteries;
    }

    @XmlElement(name = "compensation-charge")
    public SettingParameter getCompensationCharge() {
        return compensationCharge;
    }

    public void setCompensationCharge(SettingParameter compensationCharge) {
        this.compensationCharge = compensationCharge;
    }

    @XmlElement(name = "capacity-control")
    public SettingParameter getCapacityControl() {
        return capacityControl;
    }

    public void setCapacityControl(SettingParameter capacityControl) {
        this.capacityControl = capacityControl;
    }

    @XmlElement(name = "disable-specials")
    public SettingParameter getDisableSpecials() {
        return disableSpecials;
    }

    public void setDisableSpecials(SettingParameter disableSpecials) {
        this.disableSpecials = disableSpecials;
    }
}
