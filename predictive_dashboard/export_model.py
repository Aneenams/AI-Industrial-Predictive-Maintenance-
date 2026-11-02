from micromlgen import port
import joblib

# Load your existing trained Random Forest model
model = joblib.load('predictive_maintenance_model.pkl') 

# Convert the model to C++ code
c_code = port(model)

# Save as a C++ header file
with open('model.h', 'w') as f:
    f.write(c_code)
    
print("Success! C++ model.h generated.")