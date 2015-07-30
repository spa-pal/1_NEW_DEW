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
public class UKU_LIFO {

    private Object[] objects = new Object[128];
    private int objects_inside = 0;

    public UKU_LIFO() {
    }

    public int is_empty(){
        return ((this.objects_inside == 0)?1:0);
    }

    public void add(Object object){
        if (objects_inside < 127){
            this.objects[objects_inside] = object;
            objects_inside++;
        }
    }

    public Object get(){
        if (objects_inside != 0){
            objects_inside--;
            return this.objects[objects_inside];
        }
        return null;
    }


}
