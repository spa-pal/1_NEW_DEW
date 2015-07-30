package uku_control;

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
public class Special_Settings {

    /*  Parameters available  */

    public static final int PRIMARY_BPS = 0x14;
    public static final int SOUND_ALARM = 0x28;
    public static final int AUTO_ALARM_SWITCH_OFF = 0x29;
    public static final int BATTERY_LOST_CHECK = 0x2A;
    public static final int MAX_VOLTAGE_BPS_ALARM = 0x31;
    public static final int VOLTAGE_NEEDED_0_DEG_ENV = 0x32;

    /*   Parameters' screen view types  */

    public static final int NONE = 0x00;
    public static final int ZERO_TO_ONE = 0x01;
    public static final int ENABLED_DISABLED = 0x02;
    public static final int MANUAL_AUTO = 0x03;
    public static final int MULTIPLIED = 0x04;

    /*    Settings sets   */


    // public int[] sets[] = new int[15][40];
    public int sets_deep[] = new int[15];
    public SParameters_Set sets[] = new SParameters_Set[50];
    public Special_Parameters parameters[] = new Special_Parameters[50];
    public Integer_Value active_set = new Integer_Value(1);

    public Special_Settings() {
        /*   sets_deep[0] = 15;
           sets[0][0] = 20; //0x14;
           sets[0][1] = 40; //(0x28)
           sets[0][2] = 42; //(0x2A)
           sets[0][3] = 50; //(0x32)
           sets[0][4] = 51; //(0x33)
           sets[0][5] = 52; //(0x34)
           sets[0][6] = 53; //(0x35)
           sets[0][7] = 54; //(0x36)
           sets[0][8] = 55; //(0x37)
           sets[0][9] = 56; //(0x38)
           sets[0][10] = 57; //(0x39)
           sets[0][11] = 58; //(0x3A)
           sets[0][12] = 59; //(0x3B)
           sets[0][13] = 60; //(0x3C)
           sets[0][14] = 61; //(0x3D)
         */
        for (int i = 0; i < 15; i++) {
            sets[i] = new SParameters_Set();
            sets[i].ID.set(i);
        }

        parameters[0] = new Special_Parameters(0x14,
                                               "�������� ��������  �", "", 1,
                                               Special_Settings.ZERO_TO_ONE,
                                               "�������� �������� � ����� � ����������� ���������� (1 ��� 2)",
                                               1, 1, 2);
        parameters[1] = new Special_Parameters(0x28,
                                               "�������� ������������", "", 1,
                                               Special_Settings.
                                               ENABLED_DISABLED,
                                               "���������/���������� ��������� ���������� �� ������� � �������",
                                               1);
        parameters[2] = new Special_Parameters(0x29,
                                               "���������� ������� ������", "",
                                               1,
                                               Special_Settings.MANUAL_AUTO,
                                               "�������������� ������ ��������� ������������ ��� ���������� ��������� ������",
                                               1);

        parameters[3] = new Special_Parameters(0x2A,
                                               "����� �������� ���� ������� (���.)",
                                               "", 0, Special_Settings.NONE,
                                               "������ �������� ������� ������� (5 - 60 ���.)",
                                               1, 5, 60);

        parameters[4] = new Special_Parameters(0x31,
                                               "Umax (�)",
                                               "", 0, Special_Settings.NONE,
                                               "������������ ���������� �����, ��� ���������� � ������ (20 - 80 �)",
                                               1, 20, 80);

        parameters[5] = new Special_Parameters(0x32,
                                               "U� 0\u00B0C (�)",
                                               "", 0,
                                               Special_Settings.MULTIPLIED,
                                               "����������, ����������� ��� ���������� ������� ��� 0\u00B0C ���������� ����� (20.0 - 80.0 �)",
                                               10, 200, 800);

        parameters[6] = new Special_Parameters(0x33,
                                               "U� 20\u00B0C (�)",
                                               "", 0,
                                               Special_Settings.MULTIPLIED,
                                               "����������, ����������� ��� ���������� ������� ��� 20\u00B0C ���������� ����� (20.0 - 80.0 �)",
                                               10, 200, 800);

        parameters[7] = new Special_Parameters(0x34,
                                               "U����. (�)",
                                               "", 0, Special_Settings.NONE,
                                               "����������� ���������� �������, �������� ���� �������� ��������� ������� ��� ������ �������� (20-80 �)",
                                               1, 20, 80);

        parameters[8] = new Special_Parameters(0x35,
                                               "Umin.���� (�)",
                                               "", 5, Special_Settings.NONE,
                                               "����������� ���������� ��������� ����, �������� ���� �������� ��������� ������� (150 - 250 �)",
                                               1, 150, 250);

        parameters[9] = new Special_Parameters(0x36,
                                               "U0� (�)",
                                               "", 5,
                                               Special_Settings.MULTIPLIED,
                                               "����������, �������������� ������, ��� ������ ��� �������(���� �� ������� (20.0 - 80.0 �))",
                                               10, 200, 800);

        parameters[10] = new Special_Parameters(0x37,
                                                "I��. (�)",
                                                "", 5,
                                                Special_Settings.MULTIPLIED,
                                                "����������� ��� �������, ������������ ��� �������� ������� ������� (0.01 - 10.00 �)",
                                                100, 1, 1000);

        parameters[11] = new Special_Parameters(0x38,
                                                "I�.max. (�)",
                                                "", 5,
                                                Special_Settings.MULTIPLIED,
                                                "����������� ���� ������ ������� (1.0 - 100.0 �)",
                                                10, 10, 1000);

        parameters[12] = new Special_Parameters(0x39,
                                                "Imax (�)",
                                                "", 5,
                                                Special_Settings.MULTIPLIED,
                                                "������������ ��� ������ ���� (1.0 - 30.0 �)",
                                                10, 10, 300);

        parameters[13] = new Special_Parameters(0x3A,
                                                "Kimax",
                                                "", 5,
                                                Special_Settings.MULTIPLIED,
                                                "�����������, ������������ ������ � Imax ��� ����������� ���������� ����������� ����� � ����������� �� �������� (5 - 10)",
                                                10, 5, 10);
        parameters[14] = new Special_Parameters(0x3B,
                                                "K���.���.",
                                                "", 5,
                                                Special_Settings.MULTIPLIED,
                                                "�����������, ���������� ������ ����� � ������ �������������� ������ (1.005 - 1.030)",
                                                1000, 1005, 1030);
        parameters[15] = new Special_Parameters(0x3C,
                                                "T�.���.�.�. (�)",
                                                "", 5, Special_Settings.NONE,
                                                "����� �������� ��������� ����� ����� ��������� ���������� �������� ���� (0 - 3 �)",
                                                1, 0, 3);
        parameters[16] = new Special_Parameters(0x3D,
                                                "tmax (\u00B0C)",
                                                "", 5, Special_Settings.NONE,
                                                "������������ ����������� �����, ���������� ������� ��������� ������� (40 - 100 \u00B0C) ",
                                                1, 40, 100);

        parameters[17] = new Special_Parameters(0x47,
                                                "��� 1-� �������",
                                                "", 0,
                                                Special_Settings.ENABLED_DISABLED,
                                                "��������� ��� 1-�� �������",
                                                1);
        parameters[18] = new Special_Parameters(0x48,
                                                "��� 2-� �������",
                                                "", 0,
                                                Special_Settings.ENABLED_DISABLED,
                                                "��������� ��� 2-�� �������",
                                                1);
        parameters[19] = new Special_Parameters(0x49,
                                                "������ ��� 2 (�.)",
                                                "", 1, Special_Settings.NONE,
                                                "������ ��� 2-�� ������ (1 - 24 �.)",
                                                1, 1, 24);
        parameters[20] = new Special_Parameters(0x50,
                                                "������� ���������� �����������",
                                                "", 1, Special_Settings.NONE,
                                                "������� ���������� ����������� (1-11)",
                                                1, 1, 11);

        sets[1].deep.set(0);

        sets[1].parameters[0] = parameters[0];
        sets[1].parameters[1] = parameters[1];
        sets[1].parameters[2] = parameters[3];
        sets[1].parameters[3] = parameters[5];
        sets[1].parameters[4] = parameters[6];
        sets[1].parameters[5] = parameters[7];
        sets[1].parameters[6] = parameters[8];
        sets[1].parameters[7] = parameters[9];
        sets[1].parameters[8] = parameters[10];
        sets[1].parameters[9] = parameters[11];
        sets[1].parameters[10] = parameters[12];
        sets[1].parameters[11] = parameters[13];
        sets[1].parameters[12] = parameters[14];
        sets[1].parameters[13] = parameters[15];
        sets[1].parameters[14] = parameters[16];
        sets[1].parameters[15] = parameters[17];
        sets[1].parameters[16] = parameters[18];
        sets[1].parameters[17] = parameters[19];

        sets[2].deep.set(0);

        sets[2].parameters[0] = parameters[0];
        sets[2].parameters[1] = parameters[1];
        sets[2].parameters[2] = parameters[3];
        sets[2].parameters[3] = parameters[5];
        sets[2].parameters[4] = parameters[6];
        sets[2].parameters[5] = parameters[7];
        sets[2].parameters[6] = parameters[8];
        sets[2].parameters[7] = parameters[9];
        sets[2].parameters[8] = parameters[10];
        sets[2].parameters[9] = parameters[11];
        sets[2].parameters[10] = parameters[12];
        sets[2].parameters[11] = parameters[13];
        sets[2].parameters[12] = parameters[14];
        sets[2].parameters[13] = parameters[15];
        sets[2].parameters[14] = parameters[16];
        sets[2].parameters[15] = parameters[17];
        sets[2].parameters[16] = parameters[18];
        sets[2].parameters[17] = parameters[19];
        sets[2].parameters[18] = parameters[20];

    }
}
