package uku_control;
public class Boolean_Value extends Value {
    boolean value;
    public Boolean_Value(boolean value) {
        super();
        this.value = value;

    }
    synchronized void set(boolean value){

       this.value = value;
       this.increment_news_quantity();
       this.set_value_is_new(true);
   }

   synchronized boolean get(){
       this.decrement_news_quantity();
       this.set_value_is_new(false);
       return this.value;

   }

}
