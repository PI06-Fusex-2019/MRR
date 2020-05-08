#include "test_serial.h"
#include <Arduino.h>

void envoi_trame_test(int &debug, int delay){
    if(millis()>delay and debug == 0){
            debug = 1;
            Serial3.write(0x7E);//indicateur debut trame

            Serial3.write(0x00); //longueur msb
            Serial3.write(0x04); //longueur lsb

            Serial3.write(0x00); //identifiant
            Serial3.write(0x00); //data 2
            Serial3.write(0xFF); //data 1
            Serial3.write(0xFF); //data 0
            long somme = 0x00 + 0x00 + 0xFF + 0xFF;
            int checksum = (0xFF - (somme & 0xFF));
            Serial3.write(checksum); //checksum
        }
}