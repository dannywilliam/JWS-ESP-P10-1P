int jwsNow, jwsNext;
int cHor, cMin, cSec;
int xHor, xMin, xSec;

//----------------------------------------------------------------------
// FORMAT TEKS

void textCenter(int y,String Msg) {
  
  int center = int((Disp.width()-Disp.textWidth(Msg)) / 2);
  Disp.drawText(center,y,Msg);
  
}

//----------------------------------------------------------------------
// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void AlarmSholat() {  

  int hours, minutes, seconds;

  // Tanbih Imsak
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes < 10) {
    
    minutes = 60 - minutes;
    hours --;
    
  } else {
    
    minutes = minutes - 10 ;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {

    tipealarm = 0;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;

  }

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 1;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;
    
  }


  // Dzuhur
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + 4;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0 && rHar != 5) {
    
    tipealarm = 2;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;

  } else if (rJam == hours && rMen == minutes && rDet == 0 && rHar == 5) {
    
    tipealarm = 3;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;

  }


  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 4;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;
    
  }

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 5;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;
    
  }

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 6;
    detikbeep = 0;
    Disp.clear();
    tmputama = 1;
    
  }  
  
}



//----------------------------------------------------------------------
// TAMPILAN ADZAN

void TampilAdzan() {

  BunyiBeep(2,6);
  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint16_t det;

  if (tipealarm == 0) {
      
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "TANBIH");
    textCenter(8, "IMSAK");
    
  }
  
  if (tipealarm == 1) {
  
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "SUBUH");

    menitiqmh = configjws.iqmhs;
    
  }
  
  if (tipealarm == 2) {
    
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "DZUHUR");

    menitiqmh = configjws.iqmhd;
    
  }
  
  if (tipealarm == 3) {
    
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "JUM'AT");
    
  }
  
  if (tipealarm == 4) {
  
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "ASHAR");
    
    menitiqmh = configjws.iqmha;
    
  }
  
  if (tipealarm == 5) {
  
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "MAGHRIB");

    menitiqmh = configjws.iqmhm;
    
  } 
  
  if (tipealarm == 6) {
  
    Disp.setFont(ElektronMart6x8);
    textCenter(0, "ADZAN");
    textCenter(8, "ISYA");

    menitiqmh = configjws.iqmhi;
    
  }  

  if (cM-pM >= 1000) {
    
    det++;   

    if (tipealarm == 0) {      
      
      if (det == 60) {
        Disp.clear();
        det = 0;
        detikbeep = 0;
        tmputama = 0;
      }
      
    }

    
    if (tipealarm == 3) {
    
      if (det == configjws.durasiadzan * 60) {
        Disp.clear();
        det = 0;
        detikbeep = 0;
        tmputama = 0;
      }
      
    }
    
    
    if (tipealarm == 1 or tipealarm == 2 or tipealarm == 4 or tipealarm == 5 or tipealarm == 6) {
          
      if (det == configjws.durasiadzan * 60) {
        Disp.clear();
        det = 0;
        detikbeep = 0;
        tmputama = 2;
      }
      
    }
    
    pM = cM;
    
  }  
  
}



//----------------------------------------------------------------------
// HITUNG MUNDUR WAKTU SETELAH ADZAN SAMPAI MULAI IQOMAH

void Iqomah() {

  static uint32_t pM;
  uint32_t cM = millis();
  static char hitungmundur[6];  

  Disp.setFont(ElektronMart5x6);
  textCenter(0, "IQOMAH");

  if (detikiqmh == 60) {
    detikiqmh = 0;
  }

  if (cM - pM >= 1000) {
    pM = cM;
    detikiqmh--;

    if (menitiqmh == 0 && detikiqmh == 0) {
      Disp.clear();
      detikbeep = 0;
      detikiqmh = 59;
      tmputama = 3;
    }

    if (detikiqmh < 0) {
      detikiqmh = 59;
      menitiqmh--;
    }
    
  }

  sprintf(hitungmundur, "%02d:%02d", menitiqmh, detikiqmh);
  Disp.setFont(ElektronMart6x8);
  textCenter(8, hitungmundur);
  
}



//----------------------------------------------------------------------
// TAMPILAN SAAT SHOLAT

void TampilSaatSholat() {

  BunyiBeep(1,4);

  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t durasi = 10; // Detik
  static uint32_t det;

  Disp.setFont(ElektronMart5x6);
  textCenter(0, "LURUSKAN");
  textCenter(8, "RAPATKAN");

  if (cM - pM >= 1000) {
    pM = cM;
    det++;

    if (durasi == det) {
      Disp.clear();
      detikbeep = 0;
      det = 0;
      tmputama = 0;
    }
  }  
  
}

//----------------------------------------------------------------------
void CekSholat() {  

  int hours, minutes, seconds;

  // Cek jadwal Imsak
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + configjws.ihti;

  if (minutes < 10) {
    
    minutes = 60 - minutes;
    hours --;
    
  } else {
    
    minutes = minutes - 10 ;
    
  }

  // Cek apakah sudah imsak atau belum
  if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
    jwsNow = 6;
    jwsNext = 7;
    xHor = hours;
    xMin = minutes;
  } else {
    // Cek jadwal Subuh
    get_float_time_parts(times[0], hours, minutes);
    minutes = minutes + configjws.ihti;

    if (minutes >= 60) {
      minutes = minutes - 60;
      hours ++;
    }

    if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
      jwsNow = 7;
      jwsNext = 0;
      xHor = hours;
      xMin = minutes;
    } else {
      // Cek jadwal Terbit
      get_float_time_parts(times[1], hours, minutes);
      minutes = minutes - configjws.ihti;

      if (minutes >= 60) {
        minutes = minutes - 60;
        hours ++;
      }

      if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
        jwsNow = 0;
        jwsNext = 1;
        xHor = hours;
        xMin = minutes;
      } else {
        // Cek jadwal Dzuhur
        get_float_time_parts(times[2], hours, minutes);
        minutes = minutes + 4;

        if (minutes >= 60) {
          minutes = minutes - 60;
          hours ++;
        }

        if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
          jwsNow = 1;
          jwsNext = 2;
          xHor = hours;
          xMin = minutes;
        } else {
          // Cek jadwal Ashar
          get_float_time_parts(times[3], hours, minutes);
          minutes = minutes + configjws.ihti;

          if (minutes >= 60) {
            minutes = minutes - 60;
            hours ++;
          }

          if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
            jwsNow = 2;
            jwsNext = 3;
            xHor = hours;
            xMin = minutes;
          } else {
            // Cek jadwal Maghrib
            get_float_time_parts(times[5], hours, minutes);
            minutes = minutes + configjws.ihti;

            if (minutes >= 60) {
              minutes = minutes - 60;
              hours ++;
            }

            if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
              jwsNow = 3;
              jwsNext = 5;
              xHor = hours;
              xMin = minutes;
            } else {
              // Cek jadwal Isya'
              get_float_time_parts(times[6], hours, minutes);
              minutes = minutes + configjws.ihti;

              if (minutes >= 60) {
                minutes = minutes - 60;
                hours ++;
              }

              if ((rJam < hours) or (rJam == hours && rMen <= minutes)) {
                jwsNow = 5;
                jwsNext = 6;
                xHor = hours;
                xMin = minutes;
              } else {
                // Cek jadwal Imsak
                get_float_time_parts(times[0], hours, minutes);
                minutes = minutes + configjws.ihti;

                if (minutes < 10) {
                  
                  minutes = 60 - minutes;
                  hours --;
                  
                } else {
                  
                  minutes = minutes - 10 ;
                  
                }

                jwsNow = 6;
                jwsNext = 7;
                xHor = hours;
                xMin = minutes;
              }
            }
          }
        }
      }
    }
  }
}

//----------------------------------------------------------------------
//TAMPILAN RUNNING TEKS

void TeksBerjalanKananKiri() {

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 50;
  static uint32_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(configjws.namamasjid) + width;

  Disp.setFont(ElektronMart6x8);
  textCenter(0,"#");
  Disp.drawRect(0,6,Disp.width(),6,1,1);

  if(cM - pM > Kecepatan) {

    pM = cM;

    if (x < fullScroll) {
      if (x == 0) {
        Disp.drawRect(0,0,31,15,0,0); //Mengosongi area untuk Running Text
      }
      ++x;
      
    } else {

      x = 0;
      Disp.clear();
      tmpjws = 0;
      
    }

    Disp.drawText(width - x, 8, configjws.namamasjid);
    
  }
  
}


void TeksBerjalanKiriKanan() {

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 50;
  static uint32_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(configjws.namamasjid) + width;

  Disp.setFont(ElektronMart6x8);

  if(cM - pM > Kecepatan) {

    pM = cM;

    if (x < fullScroll) {

      ++x;
      
    } else {

      x = 0;
      
    }

    Disp.drawText(x - fullScroll + width, 8, configjws.namamasjid);
    
  }
  
}


//----------------------------------------------------------------------
//TAMPILKAN TANGGAL

void TampilTanggal() {

  char hari[8];
  char tanggal[7]; // 21 SEP

  static uint32_t pM;
  uint32_t cM = millis();

  static uint8_t flag;

  if(cM - pM > 3000) {
    
    pM = cM;
    flag++;

    sprintf(hari, "%s", namaHari[rHar]);
    sprintf(tanggal, "%02d %s", rTgl, namaBulan[rBul]);
  
    Disp.setFont(ElektronMart5x6);
    textCenter(0, hari);
    textCenter(8, tanggal);

    if (flag >= 2) {
      flag = 0;
      Disp.drawRect(0,0,31,15,0,0);
      tmpinfo = 1;
      
    }
    
  } 
  
}

//----------------------------------------------------------------------
// TAMPILKAN COUNTDOWN

void TampilCountDown() {

  char TimeName[][8] = {"SUBUH","TERBIT","DZUHUR","ASHAR","TRBNM","MAGHRIB","ISYA'","IMSAK"};
  char TampilMundur[9];
  String sholat = TimeName[jwsNext];

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t pulse;

  if (cM - pM >= 1000) {
    pM = cM;
    pulse++;
  }
  
  if (pulse >= 8) {
    pulse=0;
    Disp.drawRect(0,0,31,15,0,0);
    tmpinfo = 0;
    tmpjws = 3;
  }
  
  cHor = xHor - rJam;
  cMin = xMin - rMen - 1;
  cSec = 60 - rDet;

  if (cHor < 0) {
    cHor = cHor + 24;
  }

  if (cMin < 0) {
    cMin = cMin + 60;
    cHor --;
  }

  if (cHor > 0) {
    sprintf(TampilMundur, "-%02d:%02d", cHor, cMin);
  } else if (cMin > 0) {
    sprintf(TampilMundur, "-%02d:%02d", cMin, cSec);
  } else {
    sprintf(TampilMundur, "-%02d", cSec);
  }

  //JTampilkan Hitungan Mundur
  Disp.setFont(ElektronMart5x6);
  textCenter(0, sholat);
  textCenter(8, TampilMundur);
  
}

//----------------------------------------------------------------------
// TAMPILKAN JAM

void JamBesar(uint16_t x) {

  char jam[3];
  char menit[3];

  static uint8_t y;
  static uint8_t d;           
  static uint32_t pM;
  uint32_t cM = millis();
  static boolean kedip;

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 500) {
    pMPulse = cM;
    pulse++;
    kedip = !kedip;
  }
  
  if (pulse > 8) {
    pulse=0;
  }

  if(cM - pM > 35) { 
    if(d == 0 and y < 20) {
      pM=cM;
      y++;
    }
    if(d  == 1 and y > 0) {
      pM=cM;
      y--;
    }    
  }
  
  if(cM - pM > 5000 and y == 20) { // Jam akan tampil selama 5 detik
    d=1;
  }
  
  if(y == 0 and d == 1) {
    d=0;
    tmpjws = 1;
  }
  
  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

  //JAM
  Disp.setFont(BigHour6x16);
  Disp.drawText(x+1, y - 20, jam);

  //MENIT
  Disp.setFont(BigHour6x16);
  Disp.drawText(x+18, y - 20, menit);
  
  //Mengosongi area di bawah jam sebanyak 1 piksel
  Disp.drawRect(x+0, y-4, x+31, y-4, 0,0);

  //Gambar 2 titik
  
  if (kedip) {
    Disp.drawRect(x+15, y-20, x+16,y - 4,0,0);
  } else {
    Disp.setFont(BigHour6x16);
    Disp.drawText(x+15, y-20, ":");
  }
  
}

void JamBesarIst(uint16_t x) {

  char jam[3];
  char menit[3];

  int hours, minutes;
  int tafawut;

  static uint8_t y;
  static uint8_t d;           
  static uint32_t pM;
  uint32_t cM = millis();
  static boolean kedip;

  static uint32_t pMPulse;
  static uint8_t pulse;

  //Hitung waktu tengah hari / Istiwa'
  get_float_time_parts(times[2], hours, minutes);

  //Tentukan Tafawut, yaitu jarak antara WIB ke Istiwa'
  tafawut = ((12-hours)*60)+(0-minutes);

  //Jam istiwa' adalah Jam WIB ditambah Tafawut
  int HorIst = rJam;
  int MinIst = rMen+tafawut;

  if (MinIst<0) {
    MinIst = MinIst + 60;
    HorIst --;
  }

  if (MinIst>=60) {
    MinIst = MinIst - 60;
    HorIst ++;
  }

  if (HorIst>24) {
    HorIst = HorIst - 24;
  }

  if (HorIst>12) {
    HorIst = HorIst - 12;
  }

  if (HorIst<=0) {
    HorIst = HorIst + 12;
  }

  if (cM - pMPulse >= 500) {
    pMPulse = cM;
    pulse++;
    kedip = !kedip;
  }
  
  if (pulse > 8) {
    pulse=0;
  }

  if(cM - pM > 35) { 
    if(d == 0 and y < 20) {
      pM=cM;
      y++;
    }
    if(d  == 1 and y > 0) {
      pM=cM;
      y--;
    }    
  }
  
  if(cM - pM > 5000 and y == 20) { // Jam akan tampil selama 5 detik
    d=1;
  }
  
  if(y == 0 and d == 1) {
    d=0;
    tmpjws=2;
  }
  
  sprintf(jam, "%02d", HorIst);
  sprintf(menit, "%02d", MinIst);

  //JAM
  Disp.setFont(BigArab6x16);
  Disp.drawText(x+1+int((13-Disp.textWidth(jam)) / 2), y - 20, jam);

  //MENIT
  Disp.setFont(BigArab6x16);
  Disp.drawText(x+18+int((13-Disp.textWidth(menit)) / 2), y - 20, menit);

  //Mengosongi area di bawah jam sebanyak 1 piksel
  Disp.drawRect(x+0, y-4, x+31, y-4, 0,0);

  //Gambar 2 titik
  
  if (kedip) {
    Disp.drawRect(x+15, y-20, x+16,y - 4,0,0);
  } else {
    Disp.setFont(BigArab6x16);
    Disp.drawText(x+15, y-20, ":");
  }
  
}

// PENGHITUNG JADWAL SHOLAT

void JadwalSholat() {

  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting

    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi

    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night

    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  
  */

  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(rTah, rBul, rTgl, configjws.latitude, configjws.longitude, configjws.zonawaktu, times);

}

//-----------------------------------
// UPDATE WAKTU

void UpdateWaktu() {

  static long pM;
  static uint16_t d;
  

  if (millis() - pM > 1000) {
    d++;
    if (d < 2) {
      BacaRTC();
      JadwalSholat();
      CekSholat();
    } else if (d < 60) { // Update setiap 60 detik
      rDet++;
      if (rDet > 59) {
        rMen++;
        rDet=0;
        if (rMen > 59) {
          rJam++;
          rMen = 0;
        }
      }
    } else {
      d = 0; 
    }
    pM = millis();    
  }
  
}
