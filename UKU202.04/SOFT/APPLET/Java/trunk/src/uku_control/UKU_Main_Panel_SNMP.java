package uku_control;

import uku_control.config.Alarm;
import uku_control.config.AlarmState;
import uku_control.config.Configuration;
import uku_control.config.Parameter;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;


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
public class UKU_Main_Panel_SNMP extends JPanel implements ChangeListener {

    public static final String STATUS_CARD = "status";
    public static final String TABLE_VIEW = "table_view";
    public static final String SETTINGS = "settings";
    private UKU_Panel_Big panel;

    private static JPanel right = new JPanel(new CardLayout());
    private Configuration configuration = Util.loadConfiguration();

    public static Alarm_Sound_Wav alarm_sound;


    public UKU_Main_Panel_SNMP() {
        alarm_sound = new Alarm_Sound_Wav(this.getClass().getClassLoader()
                .getResource("uku_control/ringin.wav"));

        UIManager.put("ComboBox.buttonBackground", new Color(117, 177, 217));
        UIManager.put("ComboBox.buttonShadow", Color.BLUE);
        UIManager.put("ComboBox.buttonDarkShadow", Color.white);
        UIManager.put("ComboBox.buttonHighLight", Color.darkGray);
        UIManager.put("ScrollBar.thumbHighlight", Color.WHITE);
        UIManager.put("ScrollBar.thumbDarkShadow", Color.WHITE);
        UIManager.put("ScrollBar.trackForeground", Color.white);
        UIManager.put("ScrollBar.thumb", new Color(230, 250, 250));//new Color(117, 177, 217));

        UKU_Status_Panel_Big status_panel = new UKU_Status_Panel_Big();

        panel = new UKU_Panel_Big();
        right.add(panel, TABLE_VIEW);
        right.add(status_panel, STATUS_CARD);
        UKU_Control_Panel_SNMP control_panel = new UKU_Control_Panel_SNMP(this);
        UKU_SParameters_Panel sparameters_panel = new UKU_SParameters_Panel();
        right.add(sparameters_panel, SETTINGS);
        UKU_Info_Panel system_id = new UKU_Info_Panel();

        this.setLayout(null);
        this.setSize(panel.desired_width + 250, panel.desired_height + system_id.desired_height);
        this.setBounds(0, 0, panel.desired_width + 250, panel.desired_height + system_id.desired_height);
        control_panel.setBounds(0, 20, 250, panel.desired_height);
        right.setSize(panel.desired_width, panel.desired_height);
        right.setBounds(250, system_id.desired_height, panel.desired_width, panel.desired_height);
        this.add(control_panel);
        this.add(right);
        this.add(system_id);
        switchTo(TABLE_VIEW);

        for (Parameter alarm : configuration.getAllAlarms())
            alarm.addChangeListener(this);

    }

    public void update_panel() {

        panel.update_panel();
    }

    public static void switchOnAlarm(String message) {
        if (alarm_sound.isActive())
            return;
        alarm_sound.switch_on(true);
        JOptionPane pane = new JOptionPane(message, JOptionPane.ERROR_MESSAGE);
        JDialog dialog = pane.createDialog(right, "Авария");
//            dialog.setAlwaysOnTop(true);

        dialog.setVisible(true);
        alarm_sound.switch_on(false);
    }

    public void switchTo(final String panelToShow) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                ((CardLayout) right.getLayout()).show(right, panelToShow);
                right.repaint();
            }
        });

    }

    @Override
    public void stateChanged(ChangeEvent e) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                for (Alarm alarm : configuration.getAlarms()) {
                    if (alarm.getAlarmState() == AlarmState.ALARM) {
                        switchOnAlarm(alarm.getName());
                        return;
                    }
                }
                alarm_sound.switch_on(false);
            }
        });
    }
}
