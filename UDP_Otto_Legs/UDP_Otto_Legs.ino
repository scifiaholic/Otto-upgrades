#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Servo.h>

// UDP variables
WiFiUDP UDP;
unsigned int localPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,

#define pinLeftAnkle 16
#define pinLeftHip 12
#define pinRightHip 13
#define pinRightAnkle 14

Servo servoLeftAnkle;
Servo servoLeftHip;
Servo servoRightHip;
Servo servoRightAnkle;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting Otto!");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectOTTO");

  servoLeftAnkle.attach(pinLeftAnkle);
  servoLeftHip.attach(pinLeftHip);
  servoRightAnkle.attach(pinRightAnkle);
  servoRightHip.attach(pinRightHip);

  servoLeftAnkle.write(90);
  servoLeftHip.write(90);
  servoRightAnkle.write(90);
  servoRightHip.write(90);

  Serial.println("");
  Serial.print("connected! IP: ");
  Serial.println(WiFi.localIP());

  UDP.begin(localPort);

}

void loop()
{
  int packetSize = UDP.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d ", packetSize, UDP.remoteIP().toString().c_str(), UDP.remotePort());
    int len = UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    if (len > 0)
    {
      servoLeftAnkle.write(packetBuffer[0]);
      servoLeftHip.write(packetBuffer[1]);
      servoRightAnkle.write(packetBuffer[2]);
      servoRightHip.write(packetBuffer[3]);

      Serial.print(packetBuffer[0], DEC);
      Serial.print(" ");
      Serial.print(packetBuffer[1], DEC);
      Serial.print(" ");
      Serial.print(packetBuffer[2], DEC);
      Serial.print(" ");
      Serial.print(packetBuffer[3], DEC);
      Serial.println("");
    }
  }
}











