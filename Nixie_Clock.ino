



#include <WiFi.h>
          const char * ssid="@@@@@@@@@@@@";
          const char * wifipw="##########";

#include "time.h"
          int dizHeure, uniHeure, dizMinute, uniMinute, dizDate, uniDate;
          int timeCall = 1000;
          int lastTimeCall;
         bool dotFlag = false;
         bool firstCall = true;
          int timeDay, timeMois; 
       String jour[8]  = { "", "lun", "mar", "mer", "jeu", "ven", "sam", "dim" };
       String mois[13]  = { "", "jan", "fev", "mar", "avr", "mai", "jun", "jui", "aou", "sep", "oct", "nov", "dec" };


#include <SPI.h>
#include <TFT_eSPI.h>
          TFT_eSPI tft = TFT_eSPI();
#define   TFT_LED 33

#define   FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h"

#include <TJpg_Decoder.h>
          uint16_t w = 0, h = 0;
          int x, y = 0;
          bool tft_output (int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
                           if (y >= tft.height() ) return 0;
                               tft.pushImage(x, y, w, h, bitmap);
                               return 1;    
                          }
     String icone;


void icone_display() {

     TJpgDec.getFsJpgSize(&w, &h, "/" + icone + ".jpg");
     TJpgDec.drawFsJpg(x, y, "/" + icone + ".jpg");
  
}


void setTimezone(String timezone) {
  
     Serial.printf("Choix de la 'TimeZone'  %s\n",timezone.c_str());
     setenv("TZ",timezone.c_str(),1);
     tzset();
     
}


void initTime(String timezone) {
  
     struct tm timeinfo;
     Serial.println("Acquisition de l'heure avec serveur NTP");
     configTime(0, 0, "pool.ntp.org");
     if (!getLocalTime(&timeinfo)) {
         Serial.println("Echec acquisition heure");
         return;
        }
     Serial.println("Heure acquise sur serveur NTP");     
     setTimezone(timezone);
     
}


void setTime(int yr, int month, int mday, int hr, int minute, int sec, int isDst) {
  
     struct tm tm;
            tm.tm_year = yr - 1900;
            tm.tm_mon = month-1;
            tm.tm_mday = mday;
            tm.tm_hour = hr;
            tm.tm_min = minute;
            tm.tm_sec = sec;
            tm.tm_isdst = isDst;
            time_t t = mktime(&tm);
            Serial.printf("Mise à l'heure: %s", asctime(&tm));

     struct timeval now = { .tv_sec = t };
     settimeofday(&now, NULL);
     
}


void printLocalTime() {
 
     struct tm timeinfo;
     if (!getLocalTime(&timeinfo)) {
         Serial.println("Echec acquisition heure");
         return;
        }
     char timeHour[3];
     strftime(timeHour,3, "%H", &timeinfo);
     String heures = timeHour;
     dizHeure = heures.substring(0, 1).toInt();
     uniHeure = heures.substring(1, 2).toInt();          

     char timeMinute[3];
     strftime(timeMinute,3, "%M", &timeinfo);
     String minutes = timeMinute;
     dizMinute = minutes.substring(0, 1).toInt();
     uniMinute = minutes.substring(1, 2).toInt();

     char timeInfoDay[2];
     strftime(timeInfoDay,2, "%u", &timeinfo);    
     timeDay = String(timeInfoDay).toInt();     

     char timeInfoJour[3];
     strftime(timeInfoJour,3, "%e", &timeinfo);    
     String date = timeInfoJour;    
     dizDate = date.substring(0, 1).toInt();
     uniDate = date.substring(1, 2).toInt();

     char timeInfoMois[3];
     strftime(timeInfoMois,3, "%m", &timeinfo);     
     timeMois = String(timeInfoMois).toInt();     

}


void startWifi() {
 
     WiFi.begin(ssid, wifipw);
     Serial.println("Connecting Wifi");
     while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(500);
           }
     Serial.print("Wifi RSSI=");
     Serial.println(WiFi.RSSI());
     Serial.println();
     
}


void setup() {

     Serial.begin(115200); Serial.println();

     startWifi();
     initTime("CET-1CEST,M3.5.0,M10.5.0/3");
     WiFi.disconnect();
          
     tft.init();
     tft.setRotation(3);
     pinMode(TFT_LED, OUTPUT);
     digitalWrite(TFT_LED, HIGH);
     tft.fillScreen(TFT_BLACK);

     if (!SPIFFS.begin()) {
         Serial.println("Erreur SPIFFS");
         while (1) yield();
     }

     tft.setSwapBytes(true);
     TJpgDec.setJpgScale(1);
     TJpgDec.setCallback(tft_output);     

     icone = "nixievierge"; x = 1; y = 1; icone_display();

}


void loop() {

     if (((millis() - lastTimeCall) > timeCall) || firstCall == true) {
         lastTimeCall = millis(); firstCall = false;
         if (dotFlag == true) {  
             x = 233; y = 146; icone = "dot"; icone_display(); dotFlag = false;
            } else {
             x = 232; y = 146; icone = "nodot"; icone_display(); dotFlag = true;

             printLocalTime();

             icone = jour[timeDay]; x = 70; y = 15; icone_display();

             if (dizDate != 0) {
                 icone = "p" + String(dizDate);
                } else {
                 icone = "vide"; 
                }
             x = 210; y = 15; icone_display();
             icone = "p" + String(uniDate); x = 240; y = 15; icone_display();

             icone = mois[timeMois]; x = 325; y = 15; icone_display(); 
     
             if (dizHeure != 0) {
                 icone = String(dizHeure);
                } else {
                 icone = "blank"; 
                }
             x = 31; y = 103; icone_display();
     
             icone = String(uniHeure);
             x = 131; y = 101; icone_display();
          
             icone = String(dizMinute);
             x = 288; y = 105; icone_display();     
     
             icone = String(uniMinute);
             x = 388; y = 101; icone_display();
            }
        }     
   
}
//
//
