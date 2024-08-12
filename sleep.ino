void setModemSleep() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  //setCpuFrequencyMhz(40);
}

void ModemAp() {
  setCpuFrequencyMhz(240);
  Serial.println("Mode Ap");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  //WiFiServer server(80);
  
 // WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.softAP("Flow_meter","flow1234");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  //dataRequest();
  //server.begin();
}
void wakeModemSleep() {
  setCpuFrequencyMhz(240);
  WiFi.disconnect(false);
  WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);
  connectWifi();
 //while (WiFi.status() != WL_CONNECTED) {
  //  delay(500);
  // Serial.print(".");
  //}
  //Serial.println(WiFi.localIP());
}
