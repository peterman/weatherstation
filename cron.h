/*  include "cron.h"
 *  in loop() --> do_cronjobs(); 
 */
struct Cronjob{
  int cjt1=10;  long tmp1=0; //  10sek.
  int cjt2=30;  long tmp2=0; //  30sek.
  int cjt3=300; long tmp3=0; // 300sek.
};

Cronjob cronjobs;

void cron1() {
  Serial.println("Cronjob1 active.");
}
void cron2() {
  Serial.println("Cronjob2 active.");
}
void cron3() {
  Serial.println("Cronjob3 active.");
}
void do_cronjobs(){
  long tmp=millis();
  if (tmp >= (cronjobs.tmp1+(cronjobs.cjt1*1000))){
    cron1();
    cronjobs.tmp1=millis();
  }
  if (tmp >= (cronjobs.tmp2+(cronjobs.cjt2*1000))){
    cron2();
    cronjobs.tmp2=millis();
  }
  if (tmp >= (cronjobs.tmp3+(cronjobs.cjt3*1000))){
    cron3();
    cronjobs.tmp3=millis();
  }
}
