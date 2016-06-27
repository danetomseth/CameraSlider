/*********************************************************************
Motorized Camera Slider For Timelapse
*********************************************************************/

#include <Servo.h>



//display prefs



Servo slideServo;



//outputs
int servoPin = 6;


//inputs
int limitLeft = 8; //left limit switch
int limitRight = 7; //right limit switch
int direction = 97;


//variables







void setup()   {                
  Serial.begin(9600);
  slideServo.attach(servoPin);
  pinMode(limitLeft, INPUT);
  pinMode(limitRight, INPUT);


}



void loop() {
  //check if slide has reached end
  


  int slideStatus = checkEndpoints();
  
  if(slideStatus) {
    slideCamera();
  }
  else {
    
  }
  
}


int checkEndpoints() {
  int left = !digitalRead(limitLeft);
  int right = !digitalRead(limitRight);
  Serial.println(left);
  Serial.println(right);
  

  
  if(left) {
    direction = 87;
//    direction = 85;
//    delay(1000);
  }

  if(right) {
    direction = 96;
//    direction = 100;
//    delay(1000);
  }
  return true;
}



void takePicture() {

}

int count = 0;
void slideCamera() {
  int moveVal = direction;
  slideServo.write(moveVal);
//  delay(100);
//  slideServo.write(90); //sets speed back to zero
//  delay(20);
}


void move(int dir) {
  slideServo.write(dir);
  delay(100);
  slideServo.write(90); //sets speed back to zero
}

























