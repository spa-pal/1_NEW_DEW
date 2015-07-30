package uku_control;

import java.awt.*;

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.Font;

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
 * @version 1.0
 */
public class No_Connection_Panel extends UKU_Panel {
    BorderLayout borderLayout1 = new BorderLayout();
    JLabel jLabel1 = new JLabel();

    public No_Connection_Panel() {

        try {
            jbInit();
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    private void jbInit() throws Exception {
        this.setLayout(borderLayout1);
        jLabel1.setBackground(Color.gray);
        jLabel1.setFont(new java.awt.Font("Tahoma", Font.BOLD, 24));
        jLabel1.setForeground(Color.red);
        jLabel1.setHorizontalTextPosition(JLabel.CENTER);
        jLabel1.setHorizontalAlignment(JLabel.CENTER);
        jLabel1.setVerticalAlignment(JLabel.CENTER);
        jLabel1.setVerticalTextPosition(JLabel.CENTER);
        jLabel1.setAlignmentX((float) 0.5);
        jLabel1.setAlignmentY((float) 0.5);
        jLabel1.setText("Нет Связи");
        this.setBounds(0, 0, 480, 680);
        this.setBackground(new Color(240, 240, 250));
        this.add(jLabel1, java.awt.BorderLayout.CENTER);
    }

    public void update_panel() {
    }
}
