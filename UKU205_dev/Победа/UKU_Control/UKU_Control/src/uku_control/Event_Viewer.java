package uku_control;

import javax.swing.*;
import java.awt.Font;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import javax.swing.table.AbstractTableModel;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.border.EtchedBorder;

/**
 * <p>Title: UKU Control</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Anatoly (c) 2007</p>
 *
 * <p>Company: </p>
 *
 * @author not attributable
 * @version 1.0
 */
public class Event_Viewer {

    private static JDialog viewer = new JDialog();
    private UKU_Data_Big data;
    private JTable eventsTable;
    private int table_width = 700;              // Поиграем шириной, чтобы получить приемлемое отображение :)
    private static Box b = Box.createVerticalBox();
    private JScrollPane scroll_pane;
    private EventsTableModel eventsModel;

    public Event_Viewer(UKU_Data_Big data) {
        this.data = data;
        viewer.setTitle("Журнал аварий");
        viewer.setSize(750,600);
        UIManager.put("Box.background", new Color(240, 255, 255));


        surfaceDecorator();
    }

    /**
     * surfaceD_decorator
     */
    private synchronized void surfaceDecorator() {
        try {
            if (scroll_pane != null){
                viewer.remove(scroll_pane);
            }
        }catch(Exception ex){
            ex.printStackTrace();
        }
        /*
         * Создадим таблицу
         * */

        try {
        	eventsModel = new EventsTableModel(data);
            eventsTable = new JTable(eventsModel);			//createEventsTable();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        eventsTable.setRowHeight(20);




        eventsTable.setCellSelectionEnabled(false);
        eventsTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

        adjustTableWidths();
/*
        eventsTable.setPreferredSize(new Dimension(table_width,
                                             (data.events_quantity.get() + 1) * 30));
        eventsTable.setMaximumSize(new Dimension(table_width,
                                           (data.events_quantity.get() + 1) * 30));*/

        eventsTable.setFont(new Font("SanSerif", Font.PLAIN, 12));

        eventsTable.setFocusable(false);

        eventsTable.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.RAISED));

        b = Box.createVerticalBox();
        b.add(Box.createVerticalStrut(15));
        b.add(eventsTable);

        /* area.setEditable(false);
         area.setFont(new Font("sanserif", Font.PLAIN, 12));*/
        scroll_pane = new JScrollPane(b);
        viewer.add(scroll_pane);

    }

    /**
     * Для изменения размеров таблицы/колонок. покрути тута, ок?
     */
    private void adjustTableWidths(){
    	eventsTable.getColumnModel().getColumn(0).setPreferredWidth(150);
        eventsTable.getColumnModel().getColumn(1).setPreferredWidth(100);
        eventsTable.getColumnModel().getColumn(2).setPreferredWidth(300);
        //eventsTable.getColumnModel().getColumn(3).setPreferredWidth(0);
        eventsTable.setPreferredSize(new Dimension(table_width,
                (data.events_quantity.get() + 1) * 20));
        eventsTable.setMaximumSize(new Dimension(table_width,
              (data.events_quantity.get() + 1) * 20));

    }

    private class EventsTableModel extends AbstractTableModel{

    	private UKU_Data_Big data;

    	public EventsTableModel(UKU_Data_Big data){
    		this.data = data;
    	}

		public int getColumnCount() {
			// TODO Auto-generated method stub
			return 3;
		}

		public int getRowCount() {
			// TODO Auto-generated method stub
			return data.events_quantity.get() + 1;
		}

		public Object getValueAt(int row, int col) {
			if (row == 0) {
                switch (col) {
                case 0:
                    return new String(" Событие");
                case 1:
                    return new String(" Дата и время ");
                case 2:
                    return new String(" Дополнительные сведения ");
                case 3:
                    return new String(" Время");
                /*case 4:
                    return new String("Колонка 5");*/
                }
            }
            if (row > 0) {
                    return data.events[row - 1].getEventColumn(col);
            }
            return new String("N/A");
        }

    }

    public void show_events(){
       // update_viewer();
        this.viewer.setVisible(true);

    }

    public synchronized void update_viewer() {
       // surfaceDecorator();
    	eventsModel.fireTableStructureChanged();
    	adjustTableWidths();
       /* try {
            Thread.sleep(4000);
        } catch (InterruptedException ex) {
        }*/
    //   b.repaint();
          viewer.repaint();
        //scroll_pane.repaint();
        //viewer.setSize(viewer.getSize());

        //viewer.setVisible(true);


/*        String temp_str = new String();
        //data.events_quantity.set(1);
        for (int i = 0; i < data.events_quantity.get(); i++) {
            temp_str = temp_str + (((i + 1) < 10)?" ":"") + (i + 1) + " " + data.events[i].get_textual();
        }
        if (data.events_quantity.get() == 0)
            temp_str = "В журнале нет записей";
        area.setText(temp_str);
        area.repaint();
//        this.viewer.setVisible(true);*/

    }

    public void dispose() {
        viewer = null;
    }

    public static void main(String[] args) {
        UKU_Data_Big data = new UKU_Data_Big();
        data.events_quantity.set(3);
        data.events[0].parseEvent(" 1 @ 2 @ 3 @ 4 @ 5 ");
        data.events[1].parseEvent("1@2@3@4@5");
        data.events[2].parseEvent("1@2@3@4@5");

        Event_Viewer viewer = new Event_Viewer(data);

        viewer.show_events();

        try {
            Thread.sleep(10);
            data.events_quantity.set(6);
            viewer.update_viewer();
            //Thread.sleep(1000);
            data.events[3].parseEvent("1@2@3@4@5");
            //viewer.update_viewer();
            //viewer.dispose();
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
        catch (Exception ex){
            ex.printStackTrace();
        }finally{

        }

    }



}
