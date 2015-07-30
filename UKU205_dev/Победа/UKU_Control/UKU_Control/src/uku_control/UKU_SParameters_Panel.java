package uku_control;

import java.awt.*;

import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

//import java.util.GregorianCalendar;


public class UKU_SParameters_Panel extends UKU_Panel {

    private UKU_Data_Big data;
    private int table_width = 400;
    private Box parameter[] = new Box[50];
    public static int desired_height;
    public static int desired_width;
    private boolean margin_boolean = false;

    public UKU_SParameters_Panel(UKU_Data_Big amplifier_dat) {
        this.setBounds(0, 0, 480, 680);

        this.data = amplifier_dat;
        this.desired_height = 680;
        this.desired_width = 480;
        UIManager.put("Box.background", new Color(240, 255, 255));

        this.surface_decorator();
    }

    public void surface_decorator() {
        Box b = Box.createVerticalBox();

        JLabel caption_main = new JLabel("СИСТЕМНОЕ МЕНЮ", JLabel.CENTER);
        caption_main.setFont(new Font("SanSerif", Font.PLAIN, 18));
        caption_main.setAlignmentX(0.5F);
        b.add(b.createVerticalStrut(5));
        b.add(caption_main);

        JLabel caption = new JLabel(" Параметр                                                 Значение", JLabel.LEFT);
        caption.setFont(new Font("SanSerif", Font.PLAIN, 18));
        caption.setAlignmentX(0.5F);

        caption.setMaximumSize(new Dimension(450, 30));
        caption.setMinimumSize(caption.getMaximumSize());
        caption.setPreferredSize(caption.getMaximumSize());
        b.add(b.createVerticalStrut(15));
        b.add(caption);

        if (data.special_settings.active_set.get() != 0) {
            for (int i = 0;
                         i < data.special_settings.set.size(); i++) {
                b.add(b.createVerticalStrut(15));
                parameter[i] = get_parameter_view(data.special_settings.set.get(i));
                b.add(parameter[i]);
            }
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
    private Box get_parameter_view(Special_Parameters sparam) {
        Box dinamic_parameter = Box.createHorizontalBox();

        dinamic_parameter.setToolTipText(sparam.tooltip.get());
        dinamic_parameter.setMaximumSize(new Dimension(450, 23));
        dinamic_parameter.setMinimumSize(dinamic_parameter.getMaximumSize());
        dinamic_parameter.setPreferredSize(dinamic_parameter.getMaximumSize());

        JLabel sparameter_label = new JLabel(sparam.screen_name.get(), //"Время проверки цепи батареи (Мин.)",
                                             JLabel.LEFT);
        sparameter_label.setFont(new Font("SanSerif", Font.PLAIN, 14));
        sparameter_label.setAlignmentX(0.5F);

        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(5));
        dinamic_parameter.add(sparameter_label);
        dinamic_parameter.add(dinamic_parameter.createHorizontalGlue());

        if ((sparam.screen_view.get() == Special_Settings.ENABLED_DISABLED) | (sparam.screen_view.get() == Special_Settings.MANUAL_AUTO)){

            JButton state_1 = new JButton((sparam.screen_view.get() == Special_Settings.ENABLED_DISABLED)?"Выкл.":"Ручн.");
            state_1.setBackground(new Color(112, 177, 217));
            state_1.setForeground(Color.RED);
            state_1.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            state_1.setMaximumSize(new Dimension(50, 23));
            state_1.setMinimumSize(state_1.getMaximumSize());
            state_1.setPreferredSize(state_1.getMaximumSize());
            state_1.addActionListener(new UKU_SSettings_SNMP(this));

            JButton state_2 = new JButton((sparam.screen_view.get() == Special_Settings.ENABLED_DISABLED)?"Вкл.":"АВТО");
            state_2.setBackground(new Color(112, 177, 217));
            state_2.setForeground(Color.RED);
            state_2.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            state_2.setMaximumSize(new Dimension(50, 23));
            state_2.setMinimumSize(state_1.getMaximumSize());
            state_2.setPreferredSize(state_1.getMaximumSize());
            state_2.addActionListener(new UKU_SSettings_SNMP(this));

            if (sparam.value.get() == 0) {
                state_1.setForeground(new Color(10, 10, 10));
                state_2.setForeground(new Color(150, 150, 150));
            }
            else {
                state_1.setForeground(new Color(150, 150, 150));
                state_2.setForeground(new Color(10, 10, 10));
            }
            dinamic_parameter.add(state_1);
            dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(6));
            dinamic_parameter.add(state_2);
        }else{
            JTextField value = new JTextField("");
            String tempik_str = new String();

            switch (sparam.screen_view.get()) {
            case Special_Settings.NONE:
                tempik_str = Integer.toString(sparam.value.get());
                break;
            case Special_Settings.ZERO_TO_ONE:
                tempik_str = Integer.toString(sparam.value.get() + 1);
                break;
            case Special_Settings.MULTIPLIED:
                tempik_str = Double.toString(sparam.value.get() /
                                              (double)sparam.multiply_factor.get());
                break;
            }

            value.setText(tempik_str);
            value.setHorizontalAlignment(value.RIGHT);
            value.setMaximumSize(new Dimension(50, 23));
            value.setMinimumSize(value.getMaximumSize());
            value.setPreferredSize(value.getMaximumSize());

            value.setFont(new Font("SanSerif", Font.PLAIN, 12));
            value.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            value.addActionListener(new UKU_SSettings_SNMP(this));

            JButton decrement = new JButton("<");
            decrement.setBackground(new Color(112, 177, 217));
            decrement.setForeground(Color.black);
            decrement.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            decrement.setMaximumSize(new Dimension(23, 23));
            decrement.setMinimumSize(decrement.getMaximumSize());
            decrement.setPreferredSize(decrement.getMaximumSize());
            decrement.addActionListener(new UKU_SSettings_SNMP(this));

            JButton increment = new JButton(">");
            increment.setBackground(new Color(112, 177, 217));
            increment.setForeground(Color.black);
            increment.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            increment.setMaximumSize(new Dimension(23, 23));
            increment.setMinimumSize(decrement.getMaximumSize());
            increment.setPreferredSize(decrement.getMaximumSize());
            increment.addActionListener(new UKU_SSettings_SNMP(this));
            dinamic_parameter.add(decrement);
            dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(5));
            dinamic_parameter.add(value);
            dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(5));
            dinamic_parameter.add(increment);
        }


        dinamic_parameter.add(dinamic_parameter.createHorizontalStrut(25));
    // dinamic_parameter.add(units_label);

        return dinamic_parameter;
    }


    public UKU_SParameters_Panel() {
    }


    public void update_data() {
        if (data.need_correct_sparams_panel.get() == 1) {
            data.scroll_pane_position.set(((JScrollPane)this.getAccessibleContext().getAccessibleChild(0)).getVerticalScrollBar().getValue());
            this.removeAll();
            this.surface_decorator();
            data.need_correct_sparams_panel.set(0);
        }
    }


    public void update_panel() {
        this.update_data();
        this.repaint();

    }

    /**
     * SSetings_action_performed
     *
     * @param e ActionEvent
     */
    public void SSetings_action_performed(ActionEvent e) {
        System.out.println(" SParam Settings Object activated ");
        for (int i = 0; i < data.special_settings.set.size(); i++) {
            switch (data.special_settings.set.get(i).screen_view.get()){
            case Special_Settings.ENABLED_DISABLED:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Disable ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.set.get(i).ID.get(), 0));
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(5)){
                    System.out.println(" Enable ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.set.get(i).ID.get(), 1));
                }
                break;
            case Special_Settings.MANUAL_AUTO:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Manual ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.set.get(i).ID.get(), 0));
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(5)){
                    System.out.println(" Auto ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT, data.special_settings.set.get(i).ID.get(), 1));
                }
                break;
            default:
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(3)){
                    System.out.println(" Decrement ");
//                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_DECREMENT, data.special_settings.set.get(i).ID.get()));
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT,
                            data.special_settings.set.get(i).ID.get(), data.special_settings.set.get(i).value.get() - 1));

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
                    if (no_way == 0) {
                        tempik = tempik *
                                 data.special_settings.set.get(i).
                                 multiply_factor.get();

                        if ((tempik < data.special_settings.set.get(i).
                             lowest_value.get()) |
                            (tempik > data.special_settings.set.get(i).
                             highest_value.get())) {
                            data.lifo.add(new Command_SNMP(Command_Handler.
                                    GET_SPECIAL_PARAMETER, 0,
                                    data.special_settings.set.get(i).ID.get()));

                        } else {
                            if (data.special_settings.set.get(i).screen_view.
                                get() == Special_Settings.ZERO_TO_ONE) {
                                tempik = tempik - 1;
                            }

                            data.lifo.add(new Command_SNMP(Command_Handler.
                                    SET_SPECIAL_PARAMETER,
                                    Command_Handler.SET_SPARAM_INT,
                                    data.special_settings.set.get(i).ID.get(),
                                    (int) tempik));
                        }
                    } else {
                        data.lifo.add(new Command_SNMP(Command_Handler.
                                GET_SPECIAL_PARAMETER, 0,
                                data.special_settings.set.get(i).
                                ID.get()));
                    }
                }
                if (e.getSource() == parameter[i].getAccessibleContext().getAccessibleChild(7)){
                    System.out.println(" Increment ");
                    data.lifo.add(new Command_SNMP(Command_Handler.SET_SPECIAL_PARAMETER, Command_Handler.SET_SPARAM_INT,
                            data.special_settings.set.get(i).ID.get(), data.special_settings.set.get(i).value.get() + 1));
                }
                break;
            }
        }
    }


}

class UKU_SSettings_SNMP implements
        ActionListener {
    private UKU_SParameters_Panel adaptee;
    UKU_SSettings_SNMP(
            UKU_SParameters_Panel adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.SSetings_action_performed(e);
    }
}
