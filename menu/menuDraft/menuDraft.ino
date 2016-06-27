// include the library code:
#include <LiquidCrystal.h>
#include <Stepper.h>

const int DEFAULT_KEY_PIN = A0; //analog input
const int DEFAULT_THRESHOLD = 5; //threshold for button reading

const int UPKEY_ARV = 144; //that's read "analogue read value"
const int DOWNKEY_ARV = 329;
const int LEFTKEY_ARV = 505;
const int RIGHTKEY_ARV = 0;
const int SELKEY_ARV = 742;
const int NOKEY_ARV = 1023;


//when using v-in
//const int UPKEY_ARV = 217; //that's read "analogue read value"
//const int DOWNKEY_ARV = 492;
//const int LEFTKEY_ARV = 753;
//const int RIGHTKEY_ARV = 0;
//const int SELKEY_ARV = 742;
//const int NOKEY_ARV = 1023;


const int UP_KEY = 1;
const int DOWN_KEY = 2;
const int RIGHT_KEY = 3;
const int LEFT_KEY = 4;
const int SELECT_KEY = 5;
const int NO_KEY = 0;


//Camera setting constants
const int TIMELAPSE = 1;
const int VIDEO = 2;


//Camera Settings
int videoDuration = 30; //default to 30 seconds


//Motor Settings
//Notes
// **** motor teeth = 10
// **** pitch = 5.08mm
// **** distance / rev = 50.8mm
// **** distance / step = 0.254 mm
// **** rev/slider = 17.7 revolutions

const int stepsPerRevolution = 200;
//Stepper slideStepper(stepsPerRevolution, 18, 17, 16, 15);
Stepper slideStepper(stepsPerRevolution, 15, 16, 17, 18);
const int ENAA = 19;
const int ENAB = 20;


// Input buttons
int btnInput = A0;
int limitLeft = 10; //motor-side limit
int limitRight = 9; //pulley limit



// Mode select
int selectedMode = 0; //set to zero when no mode selected





int keyPin = DEFAULT_KEY_PIN;
int threshold = DEFAULT_THRESHOLD;
int curInput = 1023; //default to nothing
int curKey = NO_KEY;
int prevInput = 1023;
int prevKey = 1023;

LiquidCrystal lcd(6, 8, 7, 2, 3, 4, 5);  

void setup() {
  Serial.begin(9600);

  slideStepper.setSpeed(20);


  lcd.begin(16, 2);
  lcd.print("Slide 0.9");
  delay(1000);
  lcd.clear();

  pinMode(limitLeft, INPUT);
  pinMode(limitRight, INPUT);
  pinMode(ENAA, OUTPUT);
  pinMode(ENAB, OUTPUT);
}

void loop() {
//  while(1) {
//    digitalWrite(ENAA, LOW);
//    digitalWrite(ENAB, LOW);
//    lcd.clear();
//    lcd.print("off");
//   slideStepper.step(30);
//   delay(5000);
//   digitalWrite(ENAA, HIGH);
//    digitalWrite(ENAB, HIGH);
//   lcd.clear();
//   lcd.print("on");
//   slideStepper.step(30);
//   delay(1000);
//   
//  }
//  delay(1000);
  
  findHome();
  mainMenu();

  delay(1000);
//  if(selectMode == VIDEO) {
//    takeVideo();
//  }


}


/*********************************************************************
Menu
*********************************************************************/

int mainMenu() {
  bool exitMenu = false;
  lcd.clear();
  lcd.print("Main Menu");
  delay(1000);

  //initialize with first menu item
  

  while(!exitMenu) {
    selectMode();
    selectSettings();
  }
}


void selectMode() {
  
  int menuIndex = 0;
  lcd.clear();
  lcd.print(">Time-lapse");
  lcd.setCursor(0,1);
  lcd.print(" Video");
  int localMode = TIMELAPSE;
  while(!selectedMode) {
    int key = getKey();
    if(key) {
      lcd.clear();
      lcd.home();
      if(key == DOWN_KEY) menuIndex++;
      if(key == UP_KEY) menuIndex--;

      //exit loop if selected and set mode of camera
      if(key == SELECT_KEY) {
        selectedMode = localMode;
        delay(500);
        break;
      }


      //Change to adjust for length of menu
      if(menuIndex > 1) {
        menuIndex = 0;
      }
      if(menuIndex < 0) {
        menuIndex = 1;
      }
      switch(menuIndex) {
        case 0:
        lcd.print(">Time-lapse");
        lcd.setCursor(0,1);
        lcd.print(" Video");
        localMode = TIMELAPSE;
        break;
        case 1:
        lcd.print(" Time-lapse");
        lcd.setCursor(0,1);
        lcd.print(">Video");
        localMode = VIDEO;
        break;
        default: 
        lcd.print("Default");
        break;
      }
      delay(500); //delay for key debounce
    }
  }
}

void selectSettings() {
  switch(selectedMode) {
    case TIMELAPSE:
    timelapseSettings();
    break;
    case VIDEO: 
    videoSettings();
    break;
    default:
    lcd.clear();
    lcd.print("Invalid Mode");
    delay(1000);
    break;
  }
}


void timelapseSettings() {
  int exitMenu = 0;
  int menuIndex = 0;
  int item;
  while(!exitMenu) {
    int key = getKey();
    if(key) {
      lcd.clear();
      lcd.home();
      if(key == DOWN_KEY) menuIndex++;
      if(key == UP_KEY) menuIndex--;

      //exit loop if selected and set mode of camera
      if(menuIndex > 2) {
        menuIndex = 0;
      }
      if(menuIndex < 0) {
        menuIndex = 1;
      }

      if(key == SELECT_KEY) {
        menuIndex = 10;
        break;
      }


      //Change to adjust for length of menu



      switch(menuIndex) {
        case 0:
        lcd.print(">Interval");
        //print current interval value
        lcd.setCursor(0,1);
        lcd.print(" Duration");
        item = 1;
        break;
        case 1:
        lcd.print(" Interval");
        //print current interval value
        lcd.setCursor(0,1);
        lcd.print(">Duration");
        item = 2;
        break;
        case 2: 
        lcd.print(" Duration");
        lcd.setCursor(0,1);
        lcd.print(">Exit");
        break;
        case 10: 
        if(item == 1) {
            //setInterval();
          }
          else if(item == 2) {
            //setDuration();
          }
          else exitMenu = 1;
          menuIndex = 0; 
          default: 
          lcd.print("Default");
          break;
        }
      delay(500); //delay for key debounce
    }
  }
}

void videoSettings() {
  int exitMenu = 0;
  lcd.clear();
  lcd.print("Duration: ");
  lcd.setCursor(0,1);
  lcd.print(videoDuration);
  lcd.print(" sec");

  while(1) {
    int key = getKey();
    if(key) {
      lcd.clear();
      if(key == RIGHT_KEY) videoDuration++;
      if(key == LEFT_KEY) videoDuration--;

      if(key == SELECT_KEY) {
        lcd.clear();
        lcd.print("Finished");
        delay(1000);
        break;
      }

      lcd.print("Duration: ");
      lcd.setCursor(0,1);
      lcd.print(videoDuration);
      lcd.print(" sec");

      delay(500); //delay for key debounce
    }
  }
}




int getKey() {
  prevInput = curInput;
  curInput = analogRead(btnInput);
  Serial.print("input: ");
  Serial.println(curInput);
  if (curInput == prevInput)
  {
   curKey = prevKey;
   return 0;
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

   return curKey;
 }
}




/*********************************************************************
Slider
*********************************************************************/
void findHome() {
 
 lcd.clear();
 lcd.print("Finding Home");
 Serial.println("waiting");
 enable();
 while(digitalRead(limitLeft) && digitalRead(limitRight)) {
   slideStepper.step(-1);
 }

 delay(1000);
 lcd.clear();
 lcd.print("Moving to Zero");
 while(!digitalRead(limitLeft) || !digitalRead(limitRight)) {
   slideStepper.step(100);
 }
 disable();
 lcd.clear();
 lcd.print("Calibrated");
 Serial.println("Calibrated");
 delay(1000);
}


//void findHome() {
// lcd.clear();
// lcd.print("Finding Home");
// Serial.println("waiting");
// while(digitalRead(limitLeft) && digitalRead(limitRight)) {
//   slideStepper.step(400);
//   delay(2000);
//   
// }
// 
//}




void takeVideo() {
  //17.7 rpm will take 1 min
  //0.295 rotations/sec
  int stepSpeed = 0.295 * videoDuration;
  slideStepper.setSpeed(stepSpeed);
  lcd.clear();
  lcd.print("Moving...");
  while(!digitalRead(limitLeft) && !digitalRead(limitRight)) {
    slideStepper.step(5);
    delay(100);
  }
  lcd.clear();
  lcd.print("Finished");
  delay(5000);

}


void enable() {
  digitalWrite(ENAA, HIGH);
  digitalWrite(ENAB, HIGH);
}


void disable() {
  digitalWrite(ENAA, LOW);
  digitalWrite(ENAB, LOW);
}

























