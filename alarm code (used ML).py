from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split

# Sample input data: [heart_rate, spo2, motion_level]
X = [
    [75, 98, 0.5],
    [135, 96, 0.3],
    [42, 85, 1.2],
    [80, 99, 0.6]
]

# Labels for each data point
y = ['normal', 'alert', 'alert', 'normal']

# Split data into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25)

# Train the model
clf = RandomForestClassifier()
clf.fit(X_train, y_train)

# Predict a new input case
prediction = clf.predict([[130, 95, 0.4]])

print("📡 Predicted Health Status:", prediction[0])
