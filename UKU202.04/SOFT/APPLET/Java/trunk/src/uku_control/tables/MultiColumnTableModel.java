package uku_control.tables;

import uku_control.Util;
import uku_control.config.IndexedParameter;
import uku_control.config.Parameter;

import javax.swing.table.AbstractTableModel;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/22/2014.
 * For the pleasure
 */
public class MultiColumnTableModel extends AbstractTableModel {

    private final List<IndexedParameter> indexedParameters;
    private Parameter<Integer> indexParameter;

    public MultiColumnTableModel(List<Parameter> parameters, List<IndexedParameter> indexedParameters) {
        this.indexedParameters = indexedParameters;

        indexParameter = parameters.get(0);

    }


    public int getColumnCount() {
        return 0;
    }

    public int getRowCount() {
        if (indexParameter.getValue() == null)
            return 0;
        return indexParameter.getValue() + 1;
    }

    public Object getValueAt(int row, int col) {
        Parameter parameter = indexedParameters.get(col);

        if (row <= 0)
            return Util.HTML_BODY_P_STYLE_MARGIN_LEFT_5 + parameter.getName();

        int rowWithoutHeader = row - 1;
        List<? extends Parameter> listByIndex = indexedParameters.get(col).getIndexedParameters();
        if (listByIndex.size() <= rowWithoutHeader)
            return "NA";
        return Util.toText(listByIndex.get(rowWithoutHeader));

    }


}
