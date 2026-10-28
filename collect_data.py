import serial
import csv

# Settings
SERIAL_PORT = 'COM6'
BAUD_RATE = 115200
OUTPUT_FILE = 'faulty_data.csv'  # Change this for the second run

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}. Saving to {OUTPUT_FILE}...")
    
    with open(OUTPUT_FILE, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['X', 'Y', 'Z'])
        
        print("Recording... Press Ctrl+C in the terminal to stop.")
        while True:
            line = ser.readline().decode('utf-8').strip()
            if line:
                # The ESP32 sends data like "X:1.23,Y:4.56,Z:7.89"
                # This splits the text to extract just the numbers
                try:
                    parts = line.split(',')
                    x = parts[0].split(':')[1]
                    y = parts[1].split(':')[1]
                    z = parts[2].split(':')[1]
                    writer.writerow([x, y, z])
                except IndexError:
                    pass # Skips any incomplete lines during startup
                
except KeyboardInterrupt:
    print("\nData collection stopped. File saved!")
except Exception as e:
    print(f"Error: {e}. Make sure the Arduino IDE Serial Plotter is closed!")