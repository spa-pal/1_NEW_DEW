package uku_control;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.net.URL;

public class Log_Frame extends JFrame {

    private JMenuBar menubar;
    private JMenu menu;
    private JTextArea textarea;
    private boolean is_pressed = false;
    JScrollPane scrollpane;
    JScrollBar scrollbar;

    public Log_Frame() {

        this.setDefaultCloseOperation(this.DISPOSE_ON_CLOSE);
        this.setTitle("Журнал событий");

        Container contentpane = this.getContentPane();

        textarea = new JTextArea();
        scrollpane = new JScrollPane(textarea);
        scrollbar = scrollpane.getVerticalScrollBar();
        scrollbar.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                is_pressed = true;
            }

            public void mouseReleased(MouseEvent e) {
                is_pressed = false;
            }


        });

        textarea.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                is_pressed = true;
            }

            public void mouseReleased(MouseEvent e) {
                is_pressed = false;
            }


        });

        contentpane.add(scrollpane, BorderLayout.CENTER);
        textarea.setText("05.04.2008 11:32 - Авария сети \r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи\r\n05.04.2008 12:57- Авария батареи");
        textarea.setFont(new Font("Arial Cyr", Font.PLAIN, 14));

        textarea.setEditable(false);
        scrollpane.setAutoscrolls(true);

    }

    private void close_frame() {
        this.setVisible(false);
    }

       private boolean scroll_need = false;
    public void update_console() {

        if (!this.isVisible())return;
        if (is_pressed)return;
        //String news = log_file.read_new_data();
        textarea.repaint();

        /*if ((news.length() != 0)) {
            textarea.append(news);
            textarea.validate();
            textarea.repaint();
            scrollpane.repaint();
            this.validate();
            this.repaint();

            textarea.scrollRectToVisible(new Rectangle(0, textarea.getHeight() - 51, 100, 100));

        }*/

    }

    public void console_show() {
        super.setVisible(true);
        this.update_console();

        textarea.validate();


    }

}
