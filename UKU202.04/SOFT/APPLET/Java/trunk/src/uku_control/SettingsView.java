package uku_control;

import uku_control.config.Parameter;
import uku_control.config.SettingParameter;
import uku_control.config.StatusMapping;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

/**
 * Created by Anatoly Danilov on 6/24/2015.
 * For the pleasure
 */
public enum SettingsView {
    Simple {
        @Override
        public JComponent getView(final SettingParameter settingParameter) {
            final Box horizontalBox = Box.createHorizontalBox();
            final JTextField valueHolder = new JTextField("");

            valueHolder.setText(settingParameter.getTextValue());
            valueHolder.setHorizontalAlignment(valueHolder.RIGHT);
            valueHolder.setMaximumSize(new Dimension(150, 23));
            valueHolder.setMinimumSize(valueHolder.getMaximumSize());
            valueHolder.setPreferredSize(valueHolder.getMaximumSize());

            valueHolder.setFont(new Font("SanSerif", Font.PLAIN, 12));
            valueHolder.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            JButton applyChanges = new JButton("Применить");
            applyChanges.setBackground(Util.BACKGROUND);
            applyChanges.setForeground(Color.white);
            applyChanges.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            applyChanges.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    String newValue = valueHolder.getText();
                    int result = JOptionPane.showConfirmDialog(horizontalBox, "Установить новое значение: " + newValue + " ?");
                    if (result != JOptionPane.OK_OPTION)
                        return;

                    try {
                        UKU_Connection_SNMP.writeParameter(settingParameter, newValue);
                        UKU_Connection_SNMP.readParameter(settingParameter);
                    } catch (Exception e1) {
                        e1.printStackTrace();
                        JOptionPane.showMessageDialog(horizontalBox, "Невозможно выполнить команду: " + e1.getMessage(), "Ошибка команды", JOptionPane.ERROR_MESSAGE);
                    }
                }
            });

            settingParameter.addChangeListener(new ChangeListener() {
                @Override
                public void stateChanged(final ChangeEvent e) {
                    SwingUtilities.invokeLater(new Runnable() {
                        public void run() {
                            Object source = e.getSource();
                            if (source != settingParameter)
                                return;

                            valueHolder.setText(settingParameter.getTextValue());
                        }
                    });
                }
            });

            horizontalBox.add(valueHolder);

            horizontalBox.add(Box.createHorizontalStrut(10));
            horizontalBox.add(applyChanges);
            return horizontalBox;
        }
    },
    ComboBox {
        @Override
        public JComponent getView(final SettingParameter settingParameter) {
            final Box horizontalBox = Box.createHorizontalBox();
            final JComboBox valueHolder = new JComboBox();
            valueHolder.setBounds(new Rectangle(166, 91, 55, 23));
            valueHolder.setForeground(new Color(117, 177, 217));
            valueHolder.setUI(new User_ComboBoxUI());
//            valueHolder.setFont(new Font("Times New Roman", Font.BOLD, 14));
            valueHolder.setForeground(new Color(117, 177, 217));
            valueHolder.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            valueHolder.setAutoscrolls(true);
            valueHolder.setEditable(false);
            valueHolder.setEnabled(false);
            final Parameter<Integer> reference = settingParameter.getReference();
            if (reference == null)
                return new JLabel("Invalid config. missing reference oid");

            reference.addChangeListener(new ChangeListener() {
                @Override
                public void stateChanged(final ChangeEvent e) {
                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            Object selectedItem = valueHolder.getSelectedItem();
                            if (reference.getValue() == null) {
                                return;
                            }
                            resetCombobox(valueHolder, reference.getValue());
                            valueHolder.setEnabled(true);
                            valueHolder.setSelectedItem(selectedItem);

                        }
                    });
                }
            });
            valueHolder.setMaximumSize(new Dimension(54, 23));
            valueHolder.setMinimumSize(valueHolder.getMaximumSize());
            valueHolder.setPreferredSize(valueHolder.getMaximumSize());

            valueHolder.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            JButton applyChanges = new JButton("Применить");
            applyChanges.setBackground(Util.BACKGROUND);
            applyChanges.setForeground(Color.white);
            applyChanges.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            applyChanges.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    String newValue = String.valueOf(valueHolder.getSelectedItem());
                    if (newValue == null)
                        return;
                    int result = JOptionPane.showConfirmDialog(horizontalBox, "Установить новое значение: " + newValue + " ?");
                    if (result != JOptionPane.OK_OPTION)
                        return;

                    try {
                        UKU_Connection_SNMP.writeParameter(settingParameter, Integer.parseInt(newValue.trim()));
                        UKU_Connection_SNMP.readParameter(settingParameter);
                    } catch (Exception e1) {
                        e1.printStackTrace();
                        JOptionPane.showMessageDialog(horizontalBox, "Невозможно выполнить команду: " + e1.getMessage(), "Ошибка команды", JOptionPane.ERROR_MESSAGE);
                    }
                }
            });

            settingParameter.addChangeListener(new ChangeListener() {
                @Override
                public void stateChanged(final ChangeEvent e) {
                    SwingUtilities.invokeLater(new Runnable() {
                        public void run() {
                            Object source = e.getSource();
                            if (source != settingParameter)
                                return;


                            Integer selectedIndex = (Integer) settingParameter.getValue();
                            if (selectedIndex == null)
                                return;

                            if (valueHolder.getItemCount() < (selectedIndex))
                                resetCombobox(valueHolder, selectedIndex);
                            valueHolder.setSelectedItem(selectedIndex);
                        }
                    });
                }
            });

            horizontalBox.add(valueHolder);

            horizontalBox.add(Box.createHorizontalStrut(10));
            horizontalBox.add(applyChanges);
            return horizontalBox;
        }

        private void resetCombobox(JComboBox valueHolder, Integer newSize) {
            valueHolder.removeAllItems();
            for (int i = 1; i <= newSize; i++) {
                valueHolder.addItem(" " + String.valueOf(i));
            }
        }
    },
    LittleStep {
        @Override
        public JComponent getView(final SettingParameter settingParameter) {
            final Box horizontalBox = Box.createHorizontalBox();
            final JTextField value = new JTextField("");

            value.setText(settingParameter.getTextValue());
            value.setHorizontalAlignment(value.RIGHT);
            value.setMaximumSize(new Dimension(50, 23));
            value.setMinimumSize(value.getMaximumSize());
            value.setPreferredSize(value.getMaximumSize());

            value.setFont(new Font("SanSerif", Font.PLAIN, 12));
            value.setBorder(BorderFactory.createLineBorder(Color.BLUE));
            value.setEditable(false);

            JButton decrement = new JButton("<");
            decrement.setBackground(new Color(112, 177, 217));
            decrement.setForeground(Color.white);
            decrement.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            decrement.setMaximumSize(new Dimension(23, 23));
            decrement.setMinimumSize(decrement.getMaximumSize());
            decrement.setPreferredSize(decrement.getMaximumSize());
            decrement.addActionListener(new StepListener(settingParameter, horizontalBox, -1));

            JButton increment = new JButton(">");
            increment.setBackground(new Color(112, 177, 217));
            increment.setForeground(Color.white);
            increment.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            increment.setMaximumSize(new Dimension(23, 23));
            increment.setMinimumSize(decrement.getMaximumSize());
            increment.setPreferredSize(decrement.getMaximumSize());
            increment.addActionListener(new StepListener(settingParameter, horizontalBox, +1));

            settingParameter.addChangeListener(new ChangeListener() {
                @Override
                public void stateChanged(final ChangeEvent e) {
                    SwingUtilities.invokeLater(new Runnable() {
                        public void run() {
                            Object source = e.getSource();
                            if (source != settingParameter)
                                return;

                            value.setText(settingParameter.getTextValue());
                        }
                    });
                }
            });

            horizontalBox.add(decrement);
            horizontalBox.add(horizontalBox.createHorizontalStrut(5));
            horizontalBox.add(value);
            horizontalBox.add(horizontalBox.createHorizontalStrut(5));
            horizontalBox.add(increment);
            return horizontalBox;
        }
    },
    Toggle {
        @Override
        public JComponent getView(final SettingParameter settingParameter) {
            final Box horizontalBox = Box.createHorizontalBox();

            List<StatusMapping> statusMappings = settingParameter.getStatusMappings();
            final StatusMapping statusMapping1 = statusMappings.get(0);
            StatusMapping statusMapping2 = statusMappings.get(1);
            final JButton state_1 = new JButton(statusMapping1.getValue());
            state_1.setBackground(new Color(112, 177, 217));
            state_1.setForeground(Color.white);
            state_1.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            state_1.setMaximumSize(new Dimension(50, 23));
            state_1.setMinimumSize(state_1.getMaximumSize());
            state_1.setPreferredSize(state_1.getMaximumSize());
            state_1.addActionListener(new SetState(settingParameter, horizontalBox, statusMapping1.getMask()));

            final JButton state_2 = new JButton(statusMapping2.getValue());
            state_2.setBackground(new Color(112, 177, 217));
            state_2.setForeground(Color.white);
            state_2.setBorder(BorderFactory.createLineBorder(Color.BLUE));

            state_2.setMaximumSize(new Dimension(50, 23));
            state_2.setMinimumSize(state_1.getMaximumSize());
            state_2.setPreferredSize(state_1.getMaximumSize());
            state_2.addActionListener(new SetState(settingParameter, horizontalBox, statusMapping2.getMask()));
            settingParameter.addChangeListener(new ChangeListener() {
                @Override
                public void stateChanged(final ChangeEvent e) {
                    SwingUtilities.invokeLater(new Runnable() {
                        public void run() {
                            Object source = e.getSource();
                            if (source != settingParameter)
                                return;

                            if (settingParameter.getValue() == null) {
                                state_1.setBackground(Constants.DISABLED_COLOR);
                                state_2.setBackground(Constants.DISABLED_COLOR);
                            } else if ((Integer) settingParameter.getValue() == statusMapping1.getMask()) {
                                state_1.setBackground(Constants.ENABLED_COLOR);
                                state_2.setBackground(Constants.DISABLED_COLOR);
                            } else {
                                state_1.setBackground(Constants.DISABLED_COLOR);
                                state_2.setBackground(Constants.ENABLED_COLOR);
                            }
                        }
                    });
                }
            });
            if (settingParameter.getValue() == null) {
                state_1.setBackground(Constants.DISABLED_COLOR);
                state_2.setBackground(Constants.DISABLED_COLOR);
            } else if ((Integer) settingParameter.getValue() == statusMapping1.getMask()) {
                state_1.setBackground(Constants.ENABLED_COLOR);
                state_2.setBackground(Constants.DISABLED_COLOR);
            } else {
                state_1.setBackground(Constants.DISABLED_COLOR);
                state_2.setBackground(Constants.ENABLED_COLOR);
            }
            horizontalBox.add(state_1);
            horizontalBox.add(horizontalBox.createHorizontalStrut(6));
            horizontalBox.add(state_2);
            return horizontalBox;
        }


    };

    public abstract JComponent getView(SettingParameter settingParameter);

    private static class StepListener implements ActionListener {
        private final SettingParameter settingParameter;
        private final Box horizontalBox;
        private int stepSign;

        public StepListener(SettingParameter settingParameter, Box horizontalBox, int stepSign) {

            this.settingParameter = settingParameter;
            this.horizontalBox = horizontalBox;
            this.stepSign = stepSign;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                UKU_Connection_SNMP.writeParameter(settingParameter, (Integer) settingParameter.getValue() + stepSign * settingParameter.getStep());
                UKU_Connection_SNMP.readParameter(settingParameter);
            } catch (Exception e1) {
                e1.printStackTrace();
                JOptionPane.showMessageDialog(horizontalBox, "Невозможно выполнить команду: " + e1.getMessage(), "Ошибка команды", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private static class SetState implements ActionListener {
        private final SettingParameter settingParameter;
        private final Box horizontalBox;
        private final int state;

        public SetState(SettingParameter settingParameter, Box horizontalBox, int state) {
            this.settingParameter = settingParameter;
            this.horizontalBox = horizontalBox;
            this.state = state;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                UKU_Connection_SNMP.writeParameter(settingParameter, state);
                UKU_Connection_SNMP.readParameter(settingParameter);
            } catch (Exception e1) {
                e1.printStackTrace();
                JOptionPane.showMessageDialog(horizontalBox, "Невозможно выполнить команду: " + e1.getMessage(), "Ошибка команды", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private static class Constants {
        public static final Color DISABLED_COLOR = new Color(200, 200, 200);
        public static final Color ENABLED_COLOR = new Color(112, 177, 217);
    }
}
