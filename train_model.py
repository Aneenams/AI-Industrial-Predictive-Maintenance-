import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import joblib

print("Loading and cleaning datasets...")
healthy = pd.read_csv('healthy_data.csv')
faulty = pd.read_csv('faulty_data.csv')

healthy['Z'] = pd.to_numeric(healthy['Z'], errors='coerce')
faulty['Z'] = pd.to_numeric(faulty['Z'], errors='coerce')
healthy = healthy.dropna()
faulty = faulty.dropna()

# Function to chunk data and extract FFT features
def extract_fft_features(data, window_size=100):
    features = []
    # Slide through the data in chunks of 100 readings
    for i in range(0, len(data) - window_size, window_size):
        window = data[i:i+window_size]
        # Calculate the Fast Fourier Transform (FFT)
        fft_values = np.abs(np.fft.fft(window))
        # Keep the average and variance of the frequencies as our AI features
        features.append([np.mean(fft_values), np.std(fft_values)])
    return features

print("Extracting FFT frequencies...")
# Label Healthy as 0, Faulty as 1
healthy_features = extract_fft_features(healthy['Z'].values)
healthy_labels = [0] * len(healthy_features)

faulty_features = extract_fft_features(faulty['Z'].values)
faulty_labels = [1] * len(faulty_features)

# Combine the datasets
X = np.array(healthy_features + faulty_features)
y = np.array(healthy_labels + faulty_labels)

# Split into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

print("Training the AI model...")
model = RandomForestClassifier(n_estimators=50, random_state=42)
model.fit(X_train, y_train)

# Test the model to see how well it learned
predictions = model.predict(X_test)
accuracy = accuracy_score(y_test, predictions)

print(f"Model Training Complete! Accuracy: {accuracy * 100:.2f}%")

# Save the trained model to a file
joblib.dump(model, 'predictive_maintenance_model.pkl')
print("Model saved as 'predictive_maintenance_model.pkl'")