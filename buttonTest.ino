/*********************************************************************
Motorized Camera Slider For Timelapse
*********************************************************************/




//display prefs




//variables

int left = 4;
int select = 5;
int right = 6;





void setup()   {                
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode(select, INPUT);
  pinMode(right, INPUT);

}



void loop() {
  //check if slide has reached end
  int reading = digitalRead(select);
  Serial.println(reading);
  delay(500);
}
























