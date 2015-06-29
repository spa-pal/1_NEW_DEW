package uku_control.config;

import uku_control.SettingsView;

import javax.swing.*;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import java.awt.*;

/**
 * Created by Anatoly Danilov on 11/23/2014.
 * For the pleasure
 */
public class SettingParameter extends Parameter<Object> {

    private String toolTip;
    private Box dinamic_parameter;
    private String valueToSet;
    private SettingsView settingsView;
    private String onText;
    private String offText;
    private Integer onValue;
    private Integer offValue;
    private Integer step = 1;


    public JComponent getView() {
        if (dinamic_parameter != null)
            return dinamic_parameter;

        if (settingsView == null)
            settingsView = SettingsView.Simple;


        dinamic_parameter = Box.createHorizontalBox();

        dinamic_parameter.setToolTipText(getToolTip());
        dinamic_parameter.setMaximumSize(new Dimension(450, 23));
        dinamic_parameter.setMinimumSize(dinamic_parameter.getMaximumSize());
        dinamic_parameter.setPreferredSize(dinamic_parameter.getMaximumSize());

        JLabel sparameter_label = new JLabel(getName(), JLabel.LEFT);
        sparameter_label.setFont(new Font("SanSerif", Font.PLAIN, 14));
        sparameter_label.setAlignmentX(0.5F);

        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(5));
        dinamic_parameter.add(sparameter_label);
        dinamic_parameter.add(dinamic_parameter.createHorizontalGlue());


        dinamic_parameter.add(settingsView.getView(this));
        return dinamic_parameter;
    }


    @XmlElement(name = "tooltip")
    public String getToolTip() {
        return toolTip;
    }

    public void setToolTip(String toolTip) {
        this.toolTip = toolTip;
    }

    @XmlAttribute(name = "value-to-set")
    public String getValueToSet() {
        return valueToSet;
    }

    public void setValueToSet(String valueToSet) {
        this.valueToSet = valueToSet;
    }

    @XmlAttribute(name = "view")
    public SettingsView getSettingsView() {
        return settingsView;
    }

    public void setSettingsView(SettingsView settingsView) {
        this.settingsView = settingsView;
    }

    @XmlAttribute(name = "off-text")
    public String getOffText() {
        return offText;
    }

    public void setOffText(String offText) {
        this.offText = offText;
    }

    @XmlAttribute(name = "on-text")
    public String getOnText() {
        return onText;
    }

    public void setOnText(String onText) {
        this.onText = onText;
    }

    @XmlAttribute(name = "off-value")
    public Integer getOffValue() {
        return offValue;
    }

    public void setOffValue(Integer offValue) {
        this.offValue = offValue;
    }

    @XmlAttribute(name = "on-value")
    public Integer getOnValue() {
        return onValue;
    }

    public void setOnValue(Integer onValue) {
        this.onValue = onValue;
    }

    public Integer getStep() {
        return step;
    }

    public void setStep(Integer step) {
        this.step = step;
    }
}
