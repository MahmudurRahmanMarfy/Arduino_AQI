import os
import serial
import pandas as pd
from datetime import datetime

# Configure the serial connection
arduino_port = '/dev/ttyUSB0'  # Change this to the correct port (e.g., 'COM3' for Windows)
baud_rate = 9600  # Match this with your Arduino's serial configuration
timeout = 2  # Timeout for reading

# Create a dynamic output file name
current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
output_folder = "data"
output_file = f"{output_folder}/sensor_readings_{current_time}.csv"

# Ensure the output folder exists
os.makedirs(output_folder, exist_ok=True)

# Initialize the DataFrame
columns = [
    "DateTime", "Humidity(%)", "Temperature(°C)", 
    "MQ5_LPG", "MQ8_H2", "MQ7_CO", 
    "MQ135_Alcohol", "MQ135_CO2", 
    "MQ135_Toluen", "MQ135_NH4", "MQ135_Aceton"
]
data = []

try:
    # Initialize serial connection
    ser = serial.Serial(arduino_port, baud_rate, timeout=timeout)
    print(f"Connected to {arduino_port}")

    while True:
        # Read a line of data from the Arduino
        line = ser.readline().decode('utf-8').strip()

        # Filter relevant lines
        if line and not (line.startswith("Calibrating") or line.startswith("DHT test!")):
            # Add date-time stamp
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            print(f"{timestamp} - {line}")

            # Parse the sensor data
            try:
                readings = {col: None for col in columns}
                readings["DateTime"] = timestamp

                # Split and extract key-value pairs
                for item in line.split():
                    if ":" in item:
                        key, value = item.split(":")
                        key = key.strip()
                        value = value.strip()
                        if key in columns:
                            readings[key] = value

                # Append to data
                data.append(readings)

            except Exception as e:
                print(f"Error parsing line: {line} - {e}")

except serial.SerialException as e:
    print(f"Serial connection error: {e}")
except KeyboardInterrupt:
    print("User interrupted the program.")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Serial connection closed.")

    # Save the collected data to a CSV file
    if data:
        df = pd.DataFrame(data, columns=columns)
        df.to_csv(output_file, index=False)
        print(f"Data saved to {output_file}")
    else:
        print("No data collected.")
