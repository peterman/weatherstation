void setupwifi(){
  
  WiFi.mode(WIFI_STA); 
  WiFi.begin(sta_ssid, sta_password);
  Serial.println("\nConnecting ");
  int timeout_counter = 0;
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
        timeout_counter++;
        if(timeout_counter >= WIFI_CONNECT_TIMEOUT*5){
          ESP.restart();
        }
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
