package uku_control.config;

import javax.swing.event.ChangeListener;
import javax.xml.bind.annotation.XmlAttribute;
import java.util.Arrays;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/26/2014.
 * For the pleasure
 */
public class Alarm extends IndexedParameter {
    private String mask;

    @XmlAttribute
    public String getMask() {
        return mask;
    }

    public void setMask(String mask) {
        this.mask = mask;
    }

    public AlarmState getAlarmState() {
        if (getIndex() == null) {
            return alarmForOneElemet(getValue());
        } else {
            if (getIndex().getValue() == null)
                return AlarmState.NO_DATA;
            boolean isAlarm = false;
            boolean isNoData = false;
            for (Parameter parameter : getIndexedParameters()) {
                AlarmState alarmState = alarmForOneElemet(parameter.getValue());
                isAlarm |= alarmState == AlarmState.ALARM;
                isNoData |= alarmState == AlarmState.NO_DATA;
            }

            if (isAlarm) {
                return AlarmState.ALARM;
            } else if (isNoData)
                return AlarmState.NO_DATA;
            else
                return AlarmState.OK;
        }
    }

    private AlarmState alarmForOneElemet(Object value) {
        if (!(value instanceof Integer))
            return AlarmState.NO_DATA;

        int maskAsInt = Integer.parseInt(mask, 16);
        return (maskAsInt & ((Integer) value)) != 0 ? AlarmState.ALARM : AlarmState.OK;
    }

    @Override
    public synchronized List<? extends Parameter> getIndexedParameters() {
        if (getIndex() == null)
            return Arrays.asList(this);

        return super.getIndexedParameters();
    }

    @Override
    public synchronized void addChangeListener(ChangeListener changeListener) {
        if (getIndex() == null) {
            super.addChangeListener(changeListener);
            return;
        }
        super.addChangeListener(changeListener);

        for (Parameter parameter : getIndexedParameters())
            parameter.addChangeListener(changeListener);
    }

}
