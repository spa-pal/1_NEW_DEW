package uku_control;

import java.awt.*;

import javax.swing.*;

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
public abstract class Abstract_spanel extends JPanel {
    BorderLayout borderLayout1 = new BorderLayout();

    public Abstract_spanel() {
        super();
        this.setLayout(null);
        UIManager.put("Panel.background", new Color(240,250,250));
    }

    public abstract void update_panel();
}
