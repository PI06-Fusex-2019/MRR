#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include "affichage.h"
#include "donnees.h"
#include "test_serial.h"
#include "radio.h"

//============== Illustrations LCD
byte Ax_logo[] = {
    B01000,
    B10100,
    B11100,
    B10100,
    B00000,
    B00101,
    B00010,
    B00101
    };
byte Ay_logo[] = {
    B01000,
    B10100,
    B11100,
    B10100,
    B00000,
    B00101,
    B00010,
    B00010
    };
byte Az_logo[] = {
    B01000,
    B10100,
    B11100,
    B10100,
    B01111,
    B00010,
    B00100,
    B01111
    };
byte Gx_logo[] = {
    B01100,
    B10000,
    B10110,
    B01100,
    B00000,
    B00101,
    B00010,
    B00101
    };
byte Gy_logo[] = {
    B01100,
    B10000,
    B10110,
    B01100,
    B00000,
    B00101,
    B00010,
    B00010
    };
byte Gz_logo[] = {
    B01100,
    B10000,
    B10110,
    B01100,
    B01111,
    B00010,
    B00100,
    B01111
    };
byte Vz_logo[] = {
    B10100,
    B10100,
    B10100,
    B01000,
    B01111,
    B00010,
    B00100,
    B01111
    };

byte SD_logo[] = {
    B11110,
    B11110,
    B11111,
    B11111,
    B11110,
    B11111,
    B11111,
    B00000
    };

//==============

LiquidCrystal_I2C lcd(LCD_ADDR,LCD_COLONNES,LCD_LIGNES);

//Variables de reception des mesures
int msg;
int longueur_msb;
int longueur_lsb;
int longueur_data;
int identifiant_data_old = 5;
int identifiant_data = 6;
byte data2;
byte data1;
byte data0;
double data;
double Ax;
double Ay;
double Az;
double Gx;
double Gy;
double Gz;
double Vz;
int checksum;
String trame_donnees;

//Variables temporelles
int instant = 0;

//---=== DEBUG ===---
int DEBUG = 1;
int debug_msg = 0;
int debug2 = 0;


void setup() {
  //---===INITIALISATION LED D'ETAT===---
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  //---===INITIALISATION ECRAN LCD===---
  affichage_init(lcd);
  lcd.createChar(0, Ax_logo);
  lcd.createChar(1, Ay_logo);
  lcd.createChar(2, Az_logo);

  lcd.createChar(3, Gx_logo);
  lcd.createChar(4, Gy_logo);
  lcd.createChar(5, Gz_logo);

  lcd.createChar(6, Vz_logo);
  lcd.createChar(7, SD_logo);

  digitalWrite(13, LOW);

  //---=== INITIALISATION UART ===---
  Serial.begin(9600);
  while(!Serial and DEBUG == 1){}
  SERIAL_XBEE.begin(9600);
  SERIAL_DEBUG.begin(9600);
}

void loop() {
  
  // ACTUALISATION DONNEES ECRAN
  if(millis()-instant > freq_maj){
    instant = millis();
    lcd.clear();
    affichage_statique(lcd);
    affichage_temps(lcd);
    affichage_donnees(lcd,Ax,Ay,Az,Gx,Gy,Gz,Vz);
    Serial.println(trame_donnees);
  }

  reception_radio(msg,longueur_msb,longueur_lsb,longueur_data,identifiant_data_old,identifiant_data,data2,data1,data0,data,Ax,Ay,Az,Gx,Gy,Gz,Vz,checksum,trame_donnees);






  //DEBUG
  if(DEBUG == 1){
    envoi_trame_test(debug_msg, 5000);
    if(millis()>7000 and debug2 == 0){
      debug2 = 1;
      Serial3.write(0x7E);//indicateur debut trame

      Serial3.write(0x00); //longueur msb
      Serial3.write(0x04); //longueur lsb

      Serial3.write(0x03); //identifiant
      Serial3.write(0x00); //data 2
      Serial3.write(0xFF); //data 1
      Serial3.write(0xFF); //data 0
      long somme = 0x03 + 0x00 + 0xFF + 0xFF;
      int checksum = (0xFF - (somme & 0xFF));
      Serial3.write(checksum); //checksum
    }
    /* if(SERIAL_XBEE.available()>0){
      digitalWrite(13, HIGH);
      Serial.print(SERIAL_XBEE.read(), HEX);
    } */
  }

}