package uku_control.config;

import javax.xml.bind.annotation.XmlElement;

/**
 * Created by Anatoly Danilov on 1/20/2015.
 * For the pleasure
 */
public class PowerSupplyUnit {

    private Parameter<Integer> quantityPsu;
    private SettingParameter setPrimary;
    private SettingParameter disablePsu;
    private SettingParameter unlock;
    private SettingParameter enableParallel;
    private SettingParameter disableParallel;

    @XmlElement(name = "set-primary")
    public SettingParameter getSetPrimary() {
        return setPrimary;
    }

    public void setSetPrimary(SettingParameter setPrimary) {
        this.setPrimary = setPrimary;
    }

    @XmlElement(name = "disable")
    public SettingParameter getDisablePsu() {
        return disablePsu;
    }

    public void setDisablePsu(SettingParameter disablePsu) {
        this.disablePsu = disablePsu;
    }

    @XmlElement
    public SettingParameter getUnlock() {
        return unlock;
    }


    public void setUnlock(SettingParameter unlock) {
        this.unlock = unlock;
    }

    @XmlElement(name = "enable-parallel")
    public SettingParameter getEnableParallel() {
        return enableParallel;
    }

    public void setEnableParallel(SettingParameter enableParallel) {
        this.enableParallel = enableParallel;
    }

    @XmlElement(name = "disable-parallel")
    public SettingParameter getDisableParallel() {
        return disableParallel;
    }

    public void setDisableParallel(SettingParameter disableParallel) {
        this.disableParallel = disableParallel;
    }

    @XmlElement(name = "quantity-psu")
    public Parameter<Integer> getQuantityPsu() {
        return quantityPsu;
    }

    public void setQuantityPsu(Parameter<Integer> quantityPsu) {
        this.quantityPsu = quantityPsu;
    }
}
