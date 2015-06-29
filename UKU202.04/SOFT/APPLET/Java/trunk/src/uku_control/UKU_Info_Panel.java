package uku_control;

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
 * @author not attributable
 * @version 1.0
 */
public class UKU_Info_Panel extends JPanel implements ChangeListener {

    public static int desired_height;
    public static int desired_width;
    private JLabel model_value = new JLabel();
    private JLabel serial_value = new JLabel();
    private JLabel location_value = new JLabel();

    private Configuration configuration = Util.loadConfiguration();

    public UKU_Info_Panel() {

        this.desired_width = 480;
        this.desired_height = 20;

        this.setSize(this.desired_width + 250, desired_height);
        this.setBackground(Color.BLUE);
        this.setBounds(0, 0, this.desired_width + 250, desired_height);
        this.setBorder(BorderFactory.createEtchedBorder(1, Color.BLUE, Color.WHITE));

        surface_decorator();
        configuration.getLocation().addChangeListener(this);
        configuration.getSerialNumber().addChangeListener(this);
        configuration.getModel().addChangeListener(this);
    }

    private void surface_decorator() {
        Box b = Box.createHorizontalBox();

        JLabel location_label = new JLabel();
        location_label.setForeground(Color.white);
        location_label.setText(configuration.getLocation().getName());
        location_label.setBounds(new Rectangle(5, 3, 100, 14));

        JLabel serial_label = new JLabel();
        serial_label.setForeground(Color.white);
        serial_label.setText(configuration.getSerialNumber().getName());
        serial_label.setBounds(new Rectangle(5, 3, 100, 14));


        JLabel model_label = new JLabel();
        model_label.setForeground(Color.white);
        model_label.setText(configuration.getModel().getName());
        model_label.setBounds(new Rectangle(5, 3, 100, 14));


        location_value.setForeground(Color.white);
        location_value.setBounds(new Rectangle(5, 3, 100, 14));


        serial_value.setForeground(Color.white);
        serial_value.setBounds(new Rectangle(5, 3, 100, 14));


        model_value.setForeground(Color.white);
        model_value.setBounds(new Rectangle(5, 3, 100, 14));


        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        b.add(b.createHorizontalStrut(5));
        b.add(location_label);
        b.add(b.createHorizontalStrut(5));
        b.add(location_value);
        b.add(b.createHorizontalGlue());

        b.add(b.createHorizontalStrut(5));
        b.add(model_label);
        b.add(b.createHorizontalStrut(5));
        b.add(model_value);
        b.add(b.createHorizontalStrut(15));
        b.add(serial_label);
        b.add(b.createHorizontalStrut(5));
        b.add(serial_value);
        b.add(b.createHorizontalStrut(15));

        this.add(b);
        updateValues();

    }

    private void updateValues() {
        location_value.setText(configuration.getLocation().getTextValue());
        serial_value.setText(configuration.getSerialNumber().getTextValue());
        Parameter model = configuration.getModel();
        model_value.setText(model.getValue() == null || model.getTextValue().length() == 0 ? "<задайте модель в настройках>" : model.getTextValue());
    }

    @Override
    public void stateChanged(ChangeEvent e) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                updateValues();
            }
        });
    }
}
















