package uku_control;

import javax.swing.*;
import java.awt.Color;
import java.awt.Rectangle;
import java.awt.Dimension;
import java.awt.LayoutManager;

/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author not attributable
 * @version 1.0
 */
public class UKU_Info_Panel extends JPanel{

    public static int desired_height;
    public static int desired_width;
    private UKU_Data_Big data;
    private JLabel model_value = new JLabel();
    private JLabel serial_value = new JLabel();
    private JLabel location_value = new JLabel();

    public UKU_Info_Panel(UKU_Data_Big data_t) {
        this.data = data_t;

        this.desired_width = 480;
        this.desired_height = 20;

        this.setSize(this.desired_width + 250, desired_height);
        this.setBackground(Color.BLUE);
        this.setBounds(0, 0, this.desired_width + 250, desired_height);
        this.setBorder(BorderFactory.createEtchedBorder(1, Color.BLUE, Color.WHITE));

        surface_decorator();
    }

    private void surface_decorator() {
        Box b = Box.createHorizontalBox();

        JLabel location_label = new JLabel();
        location_label.setForeground(Color.white);
        location_label.setText("Расположение:");
        location_label.setBounds(new Rectangle(5, 3, 100, 14));

        JLabel serial_label = new JLabel();
        serial_label.setForeground(Color.white);
        serial_label.setText("Cерийный №:");
        serial_label.setBounds(new Rectangle(5, 3, 100, 14));


        JLabel model_label = new JLabel();
        model_label.setForeground(Color.white);
        model_label.setText("Модель:");
        model_label.setBounds(new Rectangle(5, 3, 100, 14));


        location_value.setForeground(Color.white);
        location_value.setText(data.info_data.location.get());
        location_value.setBounds(new Rectangle(5, 3, 100, 14));


        serial_value.setForeground(Color.white);
        serial_value.setText(data.info_data.serial_number.get_textual());
        serial_value.setBounds(new Rectangle(5, 3, 100, 14));



        model_value.setForeground(Color.white);
        model_value.setText(data.info_data.get_model_textual());
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
    }

        public void update_panel(){
            if (data.need_update_info_panel.get() == 1){
                data.need_update_info_panel.set(0);
                //this.removeAll();
                //this.surface_decorator();
                location_value.setText(data.info_data.location.get());
                serial_value.setText(data.info_data.serial_number.get_textual());
                model_value.setText(data.info_data.get_model_textual());
                this.repaint();
            }
        }


}
















