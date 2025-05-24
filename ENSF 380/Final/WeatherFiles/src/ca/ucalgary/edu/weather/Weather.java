package ca.ucalgary.edu.weather;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Weather {
    private String cityCode;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("There was no CLI argument given"); //Print this is there is no CLI
            return;
        }

        String cityCode = args[0];
        
        System.out.println("Weather Report for " + cityCode + ": " + getWeatherReport(cityCode));
    }
    
    public Weather(String cityCode) {
        this.cityCode = cityCode;
    }
    
    public static String getWeatherReport(String cityCode) { //Gets the weather data from the page
        String urlString = "https://wttr.in/" + cityCode + "?0"; // The ?0 comes from the help page of the weather URL, allows for only the current weather to display
        try {
            String weatherData = fetchWeatherData(urlString);
            return parseWeatherData(weatherData);
        } catch (Exception e) {
            e.printStackTrace();
            return "Error fetching weather data.";
        }
    }

    public static String fetchWeatherData(String urlString) throws Exception { // Creates the connection to the URL and allows for the reader to read the information
        URL url = new URL(urlString); // This method is depracated but still functions and I'm unsure what else to use
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET"); // What we want to do with the URL

        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        StringBuilder response = new StringBuilder(); // This will hold our output from the read
        String line;
        while ((line = in.readLine()) != null) {
            response.append(line);
        }
        in.close();
        return response.toString();
    }

    public static String parseWeatherData(String data) { // This is where the regex patterns are to compare to the information pulled from the site to know what information is which
        
    	Pattern conditionPattern = Pattern.compile("(?:</span>\\s*)+\\s*(.*?)\\s*(?=<|$)"); // Matches the pattern right after the </span> tag and occasionally catching the second tag
    	Pattern tempPattern = Pattern.compile("<span[^>]*class=\"ef[^\"]*\">(\\+?\\d+)</span>" + "(?:\\(<span[^>]*class=\"ef[^\"]*\">(\\d+)</span>\\))?" + " °C"); // Matches the temp, dynamically changing the "ef" number values in case the colour changes
    	Pattern windPattern = Pattern.compile("</span>?\\s*<span class=\"bold\">([↙←→↗↖↓↑↘])</span>\\s*<span class=\"ef\\d+\">(\\d+)(?:-(\\d+))?</span>\\s*km/h"); // This regex matches wind speed with an optional range
    	Pattern visibilityPattern = Pattern.compile("</span>\\s*(\\d+) km"); // This is the visibility? The webpage is not very clear
        Pattern precipitationPattern = Pattern.compile("(?:</span>)?\\s*(\\d+\\.\\d+)(?:\\s*\\((\\d+)%\\))? mm"); // Precipitation with optional "chance of rain" percentage

        Matcher conditionMatcher = conditionPattern.matcher(data);
        Matcher tempMatcher = tempPattern.matcher(data);
        Matcher windMatcher = windPattern.matcher(data);
        Matcher precipitationMatcher = precipitationPattern.matcher(data);
        Matcher visibilityMatcher = visibilityPattern.matcher(data);

        // These lines will set the output to display that no data was found
        String temperature = "No temperature data found.";
        String wind = "No wind data found.";
        String condition = "No weather condition data found.";
        String precipitation = "No precipitation data found.";
        String visibility = "No visibility data found.";
        
        // These change the output if there was in fact some information found matching the regex
        if (conditionMatcher.find()) {
            condition = conditionMatcher.group(1).trim(); // Condition
        }

        if (tempMatcher.find()) {
            String mainTemp = tempMatcher.group(1); // Main temperature
            String secondaryTemp = tempMatcher.group(2); // Optional feels like temperature
            temperature = mainTemp + (secondaryTemp != null ? " (" + secondaryTemp + ")" : "") + " °C";
        }

        if (windMatcher.find()) {
            String direction = windMatcher.group(1); // Wind direction
            String speed = windMatcher.group(2); // Wind speed
            String range = windMatcher.group(3); // Optional range
            wind = direction + " " + speed + (range != null ? "-" + range : "") + " km/h";
        }
        
        if (visibilityMatcher.find()) {
            String visibilityAmount = visibilityMatcher.group(1); // Visibility distance
            visibility = visibilityAmount + " km";
        }

        if (precipitationMatcher.find()) {
            String precipAmount = precipitationMatcher.group(1); // Precipitation amount
            String precipPercentage = precipitationMatcher.group(2); // Optional chance of rain percentage
            precipitation = precipAmount + " mm" + (precipPercentage != null ? " | " + precipPercentage : "");
        }

        return String.format("\nCondition: %s\nTemperature: %s\nWind: %s\nVisibility: %s\nPrecipitation: %s", condition, temperature, wind, visibility, precipitation);    }
}
