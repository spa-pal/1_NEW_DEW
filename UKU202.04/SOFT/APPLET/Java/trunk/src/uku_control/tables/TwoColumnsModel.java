package uku_control.tables;

import uku_control.Util;
import uku_control.config.Parameter;

import javax.swing.table.AbstractTableModel;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 * For the pleasure
 */
public class TwoColumnsModel extends AbstractTableModel {
    private final List<Parameter> parameters;

    public TwoColumnsModel(List<Parameter> parameters) {

        this.parameters = parameters;
    }

    @Override
    public int getRowCount() {
        if (parameters == null)
            return 0;
        return parameters.size();
    }

    @Override
    public int getColumnCount() {
        return 0;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Parameter parameter = parameters.get(rowIndex);

        if (columnIndex == 0)
            return Util.HTML_BODY_P_STYLE_MARGIN_LEFT_5 + parameter.getName();
        else
            return Util.toText(parameter);
    }

}
