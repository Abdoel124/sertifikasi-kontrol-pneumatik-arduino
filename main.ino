#include <Arduino.h>
// Deklarasi Pin
int btnStart = 4;      
int limitSwitch = 5;   
int relayPneumatik = 3;    
int relayIndikator = 2;

// Variabel untuk mengunci pergerakan pneumatik (Latching)
boolean mesinMenyala = false;   

void setup() {
  // Mengaktifkan resistor pull-up internal Arduino
  // Artinya: Saat tidak ditekan nilainya HIGH, saat ditekan/tersentuh nilainya LOW
  pinMode(btnStart, INPUT_PULLUP); 
  pinMode(limitSwitch, INPUT_PULLUP);     
  
  // Set pin relay sebagai output
  pinMode(relayPneumatik, OUTPUT);
  pinMode(relayIndikator, OUTPUT);

  // Pastikan relay mati saat Arduino baru nyala
  digitalWrite(relayPneumatik, LOW);
  digitalWrite(relayIndikator, LOW);
}

void loop() {
  // 1. Baca Tombol Start
  // Jika tombol ditekan (LOW), KUNCI perintah agar mesin menyala
  if (digitalRead(btnStart) == LOW) {
    mesinMenyala = true;
    //delay(200); // Jeda sedikit agar tidak dobel klik
  }
  
  // 2. Baca Limit Switch
  // Jika limit switch tersentuh (LOW), BUKA KUNCI agar mesin mati
  if (digitalRead(limitSwitch) == LOW) {
    mesinMenyala = false;
  }

  // 3. Eksekusi pergerakan pneumatik berdasarkan status kunci di atas
  if (mesinMenyala == true) {
    digitalWrite(relayPneumatik, HIGH);    // Pneumatik Extend (Maju)
    digitalWrite(relayIndikator, LOW);     // Lampu mati
  } 
  else {
    digitalWrite(relayPneumatik, LOW);     // Pneumatik Retract (Mundur)
    digitalWrite(relayIndikator, HIGH);    // Lampu nyala
  }
}