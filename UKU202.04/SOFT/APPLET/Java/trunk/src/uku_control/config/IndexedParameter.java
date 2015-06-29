package uku_control.config;

import javax.xml.bind.annotation.XmlElement;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Created by Anatoly Danilov on 11/22/2014.
 * For the pleasure
 */
public class IndexedParameter extends Parameter<Object> {

    private Parameter<Integer> index;
    private List<Parameter> indexedParameters = new ArrayList<Parameter>();


    @XmlElement
    public Parameter<Integer> getIndex() {
        return index;
    }

    public void setIndex(Parameter<Integer> index) {
        this.index = index;
    }

    public List<? extends Parameter> getIndexedParameters() {
        Integer currentSize = index.getValue();
        if (currentSize == null || currentSize == 0)
            return Collections.emptyList();

        if (currentSize == indexedParameters.size())
            return indexedParameters;

        ArrayList<Parameter> parameters = new ArrayList<Parameter>(currentSize);
        for (int i = 1; i <= currentSize; i++) {
            Parameter parameter = new Parameter();
            parameter.setType(getType());
            parameter.setName(getName() + "." + i);
            parameter.setOid(getOid() + "." + i);
            parameter.setMultiplier(getMultiplier());
            parameter.setStatusMappings(getStatusMappings());
            parameter.addChangeListeners(getChangeListeners());
            parameters.add(parameter);
        }

        return indexedParameters = parameters;
    }

    public void setIndexedParameters(List<Parameter> indexedParameters) {
        this.indexedParameters = indexedParameters;
    }

    public Object getValueForIndex(int index) {
        if (indexedParameters.size() <= index)
            return null;

        return indexedParameters.get(index).getTextValue();
    }

}
