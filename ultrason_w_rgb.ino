
#define echoPin 2   // pin D2 on Arduino to ECHO pin of ultrasonic sensor
#define trigPin 3   // pin D3 on Arduino to TRIG pin of "            "

//https://create.arduino.cc/projecthub/muhammad-aqib/arduino-rgb-led-tutorial-fc003e
int ledR= 11;
int ledG = 10;
int ledB = 9;
long timeDur; //duration of soundwave trael
int dist;     // distance

int close = 10; //91; // close distance indicator (3ft = 91 cm)
int mid = 25; //182;  // mid distance indicator (6ft = 182 cm)
int far = 40; //273;

int brightness = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); //initializing  
  pinMode(echoPin, INPUT);  // initializing
  pinMode(ledR,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(ledB,OUTPUT);
  Serial.begin(9600);   // baude rate, how fast it comm, average is 9600
  // Serial.println() prints to serial monitor ---------------------> can also use LCD #include <LiquidCrystal.h>...etc
  Serial.println("Distance Readout in cm");

}

void loop() {
  // put your main code here, to run repeatedly:
  // clear trigPin cond

  while (true) {
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);       // wait 2 microseconds then

    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);      // set sensor output to HIGH for 10 microSec.
    digitalWrite(trigPin,LOW);  // clear trigPin again9

    noInterrupts();                   /// thanks to: https://create.arduino.cc/projecthub/panagorko/next-level-ultrasonic-sensor-a67478?ref=tag&ref_id=ultrasonic&offset=23
    timeDur = pulseIn(echoPin,HIGH);  // activate the input sensor
    interrupts();
    dist = timeDur * 0.034 / 2;     // sound wave speed / 2 to account for 2x distance travel/time. 

    
    Serial.print(dist);
    Serial.println("cm ");

    if (dist > mid and dist <= far) {
      analogWrite(ledB,brightness); //blue light value
      analogWrite(ledR,0);
      analogWrite(ledG,0);
    }
    else if (close < dist and dist <= mid) {
      analogWrite(ledG,brightness); // green light
      analogWrite(ledR,0);
      analogWrite(ledB,0);
    }
    else if (dist <= close) { 
      analogWrite(ledR,brightness); //red light
      analogWrite(ledG,0);
      analogWrite(ledB,0);
    }
    else {
      analogWrite(ledR,0);
      analogWrite(ledG,0);
      analogWrite(ledB,0);
    }
  }
  exit(0);
}
