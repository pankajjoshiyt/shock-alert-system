#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <ZMPT101B.h>
#define SENSITIVITY 500.0f

// ZMPT101B sensor output connected to analog pin A0
// and the voltage source frequency is 50 Hz
ZMPT101B voltageSensor(A0, 50.0);
#define RX 5   // SIM800L TX → Arduino pin 6
#define TX 6   // SIM800L RX → Arduino pin 5
SoftwareSerial sim800l(RX, TX);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  voltageSensor.setSensitivity(SENSITIVITY);
  sim800l.begin(9600);

  // OLED initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed!");
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  delay(2000);

  // SIM800L init
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Checking SIM800L...");
  display.display();
  delay(1000);
}

void loop() {
  // read the voltage and then print via Serial
  float voltage = voltageSensor.getRmsVoltage();
  display.clearDisplay();
  display.setCursor(10, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("Voltage");
  display.setCursor(10, 25);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(voltage);
  display.display();
  delay(1000);
  display.clearDisplay();

  if (voltage > 50)
  {
    sms();
  }
}

void sendSMS(const char *number, const char *message) {
  sim800l.print("AT+CMGF=1\r");
  delay(500);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(number);
  sim800l.println("\"");
  delay(500);
  sim800l.print(message);
  delay(500);
  sim800l.write(26);  // CTRL+Z to send SMS
  delay(5000);
}

// Optimized AT command sender
bool sendAT(const char* cmd, const char* resp, unsigned long timeout) {
  sim800l.println(cmd);
  unsigned long t = millis();
  while (millis() - t < timeout) {
    if (sim800l.find(const_cast<char*>(resp))) return true;
  }
  return false;
}

void sms ()
{
  display.setTextSize(1);
  delay(100);
  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CMGF=1");  // Set SMS text mode
  delay(1000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SIM800L Ready!");
  display.println("Sending SMS...");
  display.display();
  delay(1000);

  //sendSMS("+919325242153", "SHOCK ALERT! Voltage spike detected ");
  sendSMS("+919325242153","Shok Alert https://maps.google.com/?q=19.900356,74.494850");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SMS Sent Successfully!");
  display.display();
  delay (2000);
}
