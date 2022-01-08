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
      if(i) json+=",\n";
      json+="{";
      json+="\"rssi\":\""+String(WiFi.RSSI(i))+"\"";
      json+=",\"ssid\":\""+String(WiFi.SSID(i))+"\"";
      json+=",\"secure\":\""+String(enc_type(WiFi.encryptionType(i)))+"\"";
      json+="}";   
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
  WiFi.begin(configs.sta_ssid, configs.sta_pass);
  Serial.println("\nStarte Verbindung zu SSID: \"" + String(configs.sta_ssid) +"\"");
  int timeout_counter = 0;
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
        timeout_counter++;
        if(timeout_counter >= WIFI_CONNECT_TIMEOUT*5){
          Serial.println("\nTimeout. Starte AP mit SSID: \"" + String(configs.ap_ssid) +"\"");
          WiFi.disconnect();
          WiFi.softAP(configs.ap_ssid,configs.ap_pass);
          Serial.println("\nAP läuft. ");
          Serial.print("Lokale ESP32-IP: ");
          Serial.println(WiFi.softAPIP());
          if (MDNS.begin(configs.ap_dns_name)) {
            Serial.println("DNS gestartet, erreichbar unter: ");
            Serial.println("http://" + String(configs.ap_dns_name) + ".local/");
          }
          return;
        }
  }
  Serial.println("\nVerbunden mit WiFi Netzwerk");
  Serial.print("Locale ESP32-IP: ");
  Serial.println(WiFi.localIP());
}
