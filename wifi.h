void setupwifi(){
  
  WiFi.mode(WIFI_STA); 
  WiFi.begin(sta_ssid, sta_password);
  Serial.println("\nStarte Verbindung zu SSID: \"" + String(sta_ssid) +"\"");
  int timeout_counter = 0;
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
        timeout_counter++;
        if(timeout_counter >= WIFI_CONNECT_TIMEOUT*5){
          Serial.println("\nTimeout. Starte AP mit SSID: \"" + String(ap_ssid) +"\"");
          WiFi.disconnect();
          WiFi.softAP(ap_ssid,ap_password);
          Serial.println("\nAP läuft. ");
          Serial.print("Lokale ESP32-IP: ");
          Serial.println(WiFi.softAPIP());
          if (MDNS.begin(ap_dns_name)) {
            Serial.println("DNS gestartet, erreichbar unter: ");
            Serial.println("http://" + String(ap_dns_name) + ".local/");
          }
          return;
        }
  }
  Serial.println("\nVerbunden mit WiFi Netzwerk");
  Serial.print("Locale ESP32-IP: ");
  Serial.println(WiFi.localIP());
}
