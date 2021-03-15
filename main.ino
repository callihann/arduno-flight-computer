#include <SPI.h>
#include <SD.h>
File writeFile;
int letter;

void GenTxt() {
  int generated=0;
while (generated<6)
{
   byte randomValue = random(0, 26);
   char letter = randomValue + 'a';
   if(randomValue > 26)
      letter = (randomValue - 26) ;
      Serial.print(letter);
      generated ++;
      
}}

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
  if (SD.exists("example.txt")) {
    Serial.print("example.txt exists.");
  } else {
    Serial.print("example.txt doesn't exist.");
  }
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
