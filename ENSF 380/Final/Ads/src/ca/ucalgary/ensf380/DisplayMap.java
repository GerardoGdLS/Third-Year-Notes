package ca.ucalgary.ensf380;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.BorderLayout;

public class DisplayMap { //Unfortunately I did not have time to finish this function and could not add it
    private JLabel mapLabel;

    DisplayMap (JPanel panel) {
        mapLabel = new JLabel();
        panel.add(mapLabel, BorderLayout.CENTER);
    }

    public void showMap(String mapPath) {
        ImageIcon mapIcon = new ImageIcon(mapPath);
        mapLabel.setIcon(mapIcon);
    }
}
