//------------------------- Pixy CAM detecting color ---------------------------------------

void sensorColor()
{
  while (true)
  {
    lightOn();
    static int i = 0;
    int j;
    uint16_t blocks;
    char buf[32];

    // grab blocks!
    blocks = pixy.getBlocks();
    unsigned int max_width = 0;
    byte buffer_signature;

    // If there are detect blocks, print them!
    if (blocks)
    {
      i++;
      // do this (print) every 60 frames because printing every
      // frame would bog down the Arduino
      if (i % 60 == 0)
      {
        sprintf(buf, "Detected %d:\n", blocks);
        Serial.print(buf);
        for (j = 0; j < blocks; j++)
        {
          sprintf(buf, "  block %d:", j);
          Serial.print(buf);
          pixy.blocks[j].print();
          {
            if (pixy.blocks[j].y < 60)
            {
              if (pixy.blocks[j].width > max_width)
              {
                max_width = pixy.blocks[j].width;
                buffer_signature = pixy.blocks[j].signature;// 1-red,3-green,2-blue
              }
              Serial.println("up....");
              if (pixy.blocks[j].signature == 1)
              { Serial.println("red");
                up = 'R';
              }
              else if (pixy.blocks[j].signature == 2)
              { Serial.println("blue");
                up = 'B';
              }
              else
              { Serial.println("green");
                up = 'G';
              }
            }
            else if (pixy.blocks[j].y < 150)
            {
              if (pixy.blocks[j].width > max_width)
              {
                max_width = pixy.blocks[j].width;
                buffer_signature = pixy.blocks[j].signature;
              }

              Serial.println("middle... ");
              if (pixy.blocks[j].signature == 1)
              { Serial.println("red");
                middle = 'R';
              }
              else if (pixy.blocks[j].signature == 2)
              { Serial.println("blue");
                middle = 'B';
              }
              else
              { Serial.println("green");
                middle = 'G';
              }
            }
            else
            {
              if (pixy.blocks[j].width > max_width)
              {
                max_width = pixy.blocks[j].width;
                buffer_signature = pixy.blocks[j].signature;
              }

              Serial.println("bottom.....");
              if (pixy.blocks[j].signature == 1)
              { Serial.println("red");
                bottom = 'R';
              }
              else if (pixy.blocks[j].signature == 2)
              { Serial.println("blue");
                bottom = 'B';
              }
              else
              { Serial.println("green");
                bottom = 'G';
              }
            }
          }
        }
        break;
      }
    }
  }
}


void grabBlock() {
  if (color == up) {
    angleIncrease(servo2, 50);
    angleDecrease(servo1, 148);
    angleIncrease(servo2, 65);
    servo3.write(63);
    delay(700);
    servo1.write(160);
    servo2.write(15);
  }
  else if (color == middle) {
    angleIncrease(servo2, 50);
    angleDecrease(servo1, 140);
    angleIncrease(servo2, 60);
    angleDecrease(servo1, 120);
    angleIncrease(servo2, 90);
    servo3.write(63);
    delay(700);
    servo1.write(160);
    servo2.write(15);
  }
  else {
    angle(servo1, servo2, 20);
    angle2(servo1, servo2, 50);
    angle(servo1, servo2, 10);

    servo3.write(63);
    delay(700);
    servo1.write(160);
    servo2.write(15);
  }
}


void gotoLoadingBay() {
  int speedMvc = 1;
  while (n == 1) {
    qtrReadF();
    hunterRead();
    if (speedMvc ==0) {
      stopPointSlow();
      n = 0;
    }
    else if (dvalF[5] == 0 && dvalF[7] == 0 && hunterL == 0) {
      brake();
      goBit(250);
      turnLeftRandom(525);
      speedMvc = 0;
    }
    else if (dvalF[0] == 0 && dvalF[2] == 0 && hunterR == 0) {
      brake();
      goBit(250);
      turnRightRandom(525);
      loadingSide = 1;
      speedMvc = 0;
    }
    else {
      PIDFront(KpSlow, KdSlow, rightBaseSpeedSlow, leftBaseSpeedSlow, rightMaxSpeedSlow, leftMaxSpeedSlow);
      forward();
    }
  }
}

