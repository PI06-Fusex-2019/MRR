#ifndef RADIO_H
#define RADIO_H
#include <Arduino.h>
void reception_radio(int &msg,
                    int &longueur_msb,
                    int &longueur_lsb,
                    int &longueur_data,
                    int &identifiant_data_old,
                    int &identifiant_data ,
                    byte &data2,
                    byte &data1,
                    byte &data0,
                    double &data,
                    double &Ax,
                    double &Ay,
                    double &Az,
                    double &Gx,
                    double &Gy,
                    double &Gz,
                    double &Vz,
                    int &checksum,
                    String &trame_donnees);

#endif