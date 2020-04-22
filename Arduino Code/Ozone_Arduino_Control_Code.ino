#include "MQ131.h"
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // initialize LCD pins 
int relaypin = 9;

int maxO3 = 50; // maximum O3 concentration in PPM 
int minO3 = 25; // minimum O3 concentration in PPM  

void setup() {

  Serial.begin(115200);


  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(relaypin, OUTPUT);
  digitalWrite(relaypin, HIGH);   // set relay pin mode and turn  
  
  // Init the sensor
  // - Heater control on pin 2
  // - Sensor analog read on pin A0
  // - Model LOW_CONCENTRATION
  // - Load resistance RL of 10KOhms (10000 Ohms)
  MQ131.begin(8,A0, HIGH_CONCENTRATION, 10000 );  

  Serial.println("Calibration in progress...");
  lcd.print("CALIBRATING...");
  
  MQ131.setR0(25000);       // Set R0 and time To Read that you got from the calibration - To calibrate use: MQ131.calibrate();  
  MQ131.setTimeToRead(10);
  
  Serial.println("Calibration done!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CALIBRATION DONE");
  
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");

  lcd.setCursor(0, 1);
  lcd.print("R0=");
  lcd.print(MQ131.getR0());
  lcd.print(" Ohms");

  digitalWrite(relaypin, LOW);
  
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");

  delay(3000);
}

void loop() {

  
  MQ131.sample();                 // start the sampling 

  int count = 0 ;
  while (count<=100){

  Serial.println("Sampling...");
  
  lcd.clear();
  lcd.setCursor(0, 0);            // Printing the Sampling completion percentage 
  lcd.print("SAMPLING...");
  lcd.print(" ");
  lcd.print(count);
  lcd.print("%");
  count +=10 ;
  delay(1000);
    
  }
  
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPM));          //PPM
  Serial.println(" ppm");

  lcd.setCursor(0, 1);
  lcd.print("[O3]=");
  lcd.print(abs(MQ131.getO3(PPM)-45));     // Print the concentration in PPM on the LCD 
  lcd.print("PPM");

  
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPB));
  Serial.println(" ppb");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(MG_M3));
  Serial.println(" mg/m3");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(UG_M3));
  Serial.println(" ug/m3");


  delay(10000);   //  time between samples in miliseconds 
}
