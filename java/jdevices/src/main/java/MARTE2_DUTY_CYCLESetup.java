/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mdsplus
 */
public class MARTE2_DUTY_CYCLESetup extends DeviceSetup {

    /**
     * Creates new form MARTE2_DUTY_CYCLESetup
     */
    public MARTE2_DUTY_CYCLESetup() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        deviceButtons1 = new DeviceButtons();
        jPanel1 = new javax.swing.JPanel();
        jPanel2 = new javax.swing.JPanel();
        deviceField1 = new DeviceField();
        jPanel3 = new javax.swing.JPanel();
        deviceField2 = new DeviceField();
        deviceField3 = new DeviceField();
        jPanel4 = new javax.swing.JPanel();
        deviceField4 = new DeviceField();
        deviceField5 = new DeviceField();
        jPanel5 = new javax.swing.JPanel();
        deviceField6 = new DeviceField();
        deviceField7 = new DeviceField();
        deviceField8 = new DeviceField();
        jPanel6 = new javax.swing.JPanel();
        deviceField9 = new DeviceField();

        setDeviceProvider("spilds:8100");
        setDeviceTitle("MARTe2 DutyCycle GAM");
        setDeviceType("MARTE2_DUTY_CYCLE");
        setHeight(300);
        setWidth(600);
        getContentPane().add(deviceButtons1, java.awt.BorderLayout.PAGE_END);

        jPanel1.setLayout(new java.awt.GridLayout(5, 1));

        deviceField1.setIdentifier("");
        deviceField1.setLabelString("Timebase:");
        deviceField1.setNumCols(20);
        deviceField1.setOffsetNid(3);
        jPanel2.add(deviceField1);

        jPanel1.add(jPanel2);

        deviceField2.setIdentifier("");
        deviceField2.setLabelString("Out Frequency:");
        deviceField2.setOffsetNid(10);
        jPanel3.add(deviceField2);

        deviceField3.setIdentifier("");
        deviceField3.setLabelString("Duty Cycle (%):");
        deviceField3.setNumCols(6);
        deviceField3.setOffsetNid(13);
        jPanel3.add(deviceField3);

        jPanel1.add(jPanel3);

        deviceField4.setIdentifier("");
        deviceField4.setLabelString("And Mask: ");
        deviceField4.setNumCols(6);
        deviceField4.setOffsetNid(22);
        jPanel4.add(deviceField4);

        deviceField5.setIdentifier("");
        deviceField5.setLabelString("Or mask:");
        deviceField5.setNumCols(6);
        deviceField5.setOffsetNid(25);
        jPanel4.add(deviceField5);

        jPanel1.add(jPanel4);

        deviceField6.setIdentifier("");
        deviceField6.setLabelString("Clock Idx: ");
        deviceField6.setNumCols(4);
        deviceField6.setOffsetNid(16);
        jPanel5.add(deviceField6);

        deviceField7.setIdentifier("");
        deviceField7.setLabelString("Enable Idx: ");
        deviceField7.setNumCols(4);
        deviceField7.setOffsetNid(19);
        jPanel5.add(deviceField7);

        deviceField8.setIdentifier("");
        deviceField8.setLabelString("Out Seg. Len: ");
        deviceField8.setNumCols(6);
        deviceField8.setOffsetNid(46);
        jPanel5.add(deviceField8);

        jPanel1.add(jPanel5);

        deviceField9.setIdentifier("");
        deviceField9.setLabelString("Input: ");
        deviceField9.setNumCols(20);
        deviceField9.setOffsetNid(31);
        jPanel6.add(deviceField9);

        jPanel1.add(jPanel6);

        getContentPane().add(jPanel1, java.awt.BorderLayout.CENTER);
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private DeviceButtons deviceButtons1;
    private DeviceField deviceField1;
    private DeviceField deviceField2;
    private DeviceField deviceField3;
    private DeviceField deviceField4;
    private DeviceField deviceField5;
    private DeviceField deviceField6;
    private DeviceField deviceField7;
    private DeviceField deviceField8;
    private DeviceField deviceField9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JPanel jPanel6;
    // End of variables declaration//GEN-END:variables
}
