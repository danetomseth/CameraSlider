

/*********************************************************************
Motorized Camera Slider For Timelapse
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>



//*****************
//******display prefs
#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
Adafruit_SSD1306 display(OLED_RESET);








//outputs
Servo slideServo;
int servoPin = 6;
int shutterPin = 22; //fire camera


//inputs
int limitLeft = 8; //left limit switch
int limitRight = 7; //right limit switch
int setDelay = A0; //potentiometer analog read
int selectBtn = 10; //select button


//variables
int buttonState = LOW;
int lastButtonState = LOW;
int programActive = true;
int startReady = false;
int initialized = false;
int moveSpeed = 0;

// Slider variables
int leftSpeed = 86;
int rightSpeed = 97; //moves away from servo
int direction = rightSpeed; //starts moving away from servo


//debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers







void setup()   {                
  Serial.begin(9600);
  slideServo.attach(servoPin);

  //Buttons-Inputs
  pinMode(limitLeft, INPUT);
  pinMode(selectBtn, INPUT);
  pinMode(limitRight, INPUT);
  pinMode(shutterPin, OUTPUT);

  //initialize display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  display.clearDisplay();
}



void loop() {
  //check if slide has reached end
  int pictureDelay = analogRead(setDelay);

  if(!initialized) {
    initialize();
    initialized = true;
  }
  
  

  checkEndpoints();
 
  takePicture();
    slideCamera();
}

void initialize() {
  displayText("Starting..");
  delay(1000);
  int startReady = digitalRead(selectBtn);
  while(!startReady) {
    moveSpeed = analogRead(setDelay) / 10;
    int select = digitalRead(selectBtn);
    if(select) {
      startReady = true;
    }
    else {
      displayValue("Speed", moveSpeed);
    }
  }
  displayText("Exit");
  delay(1000);
}


int checkEndpoints() {
  int left = !digitalRead(limitLeft);
  int right = !digitalRead(limitRight);
  
  if(left) {
    direction = 86;
  }

  if(right) {
    direction = 96;
//    direction = 100;
//    delay(1000);
  }
  return true;
}



void takePicture() {
  displayText("Taking Picture");
  digitalWrite(shutterPin, HIGH);
  delay(500);
  digitalWrite(shutterPin, LOW);
  delay(2000);
}


void slideCamera() {
  displayText("Moving");
  slideServo.write(direction);
  delay(100);
  slideServo.write(90); //sets speed back to zero
}


void displayText(char message[]) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(message);
  display.display();
  display.clearDisplay();
}

void displayValue(char message[], int value) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(message);
  display.println(value);
  display.display();
}












































