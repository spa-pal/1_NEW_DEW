package uku_control.config;


import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 */
@XmlRootElement(name = "config")
public class Configuration {
    private Connection connection;
    private Parameter voltage;
    private Parameter ampers;
    private Parameter location;
    private Parameter model;
    private Parameter serialNumber;

    private List<ViewConfiguration> viewConfigurations = new ArrayList<ViewConfiguration>();

    private Journal journal;

    private Settings settings;

    private List<Alarm> alarms = new ArrayList<Alarm>();

    public List<Parameter> getAllParameters() {
        return Arrays.asList(voltage, ampers, location, model, serialNumber);
    }

    public List<ViewConfiguration> getViewConfigurations() {
        return viewConfigurations;
    }

    @XmlElement(name = "view")
    public void setViewConfigurations(List<ViewConfiguration> viewConfigurations) {
        this.viewConfigurations = viewConfigurations;
    }

    @Override
    public String toString() {
        return "Configuration{" +
                "parameters=" +
                ", viewConfigurations=" + viewConfigurations +
                '}';
    }

    @XmlElement
    public Parameter getVoltage() {
        return voltage;
    }

    public void setVoltage(Parameter voltage) {
        this.voltage = voltage;
    }

    @XmlElement
    public Parameter getAmpers() {
        return ampers;
    }

    public void setAmpers(Parameter ampers) {
        this.ampers = ampers;
    }

    @XmlElement
    public Parameter getLocation() {
        return location;
    }

    public void setLocation(Parameter location) {
        this.location = location;
    }

    @XmlElement
    public Parameter getModel() {
        return model;
    }

    public void setModel(Parameter model) {
        this.model = model;
    }

    @XmlElement
    public Parameter getSerialNumber() {
        return serialNumber;
    }

    public void setSerialNumber(Parameter serialNumber) {
        this.serialNumber = serialNumber;
    }

    public Settings getSettings() {
        return settings;
    }

    public void setSettings(Settings settings) {
        this.settings = settings;
    }

    @XmlElement(name = "connection")
    public Connection getConnection() {
        return connection;
    }

    public void setConnection(Connection connection) {
        this.connection = connection;
    }

    public Parameter getParamterByName(String name) {
        for (ViewConfiguration viewConfiguration : viewConfigurations) {
            for (Parameter parameter : viewConfiguration.getParameters()) {
                if (name.equals(parameter.getName()))
                    return parameter;
            }
        }
        return null;
    }

    @XmlElement(name = "alarm")
    public List<Alarm> getAlarms() {
        return alarms;
    }

    public void setAlarms(List<Alarm> alarms) {
        this.alarms = alarms;
    }

    public Collection<? extends Parameter> getAllAlarms() {
        ArrayList<Parameter> parameters = new ArrayList<Parameter>();
        for (Alarm alarm : alarms)
            if (alarm.getIndex() != null)
                parameters.add(alarm.getIndex());

        parameters.addAll(alarms);

        return parameters;
    }

    @XmlElement
    public Journal getJournal() {
        return journal;
    }

    public void setJournal(Journal journal) {
        this.journal = journal;
    }
}
