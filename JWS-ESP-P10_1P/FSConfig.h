// ----------------------
// FS CONFIG

int detikiqmh;
int menitiqmh;
uint8_t tipealarm;
uint8_t tmputama;
uint8_t tmpjws;
uint8_t tmpinfo;

struct ConfigJws {
  uint8_t iqmhs; // menit
  uint8_t iqmhd; // menit
  uint8_t iqmha; // menit
  uint8_t iqmhm; // menit
  uint8_t iqmhi; // menit
  uint8_t durasiadzan; // Menit
  uint8_t ihti; // Koreksi Waktu Menit Jadwal Sholat
  float latitude;
  float longitude;
  int8_t zonawaktu;
  uint8_t hilal;
  char namamasjid[512];
};

const char *fileconfigjws = "/configjws.json";
ConfigJws configjws;

String message, XML;



// -------------------------------------------
// Membuat file config JWS JSON di File Sistem

void membuatDataAwal() {

  String dataawal = "{\"iqmhs\":\"12\",\"iqmhd\":\"8\",\"iqmha\":\"6\",\"iqmhm\":\"5\",\"iqmhi\":\"5\",\"durasiadzan\":\"4\",\"ihti\":\"2\",\"latitude\":\"-7.04\",\"longitude\":\"112.70\",\"zonawaktu\":\"7\",\"hilal\":\"0\",\"namamasjid\":\"LANGGAR AL-KAROMAH\"}";

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, dataawal);

  File configFileJws = LittleFS.open(fileconfigjws, "w");
  
  if (!configFileJws) {
    Serial.println("Gagal membuat file configjws.json untuk ditulis mungkin partisi belum dibuat");
    return;
  }
  
  serializeJson(doc, configFileJws);

  if (error) {
    
    Serial.print(F("deserializeJson() gagal kode sebagai berikut: "));
    Serial.println(error.c_str());
    return;
    
  } else {
    
    configFileJws.close();
    Serial.println("Berhasil membuat file configjws.json");
  
  }  

}



// -------------------------------------------
// Membaca file config JWS JSON di File Sistem

void loadJwsConfig(const char *fileconfigjws, ConfigJws &configjws) {  

  File configFileJws = LittleFS.open(fileconfigjws, "r");

  if (!configFileJws) {
    
    Serial.println("Gagal membuka file configjws.json untuk dibaca");
    membuatDataAwal();
    Serial.println("Sistem restart...");
    ESP.restart();
    
  }

  size_t size = configFileJws.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFileJws.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());  

  if (error) {
    Serial.println("Gagal parse fileconfigjws");
    return;
  }
  
  configjws.iqmhs = doc["iqmhs"];
  configjws.iqmhd = doc["iqmhd"];
  configjws.iqmha = doc["iqmha"];
  configjws.iqmhm = doc["iqmhm"];
  configjws.iqmhi = doc["iqmhi"];
  configjws.durasiadzan = doc["durasiadzan"];
  configjws.ihti = doc["ihti"];
  configjws.latitude = doc["latitude"];
  configjws.longitude = doc["longitude"];
  configjws.zonawaktu = doc["zonawaktu"];
  configjws.hilal = doc["hilal"];
  strlcpy(configjws.namamasjid, doc["namamasjid"] | "", sizeof(configjws.namamasjid));

  configFileJws.close(); 

}


// -------------------------------------------
// MEMBACA PARAMETER YANG TERSIMPAN

void bacaParameter() {

  Serial.println(" ");
  Serial.println("PARAMETER TERSIMPAN");
  Serial.print("Iqomah Subuh   : "); Serial.println(configjws.iqmhs);
  Serial.print("Iqomah Dzuhur  : "); Serial.println(configjws.iqmhd);
  Serial.print("Iqomah Ashar   : "); Serial.println(configjws.iqmha);
  Serial.print("Iqomah Maghrib : "); Serial.println(configjws.iqmhm);
  Serial.print("Iqomah Isya    : "); Serial.println(configjws.iqmhi);
  Serial.print("Durasi Adzan   : "); Serial.println(configjws.durasiadzan);
  Serial.print("Ihtiyati       : "); Serial.println(configjws.ihti);
  Serial.print("Latitude       : "); Serial.println(configjws.latitude);
  Serial.print("Longitude      : "); Serial.println(configjws.longitude);
  Serial.print("Zona Waktu     : "); Serial.println(configjws.zonawaktu);
  Serial.print("Derajat Hilal  : "); Serial.println(configjws.hilal);
  Serial.print("Nama Masjid    : "); Serial.println(configjws.namamasjid);
  Serial.println(" ");
  
}


//----------------------------------------------------------------------
// XML UNTUK JEMBATAN DATA MESIN DENGAN WEB

void XMLWaktu(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";
  
    XML+="<Tahun>";
    XML+=rTah;
    XML+="</Tahun>";
    XML+="<Bulan>";
    XML+=rBul;
    XML+="</Bulan>";
    XML+="<Tanggal>";
    XML+=rTgl;
    XML+="</Tanggal>";
    XML+="<Jam>";
      if(rJam<10){
        XML+="0";
        XML+=rJam;
      }else{XML+=rJam;}
    XML+="</Jam>";
    XML+="<Menit>";
      if(rMen<10){
        XML+="0";
        XML+=rMen;
      }else{XML+=rMen;}
    XML+="</Menit>";
    XML+="<Detik>";
      if(rDet<10){
        XML+="0";
        XML+=rDet;
      }else{XML+=rDet;}
    XML+="</Detik>";
    XML+="<Suhu>";
    XML+= celsius - 5;
    XML+="</Suhu>";
    
  XML+="</t>"; 
}


void XMLDataJWS(){

  XML="<?xml version='1.0'?>";
  XML+="<t>";

    XML+="<IqomahSubuh>";
    XML+= configjws.iqmhs;
    XML+="</IqomahSubuh>";
    XML+="<IqomahDzuhur>";
    XML+= configjws.iqmhd;
    XML+="</IqomahDzuhur>";
    XML+="<IqomahAshar>";
    XML+= configjws.iqmha;
    XML+="</IqomahAshar>";
    XML+="<IqomahMaghrib>";
    XML+= configjws.iqmhm;
    XML+="</IqomahMaghrib>";
    XML+="<IqomahIsya>";
    XML+= configjws.iqmhi;
    XML+="</IqomahIsya>";
    XML+="<DurasiAdzan>";
    XML+= configjws.durasiadzan;
    XML+="</DurasiAdzan>";
    XML+="<Ihtiyati>";
    XML+= configjws.ihti;
    XML+="</Ihtiyati>";
    XML+="<Latitude>";
    XML+= configjws.latitude;
    XML+="</Latitude>";
    XML+="<Longitude>";
    XML+= configjws.longitude;
    XML+="</Longitude>";
    XML+="<ZonaWaktu>";
    XML+= configjws.zonawaktu;
    XML+="</ZonaWaktu>";
    XML+="<Hilal>";
    XML+= configjws.hilal;
    XML+="</Hilal>";
    XML+="<NamaMasjid>";
    XML+= configjws.namamasjid;
    XML+="</NamaMasjid>";
    
  XML+="</t>"; 
}
