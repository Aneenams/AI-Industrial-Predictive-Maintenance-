# AI-Driven Industrial Predictive Maintenance 🏭

An end-to-end Predictive Maintenance system that uses machine learning to detect hardware faults via physical vibration analysis. 

This project evolved from a Wi-Fi/MQTT connected web dashboard into a **100% offline, air-gapped Edge AI Node** running a Random Forest model directly on an ESP32 microcontroller using TinyML.

## 🚀 Features

* **Edge AI Inference (TinyML):** Runs a C++ compiled Random Forest model locally on the ESP32 without internet or cloud dependency.
* **Real-time DSP & Filtering:** Includes hardware-level deadzone filtering and dynamic feature scaling.
* **Full-Stack Telemetry (Archive):** Includes a Django backend and React frontend for remote visualization via MQTT.
* **Custom ML Pipeline:** Python scripts for raw sensor data acquisition, feature engineering, and model training.

## 📁 Repository Structure

* `/ESP32_Offline_Node/` - The final C++ Arduino sketch for standalone, air-gapped hardware deployment.
* `/ESP32_WiFi_MQTT_Node/` - Connected Arduino sketch for transmitting live telemetry to the Django backend.
* `/predictive_dashboard/` - Django backend for receiving MQTT telemetry and serving the API.
* `/frontend/` - React + Vite web application for real-time data visualization.
* `train_model.py` & `collect_data.py` - Python pipeline for generating the ML model.

## 🛠️ Hardware Requirements

* **ESP32 Microcontroller**
* **ADXL345 Accelerometer** (I2C: SDA on GPIO 21, SCL on GPIO 22)
* **LED Indicator** (Anode on GPIO 4)

## ⚙️ How It Works

1. **Data Collection:** The ADXL345 captures X, Y, and Z-axis vibrations.
2. **Model Training:** `train_model.py` processes `healthy_data.csv` and `faulty_data.csv` to train a Random Forest Classifier.
3. **Transpilation:** The Python model is transpiled into a C++ header (`model.h`) using the `eloquent_tinyml` library.
4. **Edge Deployment:** The ESP32 continuously polls the sensor, scales the features, and runs the inference loop. If a fault is predicted, a non-blocking hardware interrupt triggers the physical LED alarm.

## 💻 Running the Project

### Phase 1: Deploying the Edge Node

1. Wire the ESP32, ADXL345 sensor, and LED according to the Hardware Requirements.
2. Open the Arduino IDE and install the required libraries (`Adafruit_ADXL345`, `EloquentTinyML`, and `PubSubClient`).
3. **For Offline Mode:** Open the sketch inside `/ESP32_Offline_Node/`, flash it to the board, and power it via a portable USB bank.
4. **For Web Dashboard Mode:** Open the sketch inside `/ESP32_WiFi_MQTT_Node/`. Enter your Wi-Fi credentials and local MQTT IP address in the code, then flash it to the board. *(Note: You must also complete Phase 3 below to view the live web dashboard).*

### Phase 2: Running the ML Training Pipeline
1. Install dependencies: `pip install scikit-learn pandas numpy micromlgen`
2. Run `python train_model.py` to output the model accuracy and generate the C++ header.

### Phase 3: Web Dashboard (Legacy)
1. Backend: Navigate to `/predictive_dashboard/` and run `python manage.py runserver`.
2. Frontend: Navigate to `/frontend/`, run `npm install`, then `npm run dev`.
