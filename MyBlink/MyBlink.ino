#define RED 0
#define BLUE 1
#define PAUSE_INTERVAL 0
#define LED_BLUE 3
#define BTN_PAUSE 2
#define DEBOUNCE_TICKS 25
#define BRIGHTNESS_INTERVAL 50

int ledState = RED;
long blinkInterval = 50;
int brightness = 1;
int fadeAmount = 5;
bool lastButtonReadState = false;
unsigned long lastButtonReadTick = 0;
unsigned long nextBrightnessTick = BRIGHTNESS_INTERVAL;
unsigned long nextBlinkTick = blinkInterval;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BTN_PAUSE, INPUT);
  while (!Serial);
  Serial.begin(115200) ;
  triggerLEDs(ledState);
  Serial.println("Setup Complete.");
}
// the loop function runs over and over again forever
void loop() {
  bool buttonPressed = button_process(millis());

  led_process(millis(), buttonPressed);
}

void serialEvent() {
  if (Serial.available()) {
    int readValue = Serial.parseInt();
    Serial.read();
    blinkInterval = readValue;
  }
}

void triggerLEDs(int ledState) {
    switch(ledState) {
      case BLUE:    
        analogWrite(LED_BLUE, brightness);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case RED:
        analogWrite(LED_BLUE, LOW);
        digitalWrite(LED_BUILTIN, HIGH);
        break; 
    }
}

void led_process(unsigned long currentTick, bool buttonDown) {

  if (buttonDown && (currentTick >= nextBrightnessTick)) {
    nextBrightnessTick += BRIGHTNESS_INTERVAL;
    brightness += fadeAmount;
  
    if (brightness <= abs(fadeAmount) || brightness >= (255 - abs(fadeAmount))) {
      fadeAmount = -fadeAmount;  
    }
    nextBlinkTick = currentTick + blinkInterval;
    triggerLEDs(BLUE);
  } else if ((blinkInterval != PAUSE_INTERVAL) && (currentTick >= nextBlinkTick)){ 
    ledState = !ledState; // works if one state is 0 and the other != 0 but if more than 2 states will not work
    nextBlinkTick = currentTick + blinkInterval;
    triggerLEDs(ledState);
  }
}

bool button_process(unsigned long currentTick) {
  bool buttonState = digitalRead(BTN_PAUSE);
  
  if (buttonState != lastButtonReadState) {
    lastButtonReadState = buttonState;
    lastButtonReadTick = currentTick;
  } else if (currentTick - lastButtonReadTick > DEBOUNCE_TICKS ) {
    lastButtonReadTick = currentTick;
    return true;
  }

  return false; 
}


