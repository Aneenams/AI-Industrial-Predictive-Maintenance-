import numpy as np
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
import joblib

# 1. Generate Synthetic Dataset
print("Generating synthetic telemetry data...")
np.random.seed(42)
num_samples = 2000

# HEALTHY MACHINE DATA
# Normal vibrations (1-10 Hz), normal temp (40-45 C), normal current (10-12 A)
healthy_freq = np.random.uniform(1.0, 10.0, num_samples // 2)
healthy_temp = np.random.uniform(40.0, 45.0, num_samples // 2)
healthy_current = np.random.uniform(10.0, 12.0, num_samples // 2)
healthy_labels = ['HEALTHY'] * (num_samples // 2)

# FAULTY MACHINE DATA
# High vibrations (15+ Hz), high temp (50+ C), high current (14+ A) due to mechanical friction
faulty_freq = np.random.uniform(12.0, 30.0, num_samples // 2)
faulty_temp = np.random.uniform(48.0, 65.0, num_samples // 2)
faulty_current = np.random.uniform(13.0, 18.0, num_samples // 2)
faulty_labels = ['FAULTY'] * (num_samples // 2)

# Combine into a Feature Matrix
X = np.column_stack((
    np.concatenate([healthy_freq, faulty_freq]),
    np.concatenate([healthy_temp, faulty_temp]),
    np.concatenate([healthy_current, faulty_current])
))
y = np.concatenate([healthy_labels, faulty_labels])

# 2. Train the Random Forest Model
print("Training Random Forest Classifier...")
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# 3. Evaluate and Save
predictions = model.predict(X_test)
print("\nModel Evaluation:")
print(classification_report(y_test, predictions))

model_filename = 'predictive_maintenance_model_v2.pkl'
joblib.dump(model, model_filename)
print(f"\nSuccess! New model saved as: {model_filename}")