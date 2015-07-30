package uku_control;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
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
public class UKU_Control_Panel_SNMP extends Abstract_spanel {

    private UKU_Data_Big data;
    public Event_Viewer event_viewer;

    public UKU_Control_Panel_SNMP(UKU_Data_Big data) {
        this.data = data;
        this.event_viewer = new Event_Viewer(data);
        //viewer = new Event_Viewer(data);
        set_bps_button.addActionListener(new
                                         UKU_Control_Panel_Big_set_bps_button_actionAdapter_SNMP(this));

        disable_bps_button.addActionListener(new
                                             UKU_Control_Panel_Big_disable_bps_button_actionAdapter_SNMP(this));
        compensation_charge_button.addActionListener(new
                UKU_Control_Panel_Big_compensation_charge_button_actionAdapter_SNMP(this));

        capacity_control_button.addActionListener(new
                                                  UKU_Control_Panel_Big_capacity_control_button_actionAdapter_SNMP(this));
        disable_specfunctions_button.addActionListener(new
                UKU_Control_Panel_Big_disable_specfunctions_button_actionAdapter_SNMP(this));
        call_alarm_journal_button.addActionListener(new
                UKU_Control_Panel_Big_call_alarm_journal_button_actionAdapter_SNMP(this));
        disable_parallel_button.addActionListener(new
                                                  UKU_Control_Panel_Big_disable_parallel_button_actionAdapter_SNMP(this));
        enable_parallel_button.addActionListener(new
                                                 UKU_Control_Panel_Big_enable_parallel_button_actionAdapter_SNMP(this));
        unlock_psu_button.addActionListener(new
                                            UKU_Control_Panel_Big_unlock_psu_button_actionAdapter_SNMP(this));
        radio_status_view_select.addActionListener(new
                UKU_Control_Panel_Big_radio_status_view_select_actionAdapter_SNMP(this));
        radio_detailed_view_select.addActionListener(new
                UKU_Control_Panel_Big_radio_detailed_view_select_actionAdapter_SNMP(this));
        settings_menu.addActionListener(new
                                        UKU_Control_Panel_SNMP_settings_menu_actionAdapter(this));
        extio_panel_button.addActionListener(new
                                             UKU_Control_Panel_SNMP_extio_panel_button_actionAdapter(this));
        surface_decorator();
    }

    /**
     * surface_decorator
     */
    private void surface_decorator() {
        try {
            jbInit();
        } catch (Exception exception) {
            exception.printStackTrace();
        }

        for (int i = 1; i <= 24; i++)
            this.compensation_charge_combo.addItem(" " + Integer.toString(i) +
                    "ч.");
        for (int i = 1; i <= 255; i++)
            this.set_bps_combo.addItem(" " + Integer.toString(i));
        for (int i = 1; i <= 255; i++)
            this.disable_bps_combo.addItem(" " + Integer.toString(i));
        for (int i = 1; i <= 255; i++)
            this.capacity_control_combo.addItem(" " + Integer.toString(i));

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
        primary_psu.setBounds(new Rectangle(20, 51, 204, 41));
        set_bps_button.setBounds(new Rectangle(20, 91, 139, 23));
        set_bps_button.setFont(disable_bps_button.getFont());
        set_bps_button.setBackground(new Color(112, 177, 217));

        set_bps_button.setForeground(Color.white);
        set_bps_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        set_bps_button.setText("Установить");

        disable_psu.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 16));
        disable_psu.setForeground(new Color(112, 177, 217));
        disable_psu.setHorizontalAlignment(SwingConstants.LEFT);
        disable_psu.setText("Отключить блок питания:");

        disable_psu.setBounds(new Rectangle(20, 121, 204, 41));
        disable_bps_button.setBounds(new Rectangle(20, 161, 139, 23));
        disable_bps_button.setBackground(new Color(112, 177, 217));
        disable_bps_button.setForeground(Color.black);
        disable_bps_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
        disable_bps_button.setText("Отключить");

        specfunction_label.setFont(new java.awt.Font("Times New Roman",
                Font.BOLD, 16));
        specfunction_label.setForeground(new Color(112, 177, 217));
        specfunction_label.setHorizontalAlignment(SwingConstants.LEFT);
        specfunction_label.setText("Специальные функции:");

        int initial_offset = 305;
        specfunction_label.setBounds(new Rectangle(19, 292, 204, 41));
        compensation_charge_button.setBounds(new Rectangle(19, 336, 140, 23));
        capacity_control_button.setBounds(new Rectangle(19, 374, 140, 23));
        compensation_charge_combo.setBounds(new Rectangle(166, 336, 54, 23));
        disable_specfunctions_button.setBounds(new Rectangle(19, 411, 200, 23));

        compensation_charge_button.setBackground(new Color(112, 177, 217));
        compensation_charge_button.setForeground(Color.BLACK);
        compensation_charge_button.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));
        compensation_charge_button.setText("Выравнивающий заряд");
        compensation_charge_button.addActionListener(new
                UKU_Control_Panel_SNMP_compensation_charge_button_actionAdapter(this));

        compensation_charge_button.setFont(disable_bps_button.getFont());
        compensation_charge_combo.setForeground(new Color(117, 177, 217));
        compensation_charge_combo.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));

        compensation_charge_combo.setAutoscrolls(true);
        this.compensation_charge_combo.setUI(new BasicComboBoxUI());

        set_bps_combo.setBounds(new Rectangle(166, 91, 55, 23));
        set_bps_combo.setForeground(new Color(117, 177, 217));
        set_bps_combo.setUI(new BasicComboBoxUI());
        set_bps_combo.setFont(disable_bps_button.getFont());
        set_bps_combo.setForeground(new Color(117, 177, 217));
        set_bps_combo.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));

        set_bps_combo.setAutoscrolls(true);

        disable_bps_combo.setBounds(new Rectangle(166, 161, 55, 23));
        compensation_charge_button.setFont(disable_bps_button.getFont());
        disable_bps_combo.setForeground(new Color(117, 177, 217));
        disable_bps_combo.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));

        disable_bps_combo.setAutoscrolls(true);
        this.disable_bps_combo.setUI(new BasicComboBoxUI());

        capacity_control_combo.setBounds(new Rectangle(166, 374, 54, 23));
        capacity_control_combo.setForeground(new Color(117, 177, 217));
        capacity_control_combo.setBorder(BorderFactory.createLineBorder(
                Color.BLUE));

        capacity_control_combo.setAutoscrolls(true);
        this.capacity_control_combo.setUI(new BasicComboBoxUI());

        capacity_control_button.setFont(disable_bps_button.getFont());
        capacity_control_button.setBackground(new Color(112, 177, 217));
        capacity_control_button.setForeground(Color.BLACK);
        capacity_control_button.setBorder(BorderFactory.createLineBorder(Color.
                BLUE));
        capacity_control_button.setText("Контроль емкости");

        promo_label.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 14));
        promo_label.setForeground(new Color(120, 212, 255));
        promo_label.setHorizontalAlignment(SwingConstants.CENTER);
        promo_label.setHorizontalTextPosition(SwingConstants.CENTER);
        promo_label.setText("ООО \"Системы промавтоматики\"");
        promo_label.setVerticalAlignment(SwingConstants.BOTTOM);
        promo_label.setBounds(new Rectangle(6, 630, 235, 41));
        disable_specfunctions_button.setBackground(new Color(112, 177, 217));
        disable_specfunctions_button.setFont(this.disable_bps_button.getFont());
        disable_specfunctions_button.setForeground(Color.BLACK);
        disable_specfunctions_button.setBorder(BorderFactory.createLineBorder(
                Color.
                BLUE));
        disable_specfunctions_button.setText("Выключение спецфункций");

        alarm_journal.setFont(new java.awt.Font("Times New Roman", Font.BOLD,
                                                16));
        alarm_journal.setForeground(new Color(112, 177, 217));
        alarm_journal.setHorizontalAlignment(SwingConstants.LEFT);
        alarm_journal.setText("Журнал аварий:");
        alarm_journal.setBounds(new Rectangle(19, 442, 204, 41));
        call_alarm_journal_button.setBackground(new Color(112, 177, 217));
        call_alarm_journal_button.setBounds(new Rectangle(19, 484, 200, 23));
        call_alarm_journal_button.setForeground(Color.BLACK);
        call_alarm_journal_button.setBorder(BorderFactory.createLineBorder(
                Color.blue));
        call_alarm_journal_button.setText("Вызвать журнал аварий");
        call_alarm_journal_button.addActionListener(new
                UKU_Control_Panel_SNMP_call_alarm_journal_button_actionAdapter(this));

        disable_parallel_button.setBackground(new Color(112, 177, 217));
        disable_parallel_button.setBounds(new Rectangle(20, 260, 200, 23));
        disable_parallel_button.setForeground(Color.white);
        disable_parallel_button.setBorder(BorderFactory.createLineBorder(Color.
                blue));
        disable_parallel_button.setText("Выкл. параллельную работу");

        enable_parallel_button.setBackground(new Color(112, 177, 217));
        enable_parallel_button.setBounds(new Rectangle(20, 229, 200, 23));
        enable_parallel_button.setForeground(Color.white);
        enable_parallel_button.setBorder(BorderFactory.createLineBorder(Color.
                blue));
        enable_parallel_button.setText("Вкл. параллельную работу");

        unlock_psu_button.setBackground(new Color(112, 177, 217));
        unlock_psu_button.setBounds(new Rectangle(20, 197, 200, 23));
        unlock_psu_button.setForeground(Color.BLACK);
        unlock_psu_button.setBorder(BorderFactory.createLineBorder(Color.blue));
        unlock_psu_button.setText("Разблокировать источники");

        jLabel1.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 16));
        jLabel1.setForeground(new Color(112, 177, 217));
        jLabel1.setHorizontalAlignment(SwingConstants.LEFT);
        jLabel1.setText("Внешний вид параметров:");
        jLabel1.setBounds(new Rectangle(19, 521, 204, 41));
        radio_status_view_select.setBackground(new Color(230, 255, 255));
        radio_status_view_select.setFont(new java.awt.Font("Times New Roman",
                Font.BOLD, 16));
        radio_status_view_select.setForeground(new Color(112, 177, 217));
        radio_status_view_select.setSelected(false);
        radio_status_view_select.setText("Общий");
        radio_status_view_select.setBounds(new Rectangle(19, 556, 199, 26));

        radio_detailed_view_select.setBackground(new Color(230, 255, 255));
        radio_detailed_view_select.setFont(new java.awt.Font("Times New Roman",
                Font.BOLD,
                16));
        radio_detailed_view_select.setForeground(new Color(112, 177, 217));
        radio_detailed_view_select.setSelected(true);
        radio_detailed_view_select.setText("Детальный");
        radio_detailed_view_select.setBounds(new Rectangle(19, 583, 199, 26));

        radio_false_button.setVisible(false);
        radio_false_button.setEnabled(false);
        radio_false_button.setText("jRadioButton1");
        radio_false_button.setBounds(new Rectangle(22, 608, 196, 32));

        settings_menu.setBackground(new Color(112, 177, 217));
        settings_menu.setForeground(Color.black);
        settings_menu.setBorder(BorderFactory.createLineBorder(Color.blue));
        settings_menu.setActionCommand("Меню установок");
        settings_menu.setText("Меню установок");

        extio_panel_button.setBackground(new Color(112, 177, 217));
        extio_panel_button.setBounds(new Rectangle(133, 615, 87, 25));
        extio_panel_button.setForeground(Color.white);
        extio_panel_button.setBorder(BorderFactory.createLineBorder(Color.
                blue));
        extio_panel_button.setActionCommand("Внешние ИУ");
        extio_panel_button.setText("Внешние ИУ");

        if (data.extio_count.get() == 0) {
            settings_menu.setBounds(new Rectangle(19, 615, 196, 25));
        } else {
            settings_menu.setBounds(new Rectangle(19, 615, 109, 25));
            this.add(extio_panel_button);
        }
        this.add(main_control_label);
        this.add(promo_label);
        this.add(primary_psu);
        this.add(set_bps_button);
        this.add(disable_psu);
        this.add(disable_bps_button);
        this.add(set_bps_combo);
        this.add(disable_bps_combo);
        this.add(unlock_psu_button);
        this.add(enable_parallel_button);
        this.add(disable_parallel_button);
        this.add(compensation_charge_combo);
        this.add(capacity_control_button);
        this.add(disable_specfunctions_button);
        this.add(capacity_control_combo);
        this.add(compensation_charge_button);
        this.add(specfunction_label);
        this.add(alarm_journal);
        this.add(call_alarm_journal_button);
        this.add(jLabel1);
        this.add(radio_status_view_select);
        this.add(radio_detailed_view_select);
        this.add(radio_false_button);
        this.add(settings_menu);

        buttonGroup1.add(radio_status_view_select);
        buttonGroup1.add(radio_detailed_view_select);
        buttonGroup1.add(radio_false_button);
    }

    JLabel main_control_label = new JLabel();
    JLabel disable_psu = new JLabel();
    JButton disable_bps_button = new JButton();
    JLabel primary_psu = new JLabel();
    JButton set_bps_button = new JButton();
    JLabel specfunction_label = new JLabel();
    JButton compensation_charge_button = new JButton();
    JComboBox compensation_charge_combo = new JComboBox();
    JButton capacity_control_button = new JButton();
    JLabel promo_label = new JLabel();
    JButton disable_specfunctions_button = new JButton();
    JLabel alarm_journal = new JLabel();
    JButton call_alarm_journal_button = new JButton();
    private Event_Viewer viewer;
    JComboBox set_bps_combo = new JComboBox();
    JComboBox disable_bps_combo = new JComboBox();
    JComboBox capacity_control_combo = new JComboBox();
    JButton disable_parallel_button = new JButton();
    JButton enable_parallel_button = new JButton();
    JButton unlock_psu_button = new JButton();
    JLabel jLabel1 = new JLabel();
    JRadioButton radio_status_view_select = new JRadioButton();
    ButtonGroup buttonGroup1 = new ButtonGroup();
    JRadioButton radio_detailed_view_select = new JRadioButton();
    JButton settings_menu = new JButton();
    JRadioButton radio_false_button = new JRadioButton();
    JButton extio_panel_button = new JButton();

    public void capacity_control_8actionPerformed(ActionEvent e) {
        String pass = JOptionPane.showInputDialog(null, "Пароль",
                                                  "Необходима авторизация",
                                                  JOptionPane.WARNING_MESSAGE);
        if (pass != null)
            if (pass.equals(new String("127"))) {
            }
    }

    public void radio_status_view_select_actionPerformed(ActionEvent e) {
        data.current_view.set(data.STATUS_VIEW);
    }

    public void radio_detailed_view_select_actionPerformed(ActionEvent e) {
        data.current_view.set(data.DETAILS_VIEW);
    }

    public void update_panel() {
        if (data.need_correct_interface_control.get() == 1) {
            this.removeAll();
            this.surface_decorator();
            if (data.show_warning_table.get() == 1) {
                JOptionPane.showMessageDialog(this,
                                              "Невозможно выполнить команду",
                                              "Предупреждение",
                                              JOptionPane.WARNING_MESSAGE);
                data.show_warning_table.set(0);
            }

            if (data.show_warning_table_timeout.get() == 1) {
                JOptionPane.showMessageDialog(this,
                                              "Невозможно выполнить команду (нет ответа)",
                                              "Предупреждение",
                                              JOptionPane.WARNING_MESSAGE);
                data.show_warning_table_timeout.set(0);
            }

            boolean value = (data.show_primary_bpss.get() == 1) ? true : false;
            this.primary_psu.setVisible(value);
            this.set_bps_button.setVisible(value);
            this.set_bps_combo.setVisible(value);
            set_bps_combo.removeAllItems();
            disable_bps_combo.removeAllItems();
            capacity_control_combo.removeAllItems();

            value = (data.show_parallel_operation.get() == 0) ? true : false;
            this.enable_parallel_button.setVisible(value);
            this.disable_parallel_button.setVisible(value);

            value = (data.show_events_journal.get() == 0) ? true : false;
            this.call_alarm_journal_button.setVisible(value);
            this.alarm_journal.setVisible(value);

            for (int i = 1; i <= data.psus_count.get(); i++) {
                this.set_bps_combo.addItem(" " + Integer.toString(i));
                this.disable_bps_combo.addItem(" " + Integer.toString(i));
            }
            for (int i = 1; i <= data.batteries_count.get(); i++)
                this.capacity_control_combo.addItem(" " + Integer.toString(i));
            data.need_correct_interface_control.set(0);
            this.repaint();
        }
        if (data.need_correct_alarm_viewer.get() == 1) {
            this.event_viewer.update_viewer();
            data.need_correct_alarm_viewer.set(0);
        }
    }

    public void set_bps_button_actionPerformed(ActionEvent e) {
        int temp = this.set_bps_combo.getSelectedIndex() + 1;
        data.lifo.add((new Command_SNMP(Command_Handler.SET_ACTIVE_BPS, temp)));
    }

    public void disable_bps_button_actionPerformed(ActionEvent e) {
        int temp = this.disable_bps_combo.getSelectedIndex() + 1;
        data.lifo.add((new Command_SNMP(Command_Handler.DISABLE_BPS, temp)));
    }

    public void unlock_psu_button_actionPerformed(ActionEvent e) {
        data.lifo.add((new Command_SNMP(Command_Handler.UNLOCK_BPSS, 0)));
    }

    public void enable_parallel_button_actionPerformed(ActionEvent e) {
        data.lifo.add((new Command_SNMP(Command_Handler.
                                        ENABLE_PARRALEL_OPERATION, 0)));
    }

    public void disable_parallel_button_actionPerformed(ActionEvent e) {
        data.lifo.add((new Command_SNMP(Command_Handler.
                                        DISABLE_PARRALEL_OPERATION, 0)));
    }

    public void compensation_charge_button_actionPerformed(ActionEvent e) {
        int temp = this.compensation_charge_combo.getSelectedIndex() + 1;
        data.lifo.add((new Command_SNMP(Command_Handler.
                                        ENABLE_COMPENSATION_CHARGE, temp)));
    }

    public void capacity_control_button_actionPerformed(ActionEvent e) {
        String pass = JOptionPane.showInputDialog(null, "Пароль",
                                                  "Необходима авторизация",
                                                  JOptionPane.WARNING_MESSAGE);
        int temp = capacity_control_combo.getSelectedIndex() + 1;
        if (pass != null)
            if (pass.equals(new String("127"))) {
                data.lifo.add((new Command_SNMP(Command_Handler.
                                                ENABLE_CAPACITY_CONTROL, temp)));
            } else
                JOptionPane.showMessageDialog(null, "Пароль неверный!",
                                              "Необходима авторизация",
                                              JOptionPane.WARNING_MESSAGE);

    }

    public void disable_specfunctions_button_actionPerformed(ActionEvent e) {
        data.lifo.add((new Command_SNMP(Command_Handler.
                                        DISABLE_SPECIAL_FUNCTIONS, 0)));
    }

    public void call_alarm_journal_button_actionPerformed(ActionEvent e) {
        data.lifo.add((new Command_SNMP(Command_Handler.GET_EVENTS_QUANTITY, 0)));
        //data.command_need_to_get_all_events.set(1);
        this.event_viewer.show_events();
    }

    public void settings_menu_actionPerformed(ActionEvent e) {

        String pass = JOptionPane.showInputDialog(null, "Пароль",
                                                  "Необходима авторизация",
                                                  JOptionPane.WARNING_MESSAGE);
        if (pass != null)
            if (pass.equals(new String("127"))) {
                data.lifo.add((new Command_SNMP(Command_Handler.
                                                GET_SETTINGS_TABLE, 0)));
                this.radio_false_button.setSelected(true);
                data.current_view.set(data.SPARAMS_VIEW);
                data.command_need_to_get_all_sparams.set(1);
            } else {
                JOptionPane.showMessageDialog(null, "Пароль неверный!",
                                              "Необходима авторизация",
                                              JOptionPane.WARNING_MESSAGE);
            }

    }

    /**
     * SSetings_action_performed
     *
     * @param e ActionEvent
     */
    public void SSetings_action_performed(ActionEvent e) {
    }

    public void extio_panel_button_actionPerformed(ActionEvent e) {
        String pass = JOptionPane.showInputDialog(null, "Пароль",
                                                  "Необходима авторизация",
                                                  JOptionPane.WARNING_MESSAGE);
        if (pass != null)
            if (pass.equals(new String("127"))) {
                this.radio_false_button.setSelected(true);
                data.current_view.set(data.EXTIO_VIEW);
            } else {
                JOptionPane.showMessageDialog(null, "Пароль неверный!",
                                              "Необходима авторизация",
                                              JOptionPane.WARNING_MESSAGE);
            }
    }


}


class UKU_Control_Panel_SNMP_call_alarm_journal_button_actionAdapter implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_SNMP_call_alarm_journal_button_actionAdapter(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.call_alarm_journal_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_SNMP_compensation_charge_button_actionAdapter implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_SNMP_compensation_charge_button_actionAdapter(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.compensation_charge_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_SNMP_disable_bps_button_actionAdapter implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_SNMP_disable_bps_button_actionAdapter(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.disable_bps_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_SNMP_settings_menu_actionAdapter implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_SNMP_settings_menu_actionAdapter(UKU_Control_Panel_SNMP
            adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.settings_menu_actionPerformed(e);
    }
}


class UKU_Control_Panel_SNMP_extio_panel_button_actionAdapter implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_SNMP_extio_panel_button_actionAdapter(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.extio_panel_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_call_alarm_journal_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_call_alarm_journal_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.call_alarm_journal_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_disable_specfunctions_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_disable_specfunctions_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.disable_specfunctions_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_capacity_control_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_capacity_control_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.capacity_control_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_compensation_charge_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_compensation_charge_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.compensation_charge_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_disable_parallel_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_disable_parallel_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.disable_parallel_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_enable_parallel_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_enable_parallel_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.enable_parallel_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_unlock_psu_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_unlock_psu_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP
            adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.unlock_psu_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_disable_bps_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_disable_bps_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.disable_bps_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_set_bps_button_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_set_bps_button_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP
            adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.set_bps_button_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_radio_detailed_view_select_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_radio_detailed_view_select_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.radio_detailed_view_select_actionPerformed(e);
    }
}


class UKU_Control_Panel_Big_radio_status_view_select_actionAdapter_SNMP implements
        ActionListener {
    private UKU_Control_Panel_SNMP adaptee;
    UKU_Control_Panel_Big_radio_status_view_select_actionAdapter_SNMP(
            UKU_Control_Panel_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.radio_status_view_select_actionPerformed(e);
    }
}

