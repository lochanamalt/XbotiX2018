#include <QTRSensors.h>
#include <SPI.h>
#include <Pixy.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>


//---------------- Line PID-------------------------------------------------------------

double Kp = 0.033;
double Kd = 0.18;
int rightMaxSpeed = 160; //max speed of the robot
int leftMaxSpeed = 160; //max speed of the robogfhgf
#define rightMinSpeed 0 // min speed of xsthe robot
#define leftMinSpeed 0 // min speed of the robot  
int rightBaseSpeed = 80; // this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeed = 80; // this is the speed at which the motors should spin when the robot is perfectly on the line


double KpReverse = 0.011738; // 0.0388
double KdReverse = 0.088;   // 0.28
#define rightMaxSpeedReverse 80//max speed of the robot
#define leftMaxSpeedReverse 80//max speed of the robogfhgf
int rightBaseSpeedReverse = 47; // this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeedReverse = 47; // this is the speed at which the motors should spin when the robot is perfectly on the line


double KpSlow = 0.0388;
double KdSlow = 0.05;
int rightMaxSpeedSlow = 80; //max speed of the robot
int leftMaxSpeedSlow = 80; //max speed of the robogfhgf
int rightBaseSpeedSlow = 47; // this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeedSlow = 47; // this is the speed at which the motors should spin when the robot is perfectly on the line

int rightMotorSpeed, leftMotorSpeed;


int lastError = 0;
unsigned int position;
int error;



//---------------- Wall PID-------------------------------------------------------------

#define WrightMaxSpeed 80//max speed of the robot
#define WleftMaxSpeed 80//max speed of the robot
#define WrightMinSpeed 0 // min speed of the robot
#define WleftMinSpeed 0 // min speed of the robot  
int WrightBaseSpeed = 60; // this is the speed at which the motors should spin when the robot is perfectly aligned to wall
int WleftBaseSpeed = 60; // this is the speed at which the motors should spin when the robot is perfectly aligned to wall

int WlastError = 0;
int Werror;
int WerrorSum = 0;

char side;



//-----------------------MOTORS---------------------------------------

//M1
#define motorR_enb 26
#define motorR_dirP 49
#define motorR_dirN 41
#define motorR_PWM 6

//M2
#define motorL_enb 47
#define motorL_dirP 43
#define motorL_dirN 45
#define motorL_PWM 4




//-------------LINE HUNTER -------------------------------
#define hunterLeft A1
#define hunterRight A2
int hunterL, hunterR = 0;


//**************Line Hunter Sensor Reading ****************

void hunterRead() {
  if (analogRead (hunterLeft) > 500)
    hunterL = 1;
  else hunterL = 0;
  if (analogRead (hunterRight) > 500)
    hunterR = 1;
  else hunterR = 0;
}

//--------------- ultra sonic-----------------------------------

// specify the trig & echo pins used for the ultrasonic sensors

//right
#define FRightTrigPin  A9
#define FRightEchoPin  A8

//left
#define FLeftTrigPin  A4
#define FLeftEchoPin  A3

//back left
#define BLeftTrigPin  A7
#define BLeftEchoPin  A0

//back right
#define BRightTrigPin  A14
#define BRightEchoPin  A15

//middle
#define middleTrigPin  A6
#define middleEchoPin  A5

//left45
#define left45TrigPin  A11
#define left45EchoPin  A10

//right45
#define right45TrigPin  A12
#define right45EchoPin  A13

unsigned int FRightDistance;
int FRightDuration;

unsigned int FLeftDistance;
int FLeftDuration;

unsigned int BLeftDistance;
int BLeftDuration;

unsigned int BRightDistance;
int BRightDuration;

unsigned int middleDistance;
int middleDuration;

unsigned int right45Distance;
int right45Duration;

unsigned int left45Distance;
int left45Duration;

//-------------------------PIXY cam light-------------------------------------
#define light 22


//-------------------------Servos---------------------------------------------
Servo servo1;
Servo servo2;
Servo servo3;

//---------------------- buttons ------------------------------------------
const int buttonPin[] = {12, 13, 11, 10, 1, 0, 7, 5 };
int btnstate1 = 0, btnstate2 = 0, btnstate3 = 0 , btnstate4 = 0 , btnstate5 = 0, btnstate6 = 0, btnstate7 = 0 , btnstate8 = 0 ;


//-----------------------QTR Sensor--------------------------

#define NUM_SENSORSF  8    // number of sensors use
#define NUM_SENSORSB  8    // number of sensors use

#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN
#define buzzer 39



QTRSensorsRC qtrrcF((unsigned char[]) {
  32, 36, 38, 40, 42, 44, 46, 48
} , NUM_SENSORSF, TIMEOUT, EMITTER_PIN);
QTRSensorsRC qtrrcB((unsigned char[]) {
  14, 15, 16, 17, 18, 19, 9, 8
} , NUM_SENSORSB, TIMEOUT, EMITTER_PIN);

unsigned int sensorValuesF[NUM_SENSORSF];
unsigned int sensorValuesB[NUM_SENSORSB];

bool dvalF[NUM_SENSORSF];
bool dvalB[NUM_SENSORSB];
bool secvalF[NUM_SENSORSF];
bool secvalB[NUM_SENSORSB];

void qtrReadF() {
  qtrrcF.readLine(sensorValuesF);
  for (int i = 0; i < NUM_SENSORSF ; i++ ) {

    if (sensorValuesF[i] > 400) {
      dvalF[i] = 1;
    }
    else dvalF[i] = 0;
    //         Serial.print(dvalF[i]);
    //        Serial.print("    ");
  }
  //  Serial.println();
}

void qtrReadB() {
  qtrrcB.readLine(sensorValuesB);
  for (int i = 0; i < NUM_SENSORSB ; i++ ) {
    //    Serial.print(sensorValuesB[i]);
    //    Serial.print("    ");
    if (sensorValuesB[i] > 400) dvalB[i] = 1;
    else dvalB[i] = 0;
  }
  //  Serial.println();
}



void qtrReadSec() {
  qtrrcF.readLine(sensorValuesF);
  for (int i = 0; i < NUM_SENSORSF ; i++ ) {
    if (sensorValuesF[i] > 400) secvalF[i] = 1;
    else secvalF[i] = 0;
  }
}


void Calibrate() {
  tone(buzzer, 2000, 1000);
  for (int i = 0; i < 200; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrcF.calibrate();
  tone(buzzer, 2000, 1000);
  delay(1000);

  for (int i = 0; i < 200; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrcB.calibrate();
  tone(buzzer, 2000, 1000);
  delay(1000);
}


void saveCalibrated() {
  for (int i = 0; i < NUM_SENSORSF; ++i)
  {
    EEPROM.write(i, (qtrrcF.calibratedMinimumOn[i] / 10));
    EEPROM.write(i + 8, (qtrrcF.calibratedMaximumOn[i] / 10));
  }
  for (int i = 0; i < NUM_SENSORSB; i++)
  {
    EEPROM.write(i + 16, (qtrrcB.calibratedMinimumOn[i] / 2));
    EEPROM.write(i + 24, (qtrrcB.calibratedMaximumOn[i] / 10));
  }
}


void qtrLoad()  //loading calibrated sensor values
{
  for (int i = 0; i < NUM_SENSORSF; i++)
  {

    qtrrcF.calibratedMinimumOn[i] = 10 * EEPROM.read(i);
    qtrrcF.calibratedMaximumOn[i] = 10 * (EEPROM.read(i + 8));

  }

  for (int i = 0; i < NUM_SENSORSB; i++)
  {
    qtrrcB.calibratedMinimumOn[i] = 2 * EEPROM.read(i + 16);
    qtrrcB.calibratedMaximumOn[i] = 10 * (EEPROM.read(i + 24));
    Serial.println(qtrrcB.calibratedMinimumOn[i]);
  }
}





//  Encoders functions ------------------------------------------

volatile long leftCount = 0, rightCount = 0;
void leftISR() //ISR for left motor count
{
  leftCount++;
}
void rightISR() //ISR for right motor count
{
  rightCount++;
}


//----------------PIXY CAM ----------------------------------------

Pixy pixy;

int Lpole = 0;
int Rpole = 0;
int Mpole = 0;
int poleDetected = 0;

char up = ' ';
char middle = ' ';
char bottom = ' ';
char color = ' ';

int path = 1;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  delay(500);

  //********************SERVO**************************
  servo1.attach(30);
  servo2.attach(28);
  servo3.attach(24);

  servo1.write(160);//adu pahalata// min-10 max-160
  servo2.write(15); //adu pitipassata min-15 max-150 down-133 middle- 105 up -
  servo3.write(22);//digaariddi adu , max-58 min-22

  //***********MOTOR**************************
  pinMode(motorR_dirP, OUTPUT);
  pinMode(motorR_dirN, OUTPUT);

  pinMode(motorL_dirP, OUTPUT);
  pinMode(motorL_dirN, OUTPUT);

  pinMode(motorR_PWM, OUTPUT);
  pinMode(motorL_PWM, OUTPUT);

  pinMode(motorL_enb, OUTPUT);
  pinMode(motorR_enb, OUTPUT);

  digitalWrite(motorR_enb, HIGH);
  digitalWrite(motorL_enb, HIGH);

  // ultrasonic sensor pin configurations
  pinMode(FRightTrigPin, OUTPUT);
  pinMode(FRightEchoPin, INPUT);

  pinMode(BRightTrigPin, OUTPUT);
  pinMode(BRightEchoPin, INPUT);

  pinMode(FLeftTrigPin, OUTPUT);
  pinMode(FLeftEchoPin, INPUT);

  pinMode(BLeftTrigPin, OUTPUT);
  pinMode(BLeftEchoPin, INPUT);

  pinMode(middleTrigPin, OUTPUT);
  pinMode(middleEchoPin, INPUT);

  pinMode(right45TrigPin, OUTPUT);
  pinMode(right45EchoPin, INPUT);

  pinMode(left45TrigPin, OUTPUT);
  pinMode(left45EchoPin, INPUT);

  //*******************BUZZER************************
  pinMode(buzzer, OUTPUT);

  //********************PIXY**************************
  pixy.init();


  //*****************Color detection light***************
  pinMode(light, OUTPUT);


  //********************Buttons ****************************

  for (int x = 0; x < 8; x++)
  {
    pinMode(buttonPin[x], INPUT_PULLUP);
  }

  //************CALIBRATE***************************

  Calibrate();
  //saveCalibrated();
  //qtrLoad();

  //**********Encoders************************************

  attachInterrupt(digitalPinToInterrupt(3), leftISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), rightISR, CHANGE);

}


byte index = 0;
int n = 1 , w = 1, righthandrule = 0 , shortest = 0, parallelWall = 0, alternative = 0;
int speedTurn = 0;
String turns;
String inverseTurns;
int loadingSide = 0;

void loop() {

  btnstate1 = digitalRead(buttonPin[0]);
  btnstate2 = digitalRead(buttonPin[1]);
  btnstate3 = digitalRead(buttonPin[2]);
  btnstate4 = digitalRead(buttonPin[3]);
  btnstate5 = digitalRead(buttonPin[4]);
  btnstate6 = digitalRead(buttonPin[5]);
  btnstate7 = digitalRead(buttonPin[6]);
  btnstate8 = digitalRead(buttonPin[7]);

  // First Round Left hand rule
  if (btnstate1 == LOW)
  {
    delay(1500);
    while (1) {
      btnstate1 = digitalRead(buttonPin[0]);
      btnstate2 = digitalRead(buttonPin[1]);
      btnstate3 = digitalRead(buttonPin[2]);
      btnstate4 = digitalRead(buttonPin[3]);
      btnstate6 = digitalRead(buttonPin[5]);
      if (btnstate1 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();
        n = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }

      else if (btnstate2 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }

      else if (btnstate3 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();
        n = 1;
        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();

      }
      else if (btnstate4 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }

      else if (btnstate6 == LOW)
      {
        shortest = 1;
        readShortest();
        goToline();

        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }
    }
  }


  // First round Right hand rule
  else  if (btnstate2 == LOW)
  {
    delay(1500);
    righthandrule = 1;
    while (1) {
      btnstate1 = digitalRead(buttonPin[0]);
      btnstate2 = digitalRead(buttonPin[1]);
      btnstate3 = digitalRead(buttonPin[2]);
      btnstate4 = digitalRead(buttonPin[3]);
      btnstate6 = digitalRead(buttonPin[5]);
      if (btnstate1 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();
        n = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }

      else if (btnstate2 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();

      }

      else if (btnstate3 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();

      }
      else if (btnstate4 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        speedTurn = 0;
        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }
      else if (btnstate6 == LOW)
      {
        goToline();
        shortest = 1;
        readShortest();

        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
    }
  }

  // Second Round Left hand
  else if (btnstate3 == LOW)
  {
    delay(1500);
    while (1) {
      btnstate1 = digitalRead(buttonPin[0]);
      btnstate2 = digitalRead(buttonPin[1]);
      btnstate3 = digitalRead(buttonPin[2]);
      btnstate4 = digitalRead(buttonPin[3]);

      if (btnstate1 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################
        goOnPathRight();
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        w = 1;

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(22);
        delay(100);
        endTask();
      }

      else if (btnstate2 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }

      else if (btnstate3 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
      else if (btnstate4 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################


        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();


        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
    }
  }



  // Second Round Right hand
  else if (btnstate4 == LOW)
  {
    delay(1500);
    righthandrule = 1;
    while (1) {
      btnstate1 = digitalRead(buttonPin[0]);
      btnstate2 = digitalRead(buttonPin[1]);
      btnstate3 = digitalRead(buttonPin[2]);
      btnstate4 = digitalRead(buttonPin[3]);

      if (btnstate1 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################
        goOnPathRight();
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        w = 1;

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }

      else if (btnstate2 == LOW)
      {
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }

      else if (btnstate3 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
      else if (btnstate4 == LOW)
      {
        speedTurn = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        shortest = 1;
        readShortest();
        shortestBackward();

        solveMaze();
        goToline();
        speedTurn = 0;
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################


        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
    }

  }
  else if (btnstate6 == LOW)
  {
    delay(1500);
    while (1) {
      btnstate3 = digitalRead(buttonPin[2]);
      btnstate4 = digitalRead(buttonPin[3]);
      btnstate6 = digitalRead(buttonPin[5]);
      btnstate7 = digitalRead(buttonPin[6]);
      btnstate8 = digitalRead(buttonPin[7]);

      if (btnstate3 == LOW) {
        while (1)
        {
          qtrrcF.readLine(sensorValuesF);
          for (int i = 0; i < NUM_SENSORSF ; i++ ) {
            Serial.print(sensorValuesF[i]);
            Serial.print("    ");
          }
          Serial.println();
        }
      }
      else if (btnstate4 == LOW) {
        wall3();
      }
      else if (btnstate6 == LOW) {
        alternative = 1;
        goToline();
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();
        n = 1;
        alternative = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();
        delay(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);
        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();
        goBit(150);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);
        goBit(300);
        endTask();
      }
      else if (btnstate7 == LOW) {
        goToline();
        alternative = 1;
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        alternative = 1;
        n = 1;
        solveMaze();
        goToline();
        n = 1;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY #################################################
        goOnPathRight();
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        w = 1;

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(22);
        delay(100);
        endTask();
      }
      else if (btnstate8 == LOW) {
        speedTurn = 1;
        goToline();
        alternative = 1;
        solveMaze();
        poleCount();
        delay(80);
        turnRightRandom(1050);
        //        goToline();
        goBit(500);
        aligningBotF();

        n = 1;
        alternative = 1;
        solveMaze();
        goToline();
        n = 1;
        speedTurn = 0;
        gotoLoadingBay();

        //        ################################### CHANGE THIS ON COMPETITION DAY ################################
        delay(50);
        reversePID(400);
        turnLeftRandom(1050);
        lightOn();
        delay(50);
        sensorColor();
        lightOff();
        turnLeftRandom(1050);
        stopPointSlow();
        grabBlock();
        // #####################################################################################

        delay(100);
        turnLeftRandom(1050);
        delay(50);
        goforPath();
        delay(50);
        selectPath();

        //############## CHANGE THIS ON COMPETITION DAY ########################
        goOnPathRight();
        w = 1;
        brake();

        reverseBit(100);
        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);

        servo3.write(63);
        delay(700);
        servo1.write(160);
        servo2.write(15);

        goBit(200);
        delay(100);
        wall3();
        delay(100);
        parellelBotRight();
        delay(100);

        angle(servo1, servo2, 20);
        angle2(servo1, servo2, 50);
        angle(servo1, servo2, 10);
        delay(100);
        servo3.write(20);
        delay(100);

        endTask();
      }
    }
  }

  else if (btnstate7 == LOW)
  {
    stopPointSlow();
    reversePID(194);
    delay(100);
    angle2(servo1, servo2, 50);
    angle(servo1, servo2, 5);
    aligningBotF();
    aligningBotB();
    shakeRight(10);
    shakeLeft(20);
    shakeRight(10);
    servo3.write(30);
    angleOpposite(servo1, servo2, 10);
    angle2Opposite(servo1, servo2, 50);
    servo3.write(63);
    angle2(servo1, servo2, 50);
    angle(servo1, servo2, 3);
    servo1.write(160);
    servo2.write(15);
    servo3.write(22);
  }
  else if (btnstate8 == LOW)
  {
    stopPointSlow();
    delay(50);
    reversePID(400);
    turnLeftRandom(1050);
    delay(50);
    angle(servo1, servo2, 20);
    angle2(servo1, servo2, 50);
    angle(servo1, servo2, 10);
    lightOn();
    sensorColor();
  }
}



//PID Algorithm -------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PIDFront(double Kp, double Kd, int rightBaseSpeed, int leftBaseSpeed, int rightMaxSpeed, int leftMaxSpeed ) {

  position = qtrrcF.readLine(sensorValuesF, QTR_EMITTERS_ON, 1); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  error = position - 3500;
  //Serial.println(position);
  int motorSpeed = (Kp * error + Kd * (error - lastError));
  lastError = error;

  rightMotorSpeed = rightBaseSpeed + motorSpeed;
  leftMotorSpeed = leftBaseSpeed - motorSpeed;
  //Serial.println(motorSpeed);
  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < rightMinSpeed) rightMotorSpeed = rightMinSpeed; // keep the motor speed positive
  if (leftMotorSpeed < leftMinSpeed) leftMotorSpeed = leftMinSpeed; // keep the motor speed positive
  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
  //Serial.println(rightMotorSpeed);
  //Serial.println(leftMotorSpeed);
}

void PIDReverse()
{
  position = qtrrcB.readLine(sensorValuesB, QTR_EMITTERS_ON, 1); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  error = position - 3500;
  //Serial.println(position);
  int motorSpeed = KpReverse * error + KdReverse * (error - lastError);
  lastError = error;

  int rightMotorSpeed = rightBaseSpeedReverse - motorSpeed;
  int leftMotorSpeed = leftBaseSpeedReverse + motorSpeed;
  //Serial.println(motorSpeed);

  if (rightMotorSpeed > rightMaxSpeedReverse ) rightMotorSpeed = rightMaxSpeedReverse; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeedReverse ) leftMotorSpeed = leftMaxSpeedReverse; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < rightMinSpeed) rightMotorSpeed = rightMinSpeed; // keep the motor speed positive
  if (leftMotorSpeed < leftMinSpeed) leftMotorSpeed = leftMinSpeed; // keep the motor speed positive
  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
  // Serial.println(rightMotorSpeed);
  //  Serial.println(leftMotorSpeed);
}

// Encoder PID
void encoderPID() {

  int error = leftCount - rightCount;
  int controlSpeed = 0.8 * error + 10 * (error - lastError); // + Ki*integral;
  lastError = error;

  int rightMotorSpeed = constrain((45 + controlSpeed), 0, 100);
  int leftMotorSpeed = constrain((45 - controlSpeed), 0, 100);

  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
}

// Encoder PID fast
void encoderPIDfast() {

  int error = leftCount - rightCount;
  int controlSpeed = 0.8 * error + 10 * (error - lastError); // Kp * err + Kd * (err- lst err)     + Ki*integral;
  lastError = error;

  int rightMotorSpeed = constrain((80 + controlSpeed), 0, 120);
  int leftMotorSpeed = constrain((80 - controlSpeed), 0, 120);

  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
}
