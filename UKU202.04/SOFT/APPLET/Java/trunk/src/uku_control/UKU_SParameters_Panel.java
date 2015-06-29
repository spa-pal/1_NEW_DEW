package uku_control;

import uku_control.config.Configuration;
import uku_control.config.SettingParameter;
import uku_control.config.Settings;

import javax.swing.*;
import java.awt.*;

//import java.util.GregorianCalendar;


public class UKU_SParameters_Panel extends UKU_Panel {

    private int table_width = 400;
    private Box parameter[] = new Box[50];
    //    private Special_Parameters sparam = new Special_Parameters(0x14,
//            "Основной источник  №", "", 1, Special_Settings.ZERO_TO_ONE,
//            "Основной источник в ИБЭПе с приоритетом источников", 1);
//
//    private Special_Parameters sparam2 = new Special_Parameters(0x2A,
//            "Время проверки цепи батареи (Мин.)", "", 5, Special_Settings.NONE,
//            "Период проверки наличия батареи", 1);
//
//    private Special_Parameters sparam3 = new Special_Parameters(0x28,
//            "Звуковая сигнализация", "", 1, Special_Settings.ENABLED_DISABLED,
//            "Включение/выключение звукового оповещения об авариях и режимах", 1);
//
//    private Special_Parameters sparam4 = new Special_Parameters(0x29,
//            "Отключение сигнала аварии", "", 1, Special_Settings.MANUAL_AUTO,
//            "Автоматическое снятие аварийной сигнализации при пропадании состояния аварии", 1);
//
//    private JLabel battery_status;
    public static int desired_height;
    public static int desired_width;
    private boolean margin_boolean = false;

    private Configuration configuration = Util.loadConfiguration();

    public UKU_SParameters_Panel() {
        this.setBounds(0, 0, 480, 680);

        this.desired_height = 680;
        this.desired_width = 480;
        UIManager.put("Box.background", new Color(240, 255, 255));
        //this.setLayout(new BorderLayout());

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

        Settings settings = configuration.getSettings();
        if (settings == null)
            return;
        for (SettingParameter settingParameter : settings.getParameters()) {
            b.add(Box.createVerticalStrut(15));
            b.add(settingParameter.getView());
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
//        scroll_pane.getVerticalScrollBar().setValue(data.scroll_pane_position.get());
    }


}
