package uku;

import org.springframework.beans.factory.annotation.Autowired;
import uku.snmp.OIDParameter;

import javax.swing.*;
import javax.swing.table.TableColumn;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.List;

/**
 * Created by Anatoly Danilov on 2/8/14.
 */
public class OidPresenter {
    private JTable oidTable;
    private JPanel mainPanel;

    @Autowired
    private List<OidsTable> tables;
    @Autowired
    private SnmpConnector connector;
    private JTextField hostTextField;


    public OidPresenter() {
        mainPanel = new JPanel();
        mainPanel.setLayout(null);
        oidTable = new JTable();


        //mainPanel.add(oidTable);


    }


    public void init() {

        for (OidsTable table : tables) {
            mainPanel.add(table.getJTable());
        }

        hostTextField = new JTextField();
        hostTextField.setBounds(20, 10, 200, 20);
        hostTextField.setText(connector.getHost());
        hostTextField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                validateAndSetHost();

            }


        });
        hostTextField.addFocusListener(new FocusAdapter() {
            @Override
            public void focusLost(FocusEvent e) {
                validateAndSetHost();
            }
        });
        mainPanel.add(hostTextField);

        JButton startButton = new JButton();
        startButton.setBounds(230, 10, 140, 20);
        startButton.setText("Начать опрос");
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                connector.stop();
                connector.start();
            }
        });
        JButton stopButton = new JButton();
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                connector.stop();
            }
        });
        stopButton.setBounds(380, 10, 140, 20);
        stopButton.setText("Остановить опрос");
        mainPanel.add(startButton);
        mainPanel.add(stopButton);

    }

    private void validateAndSetHost() {
        String newHost = hostTextField.getText().trim();
        if (IPAddressValidator.validate(newHost))
            connector.setHost(newHost);
        else
            hostTextField.setText(connector.getHost());
    }

    public JPanel getMainPanel() {
        return mainPanel;
    }


}
