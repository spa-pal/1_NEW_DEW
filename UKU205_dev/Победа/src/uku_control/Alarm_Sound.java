package uku_control;

import java.util.Vector;
import javax.sound.midi.*;
//import polaris_monitoring.Time_delay;

/**
 * <p>Title: Polaris20kW</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2006</p>
 *
 * <p>Company: Triada-TV</p>
 *
 * @author Polonikov&Danilov
 * @version 1.0
 */
public class Alarm_Sound {
    private Vector synthInfos = new Vector();
    private MidiDevice device;
    private Synthesizer synthesizer;
    private MidiChannel chan[];
    private boolean is_enabled = false;

    public Alarm_Sound() {


        MidiDevice.Info[] infos = MidiSystem.getMidiDeviceInfo();
        try {
            for (int i = 0; i < infos.length; i++) {

                if (infos[i].getName().equals("Java Sound Synthesizer")) {
                    device = MidiSystem.getMidiDevice(infos[i]);
                    System.out.println(device.getDeviceInfo().getDescription() + ". " + device.getDeviceInfo().getName() + ". " + device.getDeviceInfo().getVendor());
                }
            }

            device.open();
            synthesizer = MidiSystem.getSynthesizer();
            synthesizer.open();


            //Instrument[] instrument = synthesizer.getAvailableInstruments();
            int instrument_number = 0;
            Soundbank soundbank = synthesizer.getDefaultSoundbank();
            System.out.println(soundbank);
            Instrument[] instrument = soundbank.getInstruments();
            for (int i = 0; i < instrument.length; i++){
               System.out.println(i + " " + instrument[i].getName());
                if (instrument[i].getName().equalsIgnoreCase("telephone"))
                    instrument_number = i;
            }
            System.out.println("Instrument_Number   " + instrument_number);


            synthesizer.remapInstrument(instrument[instrument_number], instrument[0]);
             chan = synthesizer.getChannels();
            // Check for null; maybe not all 16 channels exist.

             this.switch_on(false);




        } catch (MidiUnavailableException e) {
            e.printStackTrace();
        }

    }

    public void switch_on(boolean b){
        if (is_enabled == b) return;
        is_enabled = b;
        if (b){
            if (chan[0] != null) {
                    chan[0].noteOn(65, 100);
                    //chan[0].noteOn(120, 500);
                }

        }else{
            if (chan[0] != null) {
                    chan[0].allNotesOff();
                }
        }
    }

    public void close(){
        synthesizer.close();
        device.close();

    }
    public static void main(String[] args) {
        Alarm_Sound alarm_sound = new Alarm_Sound();
        alarm_sound.switch_on(true);
     //   Time_delay.sleep(10000);

     try {
         Thread.sleep(1000);
     } catch (InterruptedException ex) {
     }
     alarm_sound.close();
        System.exit(0);


    }
}
