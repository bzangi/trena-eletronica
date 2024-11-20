// INCLUSÃO DE BIBLIOTECAS
#include <NewPing.h>

// Pin definitions
#define pinTrig 3
#define pinEcho 2

#define pinLed 5

// Distance sensor definitions
#define MAX_DISTANCE 4000
#define DELAY_LEITURA 1500

// Variables
NewPing sonar(pinTrig, pinEcho, MAX_DISTANCE);
unsigned long ultimaLeitura;
float distanciaAnterior = -1;
bool firstStableMeasure = true;

void setup() {
  Serial.begin(9600);            // Serial monitor

  pinMode(pinLed, OUTPUT);
}

void loop() {
  // Lê a distância em intervalos definidos pelo DELAY_LEITURA
  if ( millis() - ultimaLeitura > DELAY_LEITURA) {
    float distancia = sonar.ping_cm();

    if ( distancia > 0)  { // Se não houver objeto na frente não envia nada
      // Verifica se a distância atual é igual à anterior (tolerância de 1cm)
      if (abs(distancia - distanciaAnterior) <= 1) {
        digitalWrite(pinLed, HIGH); // Liga o LED
        if(firstStableMeasure){
          Serial.println(distancia);
          firstStableMeasure = false;
        }
      } else {
        digitalWrite(pinLed, LOW); // Desliga o LED
        firstStableMeasure = true;
      }

      // Atualiza a distância anterior
      distanciaAnterior = distancia;
    }
    // Atualiza o tempo da última leitura
    ultimaLeitura = millis();
  }
}
