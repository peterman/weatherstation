// print file to Serial
void printFile(const char *filename){
  File file=SPIFFS.open(filename,"r");
  while (file.available()){
    Serial.print((char)file.read());
  }
  file.close();
}
