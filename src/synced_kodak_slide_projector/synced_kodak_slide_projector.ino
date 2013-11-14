float delay_ms = 1000;
volatile boolean is_playing = false;
volatile boolean button_1_input_status = LOW;
volatile boolean button_2_input_status = LOW;

volatile unsigned long button_1_pressed_time = 0;
volatile unsigned long button_2_pressed_time = 0;

const int BOUNCE = 100;

const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
const int RELAY_1_PIN = 4;
const int RELAY_2_PIN = 5;
const int BUTTON_1_STATUS_LED_PIN = 12;
const int BUTTON_2_STATUS_LED_PIN = 13;
const int POTENTIOMETER_PIN = A0;

const int MIN_DELAY = 900;
const int MAX_DELAY = 5000;

void setup()
{
  pinMode(BUTTON_1_STATUS_LED_PIN, OUTPUT);
  pinMode(BUTTON_2_STATUS_LED_PIN, OUTPUT);

  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);

  pinMode(POTENTIOMETER_PIN, INPUT);

  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);

  attachInterrupt(0, button_1_pressed, CHANGE);
  attachInterrupt(1, button_2_pressed, CHANGE);

  Serial.begin(9600);
}

void loop()
{
  int a0_raw = analogRead(POTENTIOMETER_PIN);
  delay_ms = map(a0_raw, 0, 1023, MIN_DELAY, MAX_DELAY);

  Serial.print("delay(ms)=");
  Serial.print(delay_ms);
  Serial.print(" is_playing=");
  Serial.println(is_playing);

  if(is_playing)
  {
    PORTD |= B00110000;
    //digitalWrite(RELAY_1_PIN, HIGH);
    //digitalWrite(RELAY_2_PIN, HIGH);
    delay(200);
    PORTD &= B11001111;
    //digitalWrite(RELAY_1_PIN, LOW);
    //digitalWrite(RELAY_2_PIN, LOW);
    delay(delay_ms);
  }
}

void button_1_pressed()
{
  is_playing = true;
  
  if((millis() - button_1_pressed_time) > BOUNCE)
    button_1_input_status = !button_1_input_status;
  
  button_1_pressed_time = millis();
  digitalWrite(BUTTON_1_STATUS_LED_PIN, button_1_input_status);
}

void button_2_pressed()
{
  is_playing = false;
  if((millis() - button_2_pressed_time) > BOUNCE)
  {
    button_2_input_status = !button_2_input_status;
    //is_playing = !is_playing;
  }
  button_2_pressed_time = millis();
  digitalWrite(BUTTON_2_STATUS_LED_PIN, button_2_input_status);
}

