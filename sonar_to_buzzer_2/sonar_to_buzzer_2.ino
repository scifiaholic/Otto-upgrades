// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
const int tonePin = 15;

// defines variables
long duration;
int distance;
int pitch;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(115200); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
//pitch = map(distance, 1, 150, 10000, 1000);
pitch = log(distance+1)/log(100)*5000;
tone(tonePin, pitch);
delay(500);
}

