package uku_control;
public class Double_Value extends Value {
    double value;
    public Double_Value(double value) {
        super();
        this.value = value;
    }
    synchronized void set(double value){

        this.value = value;
        this.increment_news_quantity();
        this.set_value_is_new(true);
    }

    synchronized double get(){
        this.decrement_news_quantity();
        this.set_value_is_new(false);
        return this.value;

    }

}
