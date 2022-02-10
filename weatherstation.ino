#if ( !defined(ESP32) || ( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_PROS2 || ARDUINO_MICROS2 ) )
  #error This code is intended to run only on the ESP32 (no ESP32-S2 support) platform! Please check your Tools->Board setting.
#endif

#include <ArduinoOTA.h>
#include <FastLED.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <ArduinoJson.h>

// SKETCH BEGIN
AsyncWebServer webServer(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

#include "parameter.h"
#include "functions.h"
#include "cron.h"
#include "websockets.h"

#include "fastled.h"
#include "otahandle.h"
#include "wifi.h"
#include "webserver.h"

void setup(){
  // delay(3000); // 3 sekunden delay
  Serial.begin(115200);
  Serial.println(F(__DATE__ __TIME__));
  Serial.println(F("starte Filesystem"));
  
  SPIFFS.begin();
  Serial.println(F("generate new Config"));
  Serial.setDebugOutput(true);

  // starte FastLED System ----------------------------------
  setupFastLED();
  initTest();
  // --------------------------------------------------------

  // starte WiFi --------------------------------------------
  setupwifi();
  save_wifiscan();
  printFile("/wifinets.json");
  // Wifi ende ----------------------------------------------

  
  handleOTA();

  //MDNS.addService("http","tcp",80);

  
// --------------------------------
  ws.onEvent(onWsEvent);
  webServer.addHandler(&ws);

  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!",NULL,millis(),1000);
  });
  webServer.addHandler(&events);
// ------------------------------------------
  setupWeb();
}

void loop(){
  ArduinoOTA.handle();
  ws.cleanupClients();
  do_cronjobs();
}
