package uku;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import javax.swing.*;
import java.net.SocketException;
import java.net.UnknownHostException;

/**
 * Created by Kriahtunchik on 2/8/14.
 */
public class StartMonitoring {

    private static Logger logger = Logger.getLogger(StartMonitoring.class);

    public static void main(String[] args) throws SocketException, UnknownHostException {

        setLookAndFeel();


        ApplicationContext applicationContext = null;
        try {
            applicationContext = new ClassPathXmlApplicationContext("SpringConfig.xml");
        } catch (BeansException e) {
            logger.error("Fail to init Spring. Check SpringConfig.xml is correct", e);
            return;
        }

        JFrame mainframe = new JFrame("SNMP Monitoring");
        OidPresenter presenter = applicationContext.getBean("presenter", OidPresenter.class);
        mainframe.getContentPane().add(presenter.getMainPanel());
        mainframe.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        mainframe.setSize(1280, 1024);
        mainframe.setVisible(true);
    }

    private static void setLookAndFeel() {
        try {
            // Set System L&F
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (UnsupportedLookAndFeelException | ClassNotFoundException | InstantiationException | IllegalAccessException e) {
            logger.error(e.getMessage(), e);
        }
    }
}
