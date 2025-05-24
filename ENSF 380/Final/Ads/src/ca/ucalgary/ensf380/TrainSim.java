package ca.ucalgary.ensf380;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.*;
import java.awt.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;

public class TrainSim { // This class contains all the logic for the trains
    private List<Station> stations = new ArrayList<>();
    private List<Train> trains = new ArrayList<>();
    private Map<String, List<Station>> lineStations = new HashMap<>();


    public static void main(String[] args) {
        TrainSim simulator = new TrainSim();
        simulator.parseCSV("C:\\Users\\gerar\\OneDrive\\Documents\\ENSF 380\\Final\\ForkedRepo\\SubwayScreen\\data\\subway.csv");
        simulator.initializeTrains();
        simulator.startSimulation();

        SwingUtilities.invokeLater(() -> new TrainSimGUI(simulator));
    }

    public void parseCSV(String filePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            br.readLine();

            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");

                if (values.length >= 4) { // If we caught all columns of the CSV
                    String lineCode = values[1].trim();
                    String stationCode = values[3].trim();
                    String stationName = values[4].trim();

                    if (isValidStationCode(stationCode)) { // First check if the station code is valid
                        Station station = new Station(lineCode, stationName, stationCode);
                        stations.add(station); // add it to our list
                        lineStations.putIfAbsent(lineCode, new ArrayList<>()); // Now we group them by line
                        lineStations.get(lineCode).add(station);
                    } else {
                        System.out.println("Invalid station code: " + stationCode);
                    }
                } else {
                    System.out.println("Invalid line format: " + line);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private boolean isValidStationCode(String code) {
        return code.matches("^[RGB][0-9]{2}$"); // This regex ensures we have a station code beginning with R, B, or G and then 2 numbers
    }

    public void initializeTrains() {
        if (stations.isEmpty()) {
            System.err.println("No valid stations available. Trains cannot be initialized.");
            return;
        }

        int trainCount = 12;
        int distanceBetweenTrains = 4;
        String[] lines = {"R", "B", "G"};

        for (int i = 0; i < trainCount; i++) {
            int position = (i * distanceBetweenTrains) % stations.size();
            int lineIndex = i / 4; // Since 4 trains per line
            String line = lines[lineIndex];
            boolean direction = (i % 2 == 0);  // Alternate directions
            List<Station> stationsForLine = lineStations.getOrDefault(line, new ArrayList<>());
            if (!stationsForLine.isEmpty()) {
                trains.add(new Train("T" + (i + 1), stationsForLine.get(position % stationsForLine.size()), line, direction));
            }
        }
    }

    public void startSimulation() { //Begins the simulation of trains moving
        final Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                moveTrains();
                getTrainPositions();
            }
        }, 0, 15000);
    }

    private void moveTrains() {
        for (Train train : trains) {
            
            List<Station> stationsForLine = lineStations.get(train.getLine()); // This gets the list of trains
            
            if (stationsForLine == null || stationsForLine.isEmpty()) {
                continue;
            }

            int currentIndex = stationsForLine.indexOf(train.getPosition());
            int nextIndex;

            // Determine nextIndex based on current direction (If end of line, go back)
            if (train.isMovingForward()) {
                nextIndex = currentIndex + 1;
                
                if (nextIndex >= stationsForLine.size()) { // If the index reaches the end of the lines we have
                    
                    train.setMovingForward(false); // Now set to move backward
                    nextIndex = currentIndex - 1; 
                }
            } else {
                nextIndex = currentIndex - 1;
                
                if (nextIndex < 0) { // If we reached the beginning of the line after going backwards
                    
                    train.setMovingForward(true); // Now go forward
                    nextIndex = currentIndex + 1; 
                }
            }

            // Update the train’s position
            train.setPosition(stationsForLine.get(nextIndex));
        }
    }




    public String getTrainPositions() {
        final Map<String, List<String>> lineTrainPositions = new HashMap<>();
        for (Train train : trains) {
            String line = train.getLine();
            lineTrainPositions.putIfAbsent(line, new ArrayList<>());
            lineTrainPositions.get(line).add(train.toString());
        }

        StringBuilder positions = new StringBuilder();
        for (String line : lineTrainPositions.keySet()) {
            positions.append(line).append(": ");
            positions.append(String.join(", ", lineTrainPositions.get(line)));
            positions.append("\n");
        }
        return positions.toString();
    }


    public List<Train> getTrains() {
        return this.trains;
    }
    
    public boolean isValidStation(String line, String code) {
        final Set<String> validStations = new HashSet<>(); // Make a HashSet of all valid stations
        
        for (int i = 1; i <= 43; i++) validStations.add(String.format("R%02d", i)); // Add all red line stations
        for (int i = 1; i <= 44; i++) validStations.add(String.format("B%02d", i)); // Add blue line stations
        for (int i = 1; i <= 33; i++) validStations.add(String.format("G%02d", i)); // Add green line station
        
        return validStations.contains(code);
    }
}

class Station {
    private final String line;
    private final String name;
    private final String code;

    public Station(String line, String name, String code) {
        this.line = line;
        this.name = name;
        this.code = code;
    }

    public String getLine() {
        return line;
    }

    public String getName() {
        return name;
    }

    public String getCode() {
        return code;
    }
}

class Train {
    private final String id;
    private Station position;
    private final String line;
    private boolean movingForward;

    public Train(String id, Station position, String line, boolean movingForward) {
        this.id = id;
        this.position = position;
        this.line = line;
        this.movingForward = movingForward;
    }

    public String getId() {
    	return this.id;
    }
    public Station getPosition() {
        return this.position;
    }

    public void setPosition(Station position) {
        this.position = position;
    }

    public String getLine() {
        return this.line;
    }

    public boolean isMovingForward() {
        return this.movingForward;
    }

    public void setMovingForward(boolean movingForward) {
        this.movingForward = movingForward;
    }

    @Override
    public String toString() {
        return this.getId() + "(" + position.getCode() + ", " + (this.isMovingForward() ? "F" : "B") + ")";
    }
}

class TrainSimGUI {
    private JTextArea trainPositionsArea;
    private TrainSim simulator;

    public TrainSimGUI(TrainSim simulator) {
        this.simulator = simulator;
        trainPositionsArea = new JTextArea();
        trainPositionsArea.setFont(new Font("Monospaced", Font.PLAIN, 30));
        trainPositionsArea.setEditable(false); // Set this so it cannot be changed
        trainPositionsArea.setBackground(Color.BLACK); // Background colour
        trainPositionsArea.setForeground(Color.WHITE); // Text color

        JScrollPane scrollPane = new JScrollPane(trainPositionsArea);
        scrollPane.setBorder(BorderFactory.createEmptyBorder()); // Remove border

        JPanel panel = new JPanel(new BorderLayout()); // Set layout for the TrainSim panel
        panel.setBackground(Color.BLACK); // Background color
        panel.add(scrollPane, BorderLayout.CENTER); // Position on the panel

        JFrame tempFrame = new JFrame("Subway Train Simulation"); // Add the panel to the frame
        tempFrame.setLayout(new BorderLayout());
        tempFrame.add(panel, BorderLayout.CENTER);
        tempFrame.setSize(800, 600);
        tempFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        tempFrame.setVisible(true);

        startGUIUpdate();
    }

    private void startGUIUpdate() {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                updateTrainPositions();
            }
        }, 0, 15000); // Every 15 seconds the train positions are updated 
    }

    public void updateTrainPositions() {
        SwingUtilities.invokeLater(() -> {
            String trainPositions = simulator.getTrainPositions();
            trainPositionsArea.setText(trainPositions);
        });
    }
    
    public JTextArea getTrainPositionsArea() {
        return trainPositionsArea;
    }
}