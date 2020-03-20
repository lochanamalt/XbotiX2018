//---------------------Coming to a juction------------------------
void solveMaze() {
  while (n == 1) {
    PIDFront(Kp,Kd,rightBaseSpeed,leftBaseSpeed,rightMaxSpeed,leftMaxSpeed);
    forward();
    qtrReadF();
    hunterRead();
    if ((dvalF[0] == 0 && dvalF[6] == 0) || (dvalF[1] == 0 && dvalF[7] == 0) || (dvalF[1] == 0 && dvalF[6] == 0) || (dvalF[0] == 0 && dvalF[7] == 0) || (dvalF[5] == 0 && dvalF[7] == 0 && hunterL==0) || (hunterR == 0 &&  dvalF[0] == 0 && dvalF[2] == 0)) {
      Serial.println("junction");
      brake();
      if (shortest == 1) {
        goShortest();
      }
      else if(alternative == 1){
        testLeftHandRule();
      }
      else {
       junctionType();
      }
    }
    else if (dvalF[7] == 0 && dvalF[6] == 1 && dvalF[1] == 1 && dvalF[2] == 1 && dvalF[3] == 1 && dvalF[4] == 1) {
      brake();
      backToLineLeft();
      Serial.println("back to left");
      aligningBotF();
    }
    else if (dvalF[0] == 0 && dvalF[1] == 1 && dvalF[6] == 1 && dvalF[5] == 1 && dvalF[4] == 1 && dvalF[3] == 1) {
      brake();
      backToLineRight();
       Serial.println("back to right");
       aligningBotF();
    }
    else if (dvalF[0] == 1 && dvalF[1] == 1 && dvalF[2] == 1 && dvalF[3] == 1 && dvalF[4] == 1 && dvalF[5] == 1 && dvalF[6] == 1 && dvalF[7] == 1 ) {
      brake();
      delay(90);
      turnRightRandom(1050);
      turns = turns + 'U' ;
      aligningBotF();
       Serial.println("turn u");

    }
  }
}

//=====================================================================================
