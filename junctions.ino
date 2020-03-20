//---------Detecting Junction----------------------------------
void junctionType() {

  if ((hunterL == 0 && hunterR == 0) || (dvalF[0] == 0 && dvalF[6] == 0) || (dvalF[1] == 0 && dvalF[7] == 0) || (dvalF[1] == 0 && dvalF[6] == 0) || (dvalF[0] == 0 && dvalF[7] == 0)) {
    goBit(250);
    qtrReadSec();

    //End ( All are white)
    if (secvalF[1] == 0 && secvalF[6] == 0) {
      Serial.println("end");
      n = 0;
      turns = turns + 'E' ;
      Serial.println(turns);
      saveShortest();
    }

    // T or +
    else {
      Serial.println("T or +");
      if ( righthandrule == 1) {
        turnRightRandom(525);
        turns = turns + 'R' ;
      } else {
        turnLeftRandom(525);
        turns = turns + 'L' ;
      }
      aligningBotF();
    }

    shortPath();
    delay(80);
  }
  else if (dvalF[5] == 0 && dvalF[7] == 0) {
    Serial.println("left junction");
    goBit(250);
    delay(80);
    qtrReadSec();

    if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
      turns = turns + 'E' ;
      Serial.println(turns);
      saveShortest();
    }

    // -| junction
    else if (secvalF[2] == 0 || secvalF[5] == 0 || secvalF[3] == 0 || secvalF[4] == 0) {
      Serial.println("-| left");
      if ( righthandrule == 1) {
        turns = turns + 'S' ;
      } else {
        turnLeftRandom(525);
        turns = turns + 'L' ;
      }
      aligningBotF();
    }

    //Left L junction
    else {
      Serial.println("L left");
      turns = turns + 'L' ;
      turnLeftRandom(525);
      aligningBotF();
    }

    shortPath();
    delay(80);

  } else if (dvalF[0] == 0 && dvalF[2] == 0) {
    goBit(250);
    delay(80);
    qtrReadSec();
    Serial.println("right junction");
    // Right L junction
    if (!(secvalF[2] == 0 || secvalF[5] == 0 || secvalF[3] == 0 || secvalF[4] == 0)) {
      Serial.println("L right");
      turns = turns + 'R' ;
      turnRightRandom(525);
      aligningBotF();
    }

    else if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
      turns = turns + 'E' ;
      Serial.println(turns);
      saveShortest();
    }
    // |- junction
    else {
      Serial.println("|- right");
      if ( righthandrule == 1) {
        turnRightRandom(525);
        turns = turns + 'R' ;
      } else {
        turns = turns + 'S' ;
      }
      aligningBotF();
    }
    shortPath();
    delay(80);
  }
}

//**********turning back to line at left*********************************

void backToLineLeft()
{
  while (1)  // test countings
  {
    leftTurn(45, 45);
    qtrReadF();
    if (dvalF[3] == 0 && dvalF[4] == 0) {
      brake();
      break;
    }
  }

}

//**********turning back to line at right*********************************


void backToLineRight()
{
  while (1)  // test countings
  {
    rightTurn(45, 45);
    qtrReadF();
    if (dvalF[3] == 0 && dvalF[4] == 0) {
      brake();
      break;
    }

  }
}
//**********turning 90 degrees to the left*********************************

void turnLeftRandom(int turns)
{
  leftCount = 0;
  rightCount = 0;
  while (leftCount < turns || rightCount < turns) // test countings
  {
    if (speedTurn == 1) encoderPIDfast();
    else encoderPID();
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
  }
  brake();
  delay(70);
  leftCount = 0;
  rightCount = 0;

}

//****************   turning 90 degrees to the right   ********************

void turnRightRandom(int turns)
{
  leftCount = 0;
  rightCount = 0;

  while (leftCount < turns || rightCount < turns) // test countings
  {
    if (speedTurn == 1) encoderPIDfast();
    else encoderPID();
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
  }
  brake();
  delay(70);
  leftCount = 0;
  rightCount = 0;
}




//############################################################################################################################################
void testLeftHandRule() {

  if (dvalF[5] == 0 && dvalF[7] == 0) {

    goBit(250);
    delay(80);
    qtrReadSec();

    //End ( All are white)
    if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
    }

    // -| or + junction
    else {
      Serial.println("left");
      turnLeftRandom(525);
      aligningBotF();
    }

  } else if (dvalF[0] == 0 && dvalF[2] == 0) {
    goBit(250);
    delay(80);
    qtrReadSec();

    //End ( All are white)
    if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
    }
    // |- junction
    else if (secvalF[2] == 0 || secvalF[5] == 0 || secvalF[3] == 0 || secvalF[4] == 0) {
      aligningBotF();
    }

    else {
      turnRightRandom(525);
      aligningBotF();
    }
  }
}




void testRightHandRule() {
  if (dvalF[0] == 0 && dvalF[2] == 0) {
    goBit(250);
    delay(80);
    qtrReadSec();

    //End ( All are white)
    if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
    }

    else {
      turnRightRandom(525);
      aligningBotF();
    }

  }
  else if (dvalF[5] == 0 && dvalF[7] == 0) {
    goBit(250);
    delay(80);
    qtrReadSec();

    //End ( All are white)
    if ((secvalF[1] == 0 && secvalF[6] == 0) || (secvalF[0] == 0 && secvalF[7] == 0)) {
      Serial.println("end");
      n = 0;
    }
    // -| junction
    else if (secvalF[2] == 0 || secvalF[5] == 0 || secvalF[3] == 0 || secvalF[4] == 0) {
      aligningBotF();
    }
    else {
      Serial.println("left");
      turnLeftRandom(525);
      aligningBotF();
    }

  }
}
