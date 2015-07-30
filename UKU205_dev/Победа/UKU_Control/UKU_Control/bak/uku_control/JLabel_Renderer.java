package uku_control;

import javax.swing.table.TableCellRenderer;
import java.awt.Component;
import javax.swing.*;
import java.awt.Font;
/**
 * <p>Title: UKU control </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2008</p>
 *
 * <p>Company: Lantis</p>
 *
 * @author Danilov
 * @version 1.0
 */
public class JLabel_Renderer implements TableCellRenderer {

    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
        //((JLabel_Margin) value).setFont(new Font("SanSerif", Font.PLAIN, 14));
        return ((JLabel_Margin) value );
    }

}
