void goBit(unsigned int turns) {
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) {
    encoderPID();
    if (leftCount < turns) Lforward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rforward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }
  }
  brake();
  delay(70);

  leftCount = 0;
  rightCount = 0;
}



void reverseBit(unsigned int turns) {
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) {
    encoderPID();
    if (leftCount < turns) Lbackward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rbackward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }
  }
  brake();
  delay(70);

  leftCount = 0;
  rightCount = 0;
}



void aligningBotF() {
  qtrReadF();
  position = qtrrcF.readLine(sensorValuesF);
  while (!((dvalF[3] == 0 || dvalF[4] == 0) && dvalF[1] == 1 && dvalF[6] == 1)  )
  {
    if (position < 3000) leftTurn(45, 45);
    else if (position > 4000) rightTurn(45, 45);
    qtrReadF();
    position = qtrrcF.readLine(sensorValuesF);
  }
  brake();
}

void aligningBotB() {
  qtrReadB();
  position = qtrrcB.readLine(sensorValuesB);
  while (!((dvalF[3] == 0 || dvalF[4] == 0) && dvalF[1] == 1 && dvalF[6] == 1)  )
  {
    if (position < 3000) leftTurn(45, 45);
    else if (position > 4000) rightTurn(45, 45);
    qtrReadB();
    position = qtrrcB.readLine(sensorValuesB);
  }
  brake();
}


void goToline() {
  while (1) {
    encoderPID();
    forward();
    qtrReadF();
    if (dvalF[1] == 1 || dvalF[6] == 1) {
      brake();
      aligningBotF();
      break;
    }
  }
  brake();
  delay(70);
}

void goToPath() {
  while (1) {
    encoderPID();
    forward();
    qtrReadF();
    if ((dvalF[1] == 0 && dvalF[6] == 0) || (dvalF[0] == 0 && dvalF[7] == 0)) {
      brake();
      goBit(250);
      break;
    }
  }
  brake();
  delay(70);
}


void reversePID(unsigned int turns) {
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) {
    PIDReverse();
    if (leftCount < turns) Lbackward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rbackward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }
  }

  leftCount = 0;
  rightCount = 0;
}


void goPID(unsigned int turns) {
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) {
    PIDFront(KpSlow, KdSlow, rightBaseSpeedSlow, leftBaseSpeedSlow, rightMaxSpeedSlow, leftMaxSpeedSlow);
    if (leftCount < turns) Lforward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rforward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }
  }
  brake();
  delay(70);

  leftCount = 0;
  rightCount = 0;
}
void stopPoint() {
  while (1)
  {
    PIDFront(Kp, Kd, rightBaseSpeed, leftBaseSpeed, rightMaxSpeed, leftMaxSpeed);
    forward();
    qtrReadF();
    hunterRead();
    if ((dvalF[1] == 0 && dvalF[6] == 0) || (dvalF[5] == 0 && dvalF[7] == 0 && hunterL == 0) || (hunterR == 0 &&  dvalF[0] == 0 && dvalF[2] == 0)) {
      brake();
      break;
    }
  }
}


void stopPointSlow() {
  while (1)
  {
    PIDFront(KpSlow, KdSlow, rightBaseSpeedSlow, leftBaseSpeedSlow, rightMaxSpeedSlow, leftMaxSpeedSlow);
    forward();
    hunterRead();
    qtrReadF();
    if ((dvalF[1] == 0 && dvalF[6] == 0) || (dvalF[4] == 0 && dvalF[7] == 0  && hunterL == 0) || (hunterR == 0 && dvalF[0] == 0 && dvalF[3] == 0)) {
      brake();
      break;
    }
  }
}

void angleIncrease(Servo servo, int angle) {
  for (int i = servo.read(); i < angle; ++i) {
    servo.write(i);
    delay(20);
  }
}

void angleDecrease(Servo servo, int angle) {
  for (int i = servo.read(); i > angle; --i) {
    servo.write(i);
    delay(20);
  }
}

void deadend() {
  while (1)
  {
    PIDReverse();
    reverse();
    qtrReadB();
    if (dvalB[4] == 0 && dvalB[7] == 0) {
      brake();
      reverseBit(250);
      turnRightRandom(525);
      delay(80);
    }
    else if (dvalB[0] == 0 && dvalB[3] == 0) {
      reverseBit(250);
      qtrReadB();
      if (!(dvalB[2] == 0 || dvalB[3] == 0 || dvalB[4] == 0 || dvalB[5] == 0 )) {
        turnLeftRandom(525);
        break;
      }
      delay(80);
    }
  }
}

//*********shake left*********************************

void shakeLeft(int turns)
{
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  int initial3 = servo3.read();
  int i = 0;
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) // test countings
  {
    ++i;
    encoderPID();
    if (leftCount < turns) Lbackward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rforward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }

    servo2.write(initial2 + i);
    servo1.write(initial1 - i);
    servo3.write(initial3 - 2 * i);
    delay(30);
  }
  brake();
  delay(70);
  leftCount = 0;
  rightCount = 0;

}

//****************   shake  to the right   ********************

void shakeRight(int turns)
{
  leftCount = 0;
  rightCount = 0;
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  int initial3 = servo3.read();
  int i = 0;
  while (leftCount < turns || rightCount < turns) // test countings
  {
    ++i;
    encoderPID();
    if (leftCount < turns) Lforward();
    else {
      digitalWrite(motorL_dirP, HIGH);
      digitalWrite(motorL_dirN, HIGH);
    }
    if (rightCount < turns) Rbackward();
    else {
      digitalWrite(motorR_dirP, HIGH);
      digitalWrite(motorR_dirN, HIGH);
    }


    servo2.write(initial2 + i);
    servo1.write(initial1 - i);
    servo3.write(initial3 - 2 * i);
    delay(30);
  }
  brake();
  delay(70);
  leftCount = 0;
  rightCount = 0;
}


void lightOn() {
  digitalWrite(light, HIGH);
}

void lightOff() {
  digitalWrite(light, LOW);
}

void endTask() {
  tone(buzzer, 2000, 1000);
  lightOn();
  delay(500);
  lightOff();
  delay(500);
  lightOn();
  delay(500);
  lightOff();
  delay(500);
  lightOn();
  delay(500);
  lightOff();
}

