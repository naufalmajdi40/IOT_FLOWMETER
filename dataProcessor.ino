// Replaces placeholder with LED state value
String processor(const String& var) {
  Serial.println(var);
  //  if (var == "STATE") {
  //    if (digitalRead(ledPin)) {
  //      ledState = "X";
  //    }
  //    else {
  //      ledState = "Y";
  //    }
  //    Serial.print(ledState);
  //    return ledState;
  //  }
  if (var == "config") {
    String SSIDwf="NEURIXII";
    
    String PASSwf="#neurix123#";
    //Serial.println(ssid);
    //Serial.println(password);
    String intv =String(eventTime_2_Post/1000);
    String url = serverName;
    String form = "<label for=\"ssid\">SSID</label>";
    form += "<input type=\"text\" id=\"ssid\" name=\"ssid\" placeholder=\"SSID\" value=\""+ssid+"\">";
    form += "<label for=\"pass\">PASS</label>";
    form += "<input type=\"password\" id=\"pass\" name=\"pass\" value=\""+password+"\">";
    form += "<label for=\"pass\">URL</label>";
    form += "<input type=\"text\" id=\"url\" name=\"url\" value=\""+url+"\">";
    form += "<label for=\"intv\">Sending Interval(Second)</label>";
    form += "<input type=\"number\" id=\"intv\" name=\"intv\" value=\""+intv+"\">";

    return form;
  }
  return String();
}
