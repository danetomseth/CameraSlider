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




/*********************************************************************
Menu
*********************************************************************/

int mainMenu() {
  bool exitMenu = false;
  while(!exitMenu) {
    int menuA = mainItem(); // returns menu item selected
    switch(menuA) {
    case 0: //Video Selected
      //Speed menu
      //eventually rotation
      break;
    case: 1: //Time Lapse
      //Number of pictures
      //exposure
      //Time length
      break;
    case 2: //Test
      //Move motor
      //take picture
      break;
      default:
      count = 0;
      break;
    }
    exitMenu = subItem();
  }
}

int itemSelected = 0;
int buttonPressed = 0;
int count = 0;
int mainLink() {
  if(buttonPressed != select()) {
    buttonPressed = select();
    if(buttonPressed = 3) {
      return count;
    }
    count++;
    delay(200); //might have to move to not delay menu display;
  };
  switch(count) {
    case 0:
    displayLn(">Video");
    display("Time lapse");
    display("Test");
    break;
    case: 1:
    displayLn("Video");
    display(">Time lapse");
    display("Test");
    break;
    case 2:
    displayLn("Video");
    display("Time lapse");
    display(">Test");
    break;
    default:
    count = 0;
    break;
  }
}




bool select() {
  bool left = digitalRead(leftBtn);
  bool right = digitalRead(rightBtn);
  bool select = digitalRead(selectBtn);
  if(select) {
    return 3;  //return 3 if select button pressed
  }
  else if(right) {
    return 2;  // 2 if right pressed
  }
  else if(left) {
    return 1; // 1 if left pressed
  }
  else {
    return 0;
  }
}

/*********************************************************************
Slider
*********************************************************************/

void videoSpeed() {
  //either calculate or manually set

  motorSpeed = 25;
}


void pingPong() {
  bool left = digitalRead(leftBtn); // Display No
  bool right = digitalRead(rightBtn); //Display Yes
  while(!left && !right) { //while neither is true
  left = digitalRead(leftBtn); // Display No
  right = digitalRead(rightBtn); //Display Yes

}
if(left) {
  stopAtEdge = true;
}
else {
  stopAtEdge = false;
}
}






int checkEndpoints() {
  int left = !digitalRead(limitLeft);
  int right = !digitalRead(limitRight);
  if(left || right) {

    if(stopAtEdge) {
      //Kill motor;
    }
  
    if(left) {
      direction = -1; //move camera back to right
      return false;
    }

    if(right) {
      direction = 1; //move camera back to left
      return false;
    }
  }
  return true; // return true if nothing hit
}




/*********************************************************************
Camera
*********************************************************************/




















