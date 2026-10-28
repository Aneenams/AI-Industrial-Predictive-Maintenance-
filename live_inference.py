import numpy as np
import joblib
import paho.mqtt.client as mqtt

print("Loading AI model...")
model = joblib.load('predictive_maintenance_model.pkl')
window_size = 30
z_readings = []

# This function runs automatically every time a Wi-Fi message arrives
def on_message(client, userdata, msg):
    global z_readings
    try:
        line = msg.payload.decode('utf-8')
        parts = line.split(',')
        if len(parts) == 3:
            z_val = float(parts[2].replace('Z:', ''))
            z_readings.append(z_val)

            if len(z_readings) == window_size:
                fft_values = np.abs(np.fft.fft(z_readings))
                features = np.array([[np.mean(fft_values), np.std(fft_values)]])
                prediction = model.predict(features)
                
                if prediction[0] == 0:
                    print("---> Status: HEALTHY 🟢 (Stable) <---")
                else:
                    print("---> Status: FAULTY 🔴 (Anomalous Vibration!) <---")
                
                z_readings = []
    except Exception as e:
        pass

client = mqtt.Client()
client.on_message = on_message

print("Connecting to local Mosquitto Broker...")
# 127.0.0.1 is the universal IP address for "this computer"
client.connect("127.0.0.1", 1883, 60)

print("Connected! Listening for wireless vibrations...")
client.subscribe("sensor/vibration")
client.loop_forever()