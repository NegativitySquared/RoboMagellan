

//defining pin variables
const int echoPin = 6;
const int trigPin = 7;
const int lightPin = 10;

/define variables
long duration;
int distance;
int maximumRange = 50;
int minimumRange = 0;


void setup() {
  //set the baud frequency
  Serial.begin(9600);

  //classifies whether pin is input or output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound. 
  distance = duration/58.2;

 
  //if an object is within the range of the sensor, LED light on, else, object out of range, LED off
  if(distance >= maximumRange || distance <= minimumRange){
    Serial.println("Object out of range");
    digitalWrite(lightPin, LOW);
  }else{
    //outputs the distance of object within the range
    Serial.print("Distance: ");
    Serial.println(distance)
    digitalWrite(lightPin, HIGH);
  }

  delay(50);
}













