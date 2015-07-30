package uku_control;

public class UKU_Data_SNMP {
    private UKU_Data_Big data;
    public UKU_Data_SNMP(UKU_Data_Big data) {
        this.data = data;
        SNMP_assign();
        //data.lifo.add((new Command_SNMP(Command_Handler.GET_DEVICE_INFO, 0)));
    }

    private void SNMP_assign(){

        /*      data.command_byte.setOID("1.3.6.1.4.1.33183.10.8.1.0");
              data.command_answer.setOID("1.3.6.1.4.1.33183.1.2.8.2.0");*/
        /*
         * OIDы для посылки команд
         */
        data.command_id.setOID("1.3.6.1.4.1.33183.10.8.1.0");
        data.command_parameter.setOID("1.3.6.1.4.1.33183.10.8.2.0");

        data.control_byte.setOID("1.3.6.1.4.1.33183.10.7.1.0");
        data.specfunctions.setOID("1.3.6.1.4.1.33183.10.6.1.0");

        data.power_main.voltage.setOID("1.3.6.1.4.1.33183.10.2.1.0");
        data.power_main.frequency.setOID("1.3.6.1.4.1.33183.10.2.2.0");
        data.power_main.status.setOID("1.3.6.1.4.1.33183.10.2.3.0");

        data.load.voltage.setOID("1.3.6.1.4.1.33183.10.3.1.0");
        data.load.current.setOID("1.3.6.1.4.1.33183.10.3.2.0");

        data.psus_count.setOID("1.3.6.1.4.1.33183.10.1.7.0");
        for (int i = 0; i < data.psus_array.length; i++){
            data.psus_array[i].number.setOID("1.3.6.1.4.1.33183.10.4.1.1");
            data.psus_array[i].voltage.setOID("1.3.6.1.4.1.33183.10.4.1.2");
            data.psus_array[i].current.setOID("1.3.6.1.4.1.33183.10.4.1.3");
            data.psus_array[i].temperature.setOID("1.3.6.1.4.1.33183.10.4.1.4");
            data.psus_array[i].status.setOID("1.3.6.1.4.1.33183.10.4.1.5");
        }

        data.batteries_count.setOID("1.3.6.1.4.1.33183.10.1.6.0");
        for (int i = 0; i < data.batteries_array.length; i++){
            //data.batteries_array[i].number.setOID("1.3.6.1.4.1.33183.10.5.1.1");
            data.batteries_array[i].voltage.setOID("1.3.6.1.4.1.33183.10.5.1.2");
            data.batteries_array[i].current.setOID("1.3.6.1.4.1.33183.10.5.1.3");
            data.batteries_array[i].temperature.setOID("1.3.6.1.4.1.33183.10.5.1.4");
            data.batteries_array[i].capacity.setOID("1.3.6.1.4.1.33183.10.5.1.5");
            data.batteries_array[i].charge.setOID("1.3.6.1.4.1.33183.10.5.1.6");
            data.batteries_array[i].status.setOID("1.3.6.1.4.1.33183.10.5.1.7");
        }

        data.external_temperature_count.setOID("1.3.6.1.4.1.33183.1.2.5.1.0");
       /* for (int i = 0; i < data.external_temperature_array.length; i++){
            data.external_temperature_array[i].number.setOID("1.3.6.1.4.1.33183.1.2.5.2.1.1");
            data.external_temperature_array[i].setOID("1.3.6.1.4.1.33183.1.2.5.2.1.2");
            data.external_temperature_array[i].status.setOID("1.3.6.1.4.1.33183.1.2.5.2.1.5");
        }*/

        data.external_jumper_count.setOID("1.3.6.1.4.1.33183.1.2.6.1.0");
        for (int i = 0; i < data.external_jumper_array.length; i++){
            data.external_jumper_array[i].number.setOID("1.3.6.1.4.1.33183.1.2.6.2.1.1");
            data.external_jumper_array[i].status.setOID("1.3.6.1.4.1.33183.1.2.6.2.1.4");
        }

        // Глубина журнала читается здесь
        data.events_quantity.setOID("1.3.6.1.4.1.33183.10.1.8.0");

        /**
         * Установим значения оидов :)
         * */
        for (int i = 0; i < data.events.length; i++){
            data.events[i].setOID("1.3.6.1.4.1.33183.10.9.1.1." + (i + 1));
        }

        data.extio_count.setOID("1.3.6.1.4.1.33183.1.2.10.1.0");
        data.extio_status.setOID("1.3.6.1.4.1.33183.1.2.10.2.0");

        data.info_data.device_code.setOID("1.3.6.1.4.1.33183.10.1.1.0");
        data.info_data.serial_number.setOID("1.3.6.1.4.1.33183.10.1.2.0"); // Take into account that there are two bytes
        data.info_data.location.setOID("1.3.6.1.4.1.33183.10.1.5.0");
/*
        data.extBoard.boardExists.setOID("1.3.6.1.4.1.33183.1.2.13.1.0");
        data.extBoard.voltageInput1.setOID("1.3.6.1.4.1.33183.1.2.13.2.0");
        data.extBoard.voltageInput2.setOID("1.3.6.1.4.1.33183.1.2.13.3.0");
        data.extBoard.voltagePES.setOID("1.3.6.1.4.1.33183.1.2.13.4.0");
*/
        //data.extBoard.totalPower.setOID("1.3.6.1.4.1.33183.1.2.13.5.0");
        //data.extBoard.currentPower.setOID("1.3.6.1.4.1.33183.1.2.13.6.0");

        //data.extBoard.activeInput.setOID("1.3.6.1.4.1.33183.1.2.13.7.0");
        //data.extBoard.fanSpeed.setOID("1.3.6.1.4.1.33183.1.2.13.8.0");
    }

}
