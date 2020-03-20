void Wall_PID(double ultrasonicDistance, int pidspeed, int sign, double WKp , double WKd , int distance)
{
  Werror = ultrasonicDistance - distance;
  int motorSpeed = WKp * Werror + WKd * (Werror - WlastError);
  WlastError = Werror;
  WrightBaseSpeed = pidspeed;
  WleftBaseSpeed = pidspeed;
  int rightMotorSpeed = WrightBaseSpeed - ( sign * motorSpeed);
  int leftMotorSpeed = WleftBaseSpeed + (sign * motorSpeed);
  if (rightMotorSpeed > WrightMaxSpeed ) rightMotorSpeed = WrightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > WleftMaxSpeed ) leftMotorSpeed = WleftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = WrightMinSpeed; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = WleftMinSpeed; // keep the motor speed positive
  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
}

void wall() {
  while ( w == 1) {
    if (FRightUltrasonic() < 30 && FRightUltrasonic() < 30 && FRightUltrasonic() < 30) {
      //      Serial.println("right wall detected");
      while (FRightUltrasonic() < 30) {
        if (right45Ultrasonic() < 9 && right45Ultrasonic() < 9 && right45Ultrasonic() < 9) {
          //          Serial.println("right45");
          brake();
          delay(50);
          double ultra = right45Ultrasonic();
          while (ultra < 11 )
          {
            //            Serial.println("right45 while ");
            encoderPID();
            leftTurn();
            ultra = right45Ultrasonic();
          }
          // parellelBotRight();
          break;
        } else {
          Wall_PID(FRightUltrasonic(), 40, 1 , 30 , 80 , 10);
          forward();
          side = 'R';
        }
      }
    }
    else if (FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30) {
      //      Serial.println("left wall detected");
      while (FLeftUltrasonic() < 30) {
        if (left45Ultrasonic() < 9 && left45Ultrasonic() < 9 && left45Ultrasonic() < 9) {
          brake();
          //          Serial.println("left 45");
          delay(50);
          double ultra = left45Ultrasonic();
          while (ultra < 11)
          {
            //            Serial.println("left 45 while ");
            encoderPID();
            rightTurn();
            ultra = left45Ultrasonic();
          }
          // parellelBotLeft();
          break;
        } else {
          Wall_PID(FLeftUltrasonic(), 40, -1 , 10 , 115 , 10);
          forward();
          side = 'L';
        }
      }
    } else {
      qtrReadF();
      brake();
      if (dvalF[0] == 0 && dvalF[7] == 0) {
        brake();
        w = 0;
        break;
      }
      goBit(250);
      if ((FRightUltrasonic() < 30 && FRightUltrasonic() < 30 && FRightUltrasonic() < 30) || (FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30) ) {
        continue;
      }
      else {
        switch (side) {
          case 'R' :
            turnRightRandom(300);
            delay(500);
            goBit(250);
            delay(100);
            break;
          case 'L' :
            turnLeftRandom(300);
            delay(500);
            goBit(250);
            delay(100);
            break;
          default : brake(); break;
        }
      }
    }
  }
}


void parellelBotRight() {
  if (FRightUltrasonic() < 30 && FRightUltrasonic() < 30)
  {
    while (1) {
      signed int rightdifference = BRightUltrasonic() - FRightUltrasonic() ;
      if (rightdifference == 1) {
        brake();
        break;
      }
      else if (rightdifference >= 2) {
        encoderPID();
        leftTurn();

      }
      else {
        encoderPID();
        rightTurn();
      }
    }
  }
}


void parellelBotLeft() {
  if (FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30)
  {
    while (1) {
      signed int leftdifference = BLeftUltrasonic() - FLeftUltrasonic() ;
      if (leftdifference == 1) {
        brake();
        break;
      }
      else if (leftdifference >= 2) {
        encoderPID();
        rightTurn();
      }
      else {
        encoderPID();
        leftTurn();
      }
    }
  }
}



void goToWallLeft() {
  while (FLeftUltrasonic() < 30) {
    if (FRightUltrasonic() > 30 && FRightUltrasonic() > 30 && FLeftUltrasonic() < 30) {
      brake();
      break;
    }
     Wall_PID(FRightUltrasonic(), 40, 1 , 30 , 80 , 10);
    forward();
  }
  brake();
  delay(70);
}

void goToWallRight() {
  while (FRightUltrasonic() < 30) {
    if (FLeftUltrasonic() > 30 && FLeftUltrasonic() > 30) {
      brake();
      break;
    }
    Wall_PID(FLeftUltrasonic(), 40, -1 , 10 , 115 , 10);
    forward();
  }
  brake();
  delay(70);
}
