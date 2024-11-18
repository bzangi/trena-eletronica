
// INCLUSÃO DE BIBLIOTECAS
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <WiFiEsp.h>

// Pin definitions
#define pinTrig 3
#define pinEcho 2

#define pinLed 5

// Distance sensor definitions
#define MAX_DISTANCE 4000
#define DELAY_LEITURA 3000

// MQTT Definitions
const char* ssid = "PAULO-ROGERIO";
const char* password = "opc0998801";
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "arduino/distance";

// ESP8266
#define RX 10
#define TX 11
SoftwareSerial Serial1(RX, TX);

// MQTT Client
WiFiEspClient espClient;
PubSubClient client(espClient);

// Variables
NewPing sonar(pinTrig, pinEcho, MAX_DISTANCE);
unsigned long ultimaLeitura;
float distanciaAnterior = -1;

void setup() {
  Serial.begin(9600);            // Serial monitor

  // // Define pin modes for TX and RX
  // pinMode(RX, INPUT);
  // pinMode(TX, OUTPUT);
  // Serial1.begin(9600);         // ESP8266 communication

  // // Connect to Wi-Fi
  // WiFi.init(&Serial1);
  // connectWiFi();

  // // Configure MQTT
  // client.setServer(mqtt_server, 1883);
  // connectMQTT();

  pinMode(pinLed, OUTPUT);
}

void loop() {
  // if (!client.connected()) {
  //   connectMQTT();
  // }
  // client.loop();

  // Read distance at intervals
  if ( millis() - ultimaLeitura > DELAY_LEITURA) {
    float distancia = sonar.ping_cm();

    if ( distancia > 0)  { // Se não houver objeto na frente não envia nada
      Serial.println("distancia anterior");
      Serial.println(distanciaAnterior);
      Serial.println("distancia medida");
      Serial.println(distancia);

      // Verifica se a distância atual é igual à anterior (tolerância de 1cm)
      if (abs(distancia - distanciaAnterior) <= 1) {
        digitalWrite(pinLed, HIGH); // Liga o LED
      } else {
        digitalWrite(pinLed, LOW); // Desliga o LED
      }

      // Atualiza a distância anterior
      distanciaAnterior = distancia;
    }
    // Atualiza o tempo da última leitura
    ultimaLeitura = millis();
  }
}

// Connect to Wi-Fi
void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWi-Fi connected");
}

// Connect to MQTT broker
void connectMQTT() {
  Serial.print("Connecting to MQTT broker...");
  while (!client.connected()) {
    if (client.connect("ArduinoClient")) { // Client ID
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

// Publish distance to MQTT
void publishDistance(float distance) {
  char message[8];
  dtostrf(distance, 6, 2, message); // Convert float to string
  client.publish(mqtt_topic, message);
  Serial.println("Distance published to MQTT");
}

