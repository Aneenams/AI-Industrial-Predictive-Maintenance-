# AI-Driven Industrial Predictive Maintenance 🏭

An end-to-end Predictive Maintenance system that uses machine learning to detect hardware faults via physical vibration analysis. 

This project evolved from a Wi-Fi/MQTT connected web dashboard into a **100% offline, air-gapped Edge AI Node** running a Random Forest model directly on an ESP32 microcontroller using TinyML.

## 🚀 Features

* **Edge AI Inference (TinyML):** Runs a C++ compiled Random Forest model locally on the ESP32 without internet or cloud dependency.
* **Real-time DSP & Filtering:** Includes hardware-level deadzone filtering and dynamic feature scaling.
* **Full-Stack Telemetry (Archive):** Includes a Django backend and React frontend for remote visualization via MQTT.
* **Custom ML Pipeline:** Python scripts for raw sensor data acquisition, feature engineering, and model training.

## 📁 Repository Structure

* `/ESP32_Offline_Node/` - The final C++ Arduino sketch and `model.h` for standalone hardware deployment.
* `/predictive_dashboard/` - Django backend for receiving MQTT telemetry and serving the API.
* `/frontend/` - React + Vite web application for real-time data visualization.
* `train_model.py` & `collect_data.py` - Python pipeline for generating the `.pkl` model from accelerometer data.

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

### Phase 1: Deploying the Edge Node (Standalone)
1. Open the `/ESP32_Offline_Node/` folder in the Arduino IDE.
2. Connect the ESP32 and ADXL345 via I2C.
3. Flash the `.ino` sketch to the board. 
4. Power the board via a USB battery bank; the system will actively monitor vibrations offline.

### Phase 2: Running the ML Training Pipeline
1. Install dependencies: `pip install scikit-learn pandas numpy micromlgen`
2. Run `python train_model.py` to output the model accuracy and generate the C++ header.

### Phase 3: Web Dashboard (Legacy)
1. Backend: Navigate to `/predictive_dashboard/` and run `python manage.py runserver`.
2. Frontend: Navigate to `/frontend/`, run `npm install`, then `npm run dev`.