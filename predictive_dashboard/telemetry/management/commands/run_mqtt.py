import json
import numpy as np
import joblib
import paho.mqtt.client as mqtt
from django.core.management.base import BaseCommand
from telemetry.models import VibrationLog
from scipy.fft import fft
from collections import deque

# Create sliding windows to hold the last 50 sensor readings
WINDOW_SIZE = 50
x_buffer = deque(maxlen=WINDOW_SIZE)
y_buffer = deque(maxlen=WINDOW_SIZE)
z_buffer = deque(maxlen=WINDOW_SIZE)

class Command(BaseCommand):
    help = 'Runs the MQTT listener and AI inference to save to DB'

    def handle(self, *args, **kwargs):
        self.stdout.write("Loading AI model...")
        model = joblib.load('predictive_maintenance_model.pkl')

        def on_message(client, userdata, msg):
            try:
                line = msg.payload.decode('utf-8')
                # print(f"RAW INCOMING DATA: {line}")  # <-- ADD THIS LINE
                parts = line.split(',')
                parts = line.split(',')
                
                if len(parts) == 5:
                    x_val = float(parts[0].replace('X:', ''))
                    y_val = float(parts[1].replace('Y:', ''))
                    z_val = float(parts[2].replace('Z:', ''))
                    temp_val = float(parts[3].replace('Temp:', ''))
                    current_val = float(parts[4].replace('Current:', ''))

                    print(f"Caught Simulated Temp: {temp_val}C | Current: {current_val}A")
                    
                    # Add to rolling window
                    x_buffer.append(x_val)
                    y_buffer.append(y_val)
                    z_buffer.append(z_val)

                    # Only predict and log when the 50-sample window is full
                    if len(z_buffer) == WINDOW_SIZE:
                        z_data = np.array(z_buffer)
                        fft_values = np.abs(fft(z_data))
                        
                        dominant_freq = np.argmax(fft_values[1:WINDOW_SIZE//2]) + 1
                        peak_amplitude = fft_values[dominant_freq]
                        self.stdout.write(f"FFT | Freq: {dominant_freq}Hz | Amp: {peak_amplitude:.2f}")

                        # Extract the 2 features your model expects: mean and std of FFT
                        features = np.array([[np.mean(fft_values), np.std(fft_values)]])
                        prediction = model.predict(features) 
                        status = 'HEALTHY' if prediction[0] == 0 else 'FAULTY'

                        if status == 'FAULTY':
                            client.publish('machine/alarms', 'SHUTDOWN')
                            self.stdout.write("🚨 FAULT DETECTED: Published SHUTDOWN command to MQTT 🚨")
                        else:
                            client.publish('machine/alarms', 'NORMAL')
                            self.stdout.write("✅ SYSTEM HEALTHY: Published NORMAL command to MQTT ✅")    
                        
                        # Save the latest reading to the database with the FFT-based prediction
                        VibrationLog.objects.create(
                            x_axis=x_val,
                            y_axis=y_val,
                            z_axis=z_val,
                            dominant_freq=float(dominant_freq),
                            peak_amplitude=float(peak_amplitude),
                            machine_status=status,
                            temperature=temp_val, 
                            current=current_val
                        )
                        
                        self.stdout.write(f"Logged to Database: {status}")
                    
            except Exception as e:
                self.stdout.write(f"Error processing message: {e}")

        client = mqtt.Client()
        client.on_message = on_message
        
        self.stdout.write("Connecting to local Mosquitto Broker...")
        client.connect("127.0.0.1", 1883, 60)
        self.stdout.write("Connected! Listening for wireless vibrations...")
        
        client.subscribe("sensor/vibration")
        client.loop_forever()