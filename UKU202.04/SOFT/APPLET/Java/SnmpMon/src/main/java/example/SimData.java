package example;

import org.snmp4j.agent.DuplicateRegistrationException;
import org.snmp4j.agent.MOServer;
import org.snmp4j.agent.mo.*;
import org.snmp4j.smi.Integer32;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.SMIConstants;
import org.snmp4j.smi.Variable;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Anatoly Danilov on 2/8/14.
 */
public class SimData {

    private static final Map<String, Integer32> values = new HashMap<>();
    private static final List<Integer32> valuesOfChange = new ArrayList<>();

    static {
        values.put("1.3.6.1.4.1.33183.14.2.2.0", new Integer32(1));
        values.put("1.3.6.1.4.1.33183.14.2.5.0", new Integer32(2));
        values.put("1.3.6.1.4.1.33183.14.2.6.0", new Integer32(3));
        values.put("1.3.6.1.4.1.33183.14.2.7.0", new Integer32(4));

        int i = 5;
        values.put("1.3.6.1.4.1.33183.14.3.1.0", new Integer32(i++));
        values.put("1.3.6.1.4.1.33183.14.3.2.0", new Integer32(i++));


    }

    public static final int BATTERIES_SIZE = 6;


    public static void registerSimData(MOServer server) throws DuplicateRegistrationException {
        Integer32 integer32 = new Integer32(56);
        for (Map.Entry<String, Integer32> entry : values.entrySet()) {
            MOScalar<Integer32> myScalar = new MOScalar<>(new OID(entry.getKey()),
                    MOAccessImpl.ACCESS_READ_CREATE,
                    entry.getValue());
            server.register(myScalar, null);
        }


        int i = 100;
        // PSUs
        DefaultMOTableModel<DefaultMOTableRow> psusTableModel = new DefaultMOTableModel<>();
        psusTableModel.addRow(new DefaultMOTableRow(new OID("1"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("2"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("3"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("4"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("5"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("6"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("7"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        psusTableModel.addRow(new DefaultMOTableRow(new OID("8"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));

        String psusOID = "1.3.6.1.4.1.33183.14.4.1";
        DefaultMOTable<DefaultMOTableRow, MOColumn, DefaultMOTableModel<DefaultMOTableRow>> psusTable = new DefaultMOTable<>(
                new OID(psusOID),
                new MOTableIndex(new MOTableSubIndex[]{new MOTableSubIndex(new OID(psusOID), SMIConstants.SYNTAX_INTEGER)}),
                new MOColumn[]{new MOColumn(1, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(2, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(3, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(4, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(5, SMIConstants.SYNTAX_INTEGER32)
                }, psusTableModel);

        server.register(psusTable, null);

        // SK
        i = 200;
        DefaultMOTableModel<DefaultMOTableRow> skModel = new DefaultMOTableModel<>();
        skModel.addRow(new DefaultMOTableRow(new OID("1"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        skModel.addRow(new DefaultMOTableRow(new OID("2"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        skModel.addRow(new DefaultMOTableRow(new OID("3"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));
        skModel.addRow(new DefaultMOTableRow(new OID("4"), new Variable[]{new Integer32(i++), new Integer32(i++), new Integer32(i++), new Integer32(i++)}));

        String skOID = "1.3.6.1.4.1.33183.14.15.1";
        DefaultMOTable<DefaultMOTableRow, MOColumn, DefaultMOTableModel<DefaultMOTableRow>> skTable = new DefaultMOTable<>(
                new OID(skOID),
                new MOTableIndex(new MOTableSubIndex[]{new MOTableSubIndex(new OID(skOID), SMIConstants.SYNTAX_INTEGER)}),
                new MOColumn[]{new MOColumn(1, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(2, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(3, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(4, SMIConstants.SYNTAX_INTEGER32),
                }, skModel);

        server.register(skTable, null);

        // DT Table
        i = 300;
        DefaultMOTableModel<DefaultMOTableRow> dtModel = new DefaultMOTableModel<>();
        dtModel.addRow(new DefaultMOTableRow(new OID("1"), new Variable[]{new Integer32(i++), new Integer32(i++)}));
        dtModel.addRow(new DefaultMOTableRow(new OID("2"), new Variable[]{new Integer32(i++), new Integer32(i++)}));
        dtModel.addRow(new DefaultMOTableRow(new OID("3"), new Variable[]{new Integer32(i++), new Integer32(i++)}));
        dtModel.addRow(new DefaultMOTableRow(new OID("4"), new Variable[]{new Integer32(i++), new Integer32(i++)}));

        String dtOID = "1.3.6.1.4.1.33183.14.17.1";
        DefaultMOTable<DefaultMOTableRow, MOColumn, DefaultMOTableModel<DefaultMOTableRow>> dtTable = new DefaultMOTable<>(
                new OID(dtOID),
                new MOTableIndex(new MOTableSubIndex[]{new MOTableSubIndex(new OID(dtOID), SMIConstants.SYNTAX_INTEGER)}),
                new MOColumn[]{new MOColumn(1, SMIConstants.SYNTAX_INTEGER32),
                        new MOColumn(2, SMIConstants.SYNTAX_INTEGER32),
                }, dtModel);

        server.register(dtTable, null);

        // display MakbVoltage
        i = 400;
        DefaultMOTableModel<DefaultMOTableRow> mAkbModel = new DefaultMOTableModel<>();

        for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
            Variable[] variables = new Variable[16];
            for (int indexVar = 0; indexVar < variables.length; indexVar++) {
                Integer32 integer321 = new Integer32(i++);
                variables[indexVar] = integer321;
                valuesOfChange.add(integer321);
            }
            mAkbModel.addRow(new DefaultMOTableRow(new OID(String.valueOf(rowIndex + 1)), variables));

        }

        String mAkbOID = "1.3.6.1.4.1.33183.14.16.1";
        MOColumn[] moColumns = new MOColumn[16];

        for (int columnINdex = 0; columnINdex < moColumns.length; columnINdex++) {
            moColumns[columnINdex] = new MOColumn(columnINdex + 1, SMIConstants.SYNTAX_INTEGER32);
        }

        DefaultMOTable<DefaultMOTableRow, MOColumn, DefaultMOTableModel<DefaultMOTableRow>> mAkbTable = new DefaultMOTable<>(
                new OID(mAkbOID),
                new MOTableIndex(new MOTableSubIndex[]{new MOTableSubIndex(new OID(mAkbOID), SMIConstants.SYNTAX_INTEGER)}),
                moColumns, mAkbModel);

        server.register(mAkbTable, null);
        // batteries common info

        i = 500;
        DefaultMOTableModel<DefaultMOTableRow> battModel = new DefaultMOTableModel<>();

        for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
            Variable[] variables = new Variable[BATTERIES_SIZE];
            for (int indexVar = 0; indexVar < variables.length; indexVar++) {
                Integer32 integer321 = new Integer32(i++);
                variables[indexVar] = integer321;
                valuesOfChange.add(integer321);
            }
            battModel.addRow(new DefaultMOTableRow(new OID(String.valueOf(rowIndex + 1)), variables));

        }


        String battOID = "1.3.6.1.4.1.33183.14.5.1";
        MOColumn[] battColumns = new MOColumn[BATTERIES_SIZE];

        for (int columnINdex = 0; columnINdex < battColumns.length; columnINdex++) {
            battColumns[columnINdex] = new MOColumn(columnINdex + 1, SMIConstants.SYNTAX_INTEGER32);
        }

        DefaultMOTable<DefaultMOTableRow, MOColumn, DefaultMOTableModel<DefaultMOTableRow>> battTable = new DefaultMOTable<>(
                new OID(battOID),
                new MOTableIndex(new MOTableSubIndex[]{new MOTableSubIndex(new OID(battOID), SMIConstants.SYNTAX_INTEGER)}),
                battColumns, battModel);

        server.register(battTable, null);

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    try {
                        Thread.sleep(500);

                    for (Integer32 integer321 : valuesOfChange) {
                        Thread.sleep(1000);
                        if (integer321.toInt() > 100)
                            integer321.setValue(integer321.toInt() / 10);
                        else
                            integer321.setValue(integer321.toInt() * 10);
                    }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }, "sim-data-changer").start();
    }
}
