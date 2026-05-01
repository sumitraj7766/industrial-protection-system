# ⚡ Industrial Protection System (Arduino / ESP32)

A real-time embedded system designed to monitor electrical parameters like **current and temperature** and protect the load using automatic fault detection, relay control, buzzer alarm, and LED indicators.

---

## 🚀 Features

- 📊 Real-time current monitoring
- 🌡️ Temperature monitoring system
- ⚠️ Warning mode for threshold conditions
- 🔴 Automatic fault detection
- 🔌 Relay-based load protection (cut-off system)
- 🔊 Buzzer alarm for fault alert
- 💡 LED status indication
- 🔁 Automatic retry mechanism
- 🔘 Manual reset button support

---

## 🧠 Working Principle

The system continuously reads sensor values:

- **Normal Condition** → System runs safely (LED ON)
- **Warning Condition** → LED blinks (load approaching limit)
- **Fault Condition** → Relay OFF + Buzzer ON + system protection activated

If fault persists after retries → system goes into **shutdown mode**.

---

## 🔌 Hardware Requirements

- Arduino UNO / ESP32
- Current Sensor (or potentiometer for simulation)
- Temperature Sensor (or potentiometer for simulation)
- Relay Module
- Buzzer
- LED
- Push Button (Reset)
- Resistors (220Ω)

---

## 📌 Pin Configuration (Arduino UNO)

| Component      | Pin |
|----------------|-----|
| Current Sensor | A0  |
| Temperature    | A1  |
| Reset Button   | D7  |
| Relay          | D8  |
| Buzzer         | D9  |
| Status LED     | D10 |

---

## ⚙️ System States

### 🟢 Normal Mode
- Relay ON
- LED ON
- Buzzer OFF

### 🟡 Warning Mode
- LED blinking
- System monitoring closely

### 🔴 Fault Mode
- Relay OFF
- Buzzer ON
- LED OFF
- Retry logic activated

---

## 💻 Arduino Code

```cpp
#define CURR_PIN A0
#define TEMP_PIN A1

#define RESET_PIN 7
#define RELAY_PIN 8
#define BUZZER_PIN 9
#define LED_PIN 10

int current = 0;
int temperature = 0;

int retry_count = 0;
const int MAX_RETRY = 3;

const int CURRENT_LIMIT = 600;
const int TEMP_LIMIT = 600;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);

  Serial.println("System Started");
}

void loop() {

  current = analogRead(CURR_PIN);
  temperature = analogRead(TEMP_PIN);

  Serial.print("Current: ");
  Serial.print(current);
  Serial.print(" | Temp: ");
  Serial.println(temperature);

  // RESET
  if (digitalRead(RESET_PIN) == LOW) {
    retry_count = 0;
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  }

  // NORMAL
  if (current < CURRENT_LIMIT && temperature < TEMP_LIMIT) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  }

  // WARNING
  else if (current > 500 || temperature > 500) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  // FAULT
  else {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);

    delay(2000);

    retry_count++;

    if (retry_count >= MAX_RETRY) {
      while (1);
    }
  }

  delay(500);
}
🔥 Future Improvements
📡 IoT cloud monitoring (ESP32 + MQTT)
📱 Mobile app dashboard
⚡ Real industrial-grade protection system
📊 Data logging & analytics
🤖 AI-based fault prediction
👨‍💻 Author

Sumit Kumar
Electrical & Electronics Engineering Student
Focused on Embedded Systems, IoT & Industrial Automation

⭐ Support

If you like this project:

Give a ⭐ on GitHub
Fork it
Improve it 🚀

---

If you want next level, I can also make:
🔥 :contentReference[oaicite:0]{index=0}
🔥 :contentReference[oaicite:1]{index=1}
🔥 or :contentReference[oaicite:2]{index=2}

Just tell 👍