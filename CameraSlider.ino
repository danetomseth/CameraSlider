/*********************************************************************
Motorized Camera Slider For Timelapse
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>



//display prefs
#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
Adafruit_SSD1306 display(OLED_RESET);


Servo slideServo;



//outputs
int shutterPin = 22; //fire camera
int servoPin = 21;


//inputs
int setDelay = A0; //potentiometer analog read
int selectBtn = 10; //select button
int moveBtn = 11; //move display cursor
int limitLeft = 12; //left limit switch
int limitRight = 13; //right limit switch
char direction = 1; // '1' is right and '-1' is left;


//variables
int buttonState = LOW;
int lastButtonState = LOW;
int pictureCount = 0;





long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup()   {                
  Serial.begin(9600);
  slideServo.attach(servoPin);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  display.clearDisplay();


  pinMode(selectBtn, INPUT);
  pinMode(limitLeft, INPUT);
  pinMode(limitRight, INPUT);
  pinMode(shutterPin, OUTPUT);




}



void loop() {
  //check if slide has reached end
  int left = digitalRead(limitLeft);
  int right = digitalRead(limitRight);

  if(left || right) {
    direction = direction * -1;
  }
  

  int buttonState = digitalRead(selectBtn);
  int pictureDelay = analogRead(setDelay);




  if(buttonState == HIGH) {
    Serial.println("Button Pressed");
    displayText(pictureDelay, "Pressed");
    if(pictureDelay > 800) {
      digitalWrite(shutterPin, HIGH);
    }
  }
  else {
    displayText(0, "Stndby");
    digitalWrite(shutterPin, LOW);
  }
}


void displayText(int picDelay, char message[]) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(message);
  display.println(picDelay);
  display.display();
  delay(1000);
  display.clearDisplay();
}


void takePicture() {

}


void slideCamera() {
  int moveVal = 90 + (direction * 5);
  slideServo.write(moveVal);
  delay(100);
  slideServo.write(90); //sets speed back to zero
}


void rotateCamera() {

}



void debounce(int reading) {
    if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
//        ledState = !ledState;
      }
    }
  }
}


















