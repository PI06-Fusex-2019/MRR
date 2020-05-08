#include "affichage.h"

void affichage_init(LiquidCrystal_I2C &lcd){
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.print("PI-06:");
    lcd.setCursor(0,1);
    lcd.print("DEMARRAGE EN COURS");
}

void affichage_donnees(LiquidCrystal_I2C &lcd, double Ax,double Ay,double Az,double Gx,double Gy,double Gz,double Vz){
    /*Affichage Acceleration*/
    lcd.setCursor(2,0);
    lcd.print(Ax);
    lcd.setCursor(2,1);
    lcd.print(Ay);
    lcd.setCursor(2,2);
    lcd.print(Az);

    /*Affichage Vitesse angulaire*/
    lcd.setCursor(12,0);
    lcd.print(Gx);
    lcd.setCursor(12,1);
    lcd.print(Gy);
    lcd.setCursor(12,2);
    lcd.print(Gz);

    /*Affichage Vitesse selon Z*/
    lcd.setCursor(12,3);
    lcd.print(Vz);
}


void affichage_statique(LiquidCrystal_I2C &lcd){
    /*Affichage Acceleration*/
    lcd.setCursor(0,0);
    lcd.write(0);
    lcd.print(":");
    lcd.setCursor(0,1);
    lcd.write(1);
    lcd.print(":");
    lcd.setCursor(0,2);
    lcd.write(2);
    lcd.print(":");

    /*Affichage Vitesse angulaire*/
    lcd.setCursor(10,0);
    lcd.write(3);
    lcd.print(":");
    lcd.setCursor(10,1);
    lcd.write(4);
    lcd.print(":");
    lcd.setCursor(10,2);
    lcd.write(5);
    lcd.print(":");

    /*Affichage Vitesse selon Z*/
    lcd.setCursor(10,3);
    lcd.write(6);
    lcd.print(":");

    /* Affichage logo SD */
    lcd.setCursor(19,0);
    lcd.write(7);
}
void affichage_temps(LiquidCrystal_I2C &lcd){
    int t = millis();
    lcd.setCursor(0,3);
    lcd.print("t:");
    //s = (millis()/1000)%60
    //min = millis()/60000
    lcd.print(t/60000);
    lcd.print(":");
    if((t/1000)%60 < 10){
        lcd.print("0");
    }
    lcd.print((t/1000)%60);
}