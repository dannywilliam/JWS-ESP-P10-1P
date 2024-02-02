### JWS ESP P10 - 1 Panel

#### Jadwal Waktu Sholat yang dibuat dengan ESP8266 dan Panel P10 (HUB12).

JWS ini dibuat dengan mengikuti tutorial di YouTube pada Playlist berjudul "Membuat JWS" milik "Bonny Useful". Link nya : https://www.youtube.com/watch?v=lvVriKy26gw&list=PLKuQ-UWqAt3O8WmFeoTbUa2keQKbdOXVv

Pemilik channel juga meng upload tutorialnya ke github pada link : https://github.com/busel7/Arduino/tree/master/MembuatJWS

Repository ini menggunakan lisensi GNU/GPL versi 3 sesuai dengan repository asli pemilik channel.

Repository ini saya khususkan untuk penggunaan 1 panel P10. Untuk jumlah panel yang lebih banyak, akan saya buatkan repository lain nanti.

Ada beberapa penyesuaian yang saya lakukan pada repository ini. Misalnya tampilan jam istiwa'.

### Fitur

- Jam Besar. Jam WIB dan Istiwa' tampil bergantian.
- Alarm Adzan Waktu Solat dan Tanbih Imsak
- Tanggal Masehi
- Hitung Mundur Iqomah
- Running Text Nama Masjid

### Fitur yang dihapus

- Lafadz / Logo
- Tanggal Hijriyah
- Tampilan Suhu
- Jam Kecil
- Tampilan Jadwal Waktu Sholat, diganti dengan Tampilan Hitung Mundur Waktu Sholat.

### Fitur yang ditambahkan

- Tampilan Jam Istiwa'.
- Tampilan Hitung Mundur Waktu Sholat.

### Perubahan

- Hitungan waktu Terbit. Awalnya ditambah ihtiyat, menjadi dikurangi ihtiyat.
- Hitungan waktu Dzuhur. Langsung ditambah 4, bukan ditambah ihtiyat.
- Memunculkan kembali jadwal Terbit Matahari (awalnya di skip).

### Wifi

- SSID = JWS ESP P10
- PassWord = jwsmurottal
- IP Address : 192.168.4.1

### Pin on DMD LED P10 Panel

| DMD P10 | GPIO | NODEMCU | 
| ------- | ---- | ------- |
| A       | GPIO16 | D0    |                                                 
| B       | GPIO12 | D6    |                                                  
| CLK     | GPIO14 | D5    |                           
| SCK     | GPIO0  | D3    |                           
| R       | GPIO13 | D7    |
| NOE     | GPIO15 | D8    |
| GND     | GND    | GND   |

### Pin on RTC DS3231

| DS3231 | NODEMCU |
| ------ | ------- |
| SCL    | D1 (GPIO 5) |
| SDA    | D2 (GPIO 4) |
| VCC    | 3V          |
| GND    | GND         |

### Pin on Buzzer

| Buzzer | NODEMCU |
| ------ | ------- |
| +      | RX (GPIO 3) |
| -      | GND         |

### Eksternal Library
- DMDESP : https://github.com/busel7/DMDESP
- PrayerTime : https://github.com/asmaklad/Arduino-Prayer-Times
- RTC DS3231 : https://github.com/Makuna/Rtc
- ArduinoJson V6 : https://github.com/bblanchon/ArduinoJson

Tools : 
- Desain bitmap dan font : http://dotmatrixtool.com
- LittleFS Uploader : https://github.com/earlephilhower/arduino-esp8266littlefs-plugin/releases
        
### Catatan : 
- Perlu Power Eksternal 5V ke LED P10.
- Saat Flashing (upload program) cabut sementara pin untuk buzzer.
