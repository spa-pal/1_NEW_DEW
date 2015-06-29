package uku_control.config;

import uku_control.tables.*;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.AbstractTableModel;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.awt.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/21/2014.
 */
@XmlRootElement(name = "view-config")
public class ViewConfiguration implements ChangeListener {

    public static final int FIRST_IS_INDEX = 0;
    private List<Parameter> parameters = new ArrayList<Parameter>();
    private String tableCaption;
    private TableType tableType;
    private JComponent component;
    private JTable table;
    private List<IndexedParameter> indexedParameters = new ArrayList<IndexedParameter>();
    private List<Column> columns = new ArrayList<Column>();


    public String getTableCaption() {
        return tableCaption;
    }

    @XmlAttribute
    public void setTableCaption(String tableCaption) {
        this.tableCaption = tableCaption;
    }

    @XmlAttribute
    public TableType getTableType() {
        return tableType;
    }

    public void setTableType(TableType tableType) {
        this.tableType = tableType;
    }

    public JComponent getComponent() {
        if (component == null)
            init();

        return component;
    }

    private void init() {
        Box container = Box.createVerticalBox();
        if (tableCaption != null) {
            JLabel caption = new JLabel(tableCaption, JLabel.CENTER);
            caption.setHorizontalTextPosition(JLabel.CENTER);
            caption.setAlignmentX(0.5F);
            caption.setFont(new Font("SanSerif", Font.BOLD, 20));
            container.add(caption);
            container.add(Box.createVerticalStrut(5));
        }

        JComponent viewComponent = getViewComponent();
        container.add(viewComponent);
        component = container;
        for (Parameter parameter : parameters)
            parameter.addChangeListener(this);

        for (IndexedParameter indexedParameter : indexedParameters) {
            indexedParameter.addChangeListener(this);
            indexedParameter.setIndex(parameters.get(FIRST_IS_INDEX));
        }
    }

    private JComponent getViewComponent() {
        switch (getTableType()) {
            case TWO_COLUMNS:

                table = new TwoColumnsTable(new TwoColumnsModel(parameters), this);
                return table;
            case MULTI_COLUMNS:
                table = new MultiColumnsTable(new MultiColumnTableModel(parameters, indexedParameters), this);
                return table;
            case MULTI_COLUMNS_HORIZONTAL:
                return table = new MultiColumnsTable(new HorizontalMultiColumnTableModel(parameters, indexedParameters), this);
            default:
                return new JLabel(parameters.toString());
        }
    }

    @Override
    public String toString() {
        return "ViewConfiguration{" +
                "tableType=" + tableType +
                ", tableCaption='" + tableCaption + '\'' +
                '}';
    }

    @XmlElement(name = "parameter")
    public List<Parameter> getParameters() {
        return parameters;
    }

    @Override
    public void stateChanged(ChangeEvent e) {
        if (table == null)
            return;

        ((AbstractTableModel) table.getModel()).fireTableDataChanged();

    }

    public List<IndexedParameter> getIndexedParameters() {
        return indexedParameters;
    }

    @XmlElement(name = "indexed")
    public void setIndexedParameters(List<IndexedParameter> indexedParameters) {
        this.indexedParameters = indexedParameters;
    }

    public Collection<? extends Parameter> getAllParameters() {
        ArrayList<Parameter> allPrameters = new ArrayList<Parameter>(parameters);
        allPrameters.addAll(indexedParameters);
        return allPrameters;
    }

    @XmlElement(name = "column")
    public List<Column> getColumns() {
        return columns;
    }

    public void setColumns(List<Column> columns) {
        this.columns = columns;
    }
}
