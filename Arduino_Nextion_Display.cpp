
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Nextion.h"
#include <MG811.h>

MG811 mySensor = MG811(A0); // Analog input A0

float v400 = 4.535;
float v40000 = 3.206;

#define ONE_WIRE_BUS1 2
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

OneWire oneWire1(ONE_WIRE_BUS1);  
 
DallasTemperature DSTEMP(&oneWire1);
                        
// Declare your Nextion objects - Example (page id = 0, component id = 1, component name = "b0") 
NexText tTempC = NexText(1, 3, "tTempC");
NexText tAltitude = NexText(1, 6, "tAltitude");
NexText tPressure = NexText(1, 10, "tPressure");
NexText tHumidty = NexText(1, 12, "tHumidty");
NexText tTemp1  = NexText(1, 17, "tTemp1");
NexText tTemp2  = NexText(1, 20, "tTemp2");
NexText tTemp3  = NexText(1, 23, "tTemp3");
NexText tTemp4  = NexText(1, 26, "tTemp4");
NexText tTemp5  = NexText(1, 29, "tTemp5");
NexText tCo2= NexText(1, 33, "tCo2");
//NexButton bUpdate = NexButton(1,35, "bUpdate");

 void bUpdatePopCallback(void *ptr) {
  
 }
 void Update() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  int t1 = DSTEMP.getTempCByIndex(0);
  int t2 = DSTEMP.getTempCByIndex(1);
  int t3 = DSTEMP.getTempCByIndex(2);
  int t4 = DSTEMP.getTempCByIndex(3);
  int t5 = DSTEMP.getTempCByIndex(4);    
  
   int t = bme.readTemperature();
   int p = bme.readPressure() / 100.0F;
   int h = bme.readHumidity();
   int  a = bme.readAltitude(SEALEVELPRESSURE_HPA);
   int  percentage = mySensor.read();
    
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)  || isnan(a) || isnan(p) ) {
    return;
  }
  // Update temperature in Celsius
  static char temperatureCTemp[6];
  dtostrf(t, 6, 2, temperatureCTemp);
  tTempC.setText(temperatureCTemp);

  static char temperatureCTemp1[6];
  dtostrf(t1, 6, 2, temperatureCTemp1);
  tTemp1.setText(temperatureCTemp1);

  static char temperatureCTemp2[6];
  dtostrf(t2, 6, 2, temperatureCTemp2);
  tTemp2.setText(temperatureCTemp2);

  static char temperatureCTemp3[6];
  dtostrf(t3, 6, 2, temperatureCTemp3);
  tTemp3.setText(temperatureCTemp3);

    static char temperatureCTemp4[6];
  dtostrf(t4, 6, 2, temperatureCTemp4);
  tTemp4.setText(temperatureCTemp4);

  static char temperatureCTemp5[6];
  dtostrf(t5, 6, 2, temperatureCTemp5);
  tTemp5.setText(temperatureCTemp5);

  static char Humidity1[6];
  dtostrf(h, 6, 2, Humidity1);
  tHumidty.setText(Humidity1);
  
  static char Pressure[6];
  dtostrf(p, 6, 2, Pressure);
  tPressure.setText(Pressure);

  static char Altitude1[6];
  dtostrf(a, 6, 2, Altitude1);
  tAltitude.setText(Altitude1);

  static char sensorValue1[6];
  dtostrf( percentage, 6, 2, sensorValue1);
  tCo2.setText(sensorValue1);

}
void setup(void){
  Serial.println("START");
  Serial.begin(9600);

  nexInit();

  //bUpdate.attachPop(bUpdatePopCallback, &bUpdate);
  DSTEMP.begin();  // DSTEMP เริ่มทำงาน

    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;

    status = bme.begin(0x76, &Wire);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
       // while (1) delay(10);
  } 
    Serial.println("-- Default Test --");
    delayTime = 2000;
    mySensor.begin(v400, v40000);
    Serial.println();
}
void loop(void){ 
     DSTEMP.requestTemperatures(); 
     Update() ;
    //printValues();
    delay(delayTime);
    }

    
 void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

  
  // แสดงค่าในหน่วย Celsius ของตัวที่ 1
  Serial.print("Temperature 1: ");
  Serial.print(DSTEMP.getTempCByIndex(0));
  Serial.println("Celsius");

  // แสดงค่าในหน่วย Celsius ของตัวที่ 2
  Serial.print("Temperature 2: ");
  Serial.print(DSTEMP.getTempCByIndex(1));
  Serial.println("Celsius");

  // แสดงค่าในหน่วย Celsius ของตัวที่ 3
  Serial.print("Temperature 3: ");
  Serial.print(DSTEMP.getTempCByIndex(2));
  Serial.println("Celsius");

  // แสดงค่าในหน่วย Celsius ของตัวที่ 4
  Serial.print("Temperature 4: ");
  Serial.print(DSTEMP.getTempCByIndex(3));
  Serial.println("Celsius");

  // แสดงค่าในหน่วย Celsius ของตัวที่ 5
  Serial.print("Temperature 5: ");
  Serial.print(DSTEMP.getTempCByIndex(4));
  Serial.println("Celsius");
  
  Serial.println("");
  delay(1000);
  
}
