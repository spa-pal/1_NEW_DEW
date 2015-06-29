//package uku_control;
//
//import javax.swing.*;
//
///**
// * Created by Kriahtunchik on 2/4/14.
// */
//public class StartUkuControl {
//    public static void main(String[] args) {
//        JFrame frame = new JFrame("demo");
//        UKU_Data_Big data = new UKU_Data_Big();
//        data.set_psu_count(4);
//        data.psus_count.set(3);
//        data.batteries_count.set(2);
//        data.current_view.set(data.STATUS_VIEW);
//        data.connection_status.set(UKU_Data_Big.CONNECTION_OK);
//
//        UKU_Main_Panel_SNMP panel = new UKU_Main_Panel_SNMP(data);
//        UKU_Connection_SNMP connection = new UKU_Connection_SNMP(data);
//        panel.update_panel();
//        frame.getContentPane().add(panel);
//        frame.setSize((int) (panel.getSize().getWidth() + 10), (int) panel.getSize().getHeight() + 50);
//        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//        frame.setVisible(true);
//    }
//}
