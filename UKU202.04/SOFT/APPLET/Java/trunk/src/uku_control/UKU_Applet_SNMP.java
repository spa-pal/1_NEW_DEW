package uku_control;

import javax.swing.*;

/**
 * <p>Title: UKU Control</p>
 * <p/>
 * <p>Description: </p>
 * <p/>
 * <p>Copyright: Anatoly (c) 2007</p>
 * <p/>
 * <p>Company: </p>
 *
 * @author Danilov
 * @version 1.10
 */


public class UKU_Applet_SNMP extends JApplet implements Runnable {

    protected UKU_Main_Panel_SNMP panel;
    protected UKU_Connection_SNMP connection;

    private boolean is_active = false;
    private Thread runner;

    //Construct the applet
    public UKU_Applet_SNMP() {
        super();

    }

    public void initWithHost(String host) {
//        panel.update_panel();

        Util.loadConfiguration();
        try {
            panel = new UKU_Main_Panel_SNMP();
            connection = new UKU_Connection_SNMP();
            this.getContentPane().add(panel);
        } catch (Throwable e) {
            e.printStackTrace();
        }

        connection.set_ip_address(host, 161);

    }

    //Initialize the applet
    public void init() {
        Util.setCodeBase("http://127.0.0.1");// + getCodeBase().getHost());
        Util.loadConfiguration();
        String host = getCodeBase().getHost();
        try {
            panel = new UKU_Main_Panel_SNMP();
            connection = new UKU_Connection_SNMP();
            this.getContentPane().add(panel);
        } catch (Throwable e) {
            e.printStackTrace();
        }

        connection.set_ip_address(host, 161);
    }


    public void destroy() {
        this.stop();
    }

    //Get Applet information
    public String getAppletInfo() {
        return "Power Supply Units Control";
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
                Util.switchColor();
                panel.update_panel();
                Thread.currentThread().sleep(1000);
            } catch (InterruptedException ex) {
                System.out.println(" Applet: Thread is interrupted.");
            } finally {
                if (Thread.currentThread().isInterrupted()) {
                    break;
                }

            }

        }
    }

    public static void main(String[] args) {
        UKU_Applet_SNMP ukuAppletSnmp = new UKU_Applet_SNMP();
        if (args.length < 0) {
            //noinspection HardCodedStringLiteral
            System.out.println("Set hostname as first argument!");
        }

        JFrame mainFrame = new JFrame();
        mainFrame.setSize(900, 768);
        mainFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        mainFrame.getContentPane().add(ukuAppletSnmp);
        mainFrame.setVisible(true);
        ukuAppletSnmp.initWithHost(args[0]);
        ukuAppletSnmp.start();
    }
}
