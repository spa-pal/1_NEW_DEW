package uku_control.config;

import javax.xml.bind.annotation.XmlAttribute;

/**
 * Created by Anatoly Danilov on 11/26/2014.
 * For the pleasure
 */
public class Connection {

    private int interval;
    private int timeoutMillis;
    private String host;
    private int port;

    @XmlAttribute
    public int getInterval() {
        return interval;
    }

    public void setInterval(int interval) {
        this.interval = interval;
    }

    @XmlAttribute
    public int getTimeoutMillis() {
        return timeoutMillis;
    }

    public void setTimeoutMillis(int timeoutMillis) {
        this.timeoutMillis = timeoutMillis;
    }

    @XmlAttribute
    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    @XmlAttribute
    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }
}
