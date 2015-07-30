package uku_control;

import java.awt.*;

import javax.swing.*;


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
public class UKU_Main_Panel_SNMP extends JPanel {
    public UKU_Main_Panel_SNMP() {

    }

    BorderLayout borderLayout1 = new BorderLayout();

    private UKU_Data_Big data;
    private No_Connection_Panel no_connection_panel = new No_Connection_Panel();
    private UKU_Status_Panel_Big status_panel;
    private UKU_SParameters_Panel sparameters_panel;
   // private UKU_ExtIO_Panel extio_panel;
    private UKU_Panel_Big panel;
    private UKU_Control_Panel_SNMP control_panel;
    private UKU_Panel current_panel = null;
    private UKU_Panel new_panel = null;
    private UKU_Info_Panel system_id;

    private UKU_Panel right = new UKU_Panel();

    BorderLayout borderLayout2 = new BorderLayout();

    public Alarm_Sound_Wav alarm_sound;

    public UKU_Main_Panel_SNMP(UKU_Data_Big data) {

        //sound init
       // alarm_sound = new Alarm_Sound_Wav(data.url.get());
        //UIManager.put("Panel.background", new Color(240,255,255));
    //        UIManager.put("JPanel.background", new Color(240,240,250));
        UIManager.put("ComboBox.buttonBackground", new Color(117, 177, 217));
        UIManager.put("ComboBox.buttonShadow", Color.BLUE);
        UIManager.put("ComboBox.buttonDarkShadow", Color.white);
        UIManager.put("ComboBox.buttonHighLight", Color.darkGray);
        UIManager.put("ScrollBar.thumbHighlight", Color.WHITE);
        UIManager.put("ScrollBar.thumbDarkShadow", Color.WHITE);
        UIManager.put("ScrollBar.trackForeground", Color.white);
        UIManager.put("ScrollBar.thumb", new Color(230, 250, 250));//new Color(117, 177, 217));

        this.data = data;
        status_panel = new UKU_Status_Panel_Big(data);
        panel = new UKU_Panel_Big(data);
        control_panel = new UKU_Control_Panel_SNMP(data);
        sparameters_panel = new UKU_SParameters_Panel(data);
      //  extio_panel = new UKU_ExtIO_Panel(data);
        system_id = new UKU_Info_Panel(data);

        this.setLayout(null);
        this.setSize(panel.desired_width + 250, panel.desired_height + system_id.desired_height);
        this.setBounds(0,0,panel.desired_width + 250, panel.desired_height + system_id.desired_height);
        control_panel.setBounds(0,20, 250, panel.desired_height);
        right.setSize(panel.desired_width, panel.desired_height);
        right.setBounds(250, system_id.desired_height, panel.desired_width, panel.desired_height);
        this.add(control_panel);
        this.add(right);
        this.add(system_id);
        this.update_panel();

    }

    public void update_panel(){

        data.margin_red.set(1 - data.margin_red.get());
        system_id.update_panel();
        //data.connection_status.set(data.CONNECTION_OK);
        if (data.connection_status.get() == data.CONNECTION_FAILED) {
            current_panel = (UKU_Panel)no_connection_panel;
                 }
                 else{
            if (data.current_view.get() == data.STATUS_VIEW)
                current_panel = status_panel;
             else if (data.current_view.get() == data.DETAILS_VIEW)
                current_panel = panel;
            else if (data.current_view.get() == data.SPARAMS_VIEW)
                current_panel = sparameters_panel;
           // else if (data.current_view.get() == data.EXTIO_VIEW)
           //     current_panel = extio_panel;
                 }


        if (current_panel != new_panel)
        {
            new_panel = current_panel;
            right.removeAll();
            right.add(new_panel);
        }

        new_panel.update_panel();
        control_panel.update_panel();

        right.validate();
        right.repaint();

        //if ((data.alarm_is_shown.get() == 0) && (data.alarm_is_to_be.get() == 1)) {
        if ((data.get_alarm() == data.ALARM) & (data.get_acknowledged() == data.NOT_ACKNOWLEDGED)){
            alarm_sound = new Alarm_Sound_Wav(data.url.get() + "/ringin.wav");
            alarm_sound.switch_on(true);
            JOptionPane pane = new JOptionPane("Àâàðèÿ", JOptionPane.ERROR_MESSAGE);
            JDialog dialog = pane.createDialog(right, "ÀÂÀÐÈß");
//            dialog.setAlwaysOnTop(true);

            dialog.setVisible(true);
            alarm_sound.switch_on(false);
            data.set_acknowledged(data.ACKNOWLEDGED);
        }
       // if ((data.get_alarm() == data.ALARM) & (data.get_acknowledged() == data.NOT_ACKNOWLEDGED)){
       //     data.alarm_is_shown.set(0);

        data.alarm_is_to_be.set(this.get_alarms());

    }

    public int get_alarms(){
        return data.get_alarm();
    }


    public static void main(String args[]){
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
        frame.setSize(480 + 250 + 30, 680 + 30);
        UKU_Data_Big data = new UKU_Data_Big();
        data.connection_status.set(data.CONNECTION_OK);
        data.current_view.set(1);
    /*    data.external_temperature_count.set(5);
        data.external_jumper_count.set(5);*/
        data.psus_count.set(2);
        data.extio_count.set(4);
        data.batteries_count.set(1);
        UKU_Main_Panel_SNMP panel = new UKU_Main_Panel_SNMP(data);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
/*

        try {
            Thread.sleep(4000);
        } catch (InterruptedException ex) {
        }


        data.batteries_count.set(3);
       data.psus_count.set(10);
       data.batteries_array[1].status.set(0x01);
       data.batteries_array[2].status.set(0x02);

       for (int i = 0; i < 10; i++){
           data.psus_array[i].status.set(0x01 << i);
           data.psus_array[i].current.set(0x01 << i);
           data.batteries_array[i].voltage.set(0x01 << i);
           data.batteries_array[i].current.set(0x01 << i);
           data.batteries_array[i].temperature.set(0x01 << i);
           data.batteries_array[i].capacity.set(0x01 << i);
           data.batteries_array[i].charge.set(0x01 << i);
       }
       data.external_jumper_count.set(4);
       data.external_temperature_count.set(4);







/*
        while (true){
                  data.psus_array[1].status.set(0x00);
                  data.batteries_array[3].status.set(0);
                  data.external_jumper_array[1].set(0);
                  data.external_temperature_array[1].set_alarm(0);
                  data.power_main.status.set(0);
                  data.psus_count.set(10);
                  data.batteries_count.set(3);
                  data.external_jumper_count.set(10);
                  data.external_temperature_count.set(10);
                  panel.update_panel();
                  try {
                      Thread.sleep(4000);
                  } catch (InterruptedException ex) {
                  }
                  data.psus_count.set(0);
                  data.batteries_count.set(0);
                  data.external_jumper_count.set(0);
                  data.external_temperature_count.set(0);
                  panel.update_panel();
                  try {
                      Thread.sleep(15000);
                  } catch (InterruptedException ex) {
                  }
                  data.power_main.status.set(1);
                  data.psus_count.set(30);
                  data.psus_array[1].status.set(0x02);
                  data.power_main.status.set(3);
                  data.batteries_array[3].status.set(1);
                  data.external_jumper_array[1].set(1);
                  data.external_temperature_count.set(30);
                  data.external_temperature_array[1].set_alarm(1);

                  data.batteries_count.set(30);
                  data.external_temperature_count.set(30);
                  data.external_jumper_count.set(30);
                  panel.update_panel();
                  try {
                      Thread.sleep(15000);
                  } catch (InterruptedException ex) {
                  }

        }*/
    }

}
