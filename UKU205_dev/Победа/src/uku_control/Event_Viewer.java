package uku_control;

import javax.swing.*;
import java.awt.Font;

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
public class Event_Viewer {

    private JDialog viewer = new JDialog();
    private JTextArea area = new JTextArea();
    private UKU_Data_Big data;

    public Event_Viewer(UKU_Data_Big data) {
        this.data = data;
        viewer.setTitle("Журнал аварий");
        viewer.setSize(600,400);
        area.setEditable(false);
        area.setFont(new Font("sanserif", Font.PLAIN, 12));
        JScrollPane scroll_pane = new JScrollPane(area);
        viewer.add(scroll_pane);

    }

    public void show_events(){
       // update_viewer();
        this.viewer.setVisible(true);

    }

    public void update_viewer() {
        String temp_str = new String();
        for (int i = 0; i < data.events_quantity.get(); i++) {
            temp_str = temp_str + (((i + 1) < 10)?" ":"") + (i + 1) + " " + data.events[i].get_textual();
        }
        if (data.events_quantity.get() == 0)
            temp_str = "В журнале нет записей";
        area.setText(temp_str);
        area.repaint();
//        this.viewer.setVisible(true);

    }


    public static void main(String[] args) {
        UKU_Data_Big data = new UKU_Data_Big();
        Event_Viewer viewer = new Event_Viewer(data);
        data.events_quantity.set(5);

        viewer.show_events();

    }



}
