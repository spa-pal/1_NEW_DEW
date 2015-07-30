package uku_control;

import java.awt.*;

import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

//import java.util.GregorianCalendar;


public class UKU_ExtIO_Panel extends UKU_Panel {

    private UKU_Data_Big data;
    private int table_width = 400;
    private Box extio_box[] = new Box[10];

    private JLabel battery_status;
    public static int desired_height;
    public static int desired_width;
    private boolean margin_boolean = false;

    public UKU_ExtIO_Panel(UKU_Data_Big amplifier_dat) {
        this.setBounds(0, 0, 480, 680);

        this.data = amplifier_dat;
        this.desired_height = 680;
        this.desired_width = 480;
        UIManager.put("Box.background", new Color(240, 255, 255));
        //this.setLayout(new BorderLayout());

        this.surface_decorator();

    }

    public void surface_decorator() {
        Box b = Box.createVerticalBox();

        JLabel caption_main = new JLabel("ВНЕШНИЕ ИСПОЛНИТЕЛЬНЫЕ УСТРОЙСТВА", JLabel.CENTER);
        caption_main.setFont(new Font("SanSerif", Font.PLAIN, 18));
        caption_main.setAlignmentX(0.5F);
        b.add(b.createVerticalStrut(5));
        b.add(caption_main);

        for (int i = 0; i < data.extio_count.get(); i++)
        {
            b.add(b.createVerticalStrut(15));
           // extio_box[i] = get_extio_view(data.extio_data_array[i]);
            b.add(extio_box[i]);

        }


        JPanel box_panel = new JPanel();
        box_panel.add(b);
        JScrollPane scroll_pane = new JScrollPane(box_panel);
        scroll_pane.setPreferredSize(new Dimension(this.desired_width,
                this.desired_height));
        scroll_pane.getVerticalScrollBar().setForeground(Color.RED);
        scroll_pane.setBorder(null);
        this.setLayout(new BorderLayout());
        this.add(scroll_pane);


        scroll_pane.getVerticalScrollBar().setValueIsAdjusting(true);
        scroll_pane.getVerticalScrollBar().setValue(data.scroll_pane_position.get());
    }

    /**
     * get_parameter_view
     *
     * @param sparam Special_Parameters
     * @return Box
     */
    private Box get_extio_view(ExtIO_Data extio_data) {
        Box dinamic_parameter = Box.createHorizontalBox();

        dinamic_parameter.setToolTipText("Внешнее исполнительное устройство № " + extio_data.number.get());
        dinamic_parameter.setMaximumSize(new Dimension(450, 23));
        dinamic_parameter.setMinimumSize(dinamic_parameter.getMaximumSize());
        dinamic_parameter.setPreferredSize(dinamic_parameter.getMaximumSize());

        JLabel sparameter_label = new JLabel("Исполнительное устройство № " + extio_data.number.get(), //"Время проверки цепи батареи (Мин.)",
                                             JLabel.LEFT);
        sparameter_label.setFont(new Font("SanSerif", Font.PLAIN, 14));
        sparameter_label.setAlignmentX(0.5F);

        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(5));
        dinamic_parameter.add(sparameter_label);
        dinamic_parameter.add(dinamic_parameter.createHorizontalGlue());

        ButtonGroup active_group = new ButtonGroup();
        JRadioButton active_button = new JRadioButton(" Активно");
        JRadioButton not_active_button = new JRadioButton(" Неактивно");
        active_group.add(active_button);
        active_group.add(not_active_button);

        active_button.setBackground(new Color(240, 255, 255));
        //active_button.setForeground(Color.white);
        active_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        active_button.addActionListener(new UKU_ExtIO_SNMP(this));

        not_active_button.setBackground(new Color(240, 255, 255));
       // not_active_button.setForeground(Color.white);
        not_active_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        not_active_button.addActionListener(new UKU_ExtIO_SNMP(this));

        if (extio_data.io_status.get() == ExtIO_Data.ON)
            active_button.setSelected(true);
        else
            not_active_button.setSelected(true);

        dinamic_parameter.add(active_button);
        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(15));
        dinamic_parameter.add(not_active_button);

        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(25));

        return dinamic_parameter;
    }


    public UKU_ExtIO_Panel() {
    }


    public void update_data() {
        if (data.need_update_extio_panel.get() == 1) {
            data.scroll_pane_position.set(((JScrollPane)this.getAccessibleContext().getAccessibleChild(0)).getVerticalScrollBar().getValue());
            this.removeAll();
            this.surface_decorator();
            data.need_update_extio_panel.set(0);
        }
    }


    public void update_panel() {
        this.update_data();
        this.repaint();

    }

    /**
     * ExtIO_action_performed
     *
     * @param e ActionEvent
     */
    public void ExtIO_action_performed(ActionEvent e) {
        System.out.println(" External IO Object activated ");
        int temp_mask = 1;
        for (int i = 0; i < data.extio_count.get(); i++) {
            if (e.getSource() ==
                extio_box[i].getAccessibleContext().getAccessibleChild(3)) {
                System.out.println(" Activate ");
               /* if (data.extio_data_array[i].io_status.get() == ExtIO_Data.OFF)
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_EXTERNAL_IO,
                                                   temp_mask,
                                                   temp_mask));*/
            }

            if (e.getSource() ==
                extio_box[i].getAccessibleContext().getAccessibleChild(5)) {
                System.out.println(" Deactivate ");
              /*  if (data.extio_data_array[i].io_status.get() == ExtIO_Data.ON)
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_EXTERNAL_IO,
                                                   0x00,
                                                   temp_mask));*/
            }

            temp_mask = temp_mask << 1;

        }
        /*
            switch (data.special_settings.sets[data.special_settings.active_set.get()].parameters[i].screen_view.get()){
            case Special_Settings.ENABLED_DISABLED:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Disable ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.sets[data.special_settings.active_set.get()].parameters[i].ID.get(), 0));
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(5)){
                    System.out.println(" Enable ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.sets[data.special_settings.active_set.get()].parameters[i].ID.get(), 1));
                }
                break;
            case Special_Settings.MANUAL_AUTO:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Manual ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.sets[data.special_settings.active_set.get()].parameters[i].ID.get(), 0));
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(5)){
                    System.out.println(" Auto ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.sets[data.special_settings.active_set.get()].parameters[i].ID.get(), 1));
                }
                break;
            default:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Decrement ");
                    data.lifo.add(new Command_SNMP(Command_Handler.
                            SET_SPECIAL_PARAMETER,
                                  Command_Handler.SET_SPARAM_DECREMENT,
                                  data.special_settings.sets[data.
                                  special_settings.active_set.get()].parameters[
                                  i].ID.get()));
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(5)){
                    System.out.println(" Value ");
                    int no_way = 0;
                    double tempik = 0.0;
                    try {
                        tempik = Double.parseDouble(((JTextField) parameter[i].
                                            getAccessibleContext().
                                            getAccessibleChild(5)).getText());
                    } catch (NumberFormatException ex) {
                        no_way = 1;
                    }
                    if (no_way == 0){
                        tempik = tempik *
                                 data.special_settings.sets[data.
                                 special_settings.
                                 active_set.get()].parameters[i].
                                 multiply_factor.get();



                        if ((tempik < data.special_settings.sets[data.
                             special_settings.active_set.get()].parameters[i].
                             lowest_value.get()) |
                            (tempik > data.special_settings.sets[data.
                             special_settings.active_set.get()].parameters[i].
                             highest_value.get())) {
                           // data.command_need_to_get_all_sparams.set(1);

                            data.lifo.add(new Command_SNMP(Command_Handler.
                                        GET_SPECIAL_PARAMETER, 0,
                                        data.special_settings.sets[data.
                                        special_settings.active_set.get()].parameters[i].ID.get()));

                        }else{
                            if (data.special_settings.sets[data.
                                                           special_settings.active_set.get()].
                                                           parameters[
                                                           i].screen_view.get() == Special_Settings.ZERO_TO_ONE){
                                tempik = tempik - 1;
                            }

                            data.lifo.add(new Command_SNMP(Command_Handler.
                                                           SET_SPECIAL_PARAMETER,
                                                           Command_Handler.SET_SPARAM_INT,
                                                           data.special_settings.sets[data.
                                                           special_settings.active_set.get()].
                                                           parameters[
                                                           i].ID.get(), (int) tempik));
                        }
                    } else {
                        data.lifo.add(new Command_SNMP(Command_Handler.
                                GET_SPECIAL_PARAMETER, 0,
                                data.special_settings.sets[data.
                                special_settings.active_set.get()].parameters[i].
                                ID.get()));
                    }
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(7)){
                    System.out.println(" Increment ");
                    data.lifo.add(new Command_SNMP(Command_Handler.
                            SET_SPECIAL_PARAMETER,
                                  Command_Handler.SET_SPARAM_INCREMENT,
                                  data.special_settings.sets[data.
                                  special_settings.active_set.get()].parameters[
                                  i].ID.get()));
                }
                break;
            }
        */
       // if (e.getSource() == parameter[1].getAccessibleContext().getAccessibleChild(5))

    }


}

class UKU_ExtIO_SNMP implements
        ActionListener {
    private UKU_ExtIO_Panel adaptee;
    UKU_ExtIO_SNMP(
            UKU_ExtIO_Panel adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.ExtIO_action_performed(e);
    }
}
