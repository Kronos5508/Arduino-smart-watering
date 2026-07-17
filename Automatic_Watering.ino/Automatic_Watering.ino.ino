#include <OneWire.h>
#include <DallasTemperature.h>

// --- PIN CONFIGURATIONS ---
const int TEMP_BUS_PIN = 2;       // DS18B20 Data pin
const int PUMP_PIN = 3;           // Relay control pin (Active HIGH)
const int BUTTON_PIN = 4;         // Tactile button to switch modes
const int MOISTURE_PIN = A0;      // Analog capacitive soil moisture sensor

// --- THRESHOLDS & SETTINGS ---
const int DRY_THRESHOLD = 400;    // Adjust based on your moisture sensor calibration
const unsigned long interval = 1000; // Serial output interval (1 second)

// --- SYSTEM STATES ---
enum SystemMode { MODE_AUTO, MODE_ON, MODE_OFF };
SystemMode currentMode = MODE_AUTO;

// --- SENSOR SETUP ---
OneWire oneWire(TEMP_BUS_PIN);
DallasTemperature sensors(&oneWire);

// --- VARIABLES ---
unsigned long previousMillis = 0;
bool lastButtonState = HIGH;      // Input pull-up defaults to HIGH
bool pumpActive = false;

void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW); // Start with pump off
  
  // Using INPUT_PULLUP means the button pin reads LOW when pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  Serial.println("System Initialized. Starting in AUTO mode...");
}

void loop() {
  handleButton();
  runWateringLogic();

  // Print system status to Serial Monitor every second
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    printStatus();
  }
}

// --- BUTTON DEBOUNCING & MODE TOGGLING ---
void handleButton() {
  bool currentButtonState = digitalRead(BUTTON_PIN);
  
  // Detect transition from unpressed (HIGH) to pressed (LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); // Simple debounce delay
    
    // Cycle through modes: AUTO -> ON -> OFF -> AUTO
    if (currentMode == MODE_AUTO) {
      currentMode = MODE_ON;
      Serial.println("\n[Mode Changed to: ALWAYS ON]");
    } else if (currentMode == MODE_ON) {
      currentMode = MODE_OFF;
      Serial.println("\n[Mode Changed to: ALWAYS OFF]");
    } else {
      currentMode = MODE_AUTO;
      Serial.println("\n[Mode Changed to: AUTOMATIC]");
    }
  }
  lastButtonState = currentButtonState;
}

// --- CORE WATERING LOGIC ---
void runWateringLogic() {
  int moistureValue = analogRead(MOISTURE_PIN);

  switch (currentMode) {
    case MODE_AUTO:
      // In Auto mode, turn the pump on if the soil is drier than the threshold
      if (moistureValue < DRY_THRESHOLD) {
        digitalWrite(PUMP_PIN, HIGH);
        pumpActive = true;
      } else {
        digitalWrite(PUMP_PIN, LOW);
        pumpActive = false;
      }
      break;

    case MODE_ON:
      // Force pump on
      digitalWrite(PUMP_PIN, HIGH);
      pumpActive = true;
      break;

    case MODE_OFF:
      // Force pump off
      digitalWrite(PUMP_PIN, LOW);
      pumpActive = false;
      break;
  }
}

// --- SERIAL OUTPUT REPORT ---
void printStatus() {
  // Request temperature from the DS18B20 sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  int moistureValue = analogRead(MOISTURE_PIN);

  Serial.print("Temp: ");
  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.print("ERR");
  } else {
    Serial.print(tempC, 1);
    Serial.print(" C");
  }

  Serial.print(" | Soil Moisture Raw: ");
  Serial.print(moistureValue);

  Serial.print(" | Mode: ");
  switch (currentMode) {
    case MODE_AUTO: Serial.print("AUTO"); break;
    case MODE_ON:   Serial.print("FORCE ON"); break;
    case MODE_OFF:  Serial.print("FORCE OFF"); break;
  }

  Serial.print(" | Pump Status: ");
  if (pumpActive) {
    Serial.println("ACTIVE (Pumping Water)");
  } else {
    Serial.println("OFF");
  }
}