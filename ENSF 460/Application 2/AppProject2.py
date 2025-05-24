import serial
import time
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def initialize_serial_connection(port, baudrate):
    return serial.Serial(port=port, 
                         baudrate=baudrate, 
                         bytesize=8, 
                         timeout=2, 
                         stopbits=serial.STOPBITS_ONE)

def read_serial_data(ser, duration=60):
    start_time = time.time()
    data_points = []
    
    print("Starting data collection...")
    
    while (time.time() - start_time) < duration:
        try:
            line = ser.readline()
            if line:
                timestamp = time.time() - start_time
                data_point = line.decode('utf-8', errors='replace').strip()
                print(f"Raw data: {data_point}")  # Debug print
                
                try:
                    intensity_str, adc_str = data_point.split(',')
                    intensity = int(intensity_str.strip())
                    adc_value = int(adc_str.strip().replace('0x', ''), 16)
                    
                    data_points.append({
                        'Time': timestamp,
                        'Intensity': intensity,
                        'ADC_Value': adc_value
                    })
                except Exception as e:
                    print(f"Error parsing data point: {e}")
                    continue
                    
        except Exception as e:
            print(f"Error reading line: {e}")
            continue

    print(f"Collected {len(data_points)} valid data points")
    return pd.DataFrame(data_points)

def plot_data(df):
    if df.empty:
        print("No data to plot!")
        return
        
    plt.figure(figsize=(15, 6))
    
    # Calculate standard deviation for both signals
    intensity_std = df['Intensity'].std()
    adc_std = df['ADC_Value'].std()
    
    # Set minimum y-axis ranges
    min_intensity_range = 20  # Minimum range of 20% for intensity
    min_adc_range = 200      # Minimum range of 200 for ADC
    
    # ADC plot (First plot with blue line)
    plt.subplot(1, 2, 1)
    plt.plot(df['Time'], df['ADC_Value'], 'b-', linewidth=1.5)  # Changed to blue line 'b-'
    plt.title('ADC Reading vs Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('ADC Reading')
    plt.grid(True, alpha=0.3)
    
    # Set y-axis limits for ADC
    if adc_std < 5:  # If values are very stable
        mean_adc = df['ADC_Value'].mean()
        plt.ylim([max(0, mean_adc - min_adc_range/2), 
                  min(1400, mean_adc + min_adc_range/2)])
    else:
        margin = max(min_adc_range/2, adc_std * 2)
        plt.ylim([max(0, df['ADC_Value'].min() - margin),
                  min(1400, df['ADC_Value'].max() + margin)])
    
    # Intensity plot (Second plot with red line)
    plt.subplot(1, 2, 2)
    plt.plot(df['Time'], df['Intensity'], 'r-', linewidth=1.5)  # Changed to red line 'r-'
    plt.title('LED Intensity vs Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Intensity (%)')
    plt.grid(True, alpha=0.3)
    
    # Set y-axis limits for Intensity
    if intensity_std < 2:  # If values are very stable
        mean_intensity = df['Intensity'].mean()
        plt.ylim([max(0, mean_intensity - min_intensity_range/2),
                  min(120, mean_intensity + min_intensity_range/2)])
    else:
        margin = max(min_intensity_range/2, intensity_std * 2)
        plt.ylim([max(0, df['Intensity'].min() - margin),
                  min(120, df['Intensity'].max() + margin)])
    
    # Add a super title
    plt.suptitle('Group 10 - LED Control System Data', fontsize=14)
    
    # Improve layout
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    # Save the plot
    plt.savefig('Group10_plot.png', dpi=300, bbox_inches='tight')
    plt.show()

def main():
    print("Initializing serial connection...")
    ser = initialize_serial_connection("COM5", 9600)
    
    print("Reading serial data...")
    df = read_serial_data(ser, 60)
    ser.close()
    
    if not df.empty:
        print("\nData sample:")
        print(df.head())
        
        print("\nSaving data...")
        df.to_csv('Group10_data.csv', index=False)
        
        print("\nGenerating plots...")
        plot_data(df)
    else:
        print("No data collected!")

if __name__ == "__main__":
    main()
