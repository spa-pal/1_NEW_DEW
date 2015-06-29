package uku_control.tables;

import uku_control.config.Column;
import uku_control.config.ViewConfiguration;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import java.awt.*;

/**
 * Created by Anatoly Danilov on 11/22/2014.
 * For the pleasure
 */
public class MultiColumnsTable extends JTable {

    public MultiColumnsTable(TableModel dm, ViewConfiguration viewConfiguration) {
        super(dm);

        setRowHeight(30);
        int i = 0;
        for (Column column : viewConfiguration.getColumns())
            addColumn(new TableColumn(i++, column.getWeight()));

        setCellSelectionEnabled(false);
        setAutoResizeMode(AUTO_RESIZE_OFF);

//        setPreferredSize(new Dimension(TwoColumnsTable.TABLE_WIDTH, 10 * 30));
//        setMaximumSize(new Dimension(TwoColumnsTable.TABLE_WIDTH, 10 * 30));
        setFont(new Font("SanSerif", Font.PLAIN, 14));

        setFocusable(false);
        setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));

    }
}
