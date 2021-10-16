// ------------ Motor Demo ------------------

void forwardReverseDemo() { //Function called to execute speeding with
                            // acceleration
  blinking();
  steer.write(neutral);
  motor.writeMicroseconds(forwardSpeed);
  delay(200);
  long  c = 0;
  long Time = 2000;
  while ( c < Time ){
    int dis1 = sonarL();
    int dis2 = sonarR();
    if (dis1 <= 20 || dis2 <= 20 ){
      if (dis1 <= 20){
        rightTurn();
      } else {
        leftTurn();
      }
    }
    delay(20);
    c += 20;
  }
  turnOnLED(LEDB);
  breaking();
  speedCenterN();
  delay(1000);
  turnOnLED(LEDB);
  motor.writeMicroseconds(reverseSpeed);
  c = 0;
  Time = 1000;
  while ( c < Time ){
    int dis1 = sonarL();
    int dis2 = sonarR();
    if (dis1 <= 20 || dis2 <= 20 ){
      if (dis1 <= 20){
        rightTurn();
      } else {
        leftTurn();
      }
    }
    delay(20);
    c += 20;
  }
  motor.writeMicroseconds(speedCenter);
  delay(100);
  turnOffLED();
}

// ------------ Steer Demo ------------------

void SteerDemo() { //  Function called to execute a multiple turn while speeding
  steer.write(neutral); 
  motor.writeMicroseconds(forwardSpeed);
  delay(1000);
  steer.write(steerLeft); 
  delay(800);
  steer.write(steerRight);
  delay(800);
  steer.write(neutral);
  delay(1000);
  breaking();
}

// ------------ autoParking Demo ------------------

void autoParking() {
  blinking();
  delay(1000); //wait 1 second
  steer.write(neutral);
  long  c = 0; // loop counter
  long Time = 3000; // time for demo to stop the car after +-3 seconds 
  while ( c < Time ){
    int frs = sonarFRSide(); // check front right side sensor 
    int ms = sonarR(); // check front middel sensor
    if (ms > 15 && ms < 20){ // if mesuered distance is >15 && < 20 correct direction 
      shortshortRightTurn(); // preform a short right turn 
    }  
    if (frs > 20){
      delay(90);
      frs = sonarFRSide();
      int brs = sonarBR();
      c += 120;
      if (frs > 20 && brs > 20){
      breaking();
      motor.writeMicroseconds(reverseSpeed);
      delay(250);
      motor.writeMicroseconds(speedCenter);
      delay(1000);
      motor.writeMicroseconds(forwardSpeed);
      widerightTurn();
      breaking();     
      return;
      }
    }
    c += 4;  
  }
  breaking();
}

void park(){
  turnOnLED(LEDB);
  motor.writeMicroseconds(reverseSpeed); // reverse wait 1 s speedCenter wait 1s 
  delay(1000);
  motor.writeMicroseconds(speedCenter);
  delay(1000);
  steer.write(steerRight);
      motor.writeMicroseconds(forwardSpeed);
      delay(80);
      breaking();
      motor.writeMicroseconds(speedCenter);
}

// ------------ autoDrive Demo ------------------

//preforme a predefined tour 
void autoDrive() {
  blinking();
  steer.write(neutral);
  motor.writeMicroseconds(forwardSpeed);
  delay(2500);
  widerightTurn();
  breaking();
  delay(800);
  motor.writeMicroseconds(reverseSpeed);
  steer.write(steerLeft);
  delay(400);
  motor.writeMicroseconds(speedCenter);
  delay(800);
  steer.write(neutral);
  motor.writeMicroseconds(forwardSpeed);
  delay(2800);
  breaking();
  delay(800);
  motor.writeMicroseconds(reverseSpeed);
  steer.write(steerLeft);
  delay(400);
  motor.writeMicroseconds(speedCenter);
  delay(800);
  steer.write(neutral);
  motor.writeMicroseconds(forwardSpeed);
  delay(2800);
  breaking();
  speedCenterN();
}

// --------------- overTaking Demo -------------------



int danger(){  
  float distance1 = sonarFL();
  float distance2 = sonarFR();
  if (distance1 <= 10) {        // check if left is detected
    return 1;
  } else if (distance2 <= 10) { // check if right is detected
    return 2;
  }
  return 0;
}

int opsticalDetection() { // Helper function used to mesure destance if obstical
                          // is detected return 1 or if obstical is detected
                          // and 0 if not.
  float distance1 = sonarFront();
  if (distance1 <= 50) {
    turnOnLED(LEDB);
    Serial.println("obstical is detected");
    return 1;
  }
  return 0; // nothing is detected the path is clear
}

int outOfRange(int sensor) { // sonarFL -> 1  sonarFR -> 2
  float i;
  if (sensor == 1) {
    i = sonarFL();
    return i > 45;
  }
  i = sonarFR();
  return i > 45;
}

void turnToOvertake() {
  int x = opsticalDetection();
  if (x == 0) {
    return;
  } else if (x == 1) {
     turnOnLED(LEDR);
    float sf = sonarFront();
    while (sf > 35 && sf < 60) {
      sf = sonarFront();
    /*  int dang = danger();
      if (dang != 0){
        breaking();
        loop();
      }*/
    }
    turnOnLED(LEDB);
    if (sf <= 37) { // overtake rotine now
      if (outOfRange(1)) {
        turnOnLED(LED);
        steer.write(steerLeft);
        Serial.println("LEFT TURN");
        delay(400);
        steer.write(neutral);
        steer.write(steerRight);
        Serial.println("Right a little");
        delay(100);
        steer.write(neutral);
        Serial.println("neutral -> checking right ...");
        int right = outOfRange(2); // check if right is available
        while (right == 0) {
          right = outOfRange(2);
          if (sonarFront() < 8) {
            breaking();
            loop();
          }
        }
        int back = sonarBR();
        while (back <= 8) {
          if (sonarFront() < 6) {
            breaking();
            loop();
          }
          back = sonarBR();
        }
        delay(200);
        steer.write(steerRight);
        if (sonarFront() < 6) {
          breaking();
          loop();
        }
        delay(200);
        steer.write(steerLeft);
        if (sonarFront() < 6) {
          breaking();
          loop();
        }
        Serial.println("Left a little");
        delay(60);
        breaking(); // overtake done
        blinking();
        loop();
      } else {
       // breaking(); // no way to overtake
       // loop();
      }
    }
  }
}

void overTaking() { // function used to preform an overtaking if an obstical is
                    // detected in front of the car this function calles
                    // multipel helper functions to take a dicesion. The
                    // function
                    // start by moving the car forword for 10s
  blinking();
  long counterMillis = 0;// current time
  const long interval = 5000; //timer for 10 senconds
  steer.write(neutral); // set steer to front 
  motor.writeMicroseconds(speedCenter);
  motor.writeMicroseconds(forwardSpeed); // move the car froward
  while (counterMillis < interval) {
    motor.writeMicroseconds(forwardSpeed);
    turnToOvertake(); // call the function opsticalDetection
    delay(10);
    counterMillis += 10;
  }
  breaking(); // breaking if the overtaking failed 
  speedCenterN();
  blinking();
}
/*
 * OverTaking : 

Fonction qui a pour but de doubler une voiture, elle se compose de 4 functions, la fonction  overTaking()  qui est la fonction principale 

forwardReverseDemo done 
SteerDemo –> done 
autoDrive --> done 
autoParking 
overTaking –> done 
full autonomy --> done */
