#include <SD.h>
#include <PN532.h>
#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
const int chipSelect = 53;
int buzzer = 3;
int start = 4;
	#define PN532_CS 9
	#define SCK  52  
	#define MOSI 51  
	#define MISO 50
	#define SS 9

File dataWrite;
File dataRead;
PN532 nfc(PN532_CS);
#define  NFC_DEMO_DEBUG 1

char buffer[50];
char Geheugen[100];
byte server[] = { 131,180,122,144 }; 
String location = "/NFC/index.htm HTTP/1.0";
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1E, 0x4B };
IPAddress ip(131,180,92,208);
EthernetClient client;
char inString[4096]; 
int stringPos = 0;
boolean startRead; 



void setup(void) {
     Ethernet.begin(mac, ip);
  pinMode(buzzer, OUTPUT);
  pinMode(53, OUTPUT);
  pinMode(4, OUTPUT);
   Serial.begin(9600);
   Serial.println("Bradley But");
   Serial.println("No arduinos were euthanised during development of this product");
   SPI.setDataMode(SPI_MODE1);
   
   
      #ifdef NFC_DEMO_DEBUG
      Serial.print("Initializing SD card...");
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      delay(30);
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      delay(30);
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      
      
        #endif
        pinMode(10, OUTPUT);
        
            if (!SD.begin(4)) {
            #ifdef NFC_DEMO_DEBUG
            Serial.println("Card failed, or not present");

              #endif
              return;
              }
  Serial.println("card initialized.");
  //++++++++++++++++++++++++++++++++++++++++++++++-- SD bestand openen--++++++
   dataWrite = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (dataWrite)
  {
    Serial.print("Writing to datalog.txt...");
    dataWrite.println("Reboot");
	// close the file:
    dataWrite.close();
    Serial.println("done.");
    
    
          } else {
           // if the file didn't open, print an error:
           Serial.println("error opening test.txt");
           //++++++++++++++++++++++++++++++++++++++++++++++-- SD bestand openen--++++++
  }
   
#ifdef NFC_DEMO_DEBUG
  Serial.println("Hello!");
#endif
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
#ifdef NFC_DEMO_DEBUG  
  if (! versiondata)
    Serial.print("Didn't find PN53x board");
#endif
  
#ifdef NFC_DEMO_DEBUG
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
#endif
  nfc.SAMConfig();
  dataWrite = SD.open("datalog.txt", FILE_WRITE);
  if(!dataWrite)
#ifdef NFC_DEMO_DEBUG
    Serial.println("Couldn't open datafile on sd card"); 
#endif
}

void loop(void) {
    nfc.begin();
    SD.begin(4);
  uint32_t id;
  //++++++++++++++++++++++++++++++++++--zoeken naar de nfc--++++++++++++++++++++++
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
     dataWrite = SD.open("datalog.txt", FILE_WRITE);
     Geheugen = SD.open("datalog.txt", FILE_READ);
     


    if (id != 0 && id == Geheugen)
    
    digitalWrite(start, HIGH);
    }
    
    else if ( id != 0 && != Geheugen)
    {
      Serial.println("Updating");
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      delay(30);
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      delay(30);
      analogWrite(buzzer, 20);
      delay(70);
      analogWrite(buzzer, 0);
      
        String pageValue = connectAndRead(); 
        Serial.println(pageValue); 
        delay(5000); 

          String connectAndRead(){
      
            Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();
    return readPage();

  }else{
    return "connection failed";
  }

}

String readPage(){


  stringPos = 0;
  memset( &inString, 0, 4096 ); 

  while(true){

    if (client.available()) {
      char c = client.read();

      if (c == '[' ) { 
        startRead = true;
       
      }
      else if(startRead)
      {
          if(c != ']')
          {
          inString[stringPos] = c;
          //stringPos ++;
          Serial.print(inString);
          }
            else
            {
        
          client.flush();
          Serial.println("disconnecting.");
          return inString;

        }

      }
    }

  }

}

    
    
    
    





