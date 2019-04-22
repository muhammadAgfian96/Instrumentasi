asi#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example
int a,b, adc, val[150];
long unsigned int adc_new = 0;
float sudut;
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

int batas = 100; //untuk rata2 adc sensor

void setup()   {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 0);
  display.clearDisplay();
  display.println("HALO, SAYANG");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45, 20);
  display.println("INK");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50, 50);
  display.println("sudut");

  display.display();

  delay(3000);
  display.clearDisplay();

}

void loop() {
  //-------Proses Akusisi Data ------------
  adc_new = 0;
  for (int i = 0; i < batas; i++) {
    val[i] = analogRead(A0);
    adc_new = adc_new + val[i];
    delay(15);
  }
// hasil akhir adc
  adc = int(adc_new / batas);
  
//----persanamaan regresi liniar-----
  sudut = 0.2917*adc + 25.09;

  //------Buat Tampilan LCD ---------------

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 12);
  display.clearDisplay();
  display.println("Nilai adc:");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(65, 10);
  display.println(adc);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("sudut:");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 42);
  display.println(sudut);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(85, 45);
  display.println("derajat");

  display.display();
}
