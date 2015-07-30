package uku_control;

public class Integer_Value extends Value {
    int value;



    public Integer_Value(int value) {
        super();
        this.value = value;
    }
    synchronized void set(int value){

        this.value = value;
        this.increment_news_quantity();
        this.set_value_is_new(true);
    }

    synchronized int get(){
        this.decrement_news_quantity();
        this.set_value_is_new(false);
        return this.value;

    }

    synchronized int increase(){
        this.value++;
        this.increment_news_quantity();
        this.set_value_is_new(true);
        return this.value;
    }

    synchronized int decrease(){
        this.value--;
        this.increment_news_quantity();
        this.set_value_is_new(true);
        return this.value;
    }

    synchronized String get_textual(){
        return Integer.toString(value);
    }





}
