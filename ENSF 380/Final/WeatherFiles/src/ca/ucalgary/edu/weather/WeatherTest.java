package ca.ucalgary.edu.weather;

public class WeatherTest {
    public static void main(String[] args) {
        // Define a city code for testing
        String cityCode = "Calgary";
        
        // Fetch and print the weather report for the specified city code
        Weather.main(new String[]{cityCode});
    }
}

