#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_LIGNES 4
#define LCD_COLONNES 20
#define freq_maj 1000 //freq mise a jour ecran

void affichage_init(LiquidCrystal_I2C &lcd);

void affichage_donnees(LiquidCrystal_I2C &lcd, double Ax,double Ay,double Az,double Gx,double Gy,double Gz,double Vz);
void affichage_statique(LiquidCrystal_I2C &lcd);
void affichage_temps(LiquidCrystal_I2C &lcd);

#endif