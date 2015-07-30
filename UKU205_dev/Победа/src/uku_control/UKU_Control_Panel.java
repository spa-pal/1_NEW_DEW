package uku_control;

import java.awt.*;

import javax.swing.*;
import java.awt.Rectangle;
import java.awt.Font;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import java.awt.Color;
import javax.swing.plaf.ComboBoxUI;
import javax.swing.plaf.basic.BasicComboBoxUI;

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
public class UKU_Control_Panel extends JPanel {

    private UKU_Data data;

    public UKU_Control_Panel(UKU_Data data) {
        this.data = data;
 //       viewer = new Event_Viewer(data);
        try {
            jbInit();
        } catch (Exception exception) {
            exception.printStackTrace();
        }

        for (int i = 1; i <= 24; i++)
            this.compensation_charge_combo.addItem(Integer.toString(i) + "ч.");
    }

    private void jbInit() throws Exception {
        this.setLayout(null);
        this.setBackground(new Color(230, 255, 255));
        this.setMaximumSize(new Dimension(250, UKU_Panel.desired_height));
        this.setMinimumSize(new Dimension(250, UKU_Panel.desired_height));
        this.setPreferredSize(new Dimension(250, UKU_Panel.desired_height));
        this.setToolTipText("");
        int button_width = 75;
        int button_height = 23;

        main_control_label.setFont(new java.awt.Font("Times New Roman",
                Font.BOLD, 24));
        main_control_label.setForeground(new Color(112, 177, 217));
        main_control_label.setMaximumSize(new Dimension(130, 28));
        main_control_label.setMinimumSize(new Dimension(130, 28));
        main_control_label.setPreferredSize(new Dimension(130, 28));
        main_control_label.setHorizontalAlignment(SwingConstants.CENTER);
        main_control_label.setHorizontalTextPosition(SwingConstants.CENTER);
        main_control_label.setText("Управление");
        main_control_label.setBounds(new Rectangle(30, 10, 180, 40));
        primary_psu.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 16));
        primary_psu.setForeground(new Color(112, 177, 217));
        primary_psu.setHorizontalAlignment(SwingConstants.LEFT);
        primary_psu.setText("Установить основной БПС:");
        int initial_offset_y = 75;
        disable_bps_1.setFont(new java.awt.Font("Tahoma", Font.PLAIN, 11));
        primary_psu.setBounds(new Rectangle(20, initial_offset_y, 204, 41));
        set_bps_1.setBounds(new Rectangle(30, initial_offset_y + 40,
                                          button_width, button_height));
        set_bps_2.setBounds(new Rectangle(135, initial_offset_y + 40,
                                          button_width, button_height));

        set_bps_2.setFont(disable_bps_1.getFont());
        set_bps_2.setBackground(new Color(112, 177, 217));

        set_bps_2.setForeground(Color.white);
        set_bps_2.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        set_bps_2.setText("БПС-2");
        set_bps_1.setFont(disable_bps_1.getFont());
        set_bps_1.setBackground(new Color(112, 177, 217));

        set_bps_1.setForeground(Color.white);
        set_bps_1.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        set_bps_1.setText("БПС-1");
        disable_psu.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 16));
        disable_psu.setForeground(new Color(112, 177, 217));
        disable_psu.setHorizontalAlignment(SwingConstants.LEFT);
        disable_psu.setText("Отключить блок питания:");

        disable_psu.setBounds(new Rectangle(20, initial_offset_y + 70, 204, 41));
        disable_bps_1.setBounds(new Rectangle(30, initial_offset_y + 110, 75,
                                              23));
        disable_bps_2.setBounds(new Rectangle(135, initial_offset_y + 110, 75,
                                              23));

        disable_bps_1.setBackground(new Color(112, 177, 217));
        disable_bps_1.setForeground(Color.white);
        disable_bps_1.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        disable_bps_1.setText("БПС-1");

        disable_bps_2.setFont(disable_bps_1.getFont());
        disable_bps_2.setBackground(new Color(112, 177, 217));
        disable_bps_2.setForeground(Color.white);
        disable_bps_2.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        disable_bps_2.setText("БПС-2");
        specfunction_label.setFont(new java.awt.Font("Times New Roman",
                Font.BOLD, 16));
        specfunction_label.setForeground(new Color(112, 177, 217));
        specfunction_label.setHorizontalAlignment(SwingConstants.LEFT);
        specfunction_label.setText("Специальные функции:");

        int initial_offset = 305;
        specfunction_label.setBounds(new Rectangle(20, 220, 204, 41));
        compensation_charge.setBounds(new Rectangle(20, 269, 140, 23));
        capacity_control.setBounds(new Rectangle(20, 307, 200, 23));
        compensation_charge_combo.setBounds(new Rectangle(167, 269, 54, 23));
        disable_specfunctions.setBounds(new Rectangle(20, 344, 200, 23));

        compensation_charge.setBackground(new Color(112, 177, 217));
        compensation_charge.setForeground(Color.white);
        compensation_charge.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        compensation_charge.setText("Выравнивающий заряд");
        compensation_charge.setFont(disable_bps_1.getFont());
        compensation_charge_combo.setForeground(new Color(117, 177, 217));
        compensation_charge_combo.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));

        compensation_charge_combo.setAutoscrolls(true);
        this.compensation_charge_combo.setUI(new User_ComboBoxUI());
        capacity_control.setFont(disable_bps_1.getFont());
        capacity_control.setBackground(new Color(112, 177, 217));
        capacity_control.setForeground(Color.white);
        capacity_control.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        capacity_control.setText("Контроль емкости");
        promo_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 14));
        promo_label.setForeground(new Color(120, 212, 255));
        promo_label.setHorizontalAlignment(SwingConstants.CENTER);
        promo_label.setHorizontalTextPosition(SwingConstants.CENTER);
        promo_label.setText("ООО \"Системы промавтоматики\"");
        promo_label.setVerticalAlignment(SwingConstants.BOTTOM);
        promo_label.setBounds(new Rectangle(6, 630, 235, 41));
        disable_specfunctions.setBackground(new Color(112, 177, 217));
        disable_specfunctions.setFont(this.disable_bps_1.getFont());
        disable_specfunctions.setForeground(Color.white);
        disable_specfunctions.setBorder(BorderFactory.createLineBorder(Color.
                BLUE));
        disable_specfunctions.setText("Выключение спецфункций");
        alarm_journal.setFont(new java.awt.Font("Times New Roman", Font.BOLD,
                                                16));
        alarm_journal.setForeground(new Color(112, 177, 217));
        alarm_journal.setHorizontalAlignment(SwingConstants.LEFT);
        alarm_journal.setText("Журнал событий:");
        alarm_journal.setBounds(new Rectangle(20, 383, 204, 41));
        call_alarm_journal_button.setBackground(new Color(112, 177, 217));
        call_alarm_journal_button.setBounds(new Rectangle(20, 431, 200, 23));
        call_alarm_journal_button.setForeground(Color.white);
        call_alarm_journal_button.setBorder(BorderFactory.createLineBorder(
                Color.black));
        call_alarm_journal_button.setText("Вызвать журнал событий");
        this.add(main_control_label);
        this.add(primary_psu);
        this.add(set_bps_1);
        this.add(set_bps_2);
        this.add(disable_psu);
        this.add(disable_bps_1);
        this.add(disable_bps_2);
        this.add(promo_label);
        this.add(specfunction_label);
        this.add(compensation_charge);
        this.add(compensation_charge_combo);
        this.add(capacity_control);
        this.add(disable_specfunctions);
        this.add(alarm_journal);
        this.add(call_alarm_journal_button);
    }

    JLabel main_control_label = new JLabel();
    JLabel disable_psu = new JLabel();
    JButton disable_bps_1 = new JButton();
    JButton set_bps_2 = new JButton();
    JLabel primary_psu = new JLabel();
    JButton disable_bps_2 = new JButton();
    JButton set_bps_1 = new JButton();
    JLabel specfunction_label = new JLabel();
    JButton compensation_charge = new JButton();
    JComboBox compensation_charge_combo = new JComboBox();
    JButton capacity_control = new JButton();
    JLabel promo_label = new JLabel();
    JButton disable_specfunctions = new JButton();
    JLabel alarm_journal = new JLabel();
    JButton call_alarm_journal_button = new JButton();
    private Event_Viewer viewer;

    public void jButton1_actionPerformed(ActionEvent e) {
        data.need_to_disable_bps.set(data.BPS_1);
    }

    public static void main(String args[]) {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        UKU_Control_Panel panel = new UKU_Control_Panel(new UKU_Data());
        frame.getContentPane().add(panel);
        frame.setSize(250, 720);
        frame.setVisible(true);

    }

    public void set_bps_1_actionPerformed(ActionEvent e) {
        data.need_to_switch_bps.set(data.BPS_1);
    }

    public void set_bps_2_actionPerformed(ActionEvent e) {
        data.need_to_switch_bps.set(data.BPS_2);
    }

    public void disable_bps_2_actionPerformed(ActionEvent e) {
        data.need_to_disable_bps.set(data.BPS_2);
    }

    public void compensation_charge_actionPerformed(ActionEvent e) {
        int temp = this.compensation_charge_combo.getSelectedIndex() + 1;
        data.need_to_enable_compensation_charge.set(temp);
    }

    public void capacity_control_actionPerformed(ActionEvent e) {
        String pass = JOptionPane.showInputDialog(null, "Пароль",
                                                  "Необходима авторизация",
                                                  JOptionPane.WARNING_MESSAGE);
        if (pass != null)
            if (pass.equals(new String("127"))) {
                data.need_to_enable_capacity_control.set(data.TRUE);
            }
    }

    public void disable_specfunctions_actionPerformed(ActionEvent e) {
        data.need_to_disable_special_function.set(2);
    }

    public void call_alarm_journal_button_actionPerformed(ActionEvent e) {
        viewer.show_events();

    }

}


class User_ComboBoxUI extends BasicComboBoxUI {

    User_ComboBoxUI() {
        super();

        //this.arrowButton.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        //this.arrowButton.setForeground(new Color(117, 177, 217));
    }
}


