package uku_control.tables;

import uku_control.config.IndexedParameter;
import uku_control.config.Parameter;

import java.util.List;

/**
 * Created by Anatoly Danilov on 11/23/2014.
 * For the pleasure
 */
public class HorizontalMultiColumnTableModel extends MultiColumnTableModel {

    private final List<IndexedParameter> indexedParameters;

    public HorizontalMultiColumnTableModel(List<Parameter> parameters, List<IndexedParameter> indexedParameters) {
        super(parameters, indexedParameters);
        this.indexedParameters = indexedParameters;
    }

    @Override
    public int getRowCount() {
        return indexedParameters.size();
    }

    @Override
    public Object getValueAt(int row, int col) {
        return super.getValueAt(col, row);
    }
}
