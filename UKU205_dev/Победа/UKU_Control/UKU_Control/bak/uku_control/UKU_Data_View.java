package uku_control;

import javax.swing.*;
import java.awt.Color;
/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Data_View {


    public static String temperature_value(Temperature_Value val) {
        return new String((val.get_alarm() == 1)? " ÀÂÀÐÈß": " ÍÎÐÌÀ");
    }

    public static String jumper_value(Jumper_Value val) {
        return new String(((val.status.get() & 0x02) == 0x02) ? " ÀÂÀÐÈß" : " ÍÎÐÌÀ");
    }

    public static String voltage_bps(int n){

        String k = new String(Double.toString(n / 10.0));
        StringBuffer result = new StringBuffer();
        if (n >= 1000) {
            result.append(" >=");
            result.append(k);
        }
        else {
            result.append(" ");
            result.append(k);
        }
        return (result.toString());
    }

    public static String voltage_battery_load(int n){
        String k = new String(Double.toString(n / 10.0));
        StringBuffer result = new StringBuffer();

        if (n >= 1000) {
            result.append(" >=");
            result.append(k);
        }

        else {
            result.append(" ");
            result.append(k);
        }

        return result.toString();
    }

    public static String current_bps(int n){
        String k = new String(Double.toString(n / 10.0));
        StringBuffer result = new StringBuffer();

        if (n >= 127)  {
            result.append(" >=");
            result.append(k);
        }

        else {
            result.append(" ");
            result.append(k);
        }

        return result.toString();
    }

    public static String current_battery(int n){
        String k = new String(Double.toString(n / 10.0));
        StringBuffer result = new StringBuffer();

        if (n >= 127)  {
            result.append(" >=");
        }
        if (n <= -127)  {
            result.append(" <=");
        }

           result.append(" ");
           result.append(k);



        return result.toString();
    }

    public static String temperature(int n){
        String k = new String(Integer.toString(n));
        StringBuffer result = new StringBuffer();

        if (n >= 125) {
            result.append(" >=");
        }

        if (n <= 0) {
            result.append(" <=");
            result.append(k);
        }

        else {
            result.append(" +");
            result.append(k);
        }

        return result.toString();
    }

    public static String voltage_circuit(int n){
        String k = new String(Integer.toString(n));
        StringBuffer result = new StringBuffer();

        if (n >= 254) {
            result.append(" >=");
            result.append(k);
        }

        else {
            result.append(" ");
            result.append(k);
        }

        return result.toString();

    }
    public static String battery_capacity(int n){
        String k = new String(Integer.toString(n));
        StringBuffer result = new StringBuffer();

        if (n >= 254) {
            result.append(" >=");
            result.append(k);
        }

        else {
            result.append(" ");
            result.append(k);
        }

        return result.toString();

    }

    public static String battery_charge(int n){
        String k = new String(Integer.toString(n ));
        StringBuffer result = new StringBuffer();

        {
            result.append(" ");
            result.append(k);
        }

        return result.toString();

    }

    public static String special_functions(int n1, int n2){
        String k1 = new String(" Ñïåöôóíêöèè");
        String k2 = new String(" Âûðàâíèâàþùèé çàðÿä");
        String k3 = new String(" Êîíòðîëü åìêîñòè");
        StringBuffer result = new StringBuffer();

        if (n1 == UKU_Data.COMPENSATION_ON) k1 = k2;
        if (n2 == UKU_Data.CAPACITY_CONTROL_ON) k1 = k3;
        return k1;
    }

    public static String special_functions_on_off(int n1, int n2){
        String k1 = new String(" Âêë");
        String k2 = new String(" Âûêë");

        return (n1 + n2)>0?k1:k2;
    }
    public static String circuit_frequency(int n){
        String k = new String(Double.toString(n / 10.0));
        StringBuffer result = new StringBuffer();

        if (n <= 400) {
            result.append(" <=");
            return new String(" ---");
        }

        if (n >= 654) {
            result.append(" >=");
        }


        {
            result.append(" ");
            result.append(k);
        }

        return result.toString();
    }


    public UKU_Data_View() {
    }
}
