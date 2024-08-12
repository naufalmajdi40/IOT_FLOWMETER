void tampilOled() {
  dtostrf(flowRate, 6, 6, fr1);
  dtostrf(volume, 6, 6, vl1);
  dtostrf(flowRate2, 6, 6, fr2);
  dtostrf(volume2, 6, 4, vl2);

  // bootVol=(string)vl2;
  //dtostrf(bootvol, 6, 6, vl2);

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);           //Instruksi mengatur ukuran karakter
  display.setCursor(0, 0);         //Karakter dumulai dari kolom 32 baris 1
  display.print("Vol(m3) :");
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print(vl2);

  display.setTextSize(1);           //Instruksi mengatur ukuran karakter
  display.setCursor(0, 30);         //Karakter dumulai dari kolom 32 baris 1
  display.print("Rate(m3/h):");
  display.setCursor(60, 30);
  display.setTextSize(1);
  display.print(fr2);

  display.setTextSize(1);           //Instruksi mengatur ukuran karakter
  display.setCursor(0, 40);         //Karakter dumulai dari kolom 32 baris 1
  display.print("Rate(l/m):");
  display.setCursor(60, 40);
  display.setTextSize(1);
  display.print(String(flowRate));

  display.display();
}

void sendWifiOled() {
  display.setTextSize(1);           //Instruksi mengatur ukuran karakter
  display.setCursor(0, 50);         //Karakter dumulai dari kolom 32 baris 1
  display.print("Send toServer");
  display.display();
}
