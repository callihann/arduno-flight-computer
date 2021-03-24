#include <SPI.h>
#include <SD.h>
File writeFile;


String genTxt(int randomWordLength) { 

   char generated[randomWordLength];  // creates a char array  (aka string) of length passed in
 
   for(int i = 0; i < randomWordLength; i++) 
   { 
    int randomValue = random(0, 26);   // random int between 0 and 25
    generated[i] = randomValue + 'a';    // adding a is like adding 97 to the number from 0 to 25 to shift to match the ASCII table
   }

   return generated;
}

const int chipSelect = 10;

void setup() {
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  pinMode(2, INPUT_PULLUP);
  if (SD.exists("example.txt")) {
    Serial.print("example.txt exists.");
  } else {
    Serial.print("example.txt doesn't exist.");
  }
  Serial.println("Creating example.txt...");
  writeFile = SD.open("example.txt", FILE_WRITE);
}
void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = digitalRead(2);
  if (sensorVal == HIGH) {
    Serial.print("Low");
    writeFile.close();
    delay(10000);
  } else {
    Serial.print("High\n"); 
    GenTxt(); 
    writeFile.println(letter);
    delay(500); 
  }
}
