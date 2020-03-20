void wall4() {
  while ( w == 1) {
    if (FRightUltrasonic() < 31 && FRightUltrasonic() < 31 && FRightUltrasonic() < 31) {
      while (FRightUltrasonic() < 31) {

        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnLeftRandom(200);
        }
        if (right45Ultrasonic() < 11 && right45Ultrasonic() < 11 )
        {
          turnLeftRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FRightUltrasonic(), 40, 1 , 30 , 80 , 10);
        forward();
        side = 'R';
      }
    }

    else if (FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31) {
      while (FLeftUltrasonic() < 31) {
        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnRightRandom(200);
        }
        if (left45Ultrasonic() < 11 && left45Ultrasonic() < 11)
        {
          turnRightRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FLeftUltrasonic(), 40, -1 , 10 , 115 , 10);
        forward();
        side = 'L';
      }
    } else {
      goBit(250);
      hunterRead();
      if (hunterR == 0 || hunterL == 0)
      {
        brake();
        w = 0;
        break;
      }
      else {
        if ((FRightUltrasonic() < 30 && FRightUltrasonic() < 30 && FRightUltrasonic() < 30) || (FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30 && FLeftUltrasonic() < 30) ) {
          continue;
        }
        else if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          // Serial.println("no walls in either sides");
          switch (side) {
            case 'R' : turnLeftRandom(200);
              //Serial.println("right");
              break;
            case 'L' : turnRightRandom(200);
              //Serial.println("left");
              break;
          }

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
}


void wall2() {
  while ( w == 1) {
    if (FRightUltrasonic() < 31 && FRightUltrasonic() < 31 && FRightUltrasonic() < 31) {
      while (FRightUltrasonic() < 31) {
        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnLeftRandom(200);
        }
        if (right45Ultrasonic() < 11 && right45Ultrasonic() < 11 )
        {
          turnLeftRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FRightUltrasonic(), 40, 1 , 23 , 115 , 10);
        forward();
        side = 'R';
      }
    }

    else if (FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31) {
      while (FLeftUltrasonic() < 31) {
        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnRightRandom(200);
        }
        if (left45Ultrasonic() < 11 && left45Ultrasonic() < 11)
        {
          turnRightRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FLeftUltrasonic(), 40, -1 , 10 , 115 , 10);
        forward();
        side = 'L';
      }
    }
    else {
      brake();
      hunterRead();
      if (hunterR == 0 || hunterL == 0)
      {
        brake();
        w = 0;
        break;
      }
      else if (middleUltrasonic() < 7 || middleUltrasonic() < 7 ) {
        reverseBit(250);
        // Serial.println("no walls in either sides");
        switch (side) {
          case 'R' : turnLeftRandom(500);
            //Serial.println("right");
            break;
          case 'L' : turnRightRandom(500);
            //Serial.println("left");
            break;
        }
      }
      else {
        goBit(300);
        if ((FRightUltrasonic() < 31 && FRightUltrasonic() < 31 && FRightUltrasonic() < 31) || (FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31) ) {
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
}


void wall3() {
  while ( w == 1) {
    if (FRightUltrasonic() < 31 && FRightUltrasonic() < 31 && FRightUltrasonic() < 31) {
      while (FRightUltrasonic() < 31) {
        if (FLeftUltrasonic() < 20 && FLeftUltrasonic() < 20)
        {
          brake();
          goToWallLeft();
          side = 'L';
          break;
        }
        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnLeftRandom(200);
        }
        if (right45Ultrasonic() < 11 && right45Ultrasonic() < 11 )
        {
          turnLeftRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FRightUltrasonic(), 40, 1 , 30 , 80 , 10);
        forward();
        side = 'R';
      }
    }

    if (FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31) {
      while (FLeftUltrasonic() < 31) {
        if (FRightUltrasonic() < 20 && FRightUltrasonic() < 20)
        {
          brake();
          goToWallRight();
          tone(buzzer, 2000, 1000);
          side = 'R';
          break;
        }
        if (middleUltrasonic() < 7 && middleUltrasonic() < 7 )
        {
          brake();
          tone(buzzer, 2000, 1000);
          reverseBit(100);
          turnRightRandom(200);
        }
        if (left45Ultrasonic() < 11 && left45Ultrasonic() < 11)
        {
          turnRightRandom(200);
        }
        hunterRead();
        if (hunterR == 0 || hunterL == 0)
        {
          brake();
          w = 0;
          break;
        }
        Wall_PID(FLeftUltrasonic(), 40, -1 , 10 , 115 , 10);
        forward();
        side = 'L';
      }
    }

    if ((FRightUltrasonic() > 30 && FRightUltrasonic() > 30 && FRightUltrasonic() > 30) && (FLeftUltrasonic() > 30 && FLeftUltrasonic() > 30 && FLeftUltrasonic() > 30) ) {
      brake();
      hunterRead();
      if (hunterR == 0 || hunterL == 0)
      {
        brake();
        w = 0;
        break;
      }
      else if (middleUltrasonic() < 7 && middleUltrasonic() < 7 ) {
        reverseBit(250);
        // Serial.println("no walls in either sides");
        switch (side) {
          case 'R' : turnLeftRandom(500);
            //Serial.println("right");
            break;
          case 'L' : turnRightRandom(500);
            //Serial.println("left");
            break;
        }
      }
      else {
        goBit(300);
        if ((FRightUltrasonic() < 31 && FRightUltrasonic() < 31 && FRightUltrasonic() < 31) || (FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31 && FLeftUltrasonic() < 31) ) {
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
}
