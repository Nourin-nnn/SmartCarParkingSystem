#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9


MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo Servomotor; //define servo name
int ir1 = 2;
int ir2 = 4;
int ir3 = 5;
int gled = 7;
int rled = 6;
void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Servomotor.attach(3); //servo pin
  Servomotor.write(0); //servo start position
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void loop() {

  int value1 = digitalRead(ir1);
  int value2 = digitalRead(ir2);
  int value3 = digitalRead(ir3);
  if ((value1 == 1) || (value2 == 1) || (value3 == 1))
  {
    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
  }
  else
  { digitalWrite(rled, HIGH);
    digitalWrite(gled, LOW);
  }


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
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


  if (content.substring(1) == "97 6D A8 7A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access || Blue card || slot---2");
    Serial.println();
    delay(500);


    Servomotor.write(90);
    delay(5000);
    Servomotor.write(0);

  }

  if (content.substring(1) == "E7 B2 F7 19") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access || White card || slot---3");
    Serial.println();
    delay(500);


    Servomotor.write(180);
    delay(5000);
    Servomotor.write(0);

  }
}
