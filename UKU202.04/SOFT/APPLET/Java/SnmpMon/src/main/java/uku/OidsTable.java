package uku;

import uku.snmp.OIDParameter;
import uku.snmp.OIDParameterChangeListener;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableColumn;
import java.awt.*;
import java.util.List;

/**
 * Created by Anatoly Danilov on 2/8/14.
 */
public class OidsTable {

    private List<OIDParameter> oidParameters;
    private int x;
    private int y;
    private JTable table;
    private String title;
    private int width = 360;


    public void setOidParameters(List<OIDParameter> oidParameters) {
        this.oidParameters = oidParameters;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public JTable getJTable() {
        SpringControlledModel dataModel = new SpringControlledModel(oidParameters, title);


        table = new JTable(dataModel);
        table.setName(title);
        table.setShowGrid(false);
        table.setShowHorizontalLines(true);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        int rowHeight = 25;
        table.setRowHeight(rowHeight);
        TableColumn nameColumn = new TableColumn(0, 200, null, null);
        TableColumn valueColumn = new TableColumn(1, 35, null, null);
        table.setBounds(x, y, width, table.getRowCount() * rowHeight);
        table.addColumn(nameColumn);
        table.addColumn(valueColumn);

        table.setCellSelectionEnabled(false);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));
        table.setFocusable(false);
        return table;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    /**
    * Created by Anatoly Danilov on 2/8/14.
    */
    static class SpringControlledModel extends AbstractTableModel implements OIDParameterChangeListener {

        private List<OIDParameter> parameters;
        private String title;
        private static  final Object[] columnNames = new String[] {"Название", "", ""};

        SpringControlledModel(List<OIDParameter> parameters, String title) {
            this.parameters = parameters;
            for (OIDParameter parameter : parameters) {
                parameter.addChangeListeners(this);
            }
            this.title = title;
        }

        @Override
        public int getRowCount() {
            return parameters.size() + 1;
        }

        @Override
        public int getColumnCount() {
            return 0;
        }


        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {

            if (rowIndex == 0) {
                return columnIndex == 0 ? title : columnNames[columnIndex];
            }
            rowIndex--;
            OIDParameter oidParameter = parameters.get(rowIndex);
            switch (columnIndex) {
                case 0:
                    return oidParameter.getDisplayName();
                case 1:
                    return oidParameter.getFormattedValue();
                case 2:
                    return oidParameter.getUnits();
            }
            return "";
        }

        @Override
        public void onValueChanged(Object value) {
            fireTableDataChanged();
        }
    }
}
