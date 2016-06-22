/*********************************************************************
Motorized Camera Slider For Timelapse
*********************************************************************/

#include <Servo.h>



//display prefs



Servo slideServo;



//outputs
int servoPin = 9;


//inputs
int limitLeft = 10; //left limit switch
int limitRight = 11; //right limit switch
int direction = 1; // '1' is right and '-1' is left;


//variables







void setup()   {                
  Serial.begin(9600);
  slideServo.attach(servoPin);
  pinMode(limitLeft, INPUT);
  pinMode(limitRight, INPUT);


}



void loop() {
  //check if slide has reached end
  

  if(left || right) {
    
  }


  int slideStatus = checkEndpoints();

  if(slideStatus) {
    slideCamera();
  }
  else {
    Serial.println('Pausing...');
  }
  
}


int checkEndpoints() {
  int left = digitalRead(limitLeft);
  int right = digitalRead(limitRight);

  if(left || right) {
    Serial.println('End Reached');
    direction = direction * -1;
    return false;
  }
  else {
    return true;
  }
}



void takePicture() {

}


void slideCamera() {
  int moveVal = 90 + (direction * 5);
  slideServo.write(moveVal);
  delay(100);
  slideServo.write(90); //sets speed back to zero
}

























