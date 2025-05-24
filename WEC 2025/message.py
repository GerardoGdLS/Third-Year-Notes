import csv
import matplotlib.pyplot as plt

# List of file paths for the three CSV files
file_paths = ['coordinates1963.csv', 'coordinates2005.csv', 'coordinates2011.csv']

# Dictionary to store square boundaries and original points for each file
data = {}

for file_path in file_paths:
    # Initialize variables to store min and max longitude and latitude
    min_longitude, max_longitude = float('inf'), float('-inf')
    min_latitude, max_latitude = float('inf'), float('-inf')

    # Store original coordinates for visualization
    original_coordinates = []

    # Open and read the CSV file
    with open(file_path, mode='r') as file:
        csv_reader = csv.reader(file)
        
        # Skip the header
        next(csv_reader)
        
        for row in csv_reader:
            # Parse longitude and latitude as floats
            longitude, latitude = map(float, row)
            original_coordinates.append((longitude, latitude))
            
            # Update min and max values
            min_longitude = min(min_longitude, longitude)
            max_longitude = max(max_longitude, longitude)
            min_latitude = min(min_latitude, latitude)
            max_latitude = max(max_latitude, latitude)

    # Print the min and max values for each file
    print(f"File: {file_path}")
    print(f"Min Longitude: {min_longitude}, Max Longitude: {max_longitude}")
    print(f"Min Latitude: {min_latitude}, Max Latitude: {max_latitude}")
    print()

    # Create a square boundary
    longitude_range = max_longitude - min_longitude
    latitude_range = max_latitude - min_latitude
    max_range = max(longitude_range, latitude_range)

    # Adjust max and min to form a square
    if longitude_range < max_range:
        diff = (max_range - longitude_range) / 2
        min_longitude -= diff
        max_longitude += diff
    elif latitude_range < max_range:
        diff = (max_range - latitude_range) / 2
        min_latitude -= diff
        max_latitude += diff

    # Square boundary coordinates
    square_boundary = {
        "Bottom-Left": (min_longitude, min_latitude),
        "Bottom-Right": (max_longitude, min_latitude),
        "Top-Right": (max_longitude, max_latitude),
        "Top-Left": (min_longitude, max_latitude),
        "Bottom-Left (again)": (min_longitude, min_latitude),  # Close the loop
    }

    # Store data
    data[file_path] = {
        "original_coordinates": original_coordinates,
        "square_boundary": square_boundary
    }

# Colors and labels for datasets
colors = ['blue', 'green', 'orange']
labels = ['1964', '2005', '2011']

# Create subplots
fig, axes = plt.subplots(2, 2, figsize=(14, 12))

# Plot individual graphs
for i, file_path in enumerate(file_paths):
    ax = axes[i // 2, i % 2]
    original_coordinates = data[file_path]["original_coordinates"]
    square_boundary = data[file_path]["square_boundary"]

    # Extract points for plotting
    original_longitudes = [coord[0] for coord in original_coordinates]
    original_latitudes = [coord[1] for coord in original_coordinates]
    square_longitudes = [point[0] for point in square_boundary.values()]
    square_latitudes = [point[1] for point in square_boundary.values()]

    # Plot original points
    ax.scatter(original_longitudes, original_latitudes, color=colors[i], label=f'Original Points {labels[i]}')

    # Plot square boundary
    ax.plot(square_longitudes, square_latitudes, color=colors[i], linestyle='--', label=f'Square Boundary {labels[i]}')

    # Labels and styling
    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title(f"Visualization of {labels[i]}")
    ax.legend()
    ax.grid(True)

# Plot overlapping graph
ax = axes[1, 1]
for i, file_path in enumerate(file_paths):
    original_coordinates = data[file_path]["original_coordinates"]
    square_boundary = data[file_path]["square_boundary"]

    # Extract points for plotting
    original_longitudes = [coord[0] for coord in original_coordinates]
    original_latitudes = [coord[1] for coord in original_coordinates]
    square_longitudes = [point[0] for point in square_boundary.values()]
    square_latitudes = [point[1] for point in square_boundary.values()]

    # Plot original points
    ax.scatter(original_longitudes, original_latitudes, color=colors[i], label=f'Original Points {labels[i]}')

    # Plot square boundary
    ax.plot(square_longitudes, square_latitudes, color=colors[i], linestyle='--', label=f'Square Boundary {labels[i]}')

# Labels and styling for the overlapping plot
ax.set_xlabel("Longitude")
ax.set_ylabel("Latitude")
ax.set_title("Overlapping Visualization")
ax.legend()
ax.grid(True)

# Adjust layout and show
plt.tight_layout()
plt.show() 


