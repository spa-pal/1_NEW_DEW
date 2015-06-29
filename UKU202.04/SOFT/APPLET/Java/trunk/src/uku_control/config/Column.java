package uku_control.config;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlRootElement;

/**
 * Created by Anatoly Danilov on 11/22/2014.
 * For the pleasure
 */
@XmlRootElement
public class Column {
    private int weight;

    @XmlAttribute
    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }
}
