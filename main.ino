
// Pin connected to N-Channel MOSFET Gate pin 
const int ledsPin = 9;
//Pins connected to HC-SR04 sensor downstairs
const int trigPinDown = 10;
const int echoPinDown = 11;
//Pins connected to HC-SR04 sensor upstairs
const int trigPinUp = 12;
const int echoPinUp = 13;

void setup() 
{
  
  pinMode(ledsPin, OUTPUT);

  //pinMode(trigPinDown, OUTPUT);
  //pinMode(echoPinDown, INPUT);
  
  pinMode(trigPinUp, OUTPUT);
  pinMode(echoPinUp, INPUT);
  
  Serial.begin(9600); // Starts the serial communication

}

int distanceToObject(const int trigPin, const int echoPin){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;

}

void lightsControl(const int ledsPin){

  for (int brightness = 0; brightness <= 255; brightness++){
    analogWrite(ledsPin, brightness);
    delay(10);
  }

  delay(10000);
  
  for (int brightness = 255; brightness >= 0; brightness--){
    analogWrite(ledsPin, brightness);
    delay(10);
  }

}

void loop() {

  int distanceDown, distanceUp;

  distanceDown = distanceToObject(trigPinDown, echoPinDown);
  distanceUp = distanceToObject(trigPinUp, echoPinUp);

  
  Serial.print("Distance Down: ");
  Serial.println(distanceDown);

  Serial.print("Distance Up: ");
  Serial.println(distanceUp);

  if(distanceDown < 60 || distanceUp < 60){

    lightsControl(ledsPin);

  }
  
}