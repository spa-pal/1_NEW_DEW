package uku_control;

import java.io.File;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.sound.sampled.LineUnavailableException;
import java.io.IOException;
import javax.sound.sampled.Clip;
import javax.swing.JOptionPane;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;


import javax.sound.sampled.Clip;
import java.io.File;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.sound.sampled.LineUnavailableException;
import java.io.IOException;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.AudioInputStream;
import java.net.*;
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
public class Alarm_Sound_Wav {

    private String filename = new String("ringin.wav");
    private File soundFile;
    private Clip clip;
    private boolean is_active = false;
     AudioInputStream source;
    public Alarm_Sound_Wav(String url_str) {
        super();
        soundFile = new File(filename);

        try {
                     source = AudioSystem.getAudioInputStream(new URL(url_str));//url_str));//soundFile);
                    DataLine.Info clipInfo = new DataLine.Info(Clip.class, source.getFormat());
                    if (AudioSystem.isLineSupported(clipInfo)) {

                        // Create a local clip to avoid discarding the old clip
                        clip = (Clip) AudioSystem.getLine(clipInfo); // Create the clip

                           clip.open(source);
                        // Deal with previous clip
                    } else {

                    }
                } catch (UnsupportedAudioFileException e) {
                    e.printStackTrace();
                } catch (LineUnavailableException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
        }
    }

    public void switch_on(boolean b) {
        if (b) {
            if (clip != null) {
                if (!is_active) {

                    clip.setMicrosecondPosition(0);
                    clip.loop(clip.LOOP_CONTINUOUSLY); // ...close it.

                        is_active = true;

                }
            }
            } else {
                if (is_active) {
                    clip.stop();
                    is_active = false;
               }
            }

    }


}
