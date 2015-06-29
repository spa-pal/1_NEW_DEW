package uku_control.config;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

/**
 * Created by Anatoly Danilov on 1/20/2015.
 * For the pleasure
 */
@XmlRootElement
public class Journal {

    private int width;
    private int height;
    private Parameter<Integer> size;
    private IndexedParameter eventTableStart;

    @XmlElement(name = "event")
    public IndexedParameter getEventTableStart() {
        return eventTableStart;
    }

    public void setEventTableStart(IndexedParameter eventTableStart) {
        this.eventTableStart = eventTableStart;
    }

    @XmlElement
    public Parameter<Integer> getSize() {
        return size;
    }

    public void setSize(Parameter<Integer> size) {
        this.size = size;
    }

    @XmlAttribute
    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    @XmlAttribute
    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }
}
