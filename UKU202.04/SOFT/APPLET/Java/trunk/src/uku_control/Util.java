package uku_control;

import uku_control.config.Configuration;
import uku_control.config.Parameter;
import uku_control.config.ViewConfiguration;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.awt.*;
import java.util.ResourceBundle;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 */
public class Util {

    public static final Color BACKGROUND = new Color(112, 177, 217);
    public static final String HTML_BODY_P_STYLE_MARGIN_LEFT_5 = "<html><body><p style='margin-left:5'>";
    private static Configuration configuration;
    private static String color;
    private static String codeBase;

    public static Configuration loadConfiguration() {
        if (configuration != null)
            return configuration;

        try {
            JAXBContext jc = JAXBContext.newInstance(Configuration.class, ViewConfiguration.class, Parameter.class);
            Unmarshaller unmarshaller = jc.createUnmarshaller();
            return configuration = (Configuration) unmarshaller.unmarshal(Util.class.getClassLoader().getResourceAsStream("uku_control/config.xml"));
        } catch (JAXBException e) {

            e.printStackTrace();
        }
        return configuration = new Configuration();
    }

    public static <T> boolean isSame(T oldValue, T newValue) {
        if (oldValue == null && newValue == null)
            return true;
        if (oldValue == null || newValue == null)
            return false;

        return newValue.equals(oldValue);
    }

    public static String toText(Parameter parameter) {
        String addMargin = "";
        if (parameter.getType() == Type.STATUS && parameter.isAlarmStatus()) {

            addMargin = "<b><FONT COLOR=" + color + ">";
        }

        return HTML_BODY_P_STYLE_MARGIN_LEFT_5 + addMargin + parameter.getTextValue();
    }

    public static void switchColor() {
        color = "RED".equals(color) ? "BLACK" : "RED";
    }

    public static void setCodeBase(String codeBase) {
        Util.codeBase = codeBase;
    }

    public static String getCodeBase() {
        return codeBase;
    }
}
