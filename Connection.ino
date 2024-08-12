void connectWifi() {
  Serial.print("Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(password);
  WiFi.begin(ssid.c_str(), password.c_str());
  //Serial.println("Connecting");
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(500);
   // Serial.print(".");
  //}
}
void getConfigFs() {
  String json = readFileStr("/config.txt");
  DeserializationError error = deserializeJson(doc, json);
  const char* ssidx =  doc["ssid"];
  const char* passx = doc["pass"];
  const char* urls = doc["url"];
  serverName = urls;
  eventTime_2_Old = doc["intv"];
  eventTime_2_Old = eventTime_2_Old * 1000;
  eventTime_2_Post = eventTime_2_Old;
  ssid = ssidx;
  String vol = readFileStr("/dataVol.txt");
  pulse2 = vol.toInt();
  pulseOld = pulse2;
  password = passx;
  Serial.println(vol);
  //Serial.println(ssid);
  //Serial.println(password);
}
