#include <Arduino.h>
#include "radio.h"
#include "donnees.h"

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
                    String &trame_donnees){
    if(Serial1.available()>0){
        
        if(Serial1.read() == 0x7E){
            delay(500);
            digitalWrite(13,HIGH);
            //lecture de la longueur
            longueur_msb = Serial1.read();
            Serial.println(longueur_msb, HEX);
            longueur_lsb = Serial1.read();
            Serial.println(longueur_lsb, HEX);
            //calcul de la longueur
            longueur_data = (longueur_msb * 256) + longueur_lsb;
            
            identifiant_data_old = identifiant_data; //mise a jour de l'identifiant precedent
            
            identifiant_data = Serial1.read();//lecture identifiant de données
            Serial.println(identifiant_data, HEX);

            /*Verification d'erreur : */
            //Identifiant_data est incrémenté de 0 à 7, puis repasse à 0 en temps normal
            //Si on lit qu'une valeur a été sautée, il faut le prendre en compte pour éviter un
            //décallage des données enregistrées
            if((identifiant_data_old == 6 and identifiant_data > 0 ) or (identifiant_data - identifiant_data_old != 1 and identifiant_data_old != 6)){
                //On a loupé une ou plusieurs valeurs
                
                int n_perdu = identifiant_data - identifiant_data_old;
                for(int i = 0;i<n_perdu-1;i++){
                    trame_donnees += 0xFFF;
                    trame_donnees += ";";
                }
                // cmb de valeurs ?
                //on remplit les n trous par X
            }
            else {
                Serial.println("Identifiant OK");
            }
            //lecture de la valeur
            /*
            Structure de la données reçues : 3 octets à la suite
            |octet 1 |octet 2 |octet 3 |
            |--------|--------|--------|
            |data2   |data1   |data0   |
            On lit donc chaque octet à la suite:
            */
            data2 = Serial1.read();
            data1 = Serial1.read();
            data0 = Serial1.read();
            checksum = Serial1.read();
            Serial.println(data2, HEX);
            Serial.println(data1, HEX);
            Serial.println(data0, HEX);
            data = data2<<16|data1<<8|data0;
                /* Verif checksum */
            long somme = identifiant_data + data2 + data1 + data0;
            int checksum_calculee = (0xFF - (somme & 0xFF));
            Serial.println(checksum_calculee);
            if(checksum_calculee != checksum){
                Serial.println("DONNEE CORROMPUE");
            } 
            switch (identifiant_data)
            {
            case ID_AX:
                Ax = data/SENSI_ACC;
                break;
            
            case ID_AY:
                Ay = data/SENSI_ACC;
                break;

            case ID_AZ:
                Az = data/SENSI_ACC;
                break;

            case ID_GX:
                Gx = data/SENSI_ACC;
                break;

            case ID_GY:
                Gy = data/SENSI_ACC;
                break;

            case ID_GZ:
                Gz = data/SENSI_ACC;
                break;

            case ID_VZ:
                Vz = data/SENSI_ACC;
                break;

            default:
                break;
            }
                trame_donnees += String(data/SENSI_ACC);
                trame_donnees += ";";
            /**Enregistrement des données**/
            /* if(identifiant_data == 7){
                File dataFile = SD.open("donnees_vol.txt", FILE_WRITE);

                // if the file is available, write to it:
                if (dataFile) {
                    dataFile.println(trame_donnees);
                    dataFile.close();
                    SD_etat = 1;
                }
                else {
                    SD_etat = 0;
                }
            } */
        }
    }
}