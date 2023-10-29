int delay_ms = 500;
/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---  DP
    D
 */
 
// Pin 2-8 is connected  to the 7 segments of the display.

int pinA =  8;  // 5641AH PIN 11 
int pinB = 12;  // 5641AH PIN  7
int pinC =  4;  // 5641AH PIN  4 
int pinD =  3;  // 5641AH PIN  2
int pinE =  2;  // 5641AH PIN  1
int pinF =  9;  // 5641AH PIN 10
int pinG =  5;  // 5641AH PIN  5
int pinDP = 13; // 5641AH PIN  3
int D1 =  7;  // 5641AH PIN 12
int D2 =  10;  // 5641AH PIN  9
int D3 =  11;  // 5641AH PIN  8
int D4 =  6;  // 5641AH PIN  6

// the setup routine  runs once when you press reset:
void setup() {     
  
  while (!Serial);
  Serial.begin(115200) ;           
  // initialize  the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);  
  pinMode(pinDP, OUTPUT);
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  

  Serial.println("Setup Complete.");
}

// the loop routine runs over  and over again forever:
void loop() {
  // THIS MOVES BELOW CODE TO THE NEXT LCD BLOCK
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 

  //THIS ENDS THE MOVEMENT AND REMAINS ON THE LAST BLOCK FOR THE FOLLOWING DIGITS
  //0
  digitalWrite(pinDP, HIGH);
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG,  LOW);   
  delay(delay_ms);               // wait for  a second
  digitalWrite(pinDP, LOW);
  // THIS MOVES BELOW CODE TO THE NEXT LCD BLOCK
  digitalWrite(D1, HIGH);
  digitalWrite(D2,  LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  //THIS ENDS THE MOVEMENT AND REMAINS ON THE LAST BLOCK FOR THE FOLLOWING DIGITS

  //1
  digitalWrite(pinA,  LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD,  LOW);
  digitalWrite(pinE,  LOW);
  digitalWrite(pinF,  LOW);
  digitalWrite(pinG,  LOW);
  delay(delay_ms); // wait for a second
  
  // THIS MOVES BELOW CODE TO THE NEXT LCD BLOCK
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3,  LOW);
  digitalWrite(D4, HIGH);
  //THIS ENDS THE MOVEMENT AND REMAINS ON THE LAST BLOCK FOR THE FOLLOWING DIGITS

  //2
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC,  LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF,  LOW);
  digitalWrite(pinG, HIGH);
  delay(delay_ms); // wait for a second

  // THIS MOVES BELOW CODE TO THE NEXT LCD BLOCK
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4,  LOW);
  //THIS ENDS THE MOVEMENT AND REMAINS ON THE LAST BLOCK FOR THE FOLLOWING DIGITS

  //3
  digitalWrite(pinA,  HIGH);
  digitalWrite(pinB,  HIGH);
  digitalWrite(pinC,  HIGH);
  digitalWrite(pinD,  HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG,  HIGH);
  delay(delay_ms); // wait for a second

  
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4,  LOW);
  //8
  digitalWrite(pinA,  HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC,  HIGH);
  digitalWrite(pinD,  HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF,  HIGH);
  digitalWrite(pinG,  HIGH);
    digitalWrite(pinDP, HIGH);
  delay(delay_ms); // wait for a second

}
  void serialEvent() {
    if (Serial.available()) {
      int readValue = Serial.parseInt();
      Serial.read();
      delay_ms = readValue;
    }
  }
