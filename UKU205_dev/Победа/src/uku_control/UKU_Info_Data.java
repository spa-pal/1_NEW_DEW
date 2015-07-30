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

    public String_Value location = new String_Value("�����������");
    public Integer_Value serial_number = new Integer_Value(99999999);
    public Integer_Value device_code = new Integer_Value(1);
    private String model_list[] = new String[50];

    public UKU_Info_Data() {

        model_list[0] = "����220/60�-24A";
        model_list[1] = "����220/60�-12A";
        model_list[2] = "����220/48�-24A";
        model_list[3] = "����220/48�-12A";
        model_list[4] = "����220/60�-10A";
        model_list[5] = "����220/60�-5A";
        model_list[6] = "����220/48�-10A";
        model_list[7] = "����220/48�-5A";
        model_list[8] = "����220/24�-24A";
        model_list[9] = "����220/24�-12A";
        model_list[10] = "����220/48�-40A";
        model_list[11] = "����220/60�-30A";
        model_list[12] = "����220/48�-20A";
        model_list[13] = "����220/60�-15A";
        model_list[14] = "����220/24�-50A";
        model_list[15] = "����220/24�-25A";
        model_list[16] = "����220/48�-60�.F.K";


    }

    public String get_model_textual(){
        if (this.device_code.get() <= 0){
            System.out.println(" Connection: Wrong Device Code");
            device_code.set(1);
             return model_list[0];
        }
        if (model_list[this.device_code.get() - 1] != null){
            return model_list[this.device_code.get() - 1];
        }
        System.out.println(" Connection: Wrong Device Code");
        return model_list[0];

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
