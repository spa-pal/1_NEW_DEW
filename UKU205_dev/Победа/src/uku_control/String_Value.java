package uku_control;

public class String_Value extends Value {
    String value;
    public String_Value(String value) {
        super();
        this.value = value;
    }
    synchronized void set(String value){

        this.value = value;
        this.increment_news_quantity();
        this.set_value_is_new(true);
    }

    synchronized String get(){
        this.decrement_news_quantity();
        this.set_value_is_new(false);
        return this.value;

    }
}
