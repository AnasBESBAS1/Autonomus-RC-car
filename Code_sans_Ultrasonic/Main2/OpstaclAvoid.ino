void readSidesAndFront() {      
  distance4 = sonarFL();             
  Serial.print("Front Left: ");
  Serial.println(distance4);
  delay(3);
  distance5 = sonarFR();
  Serial.print("Front Right: ");
  Serial.println(distance5);
  delay(3);
  distance2 = sonarL();
  Serial.print("Left: ");
  Serial.println(distance2);
  delay(3);
  distance3 = sonarR();
  Serial.print("Right: ");
  Serial.println(distance3);
  if (distance3 < distance2 && distance3 != 0 && distance2 != 0) {
    distance2 = sonarL();
    Serial.print("Left: ");
    Serial.println(distance2);
    distance3 = sonarR();
    Serial.print("Right: ");
    Serial.println(distance3);
    if (distance3 < distance2 && distance3 != 0 && distance2 != 0) {
      leftTurn();
      } else {
        motor.writeMicroseconds(forwardSpeed);
        steer.write(neutral);
      }
    } 
    else if (distance2 < distance3 && distance2 != 0 && distance3 != 0) {
    distance3 = sonarR();
    Serial.print("Right: ");
    Serial.println(distance3);
    delay(3);
    distance2 = sonarL();
    Serial.print("Left: ");
    if (distance2 < distance3 && distance2 != 0 && distance3 != 0) {
      rightTurn();
    } else {
      motor.writeMicroseconds(forwardSpeed);
      steer.write(neutral);
      }
    } else if (distance5 <= 4 && distance5 != 0) {
        breaking();
        turnOnLED(LEDB);
        steer.write(steerRight);
        motor.writeMicroseconds(speedCenter);
        delay(1000);
        turnOnLED(LEDB);
        motor.writeMicroseconds(reverseSpeed);
        Serial.println("Reversing");
        delay(500);
        motor.writeMicroseconds(speedCenter);
        steer.write(neutral);
    } else if (distance5 < frontSideThreshold && distance5 != 0) {
      distance5 = sonarFR();
      Serial.print("Front Right: ");
      Serial.println(distance5);
      if (distance5 < frontSideThreshold && distance5 != 0) {
        distance5 = sonarFR();
        Serial.print("Front Right: ");
        Serial.println(distance5);
      if (distance5 < frontSideThreshold && distance5 != 0) {
        frontLeftTurn();
      }  else {
        motor.writeMicroseconds(forwardSpeed);
        steer.write(neutral);
      }
     } else {
      motor.writeMicroseconds(forwardSpeed);
      steer.write(neutral);
    }
   } else if (distance4 < 4 && distance4 != 0) {
    steer.write(steerLeft);
    breaking(); // stop the car perparing for a reverse
    delay(500);
    //stopReverseTurn();
    //checkFront();
    motor.writeMicroseconds(reverseSpeed);
    Serial.println("Reversing  ");
    delay(950);
    motor.writeMicroseconds(speedCenter);
    steer.write(neutral);
  } else if (distance4 < frontSideThreshold && distance4 != 0) {
    distance4 = sonarFL();
    Serial.print("Front Left: ");
    Serial.println(distance4);
    if (distance4 < frontSideThreshold && distance4 != 0) {
      distance4 = sonarFL();
      Serial.print("Front Left: ");
      Serial.println(distance4);
      if (distance4 < frontSideThreshold && distance4 != 0) {
        frontRightTurn();
        //checkFront();
      } else {
        motor.writeMicroseconds(forwardSpeed);
        steer.write(neutral);
      }
    } else {
      motor.writeMicroseconds(forwardSpeed);
      steer.write(neutral);
    }
  }
}
