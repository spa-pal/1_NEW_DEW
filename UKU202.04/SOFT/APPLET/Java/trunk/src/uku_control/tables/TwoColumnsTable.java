package uku_control.tables;

import uku_control.config.Column;
import uku_control.config.ViewConfiguration;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.table.TableColumn;
import java.awt.*;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 */
public class TwoColumnsTable extends JTable {

    public static final int TABLE_WIDTH = 400;

    public TwoColumnsTable(TwoColumnsModel twoColumnsModel, ViewConfiguration viewConfiguration) {
        super(twoColumnsModel);
        setRowHeight(30);
        if (viewConfiguration.getColumns().isEmpty()) {
            TableColumn column1 = new TableColumn(0, 300, null, null);
            TableColumn column2 = new TableColumn(1, 50, null, null);
//        setBounds(50, 50, 360, 180);
            addColumn(column1);
            addColumn(column2);
        } else {
            int i = 0;
            for (Column column : viewConfiguration.getColumns()) {
                TableColumn column1 = new TableColumn(i++, column.getWeight(), null, null);
                addColumn(column1);
            }
        }

        setCellSelectionEnabled(false);
        setAutoResizeMode(AUTO_RESIZE_OFF);
        setFont(new Font("SanSerif", Font.PLAIN, 14));
        setFocusable(false);
//        setMaximumSize(new Dimension(TABLE_WIDTH, 60));
        setPreferredSize(new Dimension(TABLE_WIDTH, twoColumnsModel.getRowCount() * 30));
        setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
    }
}
