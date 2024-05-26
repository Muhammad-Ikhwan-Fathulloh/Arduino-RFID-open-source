//Check Board ESP
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Board not found"
#endif

//Library RFID
#include <SPI.h>//Serial Peripheral Interface
#include <MFRC522.h>

//Pengaturan pin data dan reset RFID
constexpr uint8_t RST_PIN = 2;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 15;     // Configurable, see typical pin layout above

//RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

int readsuccess;
byte readcard[4];
char str[32] = "";
String StrUID;

void setup() {
  //Serial.begin(9600);//Arduino
  Serial.begin(115200);//ESP
  //RFID
  SPI.begin(); // Inisialisasi SPI bus
  mfrc522.PCD_Init(); // Inisialisasi MFRC522
  Serial.println("Hello RFID");
}

void loop() {
  //Sukses pembacaan id
  readsuccess = getid();
  if(readsuccess){
    //Cetak pembacaan id
    Serial.println(StrUID); //Gunakan variabel (StrUID) ini untuk data id RFID
    Serial.println("Berhasil");
          
    //Masukkan kodemu dibawah disini 
    //---------------------------------

    
    
    //---------------------------------
  }
  delay(1000);
}

//Ambil id untuk verifikasi
int getid(){ 
  if(!mfrc522.PICC_IsNewCardPresent()){
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return 0;
  }
  
  Serial.println("Data Kartu:");
  
  for(int i=0;i<4;i++){
    readcard[i]=mfrc522.uid.uidByte[i]; //Kirim id card yang dibaca
    array_to_string(readcard, 4, str);
    StrUID = str;// id yang telah diolah
  }
  mfrc522.PICC_HaltA();
  return 1;
}
// --------------------------------------------------------------------
//Mengolah frekuensi tag kartu
void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}