package uku_control;

import javax.swing.JLabel;
import java.awt.Color;
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
public class JLabel_Margin extends JLabel {
    public JLabel_Margin(String text, int type, Color col) {
        super(text);
        this.setFont(new Font("SanSerif", (type == 1) ? Font.BOLD : Font.PLAIN,
                              14));
        this.setForeground(col);

    }

    public JLabel_Margin(String text) {
        super(text);
        this.setFont(new Font("SanSerif", Font.PLAIN, 14));
    }

    public JLabel_Margin(String text, boolean measure) {
        super(text);
        this.setFont(new Font("SanSerif", Font.PLAIN, measure ? (text.length() > 9)?(int)Math.round(14 - (text.length() - 9) * 2.4 / 35.0 * 14):14: 14));
    }



}
