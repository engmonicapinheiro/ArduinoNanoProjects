//L293D
//Motor A
const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293
//Motor B
const int motorPin3  = 10; // Pin  7 of L293
const int motorPin4  = 9;  // Pin  2 of L293


void setup()
{
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    
}


void loop()
{
    //This code  will turn Motor A (right motor) anti-clockwise for 2 sec. (walks forward)
   digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin4, HIGH);
   digitalWrite(motorPin2, LOW);
   digitalWrite(motorPin3, LOW);
   delay(2000); 


    //This code will turn Motor A and B (walks back)
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    digitalWrite(motorPin1, LOW);
    delay(2000); 



    
    //And this code will stop motors
  //  digitalWrite(motorPin1, LOW);
   // digitalWrite(motorPin2, LOW);
   // digitalWrite(motorPin3, LOW);
   // digitalWrite(motorPin4, LOW);

   // delay(2000);
  

}
