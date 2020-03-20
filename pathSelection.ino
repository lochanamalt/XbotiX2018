void goforPath() {
  stopPoint();
  goBit(250);
  if (loadingSide == 0)  turnLeftRandom(525);
  else turnRightRandom(525);
  stopPoint();
  goBit(250);
  if (dvalF[2] = 1 && dvalF[5] == 0 && dvalF[7] == 0) turnLeftRandom(525);
  else if (dvalF [5] == 1 && dvalF[0] == 0 && dvalF[2] == 0) turnRightRandom(525);
}

//########################################################### CHANGE THIS IN THE COMPETITION #################################################################################
//########################################################### CHANGE THIS IN THE COMPETITION #################################################################################
//########################################################### CHANGE THIS IN THE COMPETITION #################################################################################
void selectPath() {
  switch (color) {
    case 'R': path = 1; break;
    case 'B': path = 2; break;
    case 'G': path = 3; break;
    default : path = 1; break;
  }
}

void goOnPathRight() {
  switch (path) {
    case 1:
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      unload();
      break;
    case 2:
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      unload();
      break;
    case 3:
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      unload();
      break;
    default :
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      unload();
      break;
  }
  stopPoint();
}

void goOnPathLeft() {
  switch (path) {
    case 1:
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      stopPointSlow();
      unload();
      break;
    case 2:
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      stopPointSlow();
      unload();
      break;
    case 3:
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      stopPointSlow();
      unload();
      break;
    default :
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      delay(50);
      flatBlock();
      delay(50);
      stopPointSlow();
      unload();
      break;
  }
  stopPoint();
}



void unload() {
  reversePID(200);
  delay(100);
  angle2(servo1, servo2, 50);
  angle(servo1, servo2, 5);
  aligningBotF();
  aligningBotB();
  shakeRight(10);
  shakeLeft(20);
  shakeRight(10);
  servo3.write(30);
  delay(80);
  servo1.write(160);
  servo2.write(15);
  servo3.write(22);
  //####################################### CHANGE THIS ON THE COMPETTION ##################################################################################################
  fakeRoadLineShortRight();

}

void flatBlock() {
  aligningBotF();
  angle(servo1, servo2, 20);
  angle2(servo1, servo2, 50);
  angle(servo1, servo2, 10);
  delay(100);
  servo3.write(20);
  delay(100);
  angleDecrease(servo2, 108);//servo2-110,servo1-//80
  angle(servo1, servo2, 5);
  angleIncrease(servo1, 105);
  delay(100);
  servo3.write(63);
  delay(100);
  angle2(servo2, servo1, 35);
  angleDecrease(servo2, 55);
  delay(100);
  stopPointSlow();
}

void fakeRoadLineLongLeft() {
  turnLeftRandom(525);
  goBit(500);
  turnRightRandom(525);
  goBit(1300);
  turnRightRandom(525);
  goBit(500);
  turnLeftRandom(525);
  switch (path) {
    case 1:
      stopPointSlow();
      goBit(250);
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
    case 2:
      stopPointSlow();
      goBit(250);
      break;
    case 3:
      stopPointSlow();
      goBit(250);
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
    default:
      stopPointSlow();
      goBit(250);
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
  }
}

void fakeRoadLineLongRight() {
  turnLeftRandom(525);
  goBit(500);
  turnRightRandom(525);
  goBit(1300);
  turnRightRandom(525);
  goBit(500);
  turnLeftRandom(525);
  switch (path) {
    case 1:
      stopPointSlow();
      goBit(250);
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
    case 2:
      stopPointSlow();
      goBit(250);
      break;
    case 3:
      stopPointSlow();
      goBit(250);
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
    default:
      stopPointSlow();
      goBit(250);
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
  }
}
void fakeRoadLineShortRight() {
  switch (path) {
    case 1 :
      turnLeftRandom(525);
      goBit(500);
      turnRightRandom(525);
      goToPath();
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
    case 2 :
      turnLeftRandom(525);
      goBit(700);
      turnRightRandom(525);
      goToPath();
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
    case 3 :
      turnRightRandom(525);
      goBit(500);
      turnLeftRandom(525);
      goToPath();
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
    default:
      turnLeftRandom(525);
      goBit(500);
      turnRightRandom(525);
      goToPath();
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
  }
}


void fakeRoadLineShortLeft() {
  switch (path) {
    case 1 :
      turnRightRandom(525);
      goBit(500);
      turnLeftRandom(525);
      goToPath();
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
    case 2 :
      turnRightRandom(525);
      goBit(700);
      turnLeftRandom(525);
      goToPath();
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
    case 3 :
      turnLeftRandom(525);
      goBit(500);
      turnRightRandom(525);
      goToPath();
      turnLeftRandom(525);
      stopPoint();
      goBit(250);
      turnRightRandom(525);
      break;
    default:
      turnRightRandom(525);
      goBit(500);
      turnLeftRandom(525);
      goToPath();
      turnRightRandom(525);
      stopPoint();
      goBit(250);
      turnLeftRandom(525);
      break;
  }
}
void angle(Servo servo1, Servo servo2, int anglediff) {
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  for (int i = 0; i < anglediff; ++i) {
    servo2.write(initial2 + 2 * i);
    servo1.write(initial1 - i);
    delay(20);
  }
}

void angle2(Servo servo1, Servo servo2, int anglediff) {
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  for (int i = 0; i < anglediff; ++i) {
    servo2.write(initial2 + i);
    servo1.write(initial1 - i);
    delay(20);
  }
}
void angle3(Servo servo1, Servo servo2, int anglediff) {
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  for (int i = 0; i < anglediff; ++i) {
    servo2.write(initial2 + i);
    servo1.write(initial1 + i);
    delay(20);
  }
}

void angleOpposite(Servo servo1, Servo servo2, int anglediff) {
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  for (int i = 0; i < anglediff; ++i) {
    servo2.write(initial2 - 2 * i);
    servo1.write(initial1 + i);
    delay(20);
  }
}

void angle2Opposite(Servo servo1, Servo servo2, int anglediff) {
  int initial1 = servo1.read();
  int initial2 = servo2.read();
  for (int i = 0; i < anglediff; ++i) {
    servo2.write(initial2 - i);
    servo1.write(initial1 + i);
    delay(20);
  }
}
