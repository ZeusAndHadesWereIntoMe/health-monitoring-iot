#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// Create sensor objects
PulseOximeter pox;
Adafruit_MPU6050 mpu;

#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0;

// Beat detection callback
void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA = GPIO21, SCL = GPIO22 for ESP32

  // Initialize MAX30100
  Serial.print("Initializing pulse oximeter... ");
  if (!pox.begin()) {
    Serial.println("FAILED");
    while (1);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_46_8MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // Initialize MPU6050
  Serial.print("Initializing MPU6050... ");
  if (!mpu.begin()) {
    Serial.println("FAILED");
    while (1);
  } else {
    Serial.println("SUCCESS");
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

void loop() {
  pox.update();  // keep calling this every loop

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // Add a delay to let MAX30100 finish I2C work before MPU starts
    delay(50);

    // Get MPU data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float totalAccel = sqrt(
      a.acceleration.x * a.acceleration.x +
      a.acceleration.y * a.acceleration.y +
      a.acceleration.z * a.acceleration.z
    );

    Serial.print("HR: ");
    Serial.print(heartRate);
    Serial.print(" bpm | SpO2: ");
    Serial.print(spo2);
    Serial.print(" %");

    Serial.print(" | Accel: X=");
    Serial.print(a.acceleration.x, 2);
    Serial.print(" Y=");
    Serial.print(a.acceleration.y, 2);
    Serial.print(" Z=");
    Serial.print(a.acceleration.z, 2);
    Serial.print(" | Total: ");
    Serial.print(totalAccel, 2);

    if (heartRate > 120) {
      if (totalAccel < 1.5) {
        Serial.print(" ⚠️  Warning: High HR, but no movement!");
      } else {
        Serial.print(" 🏃 Movement detected with high HR (probably okay)");
      }
    }

    Serial.println();
    tsLastReport = millis();
  }
}
