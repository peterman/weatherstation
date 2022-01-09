// dBm zu % --------------------------------------------------------------------------------------------
int dBmtoPercent(int dBm){
  int quality;
  const int RSSI_MIN = -100;
  const int RSSI_MAX = -50;
  if(dBm <= RSSI_MIN) {quality=0;}
  else if (dBm >= RSSI_MAX){quality=100;}
  else {quality = 2*(dBm+100);}
return quality;
}
// Verschlüsslung als Klartext ---------------------------------------------------------------------------
String enc_type(int type){
  switch(type){
    case WIFI_AUTH_WEP: return "WEP"; break;
    case WIFI_AUTH_WPA_PSK: return "WPA/PSK"; break;
    case WIFI_AUTH_WPA2_PSK: return "WPA2/PSK"; break;
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2/PSK"; break;
    case WIFI_AUTH_OPEN: return "Open"; break;
    default: return "Unknown"; break;
  }
}
// Scan Netzwerk nach WiFi's ---------------------------------------------------------------------------  
void save_wifiscan(){
  WiFi.scanNetworks(true);
  int count=0;
  while ((WiFi.scanComplete() <0) && (count<10)){
    delay(500);
    Serial.print(".");
  }
  Serial.println("end scanning");
  int n=WiFi.scanComplete();
  Serial.printf("%d Netzwerke gefunden \n",n);
  String json="[\n";
  if (n){
    for (int i=0; i<n; ++i){
      if (WiFi.SSID(i)==""){continue;}; 
      json+="{";
      json+="\"ssid\":\""+WiFi.SSID(i)+"\"";
      json+=",\"rssi\":\""+String(WiFi.RSSI(i))+"\"";
      json+=",\"quality\":\""+String(dBmtoPercent(WiFi.RSSI(i)))+"\"";
      json+=",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
      json+=",\"secure\":\""+enc_type(WiFi.encryptionType(i))+"\"";
      json+="}"; 
      if(i<n-1) json+=",\n";  
    }
  }
  json+="\n]";
  SPIFFS.remove(wifinets);
  File file=SPIFFS.open(wifinets,"w");
  file.println(json);
  file.close();
  json=String();
}
// Starte WiFi ---------------------------------------------------------------------------
void setupwifi(){
  
  WiFi.mode(WIFI_STA); 
  WiFi.begin(conf.sta_ssid, conf.sta_pass);
  Serial.println("\nStarte Verbindung zu SSID: \"" + String(conf.sta_ssid) +"\"");
  int timeout_counter = 0;
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
        timeout_counter++;
        if(timeout_counter >= WIFI_CONNECT_TIMEOUT*5){
          Serial.println("\nTimeout. Starte AP mit SSID: \"" + String(conf.ap_ssid) +"\"");
          WiFi.disconnect();
          WiFi.softAP(conf.ap_ssid,conf.ap_pass);
          Serial.println("\nAP läuft. ");
          Serial.print("Lokale ESP32-IP: ");
          Serial.println(WiFi.softAPIP());
          if (MDNS.begin(conf.ap_dns_name)) {
            Serial.println("DNS gestartet, erreichbar unter: ");
            Serial.println("http://" + String(conf.ap_dns_name) + ".local/");
          }
          return;
        }
  }
  Serial.println("\nVerbunden mit WiFi Netzwerk");
  Serial.print("Locale ESP32-IP: ");
  Serial.println(WiFi.localIP());
}
