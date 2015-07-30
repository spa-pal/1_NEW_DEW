package uku_control;
public class Value {

    private boolean value_is_new = false;
    String OID = new String("1.3.6.1.2.1.1.1.0");


    private static int news_quantity = 0;

    void set_value_is_new(boolean b){
        value_is_new = b;
    }
    synchronized void setOID(String value){
        this.OID = value;
    }

    synchronized String getOID(){
        return this.OID;
    }
    boolean get_value_is_new(){
        return value_is_new;
    }

    void increment_news_quantity(){
       news_quantity ++;
    }

    void decrement_news_quantity(){
        if (news_quantity == 0) return;
        news_quantity --;
    }



}
