package ca.ucalgary.ensf380;

import javax.swing.Timer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import java.awt.Image;
import java.awt.Graphics;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import ca.ucalgary.edu.weather.Weather;

public class Ads { // The main class, originally meant to only work on ads but ended up being my main class for handling my JFrame
    private Connection dbConnect;
    
    public void createConnection() {
    	try {
    		Class.forName("com.mysql.cj.jdbc.Driver"); // Makes sure driver is registered
    		dbConnect = DriverManager.getConnection("jdbc:mysql://localhost:3306/myDB", "root", "gerardo2004"); //Establishes the connection
    		System.out.println("Connection Established Successfully"); // If it works
    	} catch(SQLException e) {
    		e.printStackTrace();
    	} catch (ClassNotFoundException e) {
            System.err.println("Driver not found. Please add the driver.");
            e.printStackTrace();
    	}
    }
    
    public List<Ad> fetchCurrentAd() { // Holds the query for the information and identifies the information to correctly create an instance of ad
        List<Ad> ads = new ArrayList<>();
        final String query = "SELECT a.* FROM Ads a JOIN Ad_Schedule s ON a.id = s.ad_id"; // Selects all from ad + ad_schedule table with matching Ids

        try (Statement stmt = dbConnect.createStatement(); ResultSet result = stmt.executeQuery(query)) {
            while (result.next()) { // Loop over all the items found using the query
                Ad ad = new Ad( //This creates a new ad for each ad by fetching the values in each of the listed columns
                    result.getInt("id"),
                    result.getString("txt"),
                    result.getString("media_path"),
                    result.getString("media_type"),
                    result.getTimestamp("created_at")
                );
                ads.add(ad); // Adds the individual ad to the list
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ads;
    }

	class Ad { // All values final as we do not want the information to change
	    private final int id;
	    private final String txt;
	    private final String path;
	    private final String type;
	    private final Timestamp time;
	    
	    Ad(int id, String txt, String path, String type, Timestamp time){
	    	this.id = id;
	    	this.txt = txt;
	    	this.path = path;
	    	this.type = type;
	    	this.time = time;
	    }
	    
	    public int getId() {
	    	return this.id;
	    }
	    
	    public String getTxt() {
	    	return this.txt;
	    }
	    
	    public String getPath() {
	    	return this.path;
	    }
	    
	    public String getType() {
	    	return this.type;
	    }
	    
	    public Timestamp getTime() {
	    	return this.time;
	    }
	    
	}

	public static class AdDisplayPanel extends JPanel {
	    private ImagePanel imagePanel;
	    private JTextArea weatherTextArea;
	    private Ads dbManager;
	    private int currentAdIndex = 0;
	    private List<Ads.Ad> ads;
	    private Timer adTimer;

	    public AdDisplayPanel(Ads dbManager, String cityCode) {
	        this.dbManager = dbManager;
	        setLayout(new BorderLayout()); // We set the layout to have no gaps between components
	        setBackground(Color.BLACK);

	        // Create a top panel for the ads, weather, news and the map
	        JPanel topPanel = new JPanel(new GridBagLayout());
	        topPanel.setBackground(Color.BLACK);
	        GridBagConstraints gbc = new GridBagConstraints(); // We will use this to change the constraints of how our overall JFrame will look
	        gbc.fill = GridBagConstraints.BOTH;
	        gbc.insets = new Insets(5, 5, 5, 5);

	        // We use an image panel for the ads and then later where the map will display
	        imagePanel = new ImagePanel();
	        
	        // These are the constraints of the JFrame we set earlier
	        gbc.gridx = 0;
	        gbc.gridy = 0;
	        gbc.gridwidth = 1;
	        gbc.gridheight = 1;
	        gbc.weightx = 0.7;
	        gbc.weighty = 1.0;
	        gbc.anchor = GridBagConstraints.NORTHWEST;
	        topPanel.add(imagePanel, gbc);

	        // Add two columns for the news and weather
	        JPanel col1 = new JPanel();
	        col1.setBackground(Color.BLACK);
	        gbc.gridx = 1;
	        gbc.gridy = 0;
	        gbc.gridwidth = 1;
	        gbc.weightx = 0.2;
	        gbc.weighty = 1.0;
	        topPanel.add(col1, gbc);

	        JPanel col2 = new JPanel();
	        col2.setBackground(Color.BLACK);
	        gbc.gridx = 2;
	        gbc.gridy = 0;
	        gbc.gridwidth = 1;
	        gbc.weightx = 0.1;
	        gbc.weighty = 1.0;
	        topPanel.add(col2, gbc);

	        add(topPanel, BorderLayout.CENTER);

	        // We now initialize and add the weather panel to the right column we just created
	        JPanel weatherPanel = new JPanel(new BorderLayout());
	        weatherPanel.setPreferredSize(new Dimension(300, 0)); // Set width and allow height to grow
	        weatherPanel.setBackground(Color.BLACK);
	        weatherTextArea = new JTextArea();
	        weatherTextArea.setEditable(false); // Do not allow it to be changed so we set it uneditable
	        weatherTextArea.setLineWrap(true); // This is for the text, if our line of text goes outside the area, start a new line
	        weatherTextArea.setWrapStyleWord(true); // This part just decides where we will begin the wrap if needed, when set to true we wrap it at the spaces
	        weatherTextArea.setFont(weatherTextArea.getFont().deriveFont(25f)); // We set font size so it is bigger
	        weatherTextArea.setBackground(Color.BLACK); // Set background color
	        weatherTextArea.setForeground(Color.WHITE); // Text colour will appear white rather than grey
	        weatherPanel.add(new JScrollPane(weatherTextArea), BorderLayout.CENTER); // Add a scroll pane to the text area
	        add(weatherPanel, BorderLayout.EAST); // Add the text area to main JFrame

	        // Finally, we initialize and add a bottom bar panel for the position of the trains
	        JPanel bottomBar = new JPanel();
	        bottomBar.setPreferredSize(new Dimension(getWidth(), 100));
	        bottomBar.setBackground(Color.BLACK);
	        add(bottomBar, BorderLayout.SOUTH);

	        loadAds(); // We call the method
	        startAdRotation(); // We call the method
	        initializeWeather(cityCode); // Initialize weather data with city code
	    }

	    public void loadAds() { // This function allows us to fetch the information from the DB and tells us which ads we were able to load to verify we correctly added everything
	        ads = dbManager.fetchCurrentAd();
	        if (ads.isEmpty()) {
	            System.out.println("No ads loaded");
	        } else {
	            System.out.println("Loaded ads:");
	            for (Ads.Ad ad : ads) {
	                System.out.println("Ad: " + ad.getTxt() + ", " + ad.getPath());
	            }
	        }
	    }

	    public void startAdRotation() { // Every 10 seconds we will change the add and rotate through all loaded ads
	        adTimer = new Timer(10000, new ActionListener() {
	            @Override
	            public void actionPerformed(ActionEvent e) {
	                if (ads != null && !ads.isEmpty()) {
	                    Ads.Ad currentAd = ads.get(currentAdIndex);
	                    String imagePath = currentAd.getPath();
	                    System.out.println("Loading image from: " + imagePath);

	                    ImageIcon imageIcon = new ImageIcon(imagePath);
	                    Image image = imageIcon.getImage().getScaledInstance(imagePanel.getWidth(), imagePanel.getHeight(), Image.SCALE_SMOOTH);
	                    imagePanel.setImage(image);
	                    currentAdIndex = (currentAdIndex + 1) % ads.size();
	                }
	            }
	        });

	        adTimer.start();
	    }

	    public void initializeWeather(String cityCode) { // Uses the city code to find the information for that city
	        String weatherReport = Weather.getWeatherReport(cityCode);
	        weatherTextArea.setText(weatherReport);
	    }

	    public static class ImagePanel extends JPanel {
	        private Image image;

	        public ImagePanel() {
	            setBackground(Color.BLACK); // Set background color when we initialize the panel
	        }

	        public void setImage(Image image) {
	            this.image = image;
	            repaint();
	        }

	        @Override
	        protected void paintComponent(Graphics g) {
	            super.paintComponent(g);
	            if (image != null) {
	                g.drawImage(image, 0, 0, getWidth(), getHeight(), this); // Draw the image scaled to fit the panel
	            }
	        }
	    }

	}
	
	public static void main(String[] args) {
	    if (args.length < 1) {
	        System.err.println("No CLI was given");
	        System.exit(1);
	    }

	    String cityCode = args[0]; // First argument will be the cityCode
	    Ads dbManager = new Ads();
	    dbManager.createConnection();

	    // We now initialize the simulation for the bottom panel
	    TrainSim trainSim = new TrainSim();
	    trainSim.parseCSV("C:\\Users\\gerar\\OneDrive\\Documents\\ENSF 380\\FinalProject\\ForkedRepo\\SubwayScreen\\data\\subway.csv");
	    trainSim.initializeTrains();
	    trainSim.startSimulation();

	    JFrame frame = new JFrame("My transit screen");
	    AdDisplayPanel adPanel = new Ads.AdDisplayPanel(dbManager, cityCode); //
	    frame.add(adPanel, BorderLayout.CENTER);

	    // Add the TrainSim panel to the bottom
	    TrainSimGUI trainSimGUI = new TrainSimGUI(trainSim);
	    JPanel bottomPanel = new JPanel(new BorderLayout());
	    bottomPanel.setBackground(Color.BLACK); // Set background color
	    bottomPanel.add(trainSimGUI.getTrainPositionsArea(), BorderLayout.CENTER);
	    frame.add(bottomPanel, BorderLayout.SOUTH);

	    frame.setSize(800, 600);
	    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    frame.setVisible(true);

	    // Now we do the same for the weather section
	    Weather weather = new Weather(cityCode);
	    String report = weather.getWeatherReport(cityCode); // Again, same issue with the static method, I could only get it to work like this for some reason
	    System.out.println(report); // Just to verify that we got the report in the console
	}

}
