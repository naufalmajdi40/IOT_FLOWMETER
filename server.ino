void postServer() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
     char svr[] = "www.hareti.co.uk";
    if (client.connect(svr, 80)) {
      Serial.println("Connected!");
      // Make a HTTP request:
      client.println("GET /get HTTP/1.1");
      client.println("Host: httpbin.org");
      client.println("Connection: close");
      client.println();
    }
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
