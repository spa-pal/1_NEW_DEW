package uku_control;

import uku_control.config.*;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * <p>Title: UKU Control</p>
 * <p/>
 * <p>Description: </p>
 * <p/>
 * <p>Copyright: Anatoly (c) 2007</p>
 * <p/>
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.0
 */
public class UKU_Control_Panel_SNMP extends Abstract_spanel implements ChangeListener {

    private final UKU_Main_Panel_SNMP mainPanelSnmp;

    private Configuration configuration = Util.loadConfiguration();

    public UKU_Control_Panel_SNMP(UKU_Main_Panel_SNMP mainPanelSnmp) {
        this.mainPanelSnmp = mainPanelSnmp;
        radio_status_view_select.addActionListener(new SwitchPanelAdapter(UKU_Main_Panel_SNMP.STATUS_CARD));
        radio_detailed_view_select.addActionListener(new SwitchPanelAdapter(UKU_Main_Panel_SNMP.TABLE_VIEW));
        settings_menu.addActionListener(new SwitchPanelAdapter(UKU_Main_Panel_SNMP.SETTINGS));
        surface_decorator();
    }


    /**
     * surface_decorator
     */
    private void surface_decorator() {
        try {
            this.setLayout(null);
            this.setBackground(new Color(230, 255, 255));
            this.setMaximumSize(new Dimension(250, UKU_Panel.desired_height));
            this.setMinimumSize(new Dimension(250, UKU_Panel.desired_height));
            this.setPreferredSize(new Dimension(250, UKU_Panel.desired_height));
            this.setToolTipText("");

            main_control_label.setFont(new Font("Times New Roman",
                    Font.BOLD, 24));
            main_control_label.setForeground(new Color(112, 177, 217));
            main_control_label.setMaximumSize(new Dimension(130, 28));
            main_control_label.setMinimumSize(new Dimension(130, 28));
            main_control_label.setPreferredSize(new Dimension(130, 28));
            main_control_label.setHorizontalAlignment(SwingConstants.CENTER);
            main_control_label.setHorizontalTextPosition(SwingConstants.CENTER);
            main_control_label.setText("Управление");
            main_control_label.setBounds(new Rectangle(30, 10, 180, 40));
            primary_psu.setFont(new Font("Times New Roman", Font.BOLD, 16));
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


            disable_psu.setFont(new Font("Times New Roman", Font.BOLD, 16));
            disable_psu.setForeground(new Color(112, 177, 217));
            disable_psu.setHorizontalAlignment(SwingConstants.LEFT);
            disable_psu.setText("Отключить блок питания:");

            disable_psu.setBounds(new Rectangle(20, 121, 204, 41));
            disable_bps_button.setBounds(new Rectangle(20, 161, 139, 23));
            disable_bps_button.setBackground(new Color(112, 177, 217));
            disable_bps_button.setForeground(Color.white);
            disable_bps_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            disable_bps_button.setText("Отключить");


            specfunction_label.setFont(new Font("Times New Roman",
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
            compensation_charge_button.setForeground(Color.white);
            compensation_charge_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            compensation_charge_button.setText("Выравнивающий заряд");

            compensation_charge_button.setFont(disable_bps_button.getFont());
            compensation_charge_combo.setForeground(new Color(117, 177, 217));
            compensation_charge_combo.setBorder(BorderFactory.createLineBorder(
                    Color.BLUE));

            compensation_charge_combo.setAutoscrolls(true);
            this.compensation_charge_combo.setUI(new User_ComboBoxUI());

            set_bps_combo.setBounds(new Rectangle(166, 91, 55, 23));
            set_bps_combo.setForeground(new Color(117, 177, 217));
            set_bps_combo.setUI(new User_ComboBoxUI());
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
            this.disable_bps_combo.setUI(new User_ComboBoxUI());

            capacity_control_combo.setBounds(new Rectangle(166, 374, 54, 23));
            capacity_control_combo.setForeground(new Color(117, 177, 217));
            capacity_control_combo.setBorder(BorderFactory.createLineBorder(
                    Color.BLUE));

            capacity_control_combo.setAutoscrolls(true);
            this.capacity_control_combo.setUI(new User_ComboBoxUI());


            capacity_control_button.setFont(disable_bps_button.getFont());
            capacity_control_button.setBackground(new Color(112, 177, 217));
            capacity_control_button.setForeground(Color.white);
            capacity_control_button.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            capacity_control_button.setText("Контроль емкости");

            promo_label.setFont(new Font("Times New Roman", Font.BOLD, 14));
            promo_label.setForeground(new Color(120, 212, 255));
            promo_label.setHorizontalAlignment(SwingConstants.CENTER);
            promo_label.setHorizontalTextPosition(SwingConstants.CENTER);
            promo_label.setText("ООО \"Системы промавтоматики\"");
            promo_label.setVerticalAlignment(SwingConstants.BOTTOM);
            promo_label.setBounds(new Rectangle(6, 630, 235, 41));
            disable_specfunctions_button.setBackground(new Color(112, 177, 217));
            disable_specfunctions_button.setFont(this.disable_bps_button.getFont());
            disable_specfunctions_button.setForeground(Color.white);
            disable_specfunctions_button.setBorder(BorderFactory.createLineBorder(Color.
                    BLUE));

            disable_specfunctions_button.setText("Выключение спецфункций");

            alarm_journal.setFont(new Font("Times New Roman", Font.BOLD,
                    16));
            alarm_journal.setForeground(new Color(112, 177, 217));
            alarm_journal.setHorizontalAlignment(SwingConstants.LEFT);
            alarm_journal.setText("Журнал аварий:");
            alarm_journal.setBounds(new Rectangle(19, 442, 204, 41));
            call_alarm_journal_button.setBackground(new Color(112, 177, 217));
            call_alarm_journal_button.setBounds(new Rectangle(19, 484, 200, 23));
            call_alarm_journal_button.setForeground(Color.white);
            call_alarm_journal_button.setBorder(BorderFactory.createLineBorder(
                    Color.blue));
            call_alarm_journal_button.setText("Вызвать журнал аварий");


            disable_parallel_button.setBackground(new Color(112, 177, 217));
            disable_parallel_button.setBounds(new Rectangle(20, 260, 200, 23));
            disable_parallel_button.setForeground(Color.white);
            disable_parallel_button.setBorder(BorderFactory.createLineBorder(Color.blue));
            disable_parallel_button.setText("Выкл. параллельную работу");

            enable_parallel_button.setBackground(new Color(112, 177, 217));
            enable_parallel_button.setBounds(new Rectangle(20, 229, 200, 23));
            enable_parallel_button.setForeground(Color.white);
            enable_parallel_button.setBorder(BorderFactory.createLineBorder(Color.blue));
            enable_parallel_button.setText("Вкл. параллельную работу");

            unlock_psu_button.setBackground(new Color(112, 177, 217));
            unlock_psu_button.setBounds(new Rectangle(20, 197, 200, 23));
            unlock_psu_button.setForeground(Color.white);
            unlock_psu_button.setBorder(BorderFactory.createLineBorder(Color.blue));
            unlock_psu_button.setText("Разблокировать источники");

            jLabel1.setFont(new Font("Times New Roman", Font.BOLD, 16));
            jLabel1.setForeground(new Color(112, 177, 217));
            jLabel1.setHorizontalAlignment(SwingConstants.LEFT);
            jLabel1.setText("Внешний вид параметров:");
            jLabel1.setBounds(new Rectangle(19, 521, 204, 41));
            radio_status_view_select.setBackground(new Color(230, 255, 255));
            radio_status_view_select.setFont(new Font("Times New Roman",
                    Font.BOLD, 16));
            radio_status_view_select.setForeground(new Color(112, 177, 217));
            radio_status_view_select.setSelected(false);
            radio_status_view_select.setText("Общий");
            radio_status_view_select.setBounds(new Rectangle(19, 556, 199, 26));

            radio_detailed_view_select.setBackground(new Color(230, 255, 255));
            radio_detailed_view_select.setFont(new Font("Times New Roman", Font.BOLD,
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
            settings_menu.setForeground(Color.white);
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

            settings_menu.setBounds(new Rectangle(19, 615, 196, 25));
            this.add(promo_label);
            this.add(jLabel1);
            this.add(radio_status_view_select);
            this.add(radio_detailed_view_select);
            this.add(radio_false_button);
            this.add(settings_menu);

            this.add(main_control_label);

            configurePSU();

            configureBattery();

            configureJournal();

            buttonGroup1.add(radio_status_view_select);
            buttonGroup1.add(radio_detailed_view_select);
            buttonGroup1.add(radio_false_button);
        } catch (Exception exception) {
            exception.printStackTrace();
        }

        for (int i = 1; i <= 24; i++)
            this.compensation_charge_combo.addItem(" " + Integer.toString(i) +
                    "ч.");
        setPsus(0);
        setBatteries(0);

    }

    private void setBatteries(int batteries) {
        if (batteries <= 1) {
            capacity_control_combo.setVisible(false);
            capacity_control_button.setBounds(new Rectangle(19, 374, 200, 23));
            disable_specfunctions_button.setBounds(new Rectangle(19, 411, 200, 23));
            return;
        }

        capacity_control_button.setBounds(new Rectangle(19, 374, 140, 23));
        disable_specfunctions_button.setBounds(new Rectangle(19, 411, 200, 23));

        capacity_control_combo.removeAllItems();
        for (int i = 1; i <= batteries; i++)
            this.capacity_control_combo.addItem(" " + Integer.toString(i));

        capacity_control_combo.setSelectedIndex(0);
    }

    private void setPsus(int quantity) {
        set_bps_combo.removeAllItems();
        disable_bps_combo.removeAllItems();
        for (int i = 1; i <= quantity; i++)
            this.set_bps_combo.addItem(" " + Integer.toString(i));
        for (int i = 1; i <= quantity; i++)
            this.disable_bps_combo.addItem(" " + Integer.toString(i));
        if (quantity > 0) {
            set_bps_combo.setSelectedIndex(0);
            disable_bps_combo.setSelectedIndex(0);
        }
    }

    private void configureJournal() {
        final Journal journal = configuration.getJournal();
        if (journal != null) {
            this.add(alarm_journal);
            call_alarm_journal_button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JTextPane textPane = new JTextPane();
                    textPane.setEditable(false);
                    textPane.setContentType("text/html");
                    StringBuilder builder = new StringBuilder("<table align=\"center\" border =\"0\">");
                    try {
                        UKU_Connection_SNMP.readParameter(journal.getSize());
                        IndexedParameter eventTableStart = journal.getEventTableStart();
                        eventTableStart.setIndex(journal.getSize());
                        for (Parameter parameter : eventTableStart.getIndexedParameters()) {
                            builder.append("<tr><td>");
                            String event = readEvent(parameter);
                            builder.append(event);
                            builder.append("</td></tr>");
                        }
                    } catch (Exception e1) {
                        e1.printStackTrace();
                        return;
                    }
                    textPane.setText(builder.toString());
                    JDialog dialog = new JDialog();
                    dialog.setTitle("Журнал аварий");
                    dialog.setSize(journal.getWidth(), journal.getHeight());
                    JScrollPane jsp = new JScrollPane(textPane);
                    dialog.add(jsp);
                    dialog.setModalityType(Dialog.ModalityType.DOCUMENT_MODAL);
                    dialog.setVisible(true);

                }
            });
            this.add(call_alarm_journal_button);

        }
    }

    private String readEvent(Parameter parameter) {
        try {
            UKU_Connection_SNMP.readParameter(parameter);
        } catch (Exception e) {
            return "Error reading event" + e.getMessage();
        }
        return (String) parameter.getValue();
    }

    private void configureBattery() {
        Battery battery = configuration.getSettings().getBattery();
        if (battery != null) {
            battery.getQuantityBatteries().addChangeListener(this);
            if (battery.getDisableSpecials() != null) {
                disable_specfunctions_button.addActionListener(new ControlSettingsUnitActionListener(battery.getDisableSpecials()));
                this.add(disable_specfunctions_button);
            }

            this.add(specfunction_label);

            if (battery.getCapacityControl() != null) {
                capacity_control_button.addActionListener(new ControlSettingsUnitActionListener(battery.getCapacityControl(), capacity_control_combo));
                this.add(capacity_control_button);
                this.add(capacity_control_combo);
            }
            if (battery.getCompensationCharge() != null) {
                compensation_charge_button.addActionListener(new ControlSettingsUnitActionListener(battery.getCompensationCharge(), compensation_charge_combo));
                this.add(compensation_charge_button);
                this.add(compensation_charge_combo);
            }

        }
    }

    private void configurePSU() {
        PowerSupplyUnit psu = configuration.getSettings().getPsu();
        if (psu != null) {
            psu.getQuantityPsu().addChangeListener(this);
            if (psu.getSetPrimary() != null) {
                this.add(primary_psu);
                set_bps_button.addActionListener(new ControlSettingsUnitActionListener(psu.getSetPrimary(), set_bps_combo));
                this.add(set_bps_button);
                this.add(set_bps_combo);
            }

            if (psu.getDisablePsu() != null) {
                this.add(disable_psu);
                disable_bps_button.addActionListener(new ControlSettingsUnitActionListener(psu.getDisablePsu(), disable_bps_combo));
                this.add(disable_bps_button);
                this.add(disable_bps_combo);
            }
            if (psu.getUnlock() != null) {
                unlock_psu_button.addActionListener(new ControlSettingsUnitActionListener(psu.getUnlock()));
                this.add(unlock_psu_button);
            }
            if (psu.getDisableParallel() != null) {
                disable_parallel_button.addActionListener(new ControlSettingsUnitActionListener(psu.getDisableParallel()));
                this.add(disable_parallel_button);
            }
            if (psu.getEnableParallel() != null) {
                enable_parallel_button.addActionListener(new ControlSettingsUnitActionListener(psu.getEnableParallel()));
                this.add(enable_parallel_button);
            }

        }
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
    //    private Event_Viewer viewer;
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

    @Override
    public void update_panel() {

    }

    @Override
    public void stateChanged(ChangeEvent e) {
        Object source = e.getSource();
        final PowerSupplyUnit psu = configuration.getSettings().getPsu();
        if (psu != null && psu.getQuantityPsu() == source)
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    setPsus(psu.getQuantityPsu().getValue());
                }
            });

        final Battery battery = configuration.getSettings().getBattery();
        if (battery != null && battery.getQuantityBatteries() == source)
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    setBatteries(battery.getQuantityBatteries().getValue());
                }
            });

    }


    private class SwitchPanelAdapter implements ActionListener {
        private final String panelToShow;

        public SwitchPanelAdapter(String panelToShow) {
            this.panelToShow = panelToShow;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == settings_menu) {
                String pass = JOptionPane.showInputDialog(null, "Пароль",
                        "Необходима авторизация",
                        JOptionPane.WARNING_MESSAGE);
                if (pass != null)
                    if (pass.equals(new String("127"))) {
                        mainPanelSnmp.switchTo(panelToShow);
                    } else {
                        JOptionPane.showMessageDialog(null, "Пароль неверный!",
                                "Необходима авторизация",
                                JOptionPane.WARNING_MESSAGE);
                    }

            } else
                mainPanelSnmp.switchTo(panelToShow);

        }
    }

    private class ControlSettingsUnitActionListener implements ActionListener {
        private final SettingParameter settingParameter;
        private final JComboBox source;

        public ControlSettingsUnitActionListener(SettingParameter settingParameter, JComboBox source) {
            this.settingParameter = settingParameter;
            this.source = source;
        }

        public ControlSettingsUnitActionListener(SettingParameter settingParameter) {
            this.settingParameter = settingParameter;
            source = null;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                Object newValue = source == null ? settingParameter.getValueToSet() : source.getSelectedItem();
                if (settingParameter.getType() == Type.INTEGER) {
                    if (source != null)
                        newValue = source.getSelectedIndex() + 1;
                    else
                        newValue = Integer.parseInt(String.valueOf(newValue).trim());
                }
                UKU_Connection_SNMP.writeParameter(settingParameter, newValue);
            } catch (Exception e1) {
                e1.printStackTrace();
                JOptionPane.showMessageDialog(UKU_Control_Panel_SNMP.this, "Невозможно выполнить команду: " + e1.getMessage(), "Ошибка команды", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}

