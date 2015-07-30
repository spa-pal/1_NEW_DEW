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

    public String_Value location = new String_Value("мНБНЯХАХПЯЙ");
    public Integer_Value serial_number = new Integer_Value(99999999);
    public Integer_Value device_code = new Integer_Value(1);
    private String model_list[] = new String[50];

    public UKU_Info_Data() {

        model_list[0] = "хащо220/60б-24A";
        model_list[1] = "хащо220/60б-12A";
        model_list[2] = "хащо220/48б-24A";
        model_list[3] = "хащо220/48б-12A";
        model_list[4] = "хащо220/60б-10A";
        model_list[5] = "хащо220/60б-5A";
        model_list[6] = "хащо220/48б-10A";
        model_list[7] = "хащо220/48б-5A";
        model_list[8] = "хащо220/24б-24A";
        model_list[9] = "хащо220/24б-12A";
        model_list[10] = "хащо220/48б-40A";
        model_list[11] = "хащо220/60б-30A";
        model_list[12] = "хащо220/48б-20A";
        model_list[13] = "хащо220/60б-15A";
        model_list[14] = "хащо220/24б-50A";
        model_list[15] = "хащо220/24б-25A";
        model_list[16] = "хащо220/48б-60ю.F.K";


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
