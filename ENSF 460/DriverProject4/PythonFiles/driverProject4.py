import serial
import time
import pandas as pd
import matplotlib.pyplot as plt
import re

# Constants for ADC conversion
ADC_MAX = 1023  # Assume a 10-bit ADC
V_REF = 3.3  # Reference voltage for ADC


def initialize_serial_connection(port, baudrate):
    """ Initialize and return a serial connection, retrying if necessary. """
    retries = 3
    for attempt in range(retries):
        try:
            print(f"Attempting to open port {port} at baudrate {baudrate} (Attempt {attempt + 1}/{retries})")
            ser = serial.Serial(port=port, baudrate=baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
            print(f"Successfully connected to {port}")
            return ser
        except serial.SerialException as e:
            print(f"Failed to open port {port}: {e}")
            time.sleep(2)  # Wait a bit before retrying

    print(f"Unable to open port {port} after {retries} attempts.")
    return None


def read_serial_data(ser, duration):
    """ Read data from the serial port for a specified duration. """
    start_time = time.time()
    data_points = []

    try:
        while start_time + duration > time.time():
            line = ser.readline()
            if line:
                timestamp = time.time() - start_time
                data_point = line.decode('utf-8', errors='replace').strip()
                data_points.append({'Time': timestamp, 'ADC Value': data_point})
            else:
                time.sleep(0.01)
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    except Exception as e:
        print(f"General error: {e}")

    if not data_points:
        print("No data received.")

    return pd.DataFrame(data_points)


def process_data(df):
    """ Process the DataFrame to calculate voltage from sanitized ADC values. """
    df['Voltage'] = None

    for index, row in df.iterrows():
        # Use parse_hexadecimal to sanitize and convert 'ADC Value'
        adc_value = parse_hexadecimal(row['ADC Value'], index)
        
        if adc_value is not None:
            voltage = (adc_value / ADC_MAX) * V_REF
            df.at[index, 'ADC Value'] = adc_value
            df.at[index, 'Voltage'] = voltage
        else:
            df.drop(index, inplace=True)  # Drop rows with invalid ADC values

    return df

def parse_hexadecimal(data, index):
    # Remove non-hexadecimal characters using regex
    hex_match = re.search(r'\b(0x[0-9A-Fa-f]+)\b', data)
    if hex_match:
        hex_string = hex_match.group(1)  # Extract matched hex string
        try:
            return int(hex_string, 16)  # Convert hex string to integer
        except ValueError as e:
            print(f"Skipping invalid row at index {index}: {data} (Error: {e})")
    else:
        print(f"Skipping invalid row at index {index}: {data} (Error: no valid hex found)")
    return None


def save_data_to_csv(df, filename):
    """ Save the DataFrame to a CSV file. """
    df.to_csv(filename, index=False)


def plot_data(df):
    """ Create and display separate plots for ADC Value and Voltage over time. """
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 6))

    ax1.plot(df['Time'], df['ADC Value'], label='ADC Value', color='tab:red')
    ax1.set_title('ADC Value over Time')
    ax1.set_xlabel('Time (seconds)')
    ax1.set_ylabel('ADC Value')
    ax1.legend()

    ax2.plot(df['Time'], df['Voltage'], label='Voltage', color='tab:blue')
    ax2.set_title('Voltage over Time')
    ax2.set_xlabel('Time (seconds)')
    ax2.set_ylabel('Voltage (V)')
    ax2.legend()

    plt.show()


def main():
    """ Main function to execute the data acquisition process. """
    print("Initializing serial connection...")
    ser = initialize_serial_connection("COM5", 4800)

    if ser is None:
        print("Failed to initialize serial connection. Exiting program.")
        return

    print("Reading serial data...")
    raw_df = read_serial_data(ser, 10)
    ser.close()

    if raw_df.empty:
        print("No data to process.")
        return

    processed_df = process_data(raw_df)
    print(processed_df)
    save_data_to_csv(processed_df, 'outputData.csv')
    plot_data(processed_df)

if __name__ == "__main__":
    main()