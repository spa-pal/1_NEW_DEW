package uku;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import snmp.*;
import uku.snmp.OIDParameter;

import java.io.IOException;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.List;

/**
 * Created by Anatoly Danilov on 2/8/14.
 */
public class SnmpConnector {

    private static final Logger logger = Logger.getLogger(SnmpConnector.class);

    public static final int VERSION_1 = 0;
    @Autowired
    List<OIDParameter> parameters;
    private static SnmpConnector snmpConnector = new SnmpConnector();
    private SNMPv1CommunicationInterface comInterface;
    private String host;
    private long timeToSleep = 200;
    private int socketTimeout;
    private Thread connectorThread;
    private boolean isRunning;
    private boolean autostart;


    public static SnmpConnector getInstance() {
        return snmpConnector;
    }


    public void readAllParameters()  {
        for (OIDParameter parameter : parameters) {
            if (!isRunning){
                logger.info("Thread is not running stop reading");
                return;
            }
            Object value = null;
            try {
                value = readParameter(parameter);
                parameter.setValue(value);
                logger.debug("Parameter read: " + parameter);

            } catch (SNMPBadValueException | IOException | SNMPGetException e) {
                logger.error("Parameter error: " + parameter);
                parameter.setNoConnection();
            }
        }
    }

    public void start() {
        try {
            logger.info("System is starting");
            comInterface = new SNMPv1CommunicationInterface(VERSION_1, InetAddress.getByName(host), "public");
            comInterface.setSocketTimeout(socketTimeout);
        } catch (UnknownHostException | SocketException e) {
            logger.error(e.getMessage());
        }
        if (connectorThread != null && isRunning) {
            logger.info("SNMP Connector is already running");
            return;
        }

        connectorThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    try {
                        readAllParameters();
                        Thread.sleep(timeToSleep);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        logger.error(e.getMessage());
                        isRunning = false;
                        return;
                    }
                }
            }
        }, "connector");
        connectorThread.start();
        isRunning = true;
    }

    public void stop() {
        if (connectorThread != null)
            connectorThread.interrupt();
        isRunning = false;
        logger.info("System stop is called");
    }

    private Object readParameter(OIDParameter parameter) throws SNMPBadValueException, IOException, SNMPGetException {
        // the getMIBEntry method of the communications interface returns an SNMPVarBindList
        // object; this is essentially a Vector of SNMP (OID,value) pairs. In this case, the
        // returned Vector has just one pair inside it.
        SNMPVarBindList newVars = comInterface.getMIBEntry(parameter.getOid());
        // extract the (OID,value) pair from the SNMPVarBindList; the pair is just a two-element
        // SNMPSequence
        SNMPSequence pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
        // extract the object identifier from the pair; it's the first element in the sequence
        SNMPObjectIdentifier snmpOID = (SNMPObjectIdentifier) pair.getSNMPObjectAt(0);

        // extract the corresponding value from the pair; it's the second element in the sequence
        SNMPObject snmpValue = pair.getSNMPObjectAt(1);
        return snmpValue;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public String getHost() {
        return host;
    }

    public void setSocketTimeout(int socketTimeout) {
        this.socketTimeout = socketTimeout;
    }

    public void setAutostart(boolean autostart) {
        this.autostart = autostart;
    }

    public void init() {
        if (autostart)
            start();
    }
}
