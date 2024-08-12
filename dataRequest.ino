void dataRequest() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/index", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

//char fr1[10];
//char fr2[10] ;
//char vl1[10];
//char vl2[10];

  server.on("/getData", HTTP_GET, [](AsyncWebServerRequest * request) {
    String jsonData="{\"vl1\":"+String(volume)+",\"vl2\":\""+String(vl2)+"\",\"fr1\":\""+String(flowRate)+"\",\"fr2\":\""+String(fr2)+"\",\"bat\":\""+String(bat)+"\"}";
    
    request->send(200, "application/json", jsonData);
 
  });

  //route dashboard
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/config.html", String(), false, processor);
  });


  server.on("/saveConfig", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    String JsonData = "";
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      if (p->name() == "intv") {
        JsonData += "\"" + p->name() + "\"" + ":"+ p->value().c_str() ;
      }
      else {
          JsonData += "\"" + p->name() + "\"" + ":""\"" + p->value().c_str() + "\"";
      }
      if(p->name()=="ssid"){
          ssid=p->value();
      }
      else if(p->name()=="pass"){
          password=p->value();
      }
      //else if(p->name()=="url"){
          //serverName=p->value();
      //}
      else if(p->name()=="intv"){
        Serial.println(p->value());
          eventTime_2_Post=atoi(p->value().c_str())*1000; 
          eventTime_2_Old=atoi(p->value().c_str())*1000;
      }
      if (i < (params - 1)) {
        JsonData += ",";
      }
    }
    writefile("{" + JsonData + "}");
    //Serial.println(JsonData);
    request->send(SPIFFS, "/save.html", String(), false, processor);
  });
 //  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
 // DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
 // DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    server.begin();
}
