#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

struct sensor{//creating a struct to manage all six sensors
   int port;
   double value;
};

sensor SensorArray[5];//creating vector to store sensor structs



 double sensitivity = .1;//if the new value of the flex sensor is less than the sensitivity, finger will be considered stationary

void setup() {
 lcd.begin(16, 2);
 lcd.clear();//clears lcd monitor
 Serial.begin(9600);//sets up console window

for(int x  = 0; x <= 5; x++){//defining all six structs within the vector, and initializing values
  SensorArray[x] = {x, 0.00};
}
}

void loop() {
//////////////////////////////////////////////////OUTPUTTING FLEX TO FINGER MOVEMENT ON LCD/////////////////////////////////////
//+ = flex increasing (fingers curling)
//blank = flex stationary (no movement)
//- = flex decreasing (fingers straightening)
//* = error; impossible?

for(int x  = 0; x <= 5; x++){
 if(abs(SensorArray[x].value - analogRead(SensorArray[x].port)) <= sensitivity){//if change in sensor is below sensitivity, mark as stationary
  lcd.setCursor(x, 0);
  lcd.print(" ");
  lcd.setCursor(x, 1);
  lcd.print(" ");
 }
 else if (abs(SensorArray[x].value - analogRead(SensorArray[x].port)) > sensitivity){//if change in sensor is above sensitivity, determine if change is pos/neg and mark as so.
  if((SensorArray[x].value - analogRead(SensorArray[x].port)) < 0){//printed above to prevent'blur' of lcd
  lcd.setCursor(x, 0);
  lcd.print("+");
  }
  else if((SensorArray[x].value - analogRead(SensorArray[x].port)) > 0){
  lcd.setCursor(x, 1);
  lcd.print("-");
  }
  else {//covering my bases (reports possible error)
  lcd.setCursor(x, 0);
  lcd.print("*");
  lcd.setCursor(x, 1);
  lcd.print("*");
  }
 }
 else {//reporting possible error again
  lcd.setCursor(x, 0);
  lcd.print("*");
  lcd.setCursor(x, 1);
  lcd.print("*");
 }
//////////////////////////////////UPDATING VARIABLES////////////////////////////////////////////////
SensorArray[x].value = analogRead(SensorArray[x].port);//updating 'flex' magnitude to current values
}

}
