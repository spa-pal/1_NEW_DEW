package uku_control;

import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

/**
 * <p>Title: Polaris20kW</p>
 * <p/>
 * <p>Description: </p>
 * <p/>
 * <p>Copyright: Copyright (c) 2006</p>
 * <p/>
 * <p>Company: Triada-TV</p>
 *
 * @author Polonikov&Danilov
 * @version 1.0
 */
public class Alarm_Sound_Wav {

    private File soundFile;
    private Clip clip;
    private boolean is_active = false;
    AudioInputStream source;

    public Alarm_Sound_Wav(URL url) {
        super();

        try {
            source = AudioSystem.getAudioInputStream(url);//url_str));//soundFile);
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


    public boolean isActive() {
        return is_active;
    }
}
