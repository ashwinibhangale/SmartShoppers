/*
  Hello World.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <Wire.h>
#include "rgb_lcd.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

rgb_lcd lcd;
byte b1;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
char a;
int i=0;
int j=0;
int state=0,state1=0;
String tot="";
void setup() 
{
   SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
      for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    //lcd.print("hello, world!");
Serial.begin(9600);
    delay(1000);
}

void loop() 
{
 

  

  
  if(Serial.available()>0)
  {
    
    
    // b1=Serial.read();
     /*if(Serial.read()=='s')
     {
         a="ant";
     }*/
     a=Serial.read();
     if(a=='>' && state==0 && state1==0)
     {
      //lcd.print("hello");
     // lcd.clear();
      state=1;
      i+=1;
     }
     if(a!='<' && state==1)
     {
      
      tot+=a;
      state1=1;
     }
     if(a=='<' && state==1 && state1==1)
     {
    //  lcd.print("dsfd");
      while(j<6)
      {
      String test="";
      while(tot[i]!=',')
      {
       test+=tot[i];
       i+=1;        
      }
      //lcd.print(tot[0]);

      i+=1;
      if(j==0)
      {
      lcd.setCursor(0, 0); //column,row
      lcd.print(String(test));

      test="";
     }

      if(j==1)
      {
      lcd.setCursor(5, 0); //column,row
      lcd.print(String(test));
      test="";
     }
     if(j==2)
     {
       lcd.setCursor(12, 0); //column,row
      lcd.print(String(test));
      test="";
     }

     if(j==3)
      {
      lcd.setCursor(0, 1); //column,row
      lcd.print(String(test));
      test="";
     }

      if(j==4)
      {
      lcd.setCursor(7, 1); //column,row
      lcd.print(String(test));
      test="";
     }
     if(j==5)
     {
       lcd.setCursor(12, 1); //column,row
      lcd.print(String(test));
      test="";
     }
     
     
     j+=1;
     }
     state=0;
     state1=0;
     i=0;
     j=0;
     tot="";
     }
   /* if(a=='.' && state==1 && state1==0)
    {
      state==0;
      state1=1; 
    }*/
     //lcd.setCursor(0, 0); //column,row
   //lcd.print("A");
/*if(state==1 && state1==0)
{
  if(a!=',')
  {
    tot+=a;
   // lcd.print(String(tot));
  }
  else if(a=='7')
  {
  lcd.setCursor(0, 1);  

   //lcd.print(String(tot));
   state=2;
  }
  else
  {
   lcd.setCursor(0, 0); //column,row
   lcd.print(String(tot));
   tot="";
   //lcd.setCursor(0, 1);  
    
  }*/
  
 
  //}
  }

if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
  //  Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();


  
    delay(5);
}


void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < 1; i++) {
   // Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    
     lcd.setRGB(0, 255, 0);
     delay(800);
     lcd.setRGB(255,0,0);


  }
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
