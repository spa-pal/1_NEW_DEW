package uku_control;

import java.util.regex.*;

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
public class Alarm_Event {

    public Integer_Value device_type = new Integer_Value(0);
    public static final int BATTERY_TYPE = 0x42;
    public static final int PSU_TYPE = 0x53;
    public static final int INVERTOR_TYPE = 0x49;
    public static final int UKU_TYPE = 0x55;
    public static final int POWER_LINE_TYPE = 0x50;
    public static final int TEMPERATURE_SENSOR = 0x54;
    public static final int EXTERNAL_JUMPER = 0x4C;

    public Integer_Value device_number = new Integer_Value(0);

    public Integer_Value event_type = new Integer_Value(0);
    public static final int LOW_POWER_VOLTAGE = 0x41;
    public static final int CONNECTION_LOST = 0x4C;
    public static final int DEVICE_LOST = 0x43;
    public static final int HIGH_VOLTAGE = 0x55;
    public static final int LOW_VOLTAGE = 0x75;
    public static final int TEMPERATURE_EVENT = 0x54;
    public static final int RELOAD_PROCESSOR = 0x52;
    public static final int BATTERY_ASSYMETRY = 0x53;

    public Integer_Value year_start = new Integer_Value(0);
    public Integer_Value month_start = new Integer_Value(0);
    public Integer_Value day_start = new Integer_Value(0);
    public Integer_Value hour_start = new Integer_Value(0);
    public Integer_Value minute_start = new Integer_Value(0);
    public Integer_Value second_start = new Integer_Value(0);

    public Integer_Value is_finished = new Integer_Value(0);

    public Integer_Value year_finished = new Integer_Value(0);
    public Integer_Value month_finished = new Integer_Value(0);
    public Integer_Value day_finished = new Integer_Value(0);
    public Integer_Value hour_finished = new Integer_Value(0);
    public Integer_Value minute_finished = new Integer_Value(0);
    public Integer_Value second_finished = new Integer_Value(0);

    public String event_string = new String("Обновление");


    public String[] eventColumns; // Хранить будем тута РАЗБИТУЮ строку


    private String oid = new String("1.1");
    public String getOID(){
        return oid;
    }

    public void setOID(String oid){
        this.oid = oid;
    }
    /**
     * Отпарсим строку. Разобьём по ключу '@'- САБАКА
     * @param event String
     */
    public void parseEvent(String event){
        event_string = event;
      if (event != null)
        eventColumns = (Pattern.compile("@")).split(event);
    else
        eventColumns = new String[]{new String("NUl")};
    }

    /**
     * Возвращает строковое значение для отображения в таблице событий
     * @param n int
     *  Номер колонки. Начинаем с НУЛЯ! %)
     * @return String
     */
    public String getEventColumn(int n){
        if (n < 0 || eventColumns == null) {
            return new String(" Загрузка...");
        }
        if (n > eventColumns.length - 1){
            return new String(" МИМО! "); // На случай, если строка неправильно распарсилась, либо строка неправильная :)
        }else{
            return eventColumns[n];
        }


    }


    public String get_textual() {
        String event_text = new String("");

        switch (this.event_type.get()) {
        case LOW_POWER_VOLTAGE:
            if (this.device_type.get() == this.POWER_LINE_TYPE)
                event_text = event_text + " Авария, Uсети занижено.";
            break;
        case CONNECTION_LOST:
            event_text = event_text + " Авария, отсутствует связь с";
            if (this.device_type.get() == this.PSU_TYPE)
                event_text = event_text + " БПС №";
            else
                event_text = event_text + " инвертором №";

            event_text = event_text + Integer.toString(device_number.get()+1) + ".";
            break;
        case DEVICE_LOST:
            event_text = event_text + " Авария, батарея №" +
                         Integer.toString(device_number.get()+1) + " не подключена.";
            break;
        case HIGH_VOLTAGE:
            event_text = event_text + " Авария, завышено выходное напряжение.";
            if (this.device_type.get() == this.PSU_TYPE)
                event_text = event_text + " БПС №";
            else
                event_text = event_text + " Инвертор №";

            event_text = event_text + Integer.toString(device_number.get()+1) + ".";

            break;
        case LOW_VOLTAGE:
            event_text = event_text + " Авария, занижено выходное напряжение.";
            if (this.device_type.get() == this.PSU_TYPE)
                event_text = event_text + " БПС №";
            else
                event_text = event_text + " Инвертор №";

            event_text = event_text + Integer.toString(device_number.get()+1) + ".";
            break;
        case TEMPERATURE_EVENT:
            if (this.device_type.get() == this.PSU_TYPE)
                event_text = event_text + " Авария, БПС №" +
                             Integer.toString(device_number.get()+1) + " перегрет";
            else if (this.device_type.get() == this.INVERTOR_TYPE)
                event_text = event_text + " Авария, Инвертор №" +
                             Integer.toString(device_number.get()+1) + " перегрет";
            else if (this.device_type.get() == this.TEMPERATURE_SENSOR)
                event_text = event_text + " Авария, температура внешнего датчика №" +
                             Integer.toString(device_number.get()+1) + " не в допуске.";

            break;
        case RELOAD_PROCESSOR:
             event_text = event_text + " Перезагрузка ЦП";
             break;
        case BATTERY_ASSYMETRY:
            event_text = event_text + " Асимметрия батареи №" +
                             Integer.toString(device_number.get()+1);
            break;
        default: event_text = event_text + " НЕ ОПРЕДЕЛЕНО" + Integer.toString(this.event_type.get());
            break;
        }

        event_text = event_text + "\n\r       ";

        if (this.event_type.get()==BATTERY_ASSYMETRY){
            event_text = event_text + " Зафиксированно  ";
        }
        else {
            event_text = event_text + " Начало: ";
        }
        event_text = event_text +
                    ((day_start.get() < 10) ? "0" : "") + day_start.get() +
                    "." +
                    ((month_start.get() < 10) ? "0" : "") + month_start.get() +
                    "." +
                    ((year_start.get() < 10) ? "0" : "") + year_start.get() +
                    " " +
                    ((hour_start.get() < 10) ? "0" : "") + hour_start.get() +
                    ":" +
                    ((minute_start.get() < 10) ? "0" : "") + minute_start.get() +
                    ":" +
                    ((second_start.get() < 10) ? "0" : "") + second_start.get() +
                    " ";
       if (this.is_finished.get() == 1)  event_text = event_text + "\n\r        Окончание: " +
                    ((day_finished.get() < 10) ? "0" : "") + day_finished.get() +
                    "." +
                    ((month_finished.get() < 10) ? "0" : "") + month_finished.get() +
                    "." +
                    ((year_finished.get() < 10) ? "0" : "") + year_finished.get() +
                    " " +
                    ((hour_finished.get() < 10) ? "0" : "") + hour_finished.get() +
                    ":" +
                    ((minute_finished.get() < 10) ? "0" : "") + minute_finished.get() +
                    ":" +
                    ((second_finished.get() < 10) ? "0" : "") + second_finished.get();
            else if ((this.event_type.get() != RELOAD_PROCESSOR)&&(this.event_type.get() != BATTERY_ASSYMETRY)) event_text = event_text + "\n\r        Не устранена. ";


        return event_text + "\n\r\n\r";
    }

    public Alarm_Event() {
        super();
    }
}
