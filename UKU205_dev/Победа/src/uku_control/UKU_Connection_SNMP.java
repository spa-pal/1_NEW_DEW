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
import java.io.*;
import java.net.*;

import snmp.*;

public class UKU_Connection_SNMP implements Runnable {
    private UKU_Data_Big data;
    private Socket socket;
    private InetAddress host_address;
    public Integer_Value port_num = new Integer_Value(161);

    private Integer_Value connection_status;
    private InputStream receive_stream;

    public static Integer_Value iv_ = new Integer_Value(1);
    private Thread runner;

    private int not_response_counter = 0;
    private int get_data_counter = 0;

    public Boolean_Value not_response = new Boolean_Value(true);
    public boolean getting_data = false;
    public boolean sending_command = false;
    public boolean getting_events = false;
    public Boolean_Value commands_handled = new Boolean_Value(false);
    public Boolean_Value is_active = new Boolean_Value(false);
    public Boolean_Value transaction_finished = new Boolean_Value(false);

    private SNMPv1CommunicationInterface comInterface;

    public UKU_Connection_SNMP(UKU_Data_Big data) {
        this.data = data;
        this.connection_status = data.connection_status;
        get_data_counter = data.get_data_period.get();
    }

    public void set_ip_address(String host, int port) {
        try {
            host_address = InetAddress.getByName(host);
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        port_num.set(port);
    }


    public void set_connection() throws Exception {
        transaction_finished.set(false);
        if (!this.is_active.get()) {
            this.is_active.set(true);

            String community = "public";
            int version = 0; // SNMPv1

            comInterface = new SNMPv1CommunicationInterface(version,
                    host_address,
                    community);

        }
    }

    public void close_connection() throws IOException {
        if (!getting_data) {
            comInterface.closeConnection();
//            socket.close();
            ///System.out.println(" Transaction: SNMP interface closed");
            iv_.increase();
            System.out.println(" Connection: Step. + " + iv_.get_textual());
            this.is_active.set(false);
        }
    }

    public String get_OID_string(String itemID) throws Exception {
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
       /* System.out.println("Retrieved value: type " +
                           snmpValue.getClass().getName() + ", value " +
                           snmpValue.toString());
        */
        // the retrieved value can be obtained from the SNMPObject using the getValue method;
        // the return type of the method is the generic base class Object, and must be cast to
        // the appropriate actual Java type; in this case, for an SNMPOctetString, the underlying
        // Java type is a byte array[]
        // byte[] javaByteArrayValue = (byte[]) snmpValue.getValue();
        return snmpValue.toString();
    }
    public int get_OID_int(String itemID) throws Exception{

        //System.out.println("Retrieving value corresponding to OID " + itemID);

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

    public void set_OID_int(String itemID, int value) throws Exception{

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


    private void get_data() throws Exception {
        int tempik;
        if (!getting_data) {
            getting_data = true;

            tempik = get_OID_int(data.info_data.serial_number.getOID());
            if (data.info_data.serial_number.get() != tempik) {
                data.info_data.serial_number.set(tempik);
                data.need_update_info_panel.set(1);

            }

            System.out.println(" Серийный номер " + data.info_data.serial_number.get_textual());

            String temp_string = get_OID_string(data.info_data.location.getOID());

            if (data.info_data.location.get() != temp_string) {
                data.info_data.location.set(temp_string);
                data.need_update_info_panel.set(1);

            }
            //data.info_data.location.set(temp_string);


            /*int tempik = get_OID_int(data.control_byte.getOID());

            if ((tempik & 0x01) != data.show_primary_bpss.get()) {
                data.show_primary_bpss.set(tempik & 0x01);
                data.need_correct_interface_control.set(1);
            }

            if (((tempik & 0x02) >> 1) != data.show_parallel_operation.get()) {
                data.show_parallel_operation.set((tempik & 0x02) >> 1);
                data.need_correct_interface_control.set(1);
            }

            if (((tempik & 0x04) >> 2) != data.show_events_journal.get()) {
                data.show_events_journal.set((tempik & 0x04) >> 2);
                data.need_correct_interface_control.set(1);
            }*/

            tempik  = get_OID_int(data.power_main.voltage.getOID());
            data.power_main.voltage.set(tempik);
            tempik  = get_OID_int(data.power_main.frequency.getOID());
            data.power_main.frequency.set(tempik);
            ///tempik  = get_OID_int(data.power_main.status.getOID());
            ///data.power_main.status.set(tempik);


            tempik  = get_OID_int(data.load.voltage.getOID());
            data.load.voltage.set(tempik);
            tempik  = get_OID_int(data.load.current.getOID());
            data.load.current.set(tempik);

            ///tempik  = get_OID_int(data.psus_count.getOID());
            ///data.psus_count.set(tempik);

            ///if (data.psus_count.get() > data.psus_array.length)
             ///   data.psus_count.set(data.psus_array.length);

            ///    for (int i = 0; i < data.psus_count.get(); i++){

            ///    tempik  = get_OID_int(data.psus_array[i].number.getOID() + "." + (i + 1));
           ///     data.psus_array[i].number.set(tempik);

           ///     tempik  = get_OID_int(data.psus_array[i].voltage.getOID() + "." + (i + 1));
           ///     data.psus_array[i].voltage.set(tempik);

           ///     tempik  = get_OID_int(data.psus_array[i].current.getOID() + "." + (i + 1));
          ///      data.psus_array[i].current.set(tempik);

          ///      tempik  = get_OID_int(data.psus_array[i].temperature.getOID() + "." + (i + 1));
          ///      data.psus_array[i].temperature.set(tempik);

                /*tempik  = get_OID_int(data.psus_array[i].status.getOID() + "." + (i + 1));
                data.psus_array[i].status.set(tempik );*/
        ///    }
            //UKU_Applet_SNMP.iv.increase();

/*            tempik  = get_OID_int(data.batteries_count.getOID());
            data.batteries_count.set(tempik);
            if (data.batteries_count.get() > data.batteries_array.length)
                data.batteries_count.set(data.batteries_array.length);

            for (int i = 0; i < data.batteries_count.get(); i++){

                tempik  = get_OID_int(data.batteries_array[i].number.getOID() + "." + (i + 1));
                data.batteries_array[i].number.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].voltage.getOID() + "." + (i + 1));
                data.batteries_array[i].voltage.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].current.getOID() + "." + (i + 1));
                data.batteries_array[i].current.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].temperature.getOID() + "." + (i + 1));
                data.batteries_array[i].temperature.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].capacity.getOID() + "." + (i + 1));
                data.batteries_array[i].capacity.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].charge.getOID() + "." + (i + 1));
                data.batteries_array[i].charge.set(tempik);

                tempik  = get_OID_int(data.batteries_array[i].status.getOID() + "." + (i + 1));
                data.batteries_array[i].status.set(tempik);
        }*/
/*
        tempik  = get_OID_int(data.external_temperature_count.getOID());
        data.external_temperature_count.set(tempik);
        if (data.external_temperature_count.get() > data.external_temperature_array.length)
            data.external_temperature_count.set(data.external_temperature_array.length);

        for (int i = 0; i < data.external_temperature_count.get(); i++){

            tempik  = get_OID_int(data.external_temperature_array[i].number.getOID() + "." + (i + 1));
            data.external_temperature_array[i].number.set(tempik);

            tempik  = get_OID_int(data.external_temperature_array[i].getOID() + "." + (i + 1));
            data.external_temperature_array[i].set(tempik);

            tempik  = get_OID_int(data.external_temperature_array[i].status.getOID() + "." + (i + 1));
            data.external_temperature_array[i].status.set(tempik);
        }

        tempik  = get_OID_int(data.external_jumper_count.getOID());
        data.external_jumper_count.set(tempik);
        if (data.external_jumper_count.get() > data.external_jumper_array.length)
            data.external_jumper_count.set(data.external_jumper_array.length);

        for (int i = 0; i < data.external_jumper_count.get(); i++){
            tempik  = get_OID_int(data.external_jumper_array[i].number.getOID() + "." + (i + 1));
            data.external_jumper_array[i].number.set(tempik);
            tempik  = get_OID_int(data.external_jumper_array[i].status.getOID() + "." + (i + 1));
            data.external_jumper_array[i].status.set(tempik);
        }

        tempik  = get_OID_int(data.specfunctions.getOID());
        data.specfunctions.set(tempik);

        tempik = get_OID_int(data.extio_count.getOID());
        if (tempik != data.extio_count.get()){
            data.extio_count.set(tempik);
            data.need_correct_interface_control.set(1);
        }
        tempik = get_OID_int(data.extio_status.getOID());
        int temp_flag = 0;
        if (tempik != data.extio_status.get()) {
            data.extio_status.set(tempik);
            temp_flag = 1;

        }
        int temp_status = 1;
        for (int i = 0; i < data.extio_count.get(); i++){
            if ((tempik & temp_status) != 0)
                data.extio_data_array[i].io_status.set(ExtIO_Data.ON);
            else
                data.extio_data_array[i].io_status.set(ExtIO_Data.OFF);
            temp_status = temp_status << 1;
        }
 *//*
int temp_flag=1;
        if (temp_flag == 1)
             data.need_update_extio_panel.set(1);*/
/*
        tempik  = get_OID_int(data.extBoard.boardExists.getOID());
        data.extBoard.boardExists.set(tempik);

        if (data.extBoard.boardExists.get() == data.extBoard.EXTENSION_BOARD_EXISTS){
            tempik  = get_OID_int(data.extBoard.voltageInput1.getOID());
            data.extBoard.voltageInput1.set(tempik);
            tempik  = get_OID_int(data.extBoard.voltageInput2.getOID());
            data.extBoard.voltageInput2.set(tempik);
            tempik  = get_OID_int(data.extBoard.voltagePES.getOID());
            data.extBoard.voltagePES.set(tempik);

            tempik  = get_OID_int(data.extBoard.totalPower.getOID());
            data.extBoard.totalPower.set(tempik);
            tempik  = get_OID_int(data.extBoard.currentPower.getOID());
            data.extBoard.currentPower.set(tempik);

            tempik  = get_OID_int(data.extBoard.activeInput.getOID());
            data.extBoard.activeInput.set(tempik);
            tempik  = get_OID_int(data.extBoard.fanSpeed.getOID());
            data.extBoard.fanSpeed.set(tempik);
        }
*/
        this.connection_status.set(UKU_Data_Big.CONNECTION_OK);
        this.not_response_counter = 0;
        }
        getting_data = false;
    }

    /**
     * awaiting_for_incoming
     */
    private void awaiting_for_incoming() throws IOException {
        int no_response = 0;
        not_response.set(false);
        while (receive_stream.available() < 2) {
            try {
                Thread.currentThread().sleep(100);
            } catch (InterruptedException ex) {
            }
            if (not_response.get()) {
                socket.close();
                System.out.println(" Transaction: Server doesn't respond");
                System.out.println(" Transaction: Socket has been closed");
                sending_command = false;
                throw new IOException();
            }
            no_response++;
            if (no_response > 20) {
                not_response.set(true);

            }
        }

        this.connection_status.set(UKU_Data_Big.CONNECTION_OK);
        this.not_response_counter = 0;

    }

      public void transaction() {
            try {
              //  this.connection_status.set(UKU_Data_Big.CONNECTION_OK);
            	//this.connection_status.set(UKU_Data_Big.CONNECTION_OK);
            	System.out.println("0");
                this.set_connection();
                System.out.println("1");
                this.send_commands();
                System.out.println("2");
                if (data.command_need_to_get_all_events.get() == 2)
                {
                    get_events();
                    System.out.println("3");
                }
                if (this.get_data_counter == data.get_data_period.get()){
                    get_data();
             //this.connection_status.set(UKU_Data_Big.CONNECTION_OK);
                    get_data_counter = 0;
                    System.out.println("4");
                }
                else get_data_counter++;
                System.out.println("5");
                close_connection();

            } catch (Exception ex1) {
                not_response_counter++;
               // System.out.println(" Transaction: Socket Error");
                System.out.println("Exception during SNMP operation:  " + ex1 + "\n");
                this.sending_command = false;
                this.getting_events = false;
                this.getting_events = false;
                if (this.not_response_counter > 2) {
                    this.connection_status.set(UKU_Data_Big.CONNECTION_FAILED);
                    this.not_response_counter = 0;
                }

                this.is_active.set(false);
            }

            this.transaction_finished.set(true);

    }

    /**
     * get_events
     */
    private void get_events() throws Exception{
        if (!getting_events) {
            getting_events = true;
            int tempik = 0;
            int finished = 0;

            if (data.events_quantity.get() > data.events.length)
                data.events_quantity.set(data.events.length);

            for (int i = 0; i < data.events_quantity.get(); i++) {
                finished = 0;
                tempik = get_OID_int(data.events[i].device_type.getOID() + "." + (i + 1));
                data.events[i].device_type.set(tempik);

                tempik = get_OID_int(data.events[i].device_number.getOID() + "." + (i + 1));
                data.events[i].device_number.set(tempik);

                tempik = get_OID_int(data.events[i].event_type.getOID() + "." + (i + 1));
                data.events[i].event_type.set(tempik);

                tempik = get_OID_int(data.events[i].year_start.getOID() + "." + (i + 1));
                data.events[i].year_start.set(tempik);

                tempik = get_OID_int(data.events[i].month_start.getOID() + "." + (i + 1));
                data.events[i].month_start.set(tempik);

                tempik = get_OID_int(data.events[i].day_start.getOID() + "." + (i + 1));
                data.events[i].day_start.set(tempik);

                tempik = get_OID_int(data.events[i].hour_start.getOID() + "." + (i + 1));
                data.events[i].hour_start.set(tempik);

                tempik = get_OID_int(data.events[i].minute_start.getOID() + "." + (i + 1));
                data.events[i].minute_start.set(tempik);

                tempik = get_OID_int(data.events[i].second_start.getOID() + "." + (i + 1));
                data.events[i].second_start.set(tempik);

                tempik = get_OID_int(data.events[i].year_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].year_finished.set(tempik);

                tempik = get_OID_int(data.events[i].month_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].month_finished.set(tempik);

                tempik = get_OID_int(data.events[i].day_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].day_finished.set(tempik);

                tempik = get_OID_int(data.events[i].hour_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].hour_finished.set(tempik);

                tempik = get_OID_int(data.events[i].minute_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].minute_finished.set(tempik);

                tempik = get_OID_int(data.events[i].second_finished.getOID() + "." + (i + 1));
                if (tempik != 65) finished = 1;
                data.events[i].second_finished.set(tempik);

                if (finished == 1)
                    data.events[i].is_finished.set(1);
                data.need_correct_alarm_viewer.set(1);
            }

            data.command_need_to_get_all_events.set(0);

            getting_events = false;
        }
    }

    /**
     * send_commands
     */
    private void send_commands() throws Exception{
        if (!sending_command) {
            sending_command = true;
            int command  = 0;
            int reply = 0;
            int no_response = 0;
            int tempik = 0;
            Command_SNMP temp_command = null;

            while (data.lifo.is_empty() != 1){
                no_response = 0;
                temp_command = (Command_SNMP) data.lifo.get();
                command = temp_command.make();

                /*
                 * Запишем в параметр attached_parameter - значение параметра
                 * ВАЖНО: сначала установим параметры, а ТОЛЬКО ПОТОМ - название команды,
                 * дабы контроллер не начал выполнять команды с неверным параметром!
                 *
                 */
                this.set_OID_int(data.command_parameter.getOID(), temp_command.attached_parameter);


                /*
                 * Запишем в параметр command_id - название команды
                 */
                this.set_OID_int(data.command_id.getOID(), temp_command.command_name);


                //this.set_OID_int(data.command_byte.getOID(), command);
                reply = this.get_OID_int(data.command_id.getOID());

                while (temp_command.command_name == reply){
                    reply = this.get_OID_int(data.command_id.getOID());
                    Thread.sleep(100);
                    no_response++;
                    if (no_response > 200) {
                        data.connection_status.set(data.CONNECTION_FAILED);
                        data.show_warning_table_timeout.set(1);
                        data.need_correct_interface_control.set(1);
                        break;
                    }
                }
                    if (reply == Command_Handler.COMMAND_OK){
                    	// НИЧЕГО не делаем, всё клёво

                    }else if (reply == Command_Handler.COMMAND_FAILED){
                    	// Выводим окошко, типа не получилося
                        data.show_warning_table.set(1);
                        data.need_correct_interface_control.set(1);
                        data.need_update_extio_panel.set(1);
                    }

            }

            if (data.command_need_to_get_all_sparams.get() == 1){
                data.need_correct_sparams_panel.set(1);
                data.command_need_to_get_all_sparams.set(0);
            }
            if (data.command_need_to_get_all_events.get() == 1)
                data.command_need_to_get_all_events.set(2);

            this.sending_command = false;
        }


    }

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
                Thread.sleep(100);
                System.out.println(
                        " Connection");
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
