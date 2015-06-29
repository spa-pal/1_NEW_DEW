package example;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.snmp4j.*;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.log.LogAdapter;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogLevel;
import org.snmp4j.mp.MPv3;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.security.*;
import org.snmp4j.smi.*;
import org.snmp4j.transport.DefaultUdpTransportMapping;
import org.springframework.validation.beanvalidation.SpringConstraintValidatorFactory;
import snmp.*;

import java.net.InetAddress;

/**
 * Created by Kriahtunchik on 2/6/14.
 */
public class TestSnmp {

    static {
        System.setProperty(LogFactory.SNMP4J_LOG_FACTORY_SYSTEM_PROPERTY, "org.snmp4j.log.JavaLogFactory");
    }

    public static final int VERSION_1 = 0;
    private SNMPv1CommunicationInterface comInterface;

    public int get_OID_int(String itemID) throws Exception {

        System.out.println("Retrieving value corresponding to OID " + itemID);

        // the getMIBEntry method of the communications interface returns an SNMPVarBindList
        // object; this is essentially a Vector of SNMP (OID,value) pairs. In this case, the
        // returned Vector has just one pair inside it.
        SNMPVarBindList newVars = comInterface.getMIBEntry(itemID);
        // extract the (OID,value) pair from the SNMPVarBindList; the pair is just a two-element
        // SNMPSequence
        SNMPSequence pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
        // extract the object identifier from the pair; it's the first element in the sequence
        SNMPObjectIdentifier snmpOID = (SNMPObjectIdentifier) pair.getSNMPObjectAt(0);

        // extract the corresponding value from the pair; it's the second element in the sequence
        SNMPObject snmpValue = pair.getSNMPObjectAt(1);

        // print out the String representation of the retrieved value
        // System.out.println("Retrieved value: type " + snmpValue.getClass().getName() +
        //                    ", value " + snmpValue.toString());
        return Integer.parseInt(snmpValue.toString());
    }


    @Test
    public void testSimpleRequest() throws Exception {
        comInterface = new SNMPv1CommunicationInterface(VERSION_1, InetAddress.getByName("127.0.0.1"), "public");
        System.out.println(" Transaction: SNMP com interface created");
        LogAdapter logger = LogFactory.getLogger(TestSnmp.class);
        logger.setLogLevel(LogLevel.ALL);
        int simID = get_OID_int("1.3.6.1.4.1.33183.14.2.1.0");

        System.out.println(simID);

    }
}
