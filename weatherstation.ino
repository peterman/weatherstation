#include <ArduinoOTA.h>
#include <FastLED.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <EEPROM.h>

// SKETCH BEGIN
AsyncWebServer webServer(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

#include "functions.h"
#include "websockets.h"
#include "parameter.h"
#include "secrets.h"
#include "fastled.h"
#include "otahandle.h"
#include "webserver.h"

void setup(){
  // delay(3000); // 3 sekunden delay
  Serial.begin(115200);
  Serial.println(F(__DATE__ __TIME__));
  Serial.println(F("starte Filesystem"));
  
  SPIFFS.begin();
  Serial.println(F("generate new Config"));
  Serial.setDebugOutput(true);

  setupFastLED();
  initTest();
  
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(hostName);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    delay(1000);
    WiFi.begin(ssid, password);
  }

  handleOTA();

  MDNS.addService("http","tcp",80);

  setupWeb();
// --------------------------------
  ws.onEvent(onWsEvent);
  webServer.addHandler(&ws);

  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!",NULL,millis(),1000);
  });
  webServer.addHandler(&events);
// ------------------------------------------
}

void loop(){
  ArduinoOTA.handle();
  ws.cleanupClients();
}
