void goShortest() {
  goBit(250);
  findDirection(turns.charAt(0));
}


void shortPath() {
  index = turns.length();
  index--;
  if (turns.charAt(index - 1) == 'U') {
    switch (turns.charAt(index - 2)) {
      case 'L' :
        switch (turns.charAt(index)) {
          case 'L' :
            turns.remove(index - 2);
            turns = turns + 'S';
            break;

          case 'R' :
            turns.remove(index - 2);
            turns = turns + 'U';
            break;

          case 'S' :
            turns.remove(index - 2);
            turns = turns + 'R';
            break;
        }
        break;


      case 'S' :
        switch (turns.charAt(index)) {
          case 'L' :
            turns.remove(index - 2);
            turns = turns + 'R';
            break;

          case 'S' :
            turns.remove(index - 2);
            turns = turns + 'U';
            break;

          case 'R' :
            turns.remove(index - 2);
            turns = turns + 'L';
            break;

        }
        break;

      case 'R' :
        switch (turns.charAt(index)) {
          case 'L' :
            turns.remove(index - 2);
            turns = turns + 'U';
            break;

          case 'R' :
            turns.remove(index - 2);
            turns = turns + 'S';
            break;

          case 'S' :
            turns.remove(index - 2);
            turns = turns + 'L';
            break;
        }
        break;

    }
  }

}


void saveShortest() {
  EEPROM.write(0, turns.length());
  for (int i = 0; i < turns.length() ; i++)
  {
    EEPROM.write(i + 1, turns.charAt(i));
  }
}

void readShortest() {
  turns ="";
  for (int i = 0; i < EEPROM.read(0) ; i++)
  {
    byte x = EEPROM.read(i + 1);
    turns = turns + char(x);
  }
}

void shortestBackward() {
  index = turns.length();
  index--;
  turns.remove(index);
  for (int i = turns.length() - 1; i >= 0; --i)
  {
    switch (turns.charAt(i)) {
      case 'R' : inverseTurns = inverseTurns + 'L'; break;
      case 'L' : inverseTurns = inverseTurns + 'R'; break;
      case 'S' : inverseTurns = inverseTurns + 'S'; break;
      default : break;
    }
  }
  inverseTurns = inverseTurns +'E';
  turns = inverseTurns;
}
  void findDirection(char direct) {
    switch (direct) {
      case 'L':
        turnLeftRandom(525);
        break;

      case 'R' :
        turnRightRandom(525);
        break;

      case 'S' :
        break;

      case 'E' :
        brake();
        shortest=0;
        n=0;
        break;
    }
    turns = turns.substring(1);
  }

