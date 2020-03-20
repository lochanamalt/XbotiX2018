void poleCount() {
  int i = 0;
  while (i < 6) {
    goBit(100);
    if (FRightUltrasonic() < 20 && Rpole == 0) Rpole = 1;
    if (FLeftUltrasonic() < 20 && Lpole == 0) Lpole = 1;
    if (middleUltrasonic() < 20 && Mpole == 0) Mpole = 1;
    ++i;
    if (Rpole + Lpole + Mpole == 3) break;

  }

  turnLeftRandom(90);
  if (middleUltrasonic() < 20 && Mpole == 0) Mpole = 1;
  delay(500);
  turnRightRandom(180);
  if (middleUltrasonic() < 20 && Mpole == 0) Mpole = 1;
  delay(500);
  turnLeftRandom(90);
  if (middleUltrasonic() < 20 && Mpole == 0) Mpole = 1;
  delay(100);
  
  switch (Rpole + Lpole + Mpole) {
    case 1: tone(buzzer, 2000, 500); delay(1000); color='R'; break;
    case 2: tone(buzzer, 2000, 500); delay(1000); tone(buzzer, 2000, 500);  delay(1000);  color='B'; break;
    case 3: tone(buzzer, 2000, 500); delay(1000); tone(buzzer, 2000, 500); delay(1000); tone(buzzer, 2000, 500);  delay(1000);  color='G'; break;
    default : break;
  }
}

unsigned int FRightUltrasonic() {
  digitalWrite(FRightTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(FRightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRightTrigPin, LOW);
  FRightDuration = pulseIn(FRightEchoPin, HIGH);
  return (FRightDuration / 2) / 29.1;
}

unsigned int FLeftUltrasonic() {
  digitalWrite(FLeftTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(FLeftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FLeftTrigPin, LOW);
  FLeftDuration = pulseIn(FLeftEchoPin, HIGH);
  return (FLeftDuration / 2) / 29.1;
}
unsigned int BRightUltrasonic() {
  digitalWrite(BRightTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(BRightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BRightTrigPin, LOW);
  BRightDuration = pulseIn(BRightEchoPin, HIGH);
  return (BRightDuration / 2) / 29.1;
}

unsigned int BLeftUltrasonic() {
  digitalWrite(BLeftTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(BLeftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BLeftTrigPin, LOW);
  BLeftDuration = pulseIn(BLeftEchoPin, HIGH);
  return (BLeftDuration / 2) / 29.1;
}

unsigned int middleUltrasonic() {
  digitalWrite(middleTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(middleTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(middleTrigPin, LOW);
  middleDuration = pulseIn(middleEchoPin, HIGH);
  return (middleDuration / 2) / 29.1;
}

unsigned int right45Ultrasonic() {
  digitalWrite(right45TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(right45TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(right45TrigPin, LOW);
  right45Duration = pulseIn(right45EchoPin, HIGH);
  return (right45Duration / 2) / 29.1;
}

unsigned int left45Ultrasonic() {
  digitalWrite(left45TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(left45TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(left45TrigPin, LOW);
  left45Duration = pulseIn(left45EchoPin, HIGH);
  return (left45Duration / 2) / 29.1;
}
