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
 * @author not attributable
 * @version 1.0
 */
public class UKU_Info_Data extends Unit_Data{

    public String_Value location = new String_Value("Новосибирск");
    public Integer_Value serial_number = new Integer_Value(99999999);
    public Integer_Value device_code = new Integer_Value(1);
    private String model_list[] = new String[50];

    public UKU_Info_Data() {

        model_list[0] = "ИБЭП220/60В-24A";
        model_list[1] = "ИБЭП220/60В-12A";
        model_list[2] = "ИБЭП220/48В-24A";
        model_list[3] = "ИБЭП220/48В-12A";
        model_list[4] = "ИБЭП220/60В-10A";
        model_list[5] = "ИБЭП220/60В-5A";
        model_list[6] = "ИБЭП220/48В-10A";
        model_list[7] = "ИБЭП220/48В-5A";
        model_list[8] = "ИБЭП220/24В-24A";
        model_list[9] = "ИБЭП220/24В-12A";
        model_list[10] = "ИБЭП220/48В-40A";
        model_list[11] = "ИБЭП220/60В-30A";
        model_list[12] = "ИБЭП220/48В-20A";
        model_list[13] = "ИБЭП220/60В-15A";
        model_list[14] = "ИБЭП220/24В-50A";
        model_list[15] = "ИБЭП220/24В-25A";
        model_list[16] = "ИБЭП220/48В-60А.F.K";
        model_list[17] = "Тип неизвестен     ";
        //model_list[18] = "Шняга 2            ";

    }

    public String get_model_textual(){
        if (this.device_code.get() <= 0){
            System.out.println(" Connection: Wrong Device Code");
            device_code.set(1);
             return model_list[17];
        }
        //if (model_list[this.device_code.get() - 1] != null){
        //    return model_list[this.device_code.get() - 1];
        //}
        if (this.device_code.get()  == 6024){
            return model_list[0];
        }
        if (this.device_code.get()  == 6012){
            return model_list[1];
        }
        if (this.device_code.get()  == 4824){
            return model_list[2];
        }
        if (this.device_code.get()  == 4812){
            return model_list[3];
        }
        if (this.device_code.get()  == 6010){
            return model_list[4];
        }
        if (this.device_code.get()  == 6005){
            return model_list[5];
        }
        if (this.device_code.get()  == 4810){
            return model_list[6];
        }
        if (this.device_code.get()  == 4805){
            return model_list[7];
        }
        if (this.device_code.get()  == 2424){
            return model_list[8];
        }
        if (this.device_code.get()  == 2412){
            return model_list[9];
        }
        if (this.device_code.get()  == 4840){
            return model_list[10];
        }
        if (this.device_code.get()  == 6030){
            return model_list[11];
        }
        if (this.device_code.get()  == 4820){
            return model_list[12];
        }
        if (this.device_code.get()  == 6015){
            return model_list[13];
        }
        if (this.device_code.get()  == 2450){
            return model_list[14];
        }
        if (this.device_code.get()  == 2425){
            return model_list[15];
        }




        System.out.println(" Connection: Wrong Device Code");
        return model_list[17];

    }

    int get_alarm() {
        return 0;
    }

    int get_acknowledged() {
        return 0;
    }

    void set_acknowledged(int value) {
    }
}
