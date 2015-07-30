package uku_control;

import javax.swing.*;
import java.awt.Rectangle;
import java.awt.Font;
import java.awt.Color;
import java.awt.SystemColor;
import java.awt.*;
import java.awt.geom.Ellipse2D;


/**
 * <p>Title: Ultimate monitor</p>
 *
 * <p>Description: universal monitoring system</p>
 *
 * <p>Copyright: Copyright (c) 2008</p>
 *
 * <p>Company: Lantis</p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Status_Panel_Big extends UKU_Panel {

    private UKU_Data_Big data;
    private int horizontal_align = 125;
    private int vertical_align = 250;
    private int radius = 7;
    private int label_offset_x = 15;
    private int label_offset_y = -15;


    public UKU_Status_Panel_Big() {
    }

    public UKU_Status_Panel_Big(UKU_Data_Big data) {
        this.desired_height = 680;
        this.desired_width = 480;
        this.data = data;
        UIManager.put("JPanel.background", new Color(240, 255, 255));
        this.setLayout(null);
        this.setMaximumSize(new Dimension(this.desired_width, this.desired_height));
        this.setBounds(0,0,this.desired_width, this.desired_height);

        surface_decorator();
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int temp_y = this.vertical_align;
        Graphics2D g2 = (Graphics2D) g;
        Ellipse2D circle = new Ellipse2D.Double();
        circle.setFrameFromCenter(horizontal_align, temp_y,
                                  horizontal_align + radius, temp_y + radius);

        if (data.power_main.get_alarm() == 0)
            g2.setColor(Color.GREEN);
        else
            g2.setColor(Color.RED);
        g2.fill(circle);
        g2.setColor(Color.black);
        g2.draw(circle);

        g2.setColor(Color.GREEN);
        if (data.psus_count.get() > 0) {
            for (int i = 0; i < data.psus_count.get(); i++) {
                if (data.psus_array[i].get_alarm() != 0) {
                    g2.setColor(Color.RED);
                    i = 300;
                }
            }
            temp_y += 30;
            circle.setFrameFromCenter(horizontal_align, temp_y,
                                      horizontal_align + radius,
                                      temp_y + radius);
            g2.fill(circle);
            g2.setColor(Color.black);
            g2.draw(circle);
        }
        g2.setColor(Color.GREEN);
        if (data.batteries_count.get() > 0) {
            for (int i = 0; i < data.batteries_count.get(); i++) {
                if (data.batteries_array[i].get_alarm() != 0) {
                    g2.setColor(Color.RED);
                    i = 300;
                }
            }
            temp_y += 30;
            circle.setFrameFromCenter(horizontal_align, temp_y,
                                      horizontal_align + radius,
                                      temp_y + radius);
            g2.fill(circle);
            g2.setColor(Color.black);
            g2.draw(circle);
        }
        g2.setColor(Color.GREEN);
        if (data.invertors_count.get() > 0) {
        }
        g2.setColor(Color.GREEN);
        if (data.external_temperature_count.get() > 0) {
           /* for (int i = 0; i < data.external_temperature_count.get(); i++) {
                if (data.external_temperature_array[i].get_alarm() != 0) {
                    g2.setColor(Color.RED);
                    i = 300;
                }
            }*/
            temp_y += 30;
            circle.setFrameFromCenter(horizontal_align, temp_y,
                                      horizontal_align + radius,
                                      temp_y + radius);
            g2.fill(circle);
            g2.setColor(Color.black);
            g2.draw(circle);
        }
        g2.setColor(Color.GREEN);

        if (data.external_jumper_count.get() > 0) {
            for (int i = 0; i < data.external_jumper_count.get(); i++) {
                if (data.external_jumper_array[i].get() != 0) {
                    g2.setColor(Color.RED);
                    i = 300;
                }
            }
            temp_y += 30;
            circle.setFrameFromCenter(horizontal_align, temp_y,
                                      horizontal_align + radius,
                                      temp_y + radius);
            g2.fill(circle);
            g2.setColor(Color.black);
            g2.draw(circle);
        }

    }

    public static void main(String[] args) {
        UKU_Data_Big data = new UKU_Data_Big();

        UKU_Status_Panel_Big panel = new UKU_Status_Panel_Big(data);
        JFrame frame = new JFrame();

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(480, 680);
        frame.getContentPane().add(panel);
        frame.setVisible(true);
        while (true){
            data.psus_array[1].status.set(0x00);
            data.batteries_array[3].status.set(0);
            data.external_jumper_array[1].set(0);
           // data.external_temperature_array[1].set_alarm(0);
            data.power_main.status.set(0);
            data.psus_count.set(10);
            data.batteries_count.set(3);
            data.external_jumper_count.set(10);
            data.external_temperature_count.set(10);
            panel.update_panel();
            try {
                Thread.sleep(1500);
            } catch (InterruptedException ex) {
            }
            data.psus_count.set(0);
            data.batteries_count.set(0);
            data.external_jumper_count.set(0);
            data.external_temperature_count.set(0);
            panel.update_panel();
            try {
                Thread.sleep(1500);
            } catch (InterruptedException ex) {
            }
            data.power_main.status.set(1);
            data.psus_count.set(30);
            data.psus_array[1].status.set(0x02);
            data.batteries_array[3].status.set(1);
            data.external_jumper_array[1].set(1);
            data.external_temperature_count.set(30);
         //   data.external_temperature_array[1].set_alarm(1);

            data.batteries_count.set(30);
            data.external_temperature_count.set(30);
            data.external_jumper_count.set(30);
            panel.update_panel();
            try {
                Thread.sleep(1500);
            } catch (InterruptedException ex) {
            }

        }
    }

    public void surface_decorator() {

        //this.removeAll();
        int temp_y = this.vertical_align;

        this.add(load_voltage_label);
        this.add(load_current_label);
        this.add(voltage_value_label);
        this.add(current_value_label);
        this.add(power_main_label);

        power_main_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
        power_main_label.setText("Первичная сеть");
        power_main_label.setBounds(new Rectangle(this.horizontal_align +
                                        this.label_offset_x,
                                        temp_y + this.label_offset_y,
                                        157, 30));
        if (data.psus_count.get() > 0) {
            temp_y += 30;
            psu_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
            psu_label.setText("Блоки питания");
            psu_label.setBounds(new Rectangle(this.horizontal_align +
                                            this.label_offset_x,
                                            temp_y +
                                            this.label_offset_y, 157, 30));
            this.add(psu_label);
        }
        if (data.batteries_count.get() > 0) {
            temp_y += 30;
            batteries_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
            batteries_label.setText("Аккумуляторные батареи");
            batteries_label.setBounds(new Rectangle(this.horizontal_align +
                                            this.label_offset_x,
                                            temp_y + this.label_offset_y, 238,
                                            30));
            this.add(batteries_label);
        }
        if (data.invertors_count.get() > 0) {
            temp_y += 30;
            invertors_label.setText("Инверторы");
            invertors_label.setBounds(new Rectangle(this.horizontal_align +
                                            this.label_offset_x,
                                            temp_y + this.label_offset_y, 157,
                                            30));
            this.add(invertors_label);
            invertors_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
        }

        if (data.external_temperature_count.get() > 0) {
            temp_y += 30;
            ext_temp_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
            ext_temp_label.setText("Датчики температуры");
            ext_temp_label.setBounds(new Rectangle(this.horizontal_align +
                                            this.label_offset_x,
                                            temp_y + this.label_offset_y, 218,
                                            30));
            this.add(ext_temp_label);
        }
        if (data.external_jumper_count.get() > 0) {
            temp_y += 30;
            ext_logic_label.setFont(new java.awt.Font("Times New Roman", Font.PLAIN, 20));
            ext_logic_label.setText("Логические входы");
            ext_logic_label.setBounds(new Rectangle(this.horizontal_align +
                                            this.label_offset_x,
                                            temp_y + this.label_offset_y, 157,
                                            30));
            this.add(ext_logic_label);
        }
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
        voltage_value_label.setText("Uн = " + data.load.voltage.get_textual() + " В");
        voltage_value_label.setBounds(new Rectangle(0, 74, 480, 30));
        this.setBackground(new Color(240, 255, 255));
        current_value_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 24));
        current_value_label.setForeground(new Color(0, 139, 117));
        current_value_label.setHorizontalAlignment(SwingConstants.CENTER);
        current_value_label.setHorizontalTextPosition(SwingConstants.CENTER);
        current_value_label.setText("Iн = " + data.load.current.get_textual() +" А");
        current_value_label.setBounds(new Rectangle(1, 140, 480, 30));

    }

    JLabel power_main_label = new JLabel();
    JLabel invertors_label = new JLabel();
    JLabel psu_label = new JLabel();
    JLabel batteries_label = new JLabel();
    JLabel ext_temp_label = new JLabel();
    JLabel ext_logic_label = new JLabel();
    JLabel load_voltage_label = new JLabel();
    JLabel load_current_label = new JLabel();
    JLabel voltage_value_label = new JLabel();
    JLabel current_value_label = new JLabel();

    public void update_panel() {
        if (data.need_correct_interface_status.get() == 1){
          //  b.removeAll();
            this.removeAll();
            this.surface_decorator();
            data.need_correct_interface_status.set(0);
        }
        voltage_value_label.setText("Uн = " + data.load.voltage.get_textual() + " В");
        current_value_label.setText("Iн = " + data.load.current.get_textual() +" А");
        this.repaint();

    }
}
