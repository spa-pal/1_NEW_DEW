package uku_control;

import java.awt.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;

//import java.util.GregorianCalendar;


public class UKU_Panel_Big extends UKU_Panel {

    private UKU_Data_Big data;
    private int table_width = 400;

    //private Box b;
    private JTable table_1, table_2, table_3;
    private JTable table_4, /*table_5, */table_6;
    private JTable table_7/*, table_8, table_9*/;
    private JLabel message = new JLabel();
    private JLabel battery_status;
    public static int desired_height;
    public static int desired_width;
    private boolean margin_boolean = false;

    public UKU_Panel_Big(UKU_Data_Big amplifier_dat) {
        this.setBounds(0, 0, 480, 680);

        this.data = amplifier_dat;
        this.desired_height = 680;
        this.desired_width = 480;
        UIManager.put("Box.background", new Color(240, 255, 255));
        //this.setLayout(new BorderLayout());

        this.surface_decorator();

    }

    public void surface_decorator() {
        Box b = Box.createVerticalBox();

        JLabel caption = new JLabel("Блоки питания", JLabel.CENTER);
        caption.setFont(new Font("SanSerif", Font.PLAIN, 18));
        caption.setAlignmentX(0.5F);
        table_1 = create_psus_table();
        b.add(b.createVerticalStrut(5));

        JLabel caption_battery = new JLabel(" Батарея", JLabel.CENTER);
        if (data.batteries_count.get() == 2)
            caption_battery.setText(" Батареи");
        caption_battery.setHorizontalTextPosition(JLabel.CENTER);
        caption_battery.setAlignmentX(0.5F);
        caption_battery.setFont(new Font("SanSerif", Font.PLAIN, 18));

        battery_status = new JLabel("Батарея отсутствует", JLabel.CENTER);
        battery_status.setHorizontalTextPosition(JLabel.CENTER);
        battery_status.setAlignmentX(0.5F);
        battery_status.setFont(new Font("SanSerif", Font.PLAIN, 14));

        // b.add(b.createVerticalStrut(5));
        //  b.add(battery_status);

        table_2 = create_batteries_table();
        table_7 = create_specfunctions_table();

        table_3 = create_power_main_table();
        table_4 = create_load_table();
       // table_5 = create_ext_temp_table();
        table_6 = create_ext_jumper_table();
      //  table_8 = create_extio_table();
      //  table_9 = createExtBoardTable();

        table_1.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_2.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_3.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_4.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
       // table_5.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_6.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
        table_7.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
      //  table_8.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));
       // table_9.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));

        message.setFont(new Font("SanSerif", Font.PLAIN, 14));
        message.setForeground(Color.RED);
        message.setAlignmentX(0.5f);
        //       b.add(message);
        //        b.add(b.createVerticalStrut(20));

        JLabel caption_mains = new JLabel("Параметры сети", JLabel.CENTER);
        caption_mains.setHorizontalTextPosition(JLabel.CENTER);
        caption_mains.setAlignmentX(0.5F);
        caption_mains.setFont(new Font("SanSerif", Font.PLAIN, 18));

        JLabel caption_load = new JLabel("Параметры нагрузки", JLabel.CENTER);
        caption_load.setHorizontalTextPosition(JLabel.CENTER);
        caption_load.setAlignmentX(0.5F);
        caption_load.setFont(new Font("SanSerif", Font.BOLD, 20));

        b.add(b.createVerticalStrut(5));
        b.add(caption_load);

        b.add(b.createVerticalStrut(5));
        b.add(table_4);
        b.add(b.createVerticalStrut(10));
        b.add(caption_mains);

        b.add(b.createVerticalStrut(5));
        b.add(table_3);

        // b.add(b.createVerticalStrut(5));
        //b.add(message);
        b.add(b.createVerticalStrut(10));
        b.add(b.createVerticalStrut(10));
        if (data.psus_count.get() > 0) {
            b.add(caption);
            b.add(b.createVerticalStrut(15));
            b.add(table_1);
        }
        if (data.batteries_count.get() > 0) {
            b.add(b.createVerticalStrut(10));
            b.add(caption_battery);
            b.add(b.createVerticalStrut(15));
            b.add(table_2);
            b.add(table_7);
        }
  /*      JLabel caption_external = new JLabel("Внешние датчики температуры",
                                             JLabel.CENTER);
        caption_external.setHorizontalTextPosition(JLabel.CENTER);
        caption_external.setAlignmentX(0.5F);
        caption_external.setFont(new Font("SanSerif", Font.PLAIN, 18));
*/
        JLabel caption_external_logic = new JLabel("Внешние логические входы",
                JLabel.CENTER);
        caption_external_logic.setHorizontalTextPosition(JLabel.CENTER);
        caption_external_logic.setAlignmentX(0.5F);
        caption_external_logic.setFont(new Font("SanSerif", Font.PLAIN, 18));

      /*  if (this.data.external_temperature_count.get() > 0) {
            b.add(b.createVerticalStrut(30));
            b.add(caption_external);
            b.add(b.createVerticalStrut(10));
            b.add(table_5);
        }*/
        if ((this.data.external_jumper_count.get()) > 0) {
            b.add(b.createVerticalStrut(30));
            b.add(caption_external_logic);
            b.add(b.createVerticalStrut(5));
            b.add(table_6);
        }


  /*      JLabel caption_extio_caption = new JLabel("Внешние исполнительные устройства",
                JLabel.CENTER);
        caption_extio_caption.setHorizontalTextPosition(JLabel.CENTER);
        caption_extio_caption.setAlignmentX(0.5F);
        caption_extio_caption.setFont(new Font("SanSerif", Font.PLAIN, 18));

        if ((this.data.extio_count.get()) > 0) {
            b.add(b.createVerticalStrut(30));
            b.add(caption_extio_caption);
            b.add(b.createVerticalStrut(15));
            b.add(table_8);

        }*/

 /*       JLabel captionExtBoard = new JLabel("Плата расширения", JLabel.CENTER);
        captionExtBoard.setHorizontalTextPosition(JLabel.CENTER);
        captionExtBoard.setAlignmentX(0.5F);
        captionExtBoard.setFont(new Font("SanSerif", Font.PLAIN, 18));

      /*  if (data.extBoard.boardExists.get() == data.extBoard.EXTENSION_BOARD_EXISTS){
            b.add(b.createVerticalStrut(30));
            b.add(captionExtBoard);
            b.add(b.createVerticalStrut(15));
            b.add(table_9);
            b.add(b.createVerticalStrut(30));

        }*/

        JPanel box_panel = new JPanel();
        box_panel.add(b);
        JScrollPane scroll_pane = new JScrollPane(box_panel);
        scroll_pane.setPreferredSize(new Dimension(this.desired_width,
                this.desired_height));
        scroll_pane.getVerticalScrollBar().setForeground(Color.RED);
        scroll_pane.setBorder(null);
        this.setLayout(new BorderLayout());
        this.add(scroll_pane);

        scroll_pane.getVerticalScrollBar().setUnitIncrement(30);

    }

    /**
     * createExtBoardTable
     *
     * @return JTable
     */
/*    private JTable createExtBoardTable() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return (5);
            }

            public Object getValueAt(int row, int col) {
                int haha = 0;

                if ((col == 0)) {
                    switch (row){
                    case 0:
                        return new String(" Напряжение ввода, В");
                    case 1:
                        return new String(" Напряжение ПЭС, В");
                    case 2:
                        return new String(" Текущая мощность, Вт");
                    case 3:
                        return new String(" Суммарная мощность, кВт*ч");
                    case 4:
                        return new String(" Позиция регулятора вентилятора");
                    default:
                        return new String(" Не определено");
                    }

                }

                if ((col == 1)) {
                    switch (row) {
                    case 0:
                        return new JLabel_Margin("  " + data.extBoard.voltageInput1.get_textual());
                   /* case 1:
                        return new JLabel_Margin("  " + data.extBoard.voltageInput2.get_textual());*/
 /*                   case 1:
                        return new JLabel_Margin("  " + data.extBoard.voltagePES.get_textual());
                    case 2:
                        return new JLabel_Margin("  " + data.extBoard.currentPower.get_textual(), true);
                    case 3:
                        return new JLabel_Margin("  " + data.extBoard.totalPower.get_textual(), true);
                   /* case 4:
                        return new JLabel_Margin((data.extBoard.activeInput.get() == 0)?"  Нет":
                                (data.extBoard.activeInput.get() == 1)?" Ввод 1":
                                (data.extBoard.activeInput.get() == 2)?"  Ввод 2":"  ПЭС");*/
 /*                   case 4:
/*                        return new JLabel_Margin("  " + data.extBoard.fanSpeed.get_textual());
                    default: return new JLabel_Margin(" Не определено");
                    }                        //return new JLabel_Margin("     " + data.batteries_array[col - 1].number.get_textual());
                }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);

        TableColumn column1 = new TableColumn(0, 300, null, null);
        TableColumn column2 = new TableColumn(1, 35, new JLabel_Renderer(), null);
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

        table.setMaximumSize(new Dimension(400, 5 * 30));
        table.setPreferredSize(new Dimension(400, 5 * 30));

        return table;
    }*/

    /**
     * create_extio_table
     *
     * @return JTable
     */
   /* private JTable create_extio_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return (data.extio_count.get());
            }

            public Object getValueAt(int row, int col) {
                int haha = 0;

                if ((col == 0)) {
                        return new String(" Исполнительное устройство " + ( row + 1));
                }

                if ((col == 1)) {

                    return data.extio_data_array[row].get_on_off_status_string();
                        //return new JLabel_Margin("     " + data.batteries_array[col - 1].number.get_textual());
                }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);

        TableColumn column1 = new TableColumn(0, 300, null, null);
        TableColumn column2 = new TableColumn(1, 100, null, null);
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

        table.setMaximumSize(new Dimension(400, data.extio_count.get() * 30));
        table.setPreferredSize(new Dimension(400, data.extio_count.get() * 30));

        return table;
    }*/


    public UKU_Panel_Big() {
    }

    private JTable create_ext_jumper_table() {
        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return data.external_jumper_count.get()-1;
            }

            public Object getValueAt(int row, int col) {
                if ((col == 0)) {
                    return new String("  " +
                                      data.external_jumper_array[row].get_name());
                }
                if ((col == 1)) {
                    if (row == 0)
                        return new JLabel_Margin(((data.external_jumper_array[0].status.get() &0x02) == 0x02)?"ОТКРЫТО":"ЗАКРЫТО",
                                        0,
                                        Color.black);
                    else
                    return new JLabel_Margin(UKU_Data_View.jumper_value(data.                            external_jumper_array[row]),                                         data.external_jumper_array[row].get(),                                         ((data.external_jumper_array[row].get() == 1) ?                                          ((data.margin_red.get() == 1) ?                                           Color.red : Color.black) : Color.black));
//                    return (data.external_jumper_array[row].get() == 1) ? "  Авария" :"  Норма";
                }

                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 300, null, null);
        TableColumn column2 = new TableColumn(1, 35, new JLabel_Renderer(), null);
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

        table.setMaximumSize(new Dimension(400,   (data.external_jumper_count.get()-1) * 30));
        table.setPreferredSize(table.getMaximumSize());
        return table;

    }

 /*   private JTable create_ext_temp_table() {
        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return data.external_temperature_count.get();
            }

            public Object getValueAt(int row, int col) {

                switch (col) {
                case 0:
                    return " " + data.external_temperature_array[row].get_name() +
                            ", \u00B0C";
                case 1:
                    return "   " +
                            Integer.toString(data.external_temperature_array[
                                             row].get());
                /*case 2:
                    return new JLabel_Margin(UKU_Data_View.temperature_value(data.
                                                external_temperature_array[row]),
                                                                 data.external_temperature_array[row].get_alarm(),
                                                                     ((data.external_temperature_array[row].get_alarm() ==
                                                    1) ?
                                                                      ((data.margin_red.get() == 1) ?
                                                    Color.red :
                                Color.black) : Color.black));*/
                    //return (data.external_temperature_array[row].get_alarm() == 1) ? "  Авария" :"  Норма" ;
 /*               }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 300, null, null);
        TableColumn column2 = new TableColumn(1, 35, null, null);
       // TableColumn column3 = new TableColumn(2, 50, new JLabel_Renderer(), null);
        table.addColumn(column1);
        table.addColumn(column2);
        //table.addColumn(column3);

        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400,
                                           data.external_temperature_count.get() *
                                           30));
        table.setPreferredSize(table.getMaximumSize());
        return table;

    }

*/
    private JTable create_load_table() {
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
                if (row == 0) {
                    if ((col == 1)) {
                        return new String("  " + data.load.voltage.get_textual());
                    }
                    if ((col == 0)) {
                        return new String(" Напряжение нагрузки, В (Uн)");
                    }
                } else if (row == 1) {
                    if ((col == 1)) {
                        return new String("  " + data.load.current.get_textual());
                    }
                    if ((col == 0)) {
                        return new String(" Ток нагрузки, А (Iн)");
                    }
                }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 300, null, null);
        TableColumn column2 = new TableColumn(1, 35, null, null);
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

    private JTable create_power_main_table() {

        TableModel dataModel = new AbstractTableModel() {


            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return ((data.power_main.status.get() & 0x02) == 2) ? 2 : 1;
            }

            public Object getValueAt(int row, int col) {
                if ((col == 1)) {
                    switch (row) {
                    case 0:
                       return new String("   " +
                                         data.power_main.voltage.get_textual());
                       //
                        //                  data.power_main.voltage.get_textual());
                    case 1:
                        return new String("   " +
                                          data.power_main.frequency.get_textual());
                    }
                }
                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new JLabel_Margin(" Напряжение сети, В (Uс)",
                                                 data.power_main.get_alarm(),
                                                 ((data.power_main.get_alarm() ==
                                1) ?
                                ((data.margin_red.get() == 1) ? Color.red :
                                 Color.black) : Color.black)); //voltage_label;
                    case 1:
                        return new JLabel_Margin(" Частота сети, Гц (F)");
                    }
                }

                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, 300, new JLabel_Renderer(), null);
        TableColumn column2 = new TableColumn(1, 35, null, null);
        //TableColumn column2 = new TableColumn(1, 50, null, null);
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

        table.setMaximumSize(new Dimension(400,
                                           ((data.power_main.status.get() & 0x02) ==
                                            2) ? 60 : 30));
        table.setPreferredSize(new Dimension(400,
                                             ((data.power_main.status.get() & 0x02) ==
                                              2) ? 60 : 30));
        return table;
    }

    private JTable create_batteries_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return (data.batteries_count.get() == 1) ? 7 : 8; //* data.batteries_count.get();
            }

            public Object getValueAt(int row, int col) {
                int haha = 0;
                if (data.batteries_count.get() == 1)
                    row = row + 1;
                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new String(" Номер батареи");
                    case 1:
                        return new String(" Напряжение батареи, В (Uб)");
                    case 2:
                        return new String(" Ток батареи, А (Iб)");
                    case 3:
                        return new String(" Температура батареи, \u00B0C (Тб)");
                    case 4:
                        return new String(" Емкость батареи, А*ч (Сб)");
                    case 5:
                        return new String(" Заряд батареи, % (Qб)");
                    case 6:
                        return new String(" Состояние");
                    case 7:
                        return new String(" Асимметрия");

                        //return new String(data.batteries_array[(row  - 6)/7].get_status());
                        /*UKU_Data_View.special_functions(data.
                                compensation_charge.get(),
                                data.capacity_control_status.get()));*/

                    }
                }

                if ((col == 1)) {
                    switch (row) {
                    case 0:
                        return new JLabel_Margin("     " + data.batteries_array[col -
                                          1].number.get_textual());
                    case 1:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].voltage.get_textual());
                    case 2:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].current.get_textual());
                    case 3:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].temperature.get_textual());
                    case 4:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].capacity.get_textual());
                    case 5:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                                 1].get_charge());
                    case 6:
                        return new JLabel_Margin(" " + data.batteries_array[col -
                                                 1].get_status(),
                                                 data.batteries_array[col -
                                                 1].get_alarm(),
                                                 ((data.batteries_array[col -
                                1].get_alarm() ==
                                1) ?
                                                  ((data.margin_red.get() == 1) ?
                                Color.red :
                                Color.black) : Color.black));
                    case 7:
                        return new JLabel_Margin(" " + data.batteries_array[col -
                                                 1].get_status(),
                                                 data.batteries_array[col -
                                                 1].get_alarm(),
                                                 ((data.batteries_array[col -
                                1].get_alarm() ==
                                1) ?
                                                  ((data.margin_red.get() == 1) ?
                                Color.red :
                                Color.black) : Color.black));


                    }
                }
                if ((col == 2)) {
                    switch (row) {
                    case 0:
                        return new JLabel_Margin("     " + data.batteries_array[col -
                                          1].number.get_textual());
                    case 1:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].voltage.get_textual());
                    case 2:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].current.get_textual());
                    case 3:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].temperature.get_textual());
                    case 4:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].capacity.get_textual());
                    case 5:
                        return new JLabel_Margin("  " + data.batteries_array[col -
                                          1].get_charge());
                    case 6:
                        return new JLabel_Margin(" " + data.batteries_array[col -
                                                 1].get_status(),
                                                 data.batteries_array[col -
                                                 1].get_alarm(),
                                                 ((data.batteries_array[col -
                                1].get_alarm() ==
                                1) ?
                                                  ((data.margin_red.get() == 1) ?
                                Color.red :
                                Color.black) : Color.black));
                    case 7:
                        /*return new JLabel_Margin(" " + data.batteries_array[col -
                                                 1].get_status(),
                                                 data.batteries_array[col -
                                                 1].get_alarm(),
                                                 ((data.batteries_array[col -
                                1].get_alarm() ==
                                1) ?
                                                  ((data.margin_red.get() == 1) ?
                                Color.red :
                                Color.black) : Color.black));*/
                        return new JLabel_Margin(" х"+ data.batteries_array[col -
                                                 1].alarm_state.alarm);
                    }
                }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        if (data.batteries_count.get() == 2) {
            TableColumn column1 = new TableColumn(0, 200, null, null);
            TableColumn column2 = new TableColumn(1, 50, new JLabel_Renderer(), null);
            TableColumn column3 = new TableColumn(2, 50, new JLabel_Renderer(), null);
            table.setBounds(50, 50, 330, 270);
            table.addColumn(column1);
            table.addColumn(column2);
            table.addColumn(column3);
        } else {
            TableColumn column1 = new TableColumn(0, 300, null, null);
            TableColumn column2 = new TableColumn(1, 50, new JLabel_Renderer(), null);
            table.setBounds(50, 50, 330, 270);
            table.addColumn(column1);
            table.addColumn(column2);
        }

        //       table.setGridColor(COLORIT);
        //      table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
        //      table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400,
                                           (data.batteries_count.get() == 1) ?
                                           210 : 240));
        table.setPreferredSize(new Dimension(400,
                                             (data.batteries_count.get() == 1) ?
                                             210 : 240));
        return table;

    }

    private JTable create_specfunctions_table() {

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

            int temp_int = data.batteries_count.get();

            public Object getValueAt(int row, int col) {
                if ((col == 0)) {
                    switch (row) {
                    case 0:
                        return new String(" Спецфункции");
                    }
                }
                if ((col == 1)) {
                    switch (row) {
                    case 0: {
                        String temp_str = new String();
                        if (data.specfunctions.get() == 10)
                            return new String("  ВЗ");
                        if ((0 < data.specfunctions.get()) &
                            (data.specfunctions.get() <= 10))
                            return new String("  КЕБ" +
                                              ((temp_int != 1) ?
                                               "№" + data.specfunctions.get() :
                                               ""));
                        return new String("  Выкл.");

                    }
                    }
                }
                return new String("No such parameter");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column1 = new TableColumn(0, (data.batteries_count.get() == 1) ?
                                              300 : 200, null, null);
        TableColumn column2 = new TableColumn(1, (data.batteries_count.get() == 1) ?
                                              50 : 134, null, null);
        table.setBounds(50, 50, 300, 30);
        table.addColumn(column1);
        table.addColumn(column2);


        //       table.setGridColor(COLORIT);
        //      table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
        //      table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        table.setMaximumSize(new Dimension(400,
                                           30));
        table.setPreferredSize(new Dimension(400,
                                             30));
        return table;

    }

    private JTable create_psus_table() {

        TableModel dataModel = new AbstractTableModel() {

            public int getColumnCount() {
                return 0;
            }

            public Class getColumnClass(int c) {
                return String.class;
            }

            public int getRowCount() {
                return (data.psus_count.get() + 1);
            }

            public Object getValueAt(int row, int col) {
                if (row == 0) {
                    switch (col) {
                    case 0:
                        return new String("   №");
                    case 1:
                        return new JLabel_Margin("  Состояние ");
                    case 2:
                        return new String("    Uвых, В");
                    case 3:
                        return new String("       I, А");
                    case 4:
                        return new String("     T, \u00B0C");
                    }
                }
                if (row > 0) {
                    switch (col) {
                    case 0:
                        return new String("     " + data.psus_array[row -
                                          1].number.get_textual());
                    case 1:
                        return new JLabel_Margin(data.psus_array[row - 1].get_status(),
                                                 data.psus_array[row - 1].get_alarm(),
                                                 ((data.psus_array[row - 1].get_alarm() ==
                                1) ?
                                ((data.margin_red.get() == 1) ? Color.red :
                                 Color.black) : Color.black));

                    case 2:
                        return new String("       " + data.psus_array[row -
                                          1].voltage.get_textual());
                    case 3:
                        return new String("       " + data.psus_array[row -
                                          1].current.get_textual());
                    case 4:
                        return new String("         " + data.psus_array[row -
                                          1].temperature.get_textual());
                    }
                }
                return new String("N/A");
            }
        };

        JTable table = new JTable(dataModel);
        table.setRowHeight(30);
        TableColumn column0 = new TableColumn(0, 1);
        TableColumn column1 = new TableColumn(1, 70, new JLabel_Renderer(), null);
        TableColumn column2 = new TableColumn(2, 30);
        TableColumn column3 = new TableColumn(3, 30);
        TableColumn column4 = new TableColumn(4, 30);
        table.addColumn(column0);
        table.addColumn(column1);
        table.addColumn(column2);
        table.addColumn(column3);
        table.addColumn(column4);
//        table.setGridColor(COLORIT);
//        table.setBorder(BorderFactory.createLineBorder(COLORIT));
        table.setCellSelectionEnabled(false);
        table.setAutoResizeMode(table.AUTO_RESIZE_OFF);

        table.setPreferredSize(new Dimension(table_width,
                                             (data.psus_count.get() + 1) * 30));
        table.setMaximumSize(new Dimension(table_width,
                                           (data.psus_count.get() + 1) * 30));
//        table.setBackground(COLOR_BACK);
        table.setFont(new Font("SanSerif", Font.PLAIN, 14));

        table.setFocusable(false);

        return table;

    }


    private int get_alarms() {
        int tempik = 0;
        /*if (data.battery_status.get() == data.BATTERY_LOST)
            tempik = 1;
                 if (data.voltage_circuit.get() < 180)
            tempik = 1;
                 if (data.external_jumper_1.get() == data.TRUE) tempik = 1;
                 if (data.external_jumper_2.get() == data.TRUE) tempik = 1;
                 if (data.external_jumper_3.get() == data.TRUE) tempik = 1;
                 if (data.external_jumper_4.get() == data.TRUE) tempik = 1;

         if (data.external_temperature_1.get() == data.TRUE) tempik = 1;
         if (data.external_temperature_2.get() == data.TRUE) tempik = 1;
         if (data.external_temperature_3.get() == data.TRUE) tempik = 1;
         */
        return tempik;
    }


    public void update_data() {
        if (data.need_correct_interface.get() == 1) {
            //  b.removeAll();
            this.removeAll();
            this.surface_decorator();
            data.need_correct_interface.set(0);
        }
    }


    public static void main(String[] args) {
        UKU_Data_Big data = new UKU_Data_Big();
        // data.psu_count = 10;
        data.batteries_count.set(3);
        data.psus_count.set(10);
        data.batteries_array[1].status.set(0x01);
        data.batteries_array[2].status.set(0x02);

        for (int i = 0; i < 10; i++) {
            data.psus_array[i].status.set(0x01 << i);
            data.psus_array[i].current.set(0x01 << i);
            data.batteries_array[i].voltage.set(0x01 << i);
            data.batteries_array[i].current.set(0x01 << i);
            data.batteries_array[i].temperature.set(0x01 << i);
            data.batteries_array[i].capacity.set(0x01 << i);
            data.batteries_array[i].charge.set(0x01 << i);
        }
        data.external_jumper_count.set(4);
        data.external_temperature_count.set(4);
        UKU_Panel_Big amplifier_panel = new UKU_Panel_Big(data);
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container content = frame.getContentPane();

        content.add(amplifier_panel);
        // content.setLayout(new BorderLayout());
        frame.setSize(amplifier_panel.desired_width,
                      amplifier_panel.desired_height);
        frame.setVisible(true);

        amplifier_panel.repaint();
        amplifier_panel.update_data();

    }

    public void update_panel() {
        this.update_data();
        this.repaint();
    }


}
