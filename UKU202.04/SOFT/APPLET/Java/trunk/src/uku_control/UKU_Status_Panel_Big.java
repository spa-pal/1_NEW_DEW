package uku_control;

import uku_control.config.Alarm;
import uku_control.config.Configuration;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.geom.Ellipse2D;


/**
 * <p>Title: Ultimate monitor</p>
 * <p/>
 * <p>Description: universal monitoring system</p>
 * <p/>
 * <p>Copyright: Copyright (c) 2008</p>
 * <p/>
 * <p>Company: Lantis</p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Status_Panel_Big extends UKU_Panel implements ChangeListener {

    private int horizontal_align = 125;
    private int VERTICAL_ALIGN = 250;
    private int radius = 7;
    private int label_offset_x = 15;
    private int label_offset_y = -15;

    private Configuration configuration = Util.loadConfiguration();


    public UKU_Status_Panel_Big() {
        this.desired_height = 680;
        this.desired_width = 480;
        UIManager.put("JPanel.background", new Color(240, 255, 255));
        this.setLayout(null);
        this.setMaximumSize(new Dimension(this.desired_width, this.desired_height));
        this.setBounds(0, 0, this.desired_width, this.desired_height);

        //surface_decorator();
        putElementsToUI();
        for (Alarm alarm : configuration.getAlarms()) {
            alarm.addChangeListener(this);
        }
    }

    private void putElementsToUI() {
        load_voltage_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 24));
        load_voltage_label.setHorizontalAlignment(SwingConstants.CENTER);
        load_voltage_label.setText("Напряжение нагрузки:");
        load_voltage_label.setBounds(new Rectangle(1, 38, 480, 30));
        load_current_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 24));
        load_current_label.setHorizontalAlignment(SwingConstants.CENTER);
        load_current_label.setText("Ток нагрузки:");
        load_current_label.setBounds(new Rectangle(1, 107, 480, 30));
        voltage_value_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 24));
        voltage_value_label.setForeground(new Color(0, 139, 117));
        voltage_value_label.setHorizontalAlignment(SwingConstants.CENTER);
        voltage_value_label.setHorizontalTextPosition(SwingConstants.CENTER);
        voltage_value_label.setBounds(new Rectangle(0, 74, 480, 30));
        this.setBackground(new Color(240, 255, 255));
        current_value_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 24));
        current_value_label.setForeground(new Color(0, 139, 117));
        current_value_label.setHorizontalAlignment(SwingConstants.CENTER);
        current_value_label.setHorizontalTextPosition(SwingConstants.CENTER);

        voltage_value_label.setText("Uн = " + configuration.getVoltage().getTextValue() + " В");
        current_value_label.setText("Iн = " + configuration.getAmpers().getTextValue() + " А");

        current_value_label.setBounds(new Rectangle(1, 140, 480, 30));

        this.add(load_voltage_label);
        this.add(load_current_label);
        this.add(voltage_value_label);
        this.add(current_value_label);
        int tempY = VERTICAL_ALIGN;
        for (Alarm alarm : configuration.getAlarms()) {
            if (noNeedForAlarm(alarm))
                continue;
            JLabel alarma = new JLabel();
            alarma.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
            alarma.setText(alarm.getName());
            alarma.setBounds(new Rectangle(this.horizontal_align + this.label_offset_x, (tempY) + this.label_offset_y, 238, 30));
            tempY += 30;
            this.add(alarma);
        }
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int temp_y = this.VERTICAL_ALIGN;
        for (Alarm alarm : configuration.getAlarms()) {
            if (noNeedForAlarm(alarm))
                continue;
            Graphics2D g2 = (Graphics2D) g;
            Ellipse2D circle = new Ellipse2D.Double();
            circle.setFrameFromCenter(horizontal_align, temp_y,
                    horizontal_align + radius, temp_y + radius);

            switch (alarm.getAlarmState()) {
                case OK:
                    g2.setColor(Color.GREEN);
                    break;
                case ALARM:
                    g2.setColor(Color.RED);
                    break;
                case NO_DATA:
                    g2.setColor(Color.GRAY);
                    break;
            }
            g2.fill(circle);
            g2.setColor(Color.black);
            g2.draw(circle);
            temp_y += 30;

        }
//        Graphics2D g2 = (Graphics2D) g;
//        Ellipse2D circle = new Ellipse2D.Double();
//        circle.setFrameFromCenter(horizontal_align, temp_y,
//                horizontal_align + radius, temp_y + radius);
//
//        if (data.power_main.get_alarm() == 0)
//            g2.setColor(Color.GREEN);
//        else
//            g2.setColor(Color.RED);
//        g2.fill(circle);
//        g2.setColor(Color.black);
//        g2.draw(circle);
//
//        g2.setColor(Color.GREEN);
//        if (data.psus_count.get() > 0) {
//            for (int i = 0; i < data.psus_count.get(); i++) {
//                if (data.psus_array[i].get_alarm() != 0) {
//                    g2.setColor(Color.RED);
//                    i = 300;
//                }
//            }
//            temp_y += 30;
//            circle.setFrameFromCenter(horizontal_align, temp_y,
//                    horizontal_align + radius,
//                    temp_y + radius);
//            g2.fill(circle);
//            g2.setColor(Color.black);
//            g2.draw(circle);
//        }
//        g2.setColor(Color.GREEN);
//        if (data.batteries_count.get() > 0) {
//            for (int i = 0; i < data.batteries_count.get(); i++) {
//                if (data.batteries_array[i].get_alarm() != 0) {
//                    g2.setColor(Color.RED);
//                    i = 300;
//                }
//            }
//            temp_y += 30;
//            circle.setFrameFromCenter(horizontal_align, temp_y,
//                    horizontal_align + radius,
//                    temp_y + radius);
//            g2.fill(circle);
//            g2.setColor(Color.black);
//            g2.draw(circle);
//        }
//        g2.setColor(Color.GREEN);
//        if (data.invertors_count.get() > 0) {
//        }
//        g2.setColor(Color.GREEN);
//        if (data.external_temperature_count.get() > 0) {
//            for (int i = 0; i < data.external_temperature_count.get(); i++) {
//                if (data.external_temperature_array[i].get_alarm() != 0) {
//                    g2.setColor(Color.RED);
//                    i = 300;
//                }
//            }
//            temp_y += 30;
//            circle.setFrameFromCenter(horizontal_align, temp_y,
//                    horizontal_align + radius,
//                    temp_y + radius);
//            g2.fill(circle);
//            g2.setColor(Color.black);
//            g2.draw(circle);
//        }
//        g2.setColor(Color.GREEN);
//
//        if (data.external_jumper_count.get() > 0) {
//            for (int i = 0; i < data.external_jumper_count.get(); i++) {
//                if (data.external_jumper_array[i].get() != 0) {
//                    g2.setColor(Color.RED);
//                    i = 300;
//                }
//            }
//            temp_y += 30;
//            circle.setFrameFromCenter(horizontal_align, temp_y,
//                    horizontal_align + radius,
//                    temp_y + radius);
//            g2.fill(circle);
//            g2.setColor(Color.black);
//            g2.draw(circle);
//        }

    }

    private boolean noNeedForAlarm(Alarm alarm) {
        if (alarm.getIndex() == null)
            return false;

        Integer value = alarm.getIndex().getValue();
        return value == null || value == 0;
    }

    JLabel load_voltage_label = new JLabel();
    JLabel load_current_label = new JLabel();
    JLabel voltage_value_label = new JLabel();
    JLabel current_value_label = new JLabel();

    public void update_panel() {

    }

    @Override
    public void stateChanged(final ChangeEvent e) {
        if (SwingUtilities.isEventDispatchThread()) {
            this.removeAll();
            putElementsToUI();
            repaint();
        } else SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                stateChanged(e);
            }
        });
    }
}
