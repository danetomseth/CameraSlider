// include the library code:
#include <LiquidCrystal.h>

const int DEFAULT_KEY_PIN = A0; //analog input
const int DEFAULT_THRESHOLD = 5; //threshold for button reading

const int UPKEY_ARV = 144; //that's read "analogue read value"
const int DOWNKEY_ARV = 329;
const int LEFTKEY_ARV = 505;
const int RIGHTKEY_ARV = 0;
const int SELKEY_ARV = 742;
const int NOKEY_ARV = 1023;


const int UP_KEY = 1;
const int DOWN_KEY = 2;
const int RIGHT_KEY = 3;
const int LEFT_KEY = 4;
const int SELECT_KEY = 5;
const int NO_KEY = 0;


int keyPin = DEFAULT_KEY_PIN;
int threshold = DEFAULT_THRESHOLD;
int curInput = 1023; //default to nothing
int curKey = NO_KEY;
int prevInput = 1023;
int prevKey = 1023;



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7); 
int btnInput = A0;

void setup() {
  // set up the LCD's number of columns and rows:\
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0, 1);
  getKey();
}



int getKey() {
  prevInput = curInput;
  curInput = analogRead(btnInput);
  if (curInput == prevInput)
   {
     curKey = prevKey;
     lcd.print("Same key");
   }
   else
   {
     prevKey = curKey;
 
     if (curInput > UPKEY_ARV - threshold && curInput < UPKEY_ARV + threshold ) curKey = UP_KEY;
     else if (curInput > DOWNKEY_ARV - threshold && curInput < DOWNKEY_ARV + threshold ) curKey = DOWN_KEY;
     else if (curInput > RIGHTKEY_ARV - threshold && curInput < RIGHTKEY_ARV + threshold ) curKey = RIGHT_KEY;
     else if (curInput > LEFTKEY_ARV - threshold && curInput < LEFTKEY_ARV + threshold ) curKey = LEFT_KEY;
     else if (curInput > SELKEY_ARV - threshold && curInput < SELKEY_ARV + threshold ) curKey = SELECT_KEY;
     else curKey = NO_KEY;
    lcd.clear();
    lcd.setCursor(0, 1);
    findButton(curKey);
    delay(1000);
  }
}


int findButton(int btn) {
    switch(btn) {
    case NO_KEY: //Video Selected
      lcd.print("No key"); 
      break;
    case UP_KEY: //Time Lapse
      lcd.print("Up key");
      break;
    case LEFT_KEY: //Test
      lcd.print("left key");
      break;
    case RIGHT_KEY: //Video Selected
      lcd.print("right key");
      break;
    case SELECT_KEY: //Time Lapse
      lcd.print("select key");
      break;
    case DOWN_KEY: //Test
      lcd.print("down key");
      break;
    default:
      lcd.print("invalid");
      break;
    }
}
