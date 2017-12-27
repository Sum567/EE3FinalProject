//int sensorPinL = 16;
//int sensorPinMid = 15;
//int sensorPinR = 14; 
int motorLeftPin = 6;
int motorRightPin = 9;
int led_right = 12;
int led_mid = 11;
int led_left = 8;
const int Sensor_threshold = 350;

int val_left = 0;
int val_right = 0;
int val_mid = 0;

bool midTrigger = false;
bool leftTrigger = false;
bool rightTrigger = false;
bool stopEverything = false;

void setup() {
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  
  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);
  
  pinMode(led_left, OUTPUT);
  pinMode(led_right, OUTPUT);
  pinMode(led_mid, OUTPUT);
 //Serial.begin(9600);
}

void loop() {
  
  val_left = analogRead(A0);
  val_mid = analogRead(A1);
  val_right = analogRead(A2);

  while(stopEverything){
     val_left = analogRead(A0);
    val_mid = analogRead(A1);
    val_right = analogRead(A2);
    if((val_left > 160 && val_right > 260)){
      stopEverything = false;
    }
  }
  
  //go straight forward
  if(val_mid < 180 && !midTrigger && !stopEverything)
  {   
    //kick speed
     analogWrite(motorLeftPin, 180); //145
     analogWrite(motorRightPin, 173); //115
     midTrigger = true;
     leftTrigger = false;
     rightTrigger = false;
     delay(50);
    
  }
  else if(val_mid < 180 && midTrigger && !stopEverything){
     analogWrite(motorLeftPin, 90); //145
     analogWrite(motorRightPin, 68); //115
     digitalWrite(led_mid, HIGH);
     digitalWrite(led_left, LOW);
     digitalWrite(led_right, LOW);
  }
  
  //turn left if left sensor gets high val by incresing the speed of right wheel
  if(val_left < 150 && !leftTrigger && !stopEverything)
  {
    analogWrite(motorLeftPin, 30); //
    analogWrite(motorRightPin, 150); //105
    leftTrigger = true;
    midTrigger = false;
    rightTrigger = false;
    //delay(60);
  }

  else if(val_left < 150 && leftTrigger && !stopEverything){
    analogWrite(motorLeftPin, 0); //
    analogWrite(motorRightPin, 93); //105
    digitalWrite(led_right, HIGH);
    digitalWrite(led_mid, LOW);
    digitalWrite(led_left, LOW);
  }

  //turn right
  if(val_right < 225 && !rightTrigger && !stopEverything)
  {
    analogWrite(motorLeftPin, 250); //145
    analogWrite(motorRightPin, 30); //
    rightTrigger = true;
    leftTrigger = false;
    midTrigger = false;
    //delay(60);
  }

  else if(val_right < 225 && rightTrigger && !stopEverything){
    analogWrite(motorLeftPin, 140); //145
    analogWrite(motorRightPin, 0); //
    digitalWrite(led_left, HIGH);
    digitalWrite(led_mid, LOW);
    digitalWrite(led_right, LOW);
  }
  
  if(val_mid < 140 && val_left < 160 && val_right < 260)
  {
    analogWrite(motorLeftPin, 0);
    analogWrite(motorRightPin, 0);
    digitalWrite(led_right, HIGH);
    digitalWrite(led_mid, HIGH);
    digitalWrite(led_left, HIGH);
    delay(100);
    stopEverything = true;
  }
  
}





