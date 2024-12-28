//#include <Arduino.h>
//
//#include "DHT.h"
//#include <MQUnifiedsensor.h>
//
////Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define ADC_Bit_Resolution 10
//
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-5" //MQ5
//#define RatioMQ5CleanAir 6.5  //RS / R0 = 6.5 ppm
//
//#define pin A1 //Analog input 1 of your arduino
//#define type "MQ-8" //MQ8
//#define RatioMQ8CleanAir 70   //RS / R0 = 70 ppm 
//
//#define pin A2 //Analog input 2 of your arduino
//#define type "MQ-7" //MQ7
//#define RatioMQ7CleanAir 27.5 //RS / R0 = 27.5 ppm
//unsigned long oldTime = 0;
//
//#define pin A3 //Analog input 3 of your arduino
//#define type "MQ-135" //MQ135
//#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm 
//
//#define DHTPIN 2
//#define DHTTYPE DHT22
//DHT dht(DHTPIN, DHTTYPE);
//
//MQUnifiedsensor MQ5(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//MQUnifiedsensor MQ8(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//void setup() 
//{
//
//  Serial.begin(9600);
//
//  MQ5.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
//  
//  //MQ5
//  MQ5.setA(80.897); MQ5.setB(-2.431); // Configure the equation to to calculate H2 concentration
//  /*
//    Exponential regression:
//  Gas    | a      | b
//  H2     | 1163.8 | -3.874
//  LPG    | 80.897 | -2.431
//  CH4    | 177.65 | -2.56
//  CO     | 491204 | -5.826
//  Alcohol| 97124  | -4.918
//  */
//  MQ5.init();   
//  Serial.print("Calibrating please wait.");
//  float calcR0 = 0;
//  for(int i = 1; i<=10; i ++)
//  {
//    MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
//    calcR0 += MQ5.calibrate(RatioMQ5CleanAir);
//    Serial.print(".");
//  }
//  MQ5.setR0(calcR0/10);
//  Serial.println("  done!.");
//  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
//  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
//
//  //MQ8
//  MQ8.setA(976.97); MQ8.setB(-0.688); // Configure the equation to to calculate H2 concentration
//  /*
//    Exponential regression:
//  GAS     | a      | b
//  H2      | 976.97  | -0.688
//  LPG     | 10000000 | -3.123
//  CH4     | 80000000000000 | -6.666
//  CO      | 2000000000000000000 | -8.074
//  Alcohol | 76101 | -1.86
//  */
//  MQ8.init();
//  Serial.print("Calibrating please wait.");
//  float calcR01 = 0;
//  for(int i = 1; i<=10; i ++)
//  {
//    MQ8.update(); // Update data, the arduino will read the voltage from the analog pin
//    calcR01 += MQ8.calibrate(RatioMQ8CleanAir);
//    Serial.print(".");
//  }
//  MQ8.setR0(calcR01/10);
//  Serial.println("  done!.");
//  if(isinf(calcR01)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
//  if(calcR01 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
//
//  //MQ7
//  MQ7.setA(99.042); MQ7.setB(-1.518); // Configure the equation to calculate CO concentration value
//  /*
//    Exponential regression:
//  GAS     | a      | b
//  H2      | 69.014  | -1.374
//  LPG     | 700000000 | -7.703
//  CH4     | 60000000000000 | -10.54
//  CO      | 99.042 | -1.518
//  Alcohol | 40000000000000000 | -12.35
//  */
//  MQ7.init(); 
//  Serial.print("Calibrating please wait.");
//  float calcR02 = 0;
//  for(int i = 1; i<=10; i ++)
//  {
//    MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
//    calcR02 += MQ7.calibrate(RatioMQ7CleanAir);
//    Serial.print(".");
//  }
//  MQ7.setR0(calcR02/10);
//  Serial.println("  done!.");
//  if(isinf(calcR02)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
//  if(calcR02 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
//  
//  //MQ135
//  MQ135.init(); 
//  Serial.print("Calibrating please wait.");
//  float calcR03 = 0;
//  for(int i = 1; i<=10; i ++)
//  {
//    MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
//    calcR03 += MQ135.calibrate(RatioMQ135CleanAir);
//    Serial.print(".");
//  }
//  MQ135.setR0(calcR03/10);
//  Serial.println("  done!.");
//  
//  if(isinf(calcR03)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
//  if(calcR03 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
//  /*
//  Exponential regression:
//  GAS      | a      | b
//  CO       | 605.18 | -3.937  
//  Alcohol  | 77.255 | -3.18 
//  CO2      | 110.47 | -2.862
//  Toluen  | 44.947 | -3.445
//  NH4      | 102.2  | -2.473
//  Aceton  | 34.668 | -3.369
//  */
//  Serial.println(F("DHT test!"));
//  dht.begin();
//
//}
//
//
//void loop() 
//{
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  float f = dht.readTemperature(true);
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }
//
//  Serial.print(F("Humidity(%):"));
//  Serial.print(h);
//  //Serial.println(F("%"));
//  Serial.print(" ");
//
//  Serial.print(F("Temperature(°C):"));
//  Serial.print(t);
//  //Serial.println(F("°C"));
//  Serial.print(" ");
//
//  //Serial.println("Measurement in PPM: ");
//
//  //MQ5
//  MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
//  Serial.print("MQ5_LPG:");
//  Serial.print(MQ5.readSensor()); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//  Serial.print(" ");
//  //MQ8
//  MQ8.update(); // Update data, the arduino will read the voltage from the analog pin
//  Serial.print("MQ8_H2:");
//  Serial.print(MQ8.readSensor()); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//  Serial.print(" ");
//  //MQ7
//  MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
//  Serial.print("MQ7_CO:");
//  Serial.print(MQ7.readSensor());// Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//  Serial.print(" ");
//  //MQ135
//  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
//
//  MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to calculate CO concentration value
//  float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//
//  MQ135.setA(77.255); MQ135.setB(-3.18); //Configure the equation to calculate Alcohol concentration value
//  float Alcohol = MQ135.readSensor(); // SSensor will read PPM concentration using the model, a and b values set previously or from the setup
//
//  MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to calculate CO2 concentration value
//  float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//
//  MQ135.setA(44.947); MQ135.setB(-3.445); // Configure the equation to calculate Toluen concentration value
//  float Toluen = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//  
//  MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configure the equation to calculate NH4 concentration value
//  float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//
//  MQ135.setA(34.668); MQ135.setB(-3.369); // Configure the equation to calculate Aceton concentration value
//  float Aceton = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
//  
//  Serial.print("MQ135_CO:"); Serial.print(CO); Serial.print(" ");
//  Serial.print("MQ135_Alcohol:"); Serial.print(Alcohol); Serial.print(" ");
//  Serial.print("MQ135_CO2:"); Serial.print(CO2 + 422.38); Serial.print(" ");
//  Serial.print("MQ135_Toluen:"); Serial.print(Toluen); Serial.print(" ");
//  Serial.print("MQ135_NH4:"); Serial.print(NH4); Serial.print(" ");
//  Serial.print("MQ135_Aceton:"); Serial.println(Aceton);  
//  Serial.println();
//  delay(2000);
//
//}
//

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup()  {

  Serial.begin(9600);

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true);
  display.display();
  delay(5000);
  display.clearDisplay();
}


void loop() {

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Humam");
  display.display();
  delay(500);
  display.clearDisplay();

  display.setCursor(15, 16);
  display.print("---THE BOT---");
  display.display();
  delay(500);
  display.clearDisplay();

  display.setCursor(90,32);
  display.print("PUK U");
  display.display();
  delay(500);
  display.clearDisplay();
}
