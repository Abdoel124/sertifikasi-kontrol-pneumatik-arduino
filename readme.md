# Sistem Kontrol Elektropneumatik Berbasis Arduino

![Arduino](https://img.shields.io/badge/Board-Arduino%20UNO%2F2009-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/Project-Certified-brightgreen?style=for-the-badge)

Dokumentasi projek **Tugas Praktik Demonstrasi Uji Sertifikasi Kompetensi (Semester 5)**. Projek ini mengimplementasikan sistem kendali otomatis untuk gerak sekuensial silinder pneumatik tunggal menggunakan papan pengembang Arduino, driver solenoid relay, serta *feedback* sensor posisi berupa *limit switch*.

---

## 📌 Ringkasan Skenario Kerja

Sistem ini dirancang untuk mengendalikan pergerakan maju (*extend*) dan mundur (*retract*) dari silinder pneumatik secara sekuensial berdasarkan input tombol dan sensor batas posisi:

1. **Kondisi Awal (Idle):**
   - Silinder pneumatik berada pada posisi **retract** (mundur).
   - Lampu indikator **menyala** menandakan sistem siap.
   - Relay pneumatik dalam kondisi **OFF** (LOW).

2. **Proses Extend (Maju):**
   - Ketika tombol **Start** ditekan, sistem mengunci status variabel (`mesinMenyala = true`).
   - Relay pneumatik aktif (**HIGH**), memicu *solenoid valve* untuk mendorong silinder maju (*extend*).
   - Lampu indikator **mati** saat silinder beroperasi.

3. **Proses Retract (Mundur Otomatis):**
   - Saat silinder mencapai posisi maksimal dan menyentuh **Limit Switch**, sistem melepas kunci status (`mesinMenyala = false`).
   - Relay pneumatik mati (**LOW**), menyebabkan silinder kembali ke posisi awal (*retract*).
   - Lampu indikator kembali **menyala**.

---

## 🛠️ Komponen dan Perangkat

### Hardware & Komponen Elektronika
* **Microcontroller:** Arduino 2009 / Arduino UNO
* **Input Devices:** Push Button (Start), Limit Switch (Sensor Posisi)
* **Output Devices:** Relay Driver / Solenoid Driver, Lampu Indikator
* **Pneumatic Components:**
  * Silinder Pneumatik Single/Double Acting
  * Solenoid Valve 5/2 Directional Control Valve
  * Air Service Unit (FR-L Unit)
  * Kompresor Udara

---

## 🔌 Pin Mapping (Skematik Rangkaian)

| Komponen | Pin Arduino | Mode Pin | Deskripsi Fungsi |
| :--- | :--- | :--- | :--- |
| **Push Button (Start)** | Pin 4 | `INPUT_PULLUP` | Memicu sinyal mulai (*Latching Active*) |
| **Limit Switch** | Pin 5 | `INPUT_PULLUP` | Memicu sinyal batas (*Reset Latching*) |
| **Relay Pneumatik** | Pin 3 | `OUTPUT` | Mengendalikan Solenoid Valve Pneumatik |
| **Relay Indikator** | Pin 2 | `OUTPUT` | Mengendalikan Lampu Indikator Status |

---

## 💡 Logika Program (Kode Sumber)

Program dikembangkan dengan bahasa C/C++ pada Arduino IDE menggunakan teknik penguncian state (*latching variable*) untuk memastikan siklus pneumatik berjalan sempurna hingga sensor limit switch tersentuh.

```cpp
// Deklarasi Pin
int btnStart = 4;      
int limitSwitch = 5;   
int relayPneumatik = 3;    
int relayIndikator = 2;

// Variabel untuk mengunci pergerakan pneumatik (Latching)
boolean mesinMenyala = false;   

void setup() {
  // Mengaktifkan resistor pull-up internal Arduino
  pinMode(btnStart, INPUT_PULLUP); 
  pinMode(limitSwitch, INPUT_PULLUP);     
  
  // Set pin relay sebagai output
  pinMode(relayPneumatik, OUTPUT);
  pinMode(relayIndikator, OUTPUT);

  // Initial state: Relay mati saat startup
  digitalWrite(relayPneumatik, LOW);
  digitalWrite(relayIndikator, LOW);
}

void loop() {
  // 1. Baca Tombol Start (Latching ON)
  if (digitalRead(btnStart) == LOW) {
    mesinMenyala = true;
  }
  
  // 2. Baca Limit Switch (Latching OFF)
  if (digitalRead(limitSwitch) == LOW) {
    mesinMenyala = false;
  }

  // 3. Eksekusi pergerakan pneumatik berdasarkan status latching
  if (mesinMenyala == true) {
    digitalWrite(relayPneumatik, HIGH);    // Pneumatik Extend (Maju)
    digitalWrite(relayIndikator, LOW);     // Lampu Indikator Mati
  } 
  else {
    digitalWrite(relayPneumatik, LOW);     // Pneumatik Retract (Mundur)
    digitalWrite(relayIndikator, HIGH);    // Lampu Indikator Nyala
  }
}
```

---

## 📷 Skematik & Dokumentasi

> *Catatan: Gambar skematik rangkaian wiring dan diagram pneumatik diambil dari Lembar Skenario Tugas Praktik Demonstrasi Uji Sertifikasi.*

*(Kamu dapat mengunggah foto skematik dari tugasmu ke folder `assets/` di repositori ini dan menyematkannya di bagian ini).*

---

## 📂 Struktur Repositori

```text
.
├── src/
│   └── pneumatic_control.ino   # File kode program utama Arduino
├── assets/
│   └── schematic_diagram.png   # Skematik rangkaian pneumatik & kontrol
└── README.md                   # Dokumentasi projek
```

---
*Projek ini dibuat sebagai bagian dari pemenuhan Tugas Praktik Demonstrasi Uji Kompetensi (Semester 5).*