#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Khai báo LCD i2c
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Khai báo DHT11
#define DHTPIN 2

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22
//#define DHTTYPE DHT21   // DHT 21

DHT dht(DHTPIN, DHTTYPE);

unsigned int currentMillis = 0;
unsigned int previousMillis = 0;

float do_am;
float do_C;
String mess;

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  dht.begin();
  lcd.setCursor(2,0);
  lcd.print("DOC NHIET DO");
  lcd.setCursor(5,1);
  lcd.print("DO AM");
  delay(1000);
  lcd.clear();
}

void loop()
{
  currentMillis = millis();
  if(currentMillis - previousMillis >= 2000){
    previousMillis = currentMillis;
    readCB();
  }
  
}


//--------------------------------------------------------
// hàm đọc nhiệt độ độ ẩm
void readCB(){
  // Độ ẩm
  do_am = dht.readHumidity();
  // Nhiệt độ
  do_C = dht.readTemperature();

  // check tín hiệu xem có cảm biến không
  if (isnan(do_am) || isnan(do_C)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("CHUA KET NOI");
    lcd.setCursor(1,1);
    lcd.print("CAM BIEN DHT11");
    mess = String("-")+ " " + String("-");
    Serial.print(mess);
    return;
  }

  // Gửi tín hiệu đến Smartphone
  mess = String(do_C)+ " " + String(do_am);
  Serial.print(mess);
  inLCD(do_am, do_C);
}


//--------------------------------------------------------
// in ra lcd
void inLCD(float do_am, float do_C){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NHIET DO:");
  lcd.setCursor(9,0);
  lcd.print(do_C);
  lcd.setCursor(14,0);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("DO AM");
  lcd.setCursor(8,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  lcd.print(do_am);
  lcd.setCursor(14,1);
  lcd.print("%");
}
