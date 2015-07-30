package uku_control;

import java.awt.*;
import java.applet.*;
import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter;

/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.10
 */


public class UKU_Applet_SNMP extends JApplet implements Runnable {

    private UKU_Data_Big data;
    protected UKU_Main_Panel_SNMP panel;
    protected UKU_Connection_SNMP connection;

    private boolean is_active = false;
    private Thread runner;


    //public Integer_Value iv;

    public static Integer_Value iv = new Integer_Value(45);
    //Construct the applet
    public UKU_Applet_SNMP() {
        super();

        data = new UKU_Data_Big();
        panel = new UKU_Main_Panel_SNMP(data);
        connection = new UKU_Connection_SNMP(data);
        this.getContentPane().add(panel);
        try {
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        // Test Palace
        //data.extBoard.boardExists.set(ExtBoardData.EXTENSION_BOARD_EXISTS);
        //data.extBoard.currentPower.set(19345678);
        //data.extBoard.totalPower.set(12345678);
        //data.extBoard.activeInput.set(2);
        //data.external_jumper_count.set(4);
        //data.external_temperature_count.set(3);

    }

    //Initialize the applet
    public void init() {
        ///panel.update_panel();

        //connection.set_ip_address(getCodeBase().getHost(), 10001);
        //data.url.set("http://" + getCodeBase().getHost());
        //System.out.println(data.url.get());

        data.url.set("http://" + "192.168.1.73");
        System.out.println(data.url.get());
        connection.set_ip_address("192.168.1.73", 161);

    }


    public void destroy( ) {
        this.stop();
    }

    //Get Applet information
    public String getAppletInfo() {
        return "Power Supply Units1 Control";
    }

    public void start() {

        runner = new Thread(this);
       runner.start();
        this.connection.start();
    }

    public void stop() {
        runner.interrupt();
        this.connection.stop();
    }

    public void run() {
        while (true) {
            try {
  /*              UKU_Text_Operation test = new UKU_Text_Operation(data.url.get());
                try {
                    test.read_it();
                    test.save_it_please();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }


                */
                Thread.currentThread().sleep(1000);
                panel.update_panel();

                iv.increase();
                System.out.println(" Applet: Step. + " + iv.get_textual());

            } catch (InterruptedException ex) {
                System.out.println(" Applet: Thread is interrupted.");
            } finally {
                if (Thread.currentThread().isInterrupted()) {
                    break;
                }

            }

        }
    }

    public void this_keyReleased(KeyEvent e) {

    }

    private void jbInit() throws Exception {
        this.addKeyListener(new UKU_Applet_SNMP_this_keyAdapter(this));
    }
}


class UKU_Applet_SNMP_this_keyAdapter extends KeyAdapter {
    private UKU_Applet_SNMP adaptee;
    UKU_Applet_SNMP_this_keyAdapter(UKU_Applet_SNMP adaptee) {
        this.adaptee = adaptee;
    }

    public void keyReleased(KeyEvent e) {
        adaptee.this_keyReleased(e);
    }
}
