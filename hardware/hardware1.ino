//##################################################################################################################
//##                                      ELET2415 DATA ACQUISITION SYSTEM CODE                                   ##
//##                                                                                                              ##
//##################################################################################################################

 

// IMPORT ALL REQUIRED LIBRARIES
#include "Arduino.h"
#include <rom/rtc.h>
#include <ArduinoJson.h>
#include <math.h>  // https://www.tutorialspoint.com/c_standard_library/math_h.htm

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "DHT.h"

#ifndef _WIFI_H 
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef ARDUINO_H
#include <Arduino.h>
#endif 
 
// DEFINE VARIABLES
#define ARDUINOJSON_USE_DOUBLE      1 

// DEFINE THE CONTROL PINS FOR THE DHT22 
#define DHTPIN 27 //datapin of sensor
#define DHTTYPE DHT22 // define the type of sensor

#define BTN1      32
#define BTN2      33
#define BTN3      25


#define TFT_DC    17
#define TFT_CS    5
#define TFT_RST   16
#define TFT_CLK   18
#define TFT_MOSI  23
#define TFT_MISO  19

//----------------------------------------Defines colors
// Assign human-readable names to some common 16-bit color values:
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define AQUA        0x04FF
#define ORANGE      0xFD20
#define DARKORANGE  0xFB60
#define MAROON      0x7800
#define BLACKM      0x18E3
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h> 

#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

double h=0;
double t=0;
double f=0;
double hi;
double pa;

const int AirValue = 3999;  //you need to replace this value with Value_1
const int WaterValue = 1999;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;

uint32_t runTime = -99999;       // time for next update
int reading1 = 0; // Value to be displayed
int d = 0; // Variable used for the sinewave test waveform
boolean alert = 0;
int8_t ramp = 1;
int tesmod =0;

char TempCelciusFahrenheit[6];

float tempF = 0;



// MQTT CLIENT CONFIG  
static const char* pubtopic      = "620154701";                    // Add your ID number here
static const char* subtopic[]    = {"620154701_sub","/elet2415"};  // Array of Topics(Strings) to subscribe to
static const char* mqtt_server   = "dbs.msjrealtms.com";         // Broker IP address or Domain name as a String 
static uint16_t mqtt_port        = 1883;

// WIFI CREDENTIALS
const char* ssid       = "MonaConnect" ; // Add your Wi-Fi ssid
const char* password   = ""; // Add your Wi-Fi password 



// TASK HANDLES 
TaskHandle_t xMQTT_Connect          = NULL; 
TaskHandle_t xNTPHandle             = NULL;  
TaskHandle_t xLOOPHandle            = NULL;  
TaskHandle_t xUpdateHandle          = NULL;
TaskHandle_t xButtonCheckeHandle    = NULL; 



// FUNCTION DECLARATION   
void checkHEAP(const char* Name);   // RETURN REMAINING HEAP SIZE FOR A TASK
void initMQTT(void);                // CONFIG AND INITIALIZE MQTT PROTOCOL
unsigned long getTimeStamp(void);   // GET 10 DIGIT TIMESTAMP FOR CURRENT TIME
void callback(char* topic, byte* payload, unsigned int length);
void initialize(void);
bool publish(const char *topic, const char *payload); // PUBLISH MQTT MESSAGE(PAYLOAD) TO A TOPIC
void vButtonCheck( void * pvParameters );
void vUpdate( void * pvParameters ); 


/* Init class Instances for the DHT22 etcc */
 DHT dht(DHTPIN,DHTTYPE);

//############### IMPORT HEADER FILES ##################
#ifndef NTP_H
#include "NTP.h"
#endif

#ifndef MQTT_H
#include "mqtt.h"
#endif

#ifndef FORECAST_H
#include "foreCast.h"
#endif

#define analogPin A3


/* Initialize class objects*/
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();


void setup() {
  Serial.begin(115200);  // INIT SERIAL  

  /* TFT DISPLAY SET UP */
  dht.begin();
  tft.begin();
  bmp.begin();
 
  // stat_display();
  tft.setRotation(1);

  /* ENABLE PULL-UP RESISTORS */
  pinMode(BTN1,INPUT_PULLUP);
  pinMode(BTN2,INPUT_PULLUP);
  pinMode(BTN3,INPUT_PULLUP);

  tft.fillScreen(RED); 

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();

  initialize();           // INIT WIFI, MQTT & NTP 

  //vButtonCheckFunction(); // UNCOMMENT IF USING BUTTONS THEN ADD LOGIC FOR INTERFACING WITH BUTTONS IN THE vButtonCheck FUNCTION

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelay(1000 / portTICK_PERIOD_MS);  
  
}

  
//####################################################################
//#                          UTIL FUNCTIONS                          #       
//####################################################################
void vButtonCheck( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );     
      
    for( ;; ) {
        // Add code here to check if a button(S) is pressed
        // then execute appropriate function if a button is pressed  

     
        vTaskDelay(200 / portTICK_PERIOD_MS);  
        }
}

void vUpdate( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );    
 
    for( ;; ) {

        soilMoistureValue = analogRead(analogPin);  //put Sensor insert into soil
        soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

        sensors_event_t temp_event, pressure_event;
        bmp_pressure->getEvent(&pressure_event);

        h = dht.readHumidity();
        t = dht.readTemperature();
        hi = dht.computeHeatIndex(t, h);
        pa = pressure_event.pressure;

        // Serial.print(F("Approx air pressure = "));
        // Serial.print(pa);
        // Serial.println(" hPa");

        // Serial.print(F("Approx altitude = "));
        // Serial.print(bmp.readAltitude(1014)); /* Adjusted to local forecast! */
        // Serial.println(" m");

        //   Serial.println(soilmoisturepercent);

        if(soilmoisturepercent >= 100)
        {
          soilmoisturepercent=100;
        }
        else if(soilmoisturepercent <=0)
        {
          soilmoisturepercent=0;
        }
        // Serial.print(F("Approx soil moisture = "));
        // Serial.print(soilmoisturepercent);
        // Serial.println("%");

        // Serial.print(F("Approx humidity = "));
        // Serial.print(h);
        // Serial.println("%");

        // Serial.print(F("Approx temperature = "));
        // Serial.print(t);
        // Serial.println(" C");

        // Serial.print(F("Approx heat index = "));
        // Serial.print(hi);
        // Serial.println("C");


        //----------------------------------------
      int xpos = 0, ypos = 5, gap = 4, radius = 52;
          // Draw a large meter
          xpos = 320/2 - 150, ypos = 15, gap = 100, radius = 50;
          
          ringMeter( t,0,90, 0,0,radius,"TEMPERATURE",4 ); // Draw analogue meter

          ringMeter( hi,0,90, 108,0,radius,"HEAT INDEX",4 ); // Draw analogue meter

          ringMeter(h,0,100, 215,0,radius,"HUMIDITY",4 ); // Draw analogue meter
          
          ringMeter(soilmoisturepercent,0,99, 0,120,radius,"SOIL MOISTURE",4 ); // Draw analogue meter
          
          ringMeter(pa,965,1040, 108,120,radius,"AIR PRESSURE",4 ); // Draw analogue meter


      
        tft.setCursor(245, 130);  
        tft.setTextSize (1);
        tft.setTextColor ( YELLOW , RED);
        tft.print("Forecast");

        

        tft.setCursor (247, 90); // Print the Humidity
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (h, 1);
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (" % ");
        tesmod = 1;

        tft.setCursor (138, 210); // Print the Humidity
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (pa, 1);
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (" hPa ");

        tft.setCursor (133, 90); // Print the Humidity
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print ("( Feels Like )");
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
      
        tft.setCursor (33, 90); // Print the Humidity
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (t, 1);
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (" *C ");

        tft.setCursor (33, 210); // Print the Humidity
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (soilmoisturepercent, 1);
        tft.setTextSize (1);
        tft.setTextColor (GREEN, RED);
        tft.print (" %   ");

      if((h)>0 &&  (h)<55 )
        {
        tft.drawBitmap(245,150, sun,50,50,YELLOW,RED);
      } else 

      if((h)>=55 &&  (h)<80 )
        {
        tft.drawBitmap(245,150, cloud,50,50,WHITE,RED);
        
      } else


      if((h)>=80 &&  (h)<100 )
        {
        tft.drawBitmap(245,150, rain,50,50,BLUE,RED);
        
        } 
      if(isNumber(t)){
              // ##Publish update according to ‘{"id": "student_id", "timestamp": 1702212234, "temperature": 30, "humidity":90, "heatindex": 30}’

              // 1. Create JSon object
              StaticJsonDocument<1000> doc;
              
              // 2. Create message buffer/array to store serialized JSON object
              char message[1100]={0};
              
              // 3. Add key:value pairs to JSon object based on above schema
              doc["id"] = "620154701";
              doc["timestamp"] = getTimeStamp();
              doc["temperature"] =  round(t * 100) / 100.0;
              doc["humidity"] =  round(h * 100) / 100.0;
              doc["heatindex"] =  round(hi * 100) / 100.0;
              doc["pressure"] =  round(pa * 100) / 100.0;
              doc["soilmoisture"] = round(soilmoisturepercent * 100) / 100.0;
              doc["altitude"] = round(bmp.readAltitude(1014) * 100) / 100.0;


              // 4. Seralize / Covert JSon object to JSon string and store in message array

              serializeJson(doc,message);
              Serial.println(message);
               
              // 5. Publish message to a topic sobscribed to by both backend and frontend
              if(mqtt.connected()){
                publish(pubtopic,message);
              }               

          }

        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}

unsigned long getTimeStamp(void) {
          // RETURNS 10 DIGIT TIMESTAMP REPRESENTING CURRENT TIME
          time_t now;         
          time(&now); // Retrieve time[Timestamp] from system and save to &now variable
          return now;
}

void callback(char* topic, byte* payload, unsigned int length) {
  // ############## MQTT CALLBACK  ######################################
  // RUNS WHENEVER A MESSAGE IS RECEIVED ON A TOPIC SUBSCRIBED TO
  
  Serial.printf("\nMessage received : ( topic: %s ) \n",topic ); 
  char *received = new char[length + 1] {0}; 
  
  for (int i = 0; i < length; i++) { 
    received[i] = (char)payload[i];    
  }

  // PRINT RECEIVED MESSAGE
  Serial.printf("Payload : %s \n",received);

 
  // CONVERT MESSAGE TO JSON
  


  // PROCESS MESSAGE


}

bool publish(const char *topic, const char *payload){   
     bool res = false;
     try{
        res = mqtt.publish(topic,payload);
        // Serial.printf("\nres : %d\n",res);
        if(!res){
          res = false;
          throw false;
        }
     }
     catch(...){
      Serial.printf("\nError (%d) >> Unable to publish message\n", res);
     }
  return res;
}

//========================================================================

//========================================================================

void ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / 3;    // Width of outer ring is 1/4 of radius 
  int angle = 150;  // Half the sweep angle of meter (300 degrees)
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
  // Variable to save "value" text colour from scheme and set default
  int colour = GREEN;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle+inc/2; i < angle-inc/2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = GREEN; break; // Fixed colour
        case 1: colour = RED; break; // Fixed colour
        case 2: colour = BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        default: colour = GREEN; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, RED);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, RED);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 2; if (value > 99) len = 3;if (value > 999) len = 4;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);

  if(value>9){
  tft.setTextColor(CYAN,RED);
  tft.setCursor(x-25,y-10);tft.setTextSize(3);
  tft.print(buf);}
  if(value==100){
  dtostrf(value, 3, 0, buf);
  buf[3] = ' '; buf[3] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextColor(ORANGE,RED);
  tft.setCursor(x-25,y-10);tft.setTextSize(3);
  tft.print(buf);
  delay(1000);
  tft.setTextColor(RED,RED);
  tft.setCursor(x-25,y-10);tft.setTextSize(3);
  tft.print(buf);
  }
  else if(value<10){
  tft.setTextColor(colour,RED);
  tft.setCursor(x-25,y-10);tft.setTextSize(3);
  tft.print(buf);}

  
  tft.setTextColor(CYAN,RED);
  
  tft.setCursor(x-20,y+55);tft.setTextSize(1);
  tft.print(units); // Units display
  
  // Calculate and return right hand side x coordinate
  // return x + r;
}
//========================================================================

bool isNumber(double number){       
        char item[20];
        snprintf(item, sizeof(item), "%f\n", number);
        if( isdigit(item[0]) )
          return true;
        return false; 
} 



unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits
  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}


