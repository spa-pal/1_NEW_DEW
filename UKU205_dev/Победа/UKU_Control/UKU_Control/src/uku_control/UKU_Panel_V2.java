package uku_control;
import java.awt.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import javax.swing.UIManager;



public class UKU_Panel_V2 extends Abstract_spanel{

    private UKU_Data data;

    private Box b;
    private JTable table_1, table_2, table_3;
    private JTable table_4, table_5;
    private JLabel message = new JLabel();
    private JLabel battery_status;
    public static int desired_height;
    public static int desired_width;
    private boolean margin_boolean = false;

    public UKU_Panel_V2(UKU_Data amplifier_dat) {
        UIManager.put("Box.background", new Color(240,255,255));
        this.setLayout(null);

        this.setBounds(0,0, 480, 680);
        this.data = amplifier_dat;
        b = Box.createVerticalBox();
        //b.setBounds(30, 30, 480, 680);
       // b.setSize(480, 680);
        //b.setOpaque(true);


       // b.setForeground(new Color(240,255,255));
        //b.setBackground(new Color(240,255,255));

        b.setMaximumSize(new Dimension(480, 680));
        b.setMinimumSize(b.getMaximumSize());
        b.setPreferredSize(b.getPreferredSize());

        this.desired_height = 680;
        this.desired_width = 480;

        JLabel caption = new JLabel("Блоки питания", JLabel.CENTER);
        caption.setFont(new Font("SanSerif", Font.BOLD, 20));
        caption.setAlignmentX(0.5F);
        b.add(b.createVerticalStrut(5));
        b.add(caption);

        table_1 = create_1st_table();

        b.add(b.createVerticalStrut(15));
        b.add(table_1);

        JLabel caption_battery = new JLabel("Параметры батареи", JLabel.CENTER);
        caption_battery.setHorizontalTextPosition(JLabel.CENTER);
        caption_battery.setAlignmentX(0.5F);
        caption_battery.setFont( new Font("SanSerif", Font.PLAIN, 18));

        battery_status = new JLabel("Батарея отсутствует", JLabel.CENTER);
        battery_status.setHorizontalTextPosition(JLabel.CENTER);
        battery_status.setAlignmentX(0.5F);
        battery_status.setFont( new Font("SanSerif", Font.PLAIN, 14));


        b.add(b.createVerticalStrut(10));
        b.add(caption_battery);

        b.add(b.createVerticalStrut(5));
        b.add(battery_status);

        b.add(b.createVerticalStrut(5));
        table_2 = create_2nd_table();

        b.add(table_2);


        table_3 = create_3rd_table();
        table_4 = create_4th_table();

        table_1.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_2.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_3.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_4.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        message.setFont( new Font("SanSerif", Font.PLAIN, 14));
        message.setForeground(Color.RED);
        message.setAlignmentX(0.5f);
        //       b.add(message);
        //        b.add(b.createVerticalStrut(20));

        JLabel caption_mains = new JLabel("Параметры сети", JLabel.CENTER);
        caption_mains.setHorizontalTextPosition(JLabel.CENTER);
        caption_mains.setAlignmentX(0.5F);
        caption_mains.setFont(new Font("SanSerif", Font.PLAIN, 18));

        b.add(b.createVerticalStrut(10));
        b.add(caption_mains);

        b.add(b.createVerticalStrut(5));
        b.add(table_3);

        b.add(b.createVerticalStrut(5));
        b.add(message);
        b.add(b.createVerticalStrut(10));

        JLabel caption_load = new JLabel("Параметры нагрузки", JLabel.CENTER);
        caption_load.setHorizontalTextPosition(JLabel.CENTER);
        caption_load.setAlignmentX(0.5F);
        caption_load.setFont(new Font("SanSerif", Font.PLAIN, 18));

        b.add(b.createVerticalStrut(5));
        b.add(caption_load);

        b.add(b.createVerticalStrut(5));
        b.add(table_4);
        b.add(b.createVerticalStrut(10));

        b.add(b.createVerticalStrut(10));


        b.setBounds(new Rectangle(0, 10, 480, 700));
        this.add(b, null);

        JPanel box_panel = new JPanel();
        box_panel.setLayout(null);
        box_panel.setBounds(0,0, 480, 800);
        box_panel.add(b);
        JScrollPane scroll_pane = new JScrollPane(box_panel);
        scroll_pane.setPreferredSize(new Dimension(this.desired_width, this.desired_height));
        this.setLayout(new BorderLayout());
        this.add(scroll_pane);

        scroll_pane.getVerticalScrollBar().setUnitIncrement(30);

    }

    /**
     * UKU_Panel_V2
     */
    public UKU_Panel_V2() {
    }

    /**
     * create_4th_table
     *
     * @return JTable
     */
    private JTable create_4th_table() {
        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return 1;
            }

            public Object getValueAt(int row, int col) {
                if ((col == 1)) {
                    return new String(UKU_Data_View.voltage_battery_load(data.voltage_resistor.get()));
                }
                if ((col == 0)) {
                    return new String(" Напряжение нагрузки, В (Uн)");
                }

                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 250, null, null);
        TableColumn column2 = new TableColumn(1, 50, null, null);
        table.setBounds(50, 50, 360, 180);
        table.addColumn(column1);
        table.addColumn(column2);

    //        table.setGridColor(COLORIT);
    //      table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
    //      table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400, 30));
        table.setPreferredSize(new Dimension(400, 30));
        return table;

    }

    private JTable create_3rd_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                    return String.class;
            }

            public int getRowCount() {
                return 2;
            }

            public Object getValueAt(int row, int col) {
                if ((col == 1)) {
                    switch (row) {
                    case 0:
                        return new String(UKU_Data_View.voltage_circuit(data.voltage_circuit.get()));
                    case 1:
                        return new String(UKU_Data_View.circuit_frequency(data.frequency_circuit.get()));
                    }
                }
                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new String(" Напряжение сети, В (Uс)");
                    case 1:
                        return new String(" Частота сети, Гц (F)");
                    }
                }

                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 250, null, null);
        TableColumn column2 = new TableColumn(1, 50, null, null);
        table.setBounds(50, 50, 360, 180);
        table.addColumn(column1);
        table.addColumn(column2);

//        table.setGridColor(COLORIT);
  //      table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
  //      table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400, 60));
        table.setPreferredSize(new Dimension(400, 60));
        return table;
    }


    private JTable create_2nd_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return 6;
            }

            public Object getValueAt(int row, int col) {

                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new String(" Напряжение батареи, В (Uб)");
                    case 1:
                        return new String(" Ток батареи, А (Iб)");
                    case 2:
                        return new String(" Температура батареи, \u00B0C (Тб)");
                    case 3:
                        return new String(" Емкость батареи, А/ч (Сб)");
                    case 4:
                        return new String(" Заряд батареи, % (Qб)");
                    case 5:
                        return new String(UKU_Data_View.special_functions(data.compensation_charge.get(),
                                data.capacity_control_status.get()));

                    }
                }

                if ((col == 1)) {
                    switch (row) {
                    case 0:
                        return new String(data.battery_status.get() == data.BATTERY_LOST?" --- ":
                                          UKU_Data_View.voltage_battery_load(data.voltage_battery.get()));
                    case 1:
                        return new String(data.battery_status.get() == data.BATTERY_LOST?" --- ":
                                          UKU_Data_View.current_battery(data.current_battery.get()));
                    case 2:
                        return new String(data.battery_status.get() == data.BATTERY_LOST?" --- ":
                                          UKU_Data_View.temperature(data.temperature_battery.get()));
                    case 3:
                        return new String(data.battery_status.get() == data.BATTERY_LOST?" --- ":
                                          UKU_Data_View.battery_capacity(data.battery_capacity.get()));
                    case 4:
                        return new String(data.battery_status.get() == data.BATTERY_LOST?" --- ":
                                          UKU_Data_View.battery_charge(data.battery_charge.get()));
                    case 5:
                        return new String(UKU_Data_View.special_functions_on_off(data.
                                compensation_charge.get(),
                                data.capacity_control_status.get()));

                      }
                }

                return new String("No such parameter");
            }
        };



        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 250, null, null);
        TableColumn column2 = new TableColumn(1, 50, null, null);

        table.setBounds(50, 50, 300, 240);
        table.addColumn(column1);
        table.addColumn(column2);

 //       table.setGridColor(COLORIT);
  //      table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
  //      table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));


        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400, 180));
        table.setPreferredSize(new Dimension(400, 180));
        return table;

    }

    private JTable create_1st_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                    return String.class;
            }

            public int getRowCount() {
                return 5;
            }

            public Object getValueAt(int row, int col) {
                if ((col == 2)) {
                    switch (row) {
                    case 0:
                        return new String("   " + " БПС-2");
                    case 1:
                         return new String(data.primary_bps.get() == data.PRIMARY_BPS_2? " Вкл": " Выкл");
                    case 2:
                         return new String(UKU_Data_View.voltage_bps(data.voltage_bps_2.get()));

                    case 3:
                         return new String(UKU_Data_View.current_bps(data.current_bps_2.get()));

                    case 4:
                        return new String(UKU_Data_View.temperature(data.temperature_bps_2.get()));

                    }
                }
                if ((col == 1)) {
                   switch (row) {
                   case 0:
                       return new String("    БПС-1");
                   case 1:
                        return new String(data.primary_bps.get() == data.PRIMARY_BPS_1?" Вкл":" Выкл");
                   case 2:
                        return new String(UKU_Data_View.voltage_bps(data.voltage_bps_1.get()));

                   case 3:
                        return new String(UKU_Data_View.current_bps(data.current_bps_1.get()));

                   case 4:
                       return new String(UKU_Data_View.temperature(data.temperature_bps_1.get()));
                   }
               }

                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new String(" ");
                    case 1:
                        return new String(" Текущее состояние");
                    case 2:
                        return new String(" Выходное напряжение, В (U1, U2)");
                    case 3:
                        return new String(" Ток, А (I1, I2)");
                    case 4:
                        return new String(" Температура, \u00B0C (Т1, T2)");
                    }
                }

                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column = new TableColumn(2, 50, null, null);
        TableColumn column1 = new TableColumn(0, 200, null, null);
        TableColumn column2 = new TableColumn(1, 50, null, null);
        table.addColumn(column1);
        table.addColumn(column2);
        table.addColumn(column);
//        table.setGridColor(COLORIT);
//        table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);

        table.setPreferredSize(new Dimension(400, 150));
        table.setMaximumSize(new Dimension(400, 150));
//        table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);


        return table;
    }

    private void battery_status_margin(){
        this.battery_status.setText(
        data.battery_status.get() == data.BATTERY_LOST?
        "Батарея отсутствует.":
        "Батарея подключена."
        );

        this.battery_status.setForeground(Color.BLACK);

        if (data.battery_status.get() == data.BATTERY_LOST){
            margin_boolean = !margin_boolean;
            this.battery_status.setForeground(margin_boolean?Color.RED:Color.BLACK);

        }

    }

    public void update_data() {
        battery_status_margin();
        if (data.voltage_circuit.get() < 180)
            message.setText("Авария сети: Uс < 180 В");
        else
            message.setText(" ");
        table_1.validate();
        table_2.validate();
        table_3.validate();
    }


    public static void main(String[] args) {
        UKU_Data data = new UKU_Data();
        UKU_Panel_V2 amplifier_panel = new UKU_Panel_V2(data);
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container content = frame.getContentPane();

        data.battery_status.set(data.BATTERY_ENABLED);
        data.battery_charge.set(80);
        data.battery_capacity.set(200);
        data.temperature_battery.set(40);
        data.current_battery.set(89);
        data.voltage_battery.set(340);

        data.primary_bps.set(data.PRIMARY_BPS_2);
        data.voltage_bps_1.set(560);
        data.voltage_bps_2.set(890);
        data.current_bps_1.set(45);
        data.current_bps_2.set(5);
        data.temperature_bps_1.set(36);
        data.temperature_bps_2.set(44);

        data.voltage_circuit.set(181);
        data.frequency_circuit.set(501);
        data.voltage_resistor.set(120);

        content.add(amplifier_panel);
       // content.setLayout(new BorderLayout());
        frame.setSize(amplifier_panel.desired_width,amplifier_panel.desired_height);
        frame.setVisible(true);

        amplifier_panel.repaint();
        amplifier_panel.update_data();

    }

    public void update_panel() {
        this.update_data();
        this.repaint();
    }


}
