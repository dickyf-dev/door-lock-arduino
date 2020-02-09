#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#define led D0
#define led1 D8

#include <SPI.h>
#include <MFRC522.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522



  /// lcd 

 Wire.begin(D4, D3);///////////////////////////////lCD D3=SCL D4=SDA

lcd.begin(16, 2);

lcd.home();

lcd.backlight();

lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("LOADING         ");
  lcd.setCursor(0, 1);
  lcd.println("......     ");
}
void loop() 
{

  //lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      SWIPE");
  lcd.setCursor(0, 1);
  lcd.print("    YOUR CARD");
  delay(500);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

  
  if (content.substring(1) == "9B 38 F7 0D") //ID sesuai dengan kartu yang sudah di scan sebelumnya
  {
    Serial.println(" Access Granted ");
    Serial.println(" Selamat datang ");
    delay(100);
    Serial.println(" :) ");
    Serial.println();
    statuss = 1;
    digitalWrite(led, HIGH);

    

  //lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SELAMAT DATANG");
  lcd.setCursor(0, 1);
  lcd.print("    KEL-10");
  delay(5000);
  lcd.clear();
  digitalWrite(led, LOW);


    
    
  }
  
  else   {
    Serial.println(" Akses ditolak ");
    delay(300);
    digitalWrite(led, LOW);
    digitalWrite(led1, HIGH);

  //lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      MAAF");
  lcd.setCursor(0, 1);
  lcd.print("  AKSES DITOLAK");
  delay(5000);
  lcd.clear();
  digitalWrite(led1, LOW);
  }
} 
