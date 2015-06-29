package uku_control;

import uku_control.config.Configuration;
import uku_control.config.ViewConfiguration;

import javax.swing.*;
import java.awt.*;

public class UKU_Panel_Big extends UKU_Panel {

    public static int DESIRED_HEIGHT = 680;
    public static int DESIRED_WIDTH = 480;

    private Configuration configuration = Util.loadConfiguration();

    public UKU_Panel_Big() {
        this.setBounds(0, 0, DESIRED_WIDTH, DESIRED_HEIGHT);

        UIManager.put("Box.background", new Color(240, 255, 255));

        init();
    }

    private void init() {
        Box b = Box.createVerticalBox();

        b.add(Box.createVerticalStrut(5));
        java.util.List<ViewConfiguration> viewConfigurations = configuration.getViewConfigurations();
        for (ViewConfiguration viewConfiguration : viewConfigurations) {
            if (viewConfiguration.getTableCaption() != null)
                b.add(Box.createVerticalStrut(10));
            JComponent component = viewConfiguration.getComponent();
            b.add(component);

        }

        JPanel box_panel = new JPanel();
        box_panel.add(b);
        JScrollPane scroll_pane = new JScrollPane(box_panel);
        scroll_pane.setPreferredSize(new Dimension(DESIRED_WIDTH, DESIRED_HEIGHT));
        scroll_pane.getVerticalScrollBar().setForeground(Color.RED);
        scroll_pane.setBorder(null);
        this.setLayout(new BorderLayout());
        this.add(scroll_pane);

        scroll_pane.getVerticalScrollBar().setUnitIncrement(30);

    }

    @Override
    public void update_panel() {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                UKU_Panel_Big.this.repaint();
            }
        });
    }

}
