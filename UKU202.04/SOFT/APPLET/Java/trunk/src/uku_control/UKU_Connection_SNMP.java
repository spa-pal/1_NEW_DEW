package uku_control;

/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.0
 */

import snmp.*;
import uku_control.config.*;

import java.io.IOException;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

public class UKU_Connection_SNMP implements Runnable {
    private static boolean connected;
    private static InetAddress host_address;
    public int port_num = 161;

    private static final ReentrantLock lock = new ReentrantLock(true);

    private Thread runner;

    private int not_response_counter = 0;

    public boolean getting_data = false;
    public boolean sending_command = false;
    public boolean getting_events = false;
    public boolean is_active;
    public boolean transaction_finished;

    private static SNMPv1CommunicationInterface comInterface;

    private List<Parameter> parameters = new ArrayList<Parameter>();
    private static Configuration configuration = Util.loadConfiguration();

    public UKU_Connection_SNMP() {

        Configuration configuration = Util.loadConfiguration();
        parameters.addAll(configuration.getAllParameters());
        parameters.addAll(configuration.getAllAlarms());
        parameters.addAll(configuration.getSettings().getAllParameters());

        List<ViewConfiguration> viewConfigurations = configuration.getViewConfigurations();
        for (ViewConfiguration viewConfiguration : viewConfigurations)
            parameters.addAll(viewConfiguration.getAllParameters());


    }

    public void set_ip_address(String host, int port) {
        try {
            host_address = InetAddress.getByName(host);
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        port_num = port;
    }


    public static void set_connection() throws SocketException {
        String community = "public";
        int version = 0; // SNMPv1
        if (comInterface != null)
            comInterface.closeConnection();

        comInterface = new SNMPv1CommunicationInterface(version,
                host_address,
                community);
        comInterface.setSocketTimeout(configuration.getConnection().getTimeoutMillis());

        connected = true;
    }

    public void close_connection() throws IOException {
        if (!getting_data) {
            comInterface.closeConnection();
            is_active = false;
        }
    }

    public static String get_OID_string(String itemID) throws Exception {
        // now send an SNMP GET request to retrieve the value of the SNMP variable
        // corresponding to OID 1.3.6.1.2.1.1.1.0; this is the OID corresponding to
        // the device identifying string, and the type is thus SNMPOctetString

        System.out.println("Retrieving value corresponding to OID " + itemID);

        // the getMIBEntry method of the communications interface returns an SNMPVarBindList
        // object; this is essentially a Vector of SNMP (OID,value) pairs. In this case, the
        // returned Vector has just one pair inside it.
        SNMPVarBindList newVars = comInterface.getMIBEntry(itemID);

        // extract the (OID,value) pair from the SNMPVarBindList; the pair is just a two-element
        // SNMPSequence
        SNMPSequence pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));

        // extract the object identifier from the pair; it's the first element in the sequence
        SNMPObjectIdentifier snmpOID = (SNMPObjectIdentifier) pair.
                getSNMPObjectAt(0);

        // extract the corresponding value from the pair; it's the second element in the sequence
        SNMPObject snmpValue = pair.getSNMPObjectAt(1);

        // print out the String representation of the retrieved value
        System.out.println("Retrieved value: type " +
                snmpValue.getClass().getName() + ", value " +
                snmpValue.toString());

        // the retrieved value can be obtained from the SNMPObject using the getValue method;
        // the return type of the method is the generic base class Object, and must be cast to
        // the appropriate actual Java type; in this case, for an SNMPOctetString, the underlying
        // Java type is a byte array[]
        // byte[] javaByteArrayValue = (byte[]) snmpValue.getValue();

        return snmpValue.toString();
    }

    public static int get_OID_int(String itemID) throws Exception {

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
        System.out.println("Retrieved value: type " + snmpValue.getClass().getName() +
                ", value " + snmpValue.toString());
        return Integer.parseInt(snmpValue.toString());
    }

    public static void set_OID_int(String itemID, int value) throws Exception {

        SNMPInteger snmp_value = new SNMPInteger(value);
        //  System.out.println("Setting value corresponding to OID " + itemID);
        //   System.out.println("New value: " + snmp_value.toString());

        // the setMIBEntry method of the communications interface returns the SNMPVarBindList
        // corresponding to the supplied OID and value
        // This call will probably cause an SNMPSetException to be thrown, since the
        // community name "public" is probably not the read/write password of the device
        SNMPVarBindList newVars = comInterface.setMIBEntry(itemID, snmp_value);

/*        System.out.println("Retrieving value corresponding to OID " + itemID);

        // the getMIBEntry method of the communications interface returns an SNMPVarBindList
        // object; this is essentially a Vector of SNMP (OID,value) pairs. In this case, the
        // returned Vector has just one pair inside it.
        newVars = comInterface.getMIBEntry(itemID);
        // extract the (OID,value) pair from the SNMPVarBindList; the pair is just a two-element
        // SNMPSequence
        SNMPSequence pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
        // extract the object identifier from the pair; it's the first element in the sequence
        SNMPObjectIdentifier snmpOID = (SNMPObjectIdentifier) pair.getSNMPObjectAt(
                0);

        // extract the corresponding value from the pair; it's the second element in the sequence
        SNMPObject snmpValue = pair.getSNMPObjectAt(1);

        // print out the String representation of the retrieved value
        System.out.println("Retrieved value: type " + snmpValue.getClass().getName() +
                           ", value " + snmpValue.toString());
  *///      return Integer.parseInt(snmpValue.toString());
    }


    private void readFromDevice() throws Exception {
        for (Parameter parameter : parameters) {
            try {
                if (parameter instanceof IndexedParameter)
                    for (Parameter indexedParameter : ((IndexedParameter) parameter).getIndexedParameters())
                        readParameter(indexedParameter);
                else
                    readParameter(parameter);
            } catch (Exception e) {
                System.out.println("exception getting parameter: " + parameter);
                parameter.setValue(null);
            }
        }

        this.not_response_counter = 0;

    }

    private void readParametersByIndex(Alarm parameter) throws Exception {
        Parameter<Integer> index = parameter.getIndex();
        readParameter(index);
    }

    public static void writeParameter(Parameter parameter, Object newValue) throws IOException, SNMPBadValueException, SNMPSetException {

        try {
            lock.tryLock(15, TimeUnit.SECONDS);
            if (!connected)
                set_connection();

            switch (parameter.getType()) {
                case OCTET_STRING:
                    set_OID_string(parameter.getOid(), (String) newValue);
                    break;
                case INTEGER:
                case DOUBLE:
                case STATUS:
                    set_OID_int(parameter.getOid(), (Integer) newValue);
                    break;
            }
        } catch (InterruptedException e) {
            System.out.println("Can't lock to read parameters. Restart if fails");
        } catch (IOException e) {
            connected = false;
            throw e;
        } catch (SNMPBadValueException e) {
            connected = false;
            throw e;
        } catch (SNMPSetException e) {
            connected = false;
            throw e;
        } catch (Exception e) {
            connected = false;
            throw new IOException(e);
        } finally {
            lock.unlock();
        }
    }

    public static void readParameter(Parameter parameter) throws Exception {

        try {
            lock.tryLock(15, TimeUnit.SECONDS);
            if (!connected)
                set_connection();
            switch (parameter.getType()) {
                case OCTET_STRING:
                    parameter.setValue(get_OID_string(parameter.getOid()));
                    break;
                case INTEGER:
                case DOUBLE:
                case STATUS:
                    parameter.setValue(get_OID_int(parameter.getOid()));
                    break;
            }
        } catch (InterruptedException e) {
            System.out.println("Can't lock to read parameters. Restart if fails");
        } catch (Exception e) {
            parameter.setValue(null);
            connected = false;
            throw e;
        } finally {
            lock.unlock();
        }
    }

    private void oldGetData() throws Exception {
        //            int tempik = get_OID_int(data.control_byte.getOID());
//
//            if ((tempik & 0x01) != data.show_primary_bpss.get()) {
//                data.show_primary_bpss.set(tempik & 0x01);
//                data.need_correct_interface_control.set(1);
//            }
//
//
//            if (((tempik & 0x02) >> 1) != data.show_parallel_operation.get()) {
//                data.show_parallel_operation.set((tempik & 0x02) >> 1);
//                data.need_correct_interface_control.set(1);
//            }
//
//            if (((tempik & 0x04) >> 2) != data.show_events_journal.get()) {
//                data.show_events_journal.set((tempik & 0x04) >> 2);
//                data.need_correct_interface_control.set(1);
//            }

//        int tempik = get_OID_int(data.info_data.device_code.getOID());
//        data.info_data.device_code.set(tempik);
//        data.info_data.modelName.set(get_OID_string(data.info_data.modelName.getOID()));
//        tempik = get_OID_int(data.info_data.serial_number.getOID());
////            tempik = (tempik) | (get_OID_int(data.info_data.serial_number.getOID() + "3.0") << 16);
//        data.info_data.serial_number.set(tempik);
//        String temp_string = get_OID_string(data.info_data.location.getOID());
//        if (!data.info_data.location.get().equals(temp_string))
//            data.need_update_info_panel.set(1);
//        data.info_data.location.set(temp_string);
//
//        tempik = get_OID_int(data.power_main.voltage.getOID());
//        data.power_main.voltage.set(tempik);
//        tempik = get_OID_int(data.power_main.frequency.getOID());
//        data.power_main.frequency.set(tempik);
//        tempik = get_OID_int(data.power_main.status.getOID());
//        data.power_main.status.set(tempik);
//
//
//        tempik = get_OID_int(data.load.voltage.getOID());
//        data.load.voltage.set(tempik);
//        tempik = get_OID_int(data.load.current.getOID());
//        data.load.current.set(tempik);
//
//        tempik = get_OID_int(data.psus_count.getOID());
//        data.psus_count.set(tempik);
//
//        if (data.psus_count.get() > data.psus_array.length)
//            data.psus_count.set(data.psus_array.length);
//
//        for (int i = 0; i < data.psus_count.get(); i++) {
//
//            tempik = get_OID_int(data.psus_array[i].number.getOID() + "." + (i + 1));
//            data.psus_array[i].number.set(tempik);
//
//            tempik = get_OID_int(data.psus_array[i].voltage.getOID() + "." + (i + 1));
//            data.psus_array[i].voltage.set(tempik);
//
//            tempik = get_OID_int(data.psus_array[i].current.getOID() + "." + (i + 1));
//            data.psus_array[i].current.set(tempik);
//
//            tempik = get_OID_int(data.psus_array[i].temperature.getOID() + "." + (i + 1));
//            data.psus_array[i].temperature.set(tempik);
//
//            tempik = get_OID_int(data.psus_array[i].status.getOID() + "." + (i + 1));
//            data.psus_array[i].status.set(tempik);
//        }
//
//        tempik = get_OID_int(data.batteries_count.getOID());
//        data.batteries_count.set(tempik);
//        if (data.batteries_count.get() > data.batteries_array.length)
//            data.batteries_count.set(data.batteries_array.length);
//
//        for (int i = 0; i < data.batteries_count.get(); i++) {
//
//            tempik = get_OID_int(data.batteries_array[i].number.getOID() + "." + (i + 1));
//            data.batteries_array[i].number.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].voltage.getOID() + "." + (i + 1));
//            data.batteries_array[i].voltage.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].current.getOID() + "." + (i + 1));
//            data.batteries_array[i].current.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].temperature.getOID() + "." + (i + 1));
//            data.batteries_array[i].temperature.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].capacity.getOID() + "." + (i + 1));
//            data.batteries_array[i].capacity.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].charge.getOID() + "." + (i + 1));
//            data.batteries_array[i].charge.set(tempik);
//
//            tempik = get_OID_int(data.batteries_array[i].status.getOID() + "." + (i + 1));
//            data.batteries_array[i].status.set(tempik);
//        }
//
//        tempik = get_OID_int(data.external_temperature_count.getOID());
//        data.external_temperature_count.set(tempik);
//        if (data.external_temperature_count.get() > data.external_temperature_array.length)
//            data.external_temperature_count.set(data.external_temperature_array.length);
//
//        for (int i = 0; i < data.external_temperature_count.get(); i++) {
//
//            tempik = get_OID_int(data.external_temperature_array[i].number.getOID() + "." + (i + 1));
//            data.external_temperature_array[i].number.set(tempik);
//
//            tempik = get_OID_int(data.external_temperature_array[i].getOID() + "." + (i + 1));
//            data.external_temperature_array[i].set(tempik);
//
//            tempik = get_OID_int(data.external_temperature_array[i].status.getOID() + "." + (i + 1));
//            data.external_temperature_array[i].status.set(tempik);
//        }
////
////            tempik = get_OID_int(data.external_jumper_count.getOID());
////            data.external_jumper_count.set(tempik);
////            if (data.external_jumper_count.get() > data.external_jumper_array.length)
////                data.external_jumper_count.set(data.external_jumper_array.length);
////
////            for (int i = 0; i < data.external_jumper_count.get(); i++) {
////                tempik = get_OID_int(data.external_jumper_array[i].number.getOID() + "." + (i + 1));
////                data.external_jumper_array[i].number.set(tempik);
////                tempik = get_OID_int(data.external_jumper_array[i].status.getOID() + "." + (i + 1));
////                data.external_jumper_array[i].status.set(tempik);
////            }
////
////            tempik = get_OID_int(data.specfunctions.getOID());
////            data.specfunctions.set(tempik);
//
////            tempik = get_OID_int(data.extio_count.getOID());
//            if (tempik != data.extio_count.get()) {
//                data.extio_count.set(tempik);
//                data.need_correct_interface_control.set(1);
//            }
//            tempik = get_OID_int(data.extio_status.getOID());
//            int temp_flag = 0;
//            if (tempik != data.extio_status.get()) {
//                data.extio_status.set(tempik);
//                temp_flag = 1;
//
//            }
//            int temp_status = 1;
//            for (int i = 0; i < data.extio_count.get(); i++) {
//                if ((tempik & temp_status) != 0)
//                    data.extio_data_array[i].io_status.set(ExtIO_Data.ON);
//                else
//                    data.extio_data_array[i].io_status.set(ExtIO_Data.OFF);
//                temp_status = temp_status << 1;
//            }
//            if (temp_flag == 1)
//                data.need_update_extio_panel.set(1);
//
//            tempik = get_OID_int(data.extBoard.boardExists.getOID());
//            data.extBoard.boardExists.set(tempik);
//
//            if (data.extBoard.boardExists.get() == data.extBoard.EXTENSION_BOARD_EXISTS) {
//                tempik = get_OID_int(data.extBoard.voltageInput1.getOID());
//                data.extBoard.voltageInput1.set(tempik);
//                tempik = get_OID_int(data.extBoard.voltageInput2.getOID());
//                data.extBoard.voltageInput2.set(tempik);
//                tempik = get_OID_int(data.extBoard.voltagePES.getOID());
//                data.extBoard.voltagePES.set(tempik);
//
//                tempik = get_OID_int(data.extBoard.totalPower.getOID());
//                data.extBoard.totalPower.set(tempik);
//                tempik = get_OID_int(data.extBoard.currentPower.getOID());
//                data.extBoard.currentPower.set(tempik);
//
//                tempik = get_OID_int(data.extBoard.activeInput.getOID());
//                data.extBoard.activeInput.set(tempik);
//                tempik = get_OID_int(data.extBoard.fanSpeed.getOID());
//                data.extBoard.fanSpeed.set(tempik);
//            }

    }

    private static void set_OID_string(String oid, String newValue) throws SNMPBadValueException, IOException, SNMPSetException {
        SNMPOctetString snmp_value = new SNMPOctetString(newValue);
        //  System.out.println("Setting value corresponding to OID " + itemID);
        //   System.out.println("New value: " + snmp_value.toString());

        // the setMIBEntry method of the communications interface returns the SNMPVarBindList
        // corresponding to the supplied OID and value
        // This call will probably cause an SNMPSetException to be thrown, since the
        // community name "public" is probably not the read/write password of the device
        SNMPVarBindList newVars = comInterface.setMIBEntry(oid, snmp_value);

    }

    public void transaction() {
        try {
            readFromDevice();
        } catch (Exception ex1) {
            not_response_counter++;
            System.out.println("Exception during SNMP operation:  " + ex1 + "\n");
            this.sending_command = false;
            this.getting_events = false;
            this.getting_events = false;
            if (this.not_response_counter > 2) {
                this.not_response_counter = 0;
            }

            is_active = false;
        }

        transaction_finished = true;

    }

    private void getData() {

    }

    /**
     * get_events
     */
    /**
     * check_connection
     */
    public void start() {
        runner = new Thread(this);
        runner.start();
    }

    public void stop() {
        if (runner != null)
            runner.interrupt();
    }

    public void run() {

        while (true) {
            try {
                transaction();
                Thread.sleep(configuration.getConnection().getInterval());
            } catch (InterruptedException e) {
                System.out.println(
                        " Connection: Socket has been interrupted");
            } finally {
                if (Thread.currentThread().isInterrupted()) {
                    System.out.println(
                            " Connection: RUN FINISH");
                    break;
                }

            }
        }

    }


}
