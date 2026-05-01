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

  Serial.println("System Started (UNO)");
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