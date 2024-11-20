# Projeto: Trena Eletrônica IoT com Arduino

Este projeto consiste em uma trena eletrônica baseada no Arduino, utilizando um sensor ultrassônico para medir distâncias com precisão. Os dados medidos podem ser enviados para a nuvem via protocolo MQTT, integrando a solução com a Internet das Coisas (IoT). O sistema inclui funcionalidades de detecção de objetos e indicação de medições estabilizadas.

## Funcionalidades
- Medição precisa de distâncias entre 2 cm e 4 metros.
- Indicação por LED quando a medição está estável.
- Envio de dados para um broker MQTT utilizando um script em Node.js.

---

## Requisitos

### Hardware
- **Arduino Uno**
- **Sensor Ultrassônico HC-SR04**
- **LED 5mm**
- Protoboard e cabos para prototipagem.

### Software
- **Arduino IDE** (para carregar o código no Arduino)
- **Node.js** (para rodar o script de comunicação MQTT)
- Dependências do Node.js:
  - `serialport`
  - `mqtt`

---

## Configuração do Projeto

### 1. Montagem do Hardware
[Diagrama](https://prnt.sc/vTZMrGT4dspv)
1. Conecte o **sensor ultrassônico HC-SR04**:
   - Trig no pino **3** do Arduino.
   - Echo no pino **2** do Arduino.
   - VCC e GND para alimentação.

2. Conecte o **LED 5mm**:
   - Anodo no pino **5** do Arduino com um resistor de 220 ohms.
   - Catodo ao GND.

3. Conecte o Arduino ao computador via USB.

---

### 2. Configuração do Arduino
1. Abra o arquivo `Sketch_arduino.ino` no Arduino IDE.
2. Instale a biblioteca **NewPing**:
   - No Arduino IDE, vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
   - Procure por **NewPing** e clique em **Instalar**.
3. Carregue o código para o Arduino.

---

### 3. Configuração do Node.js
1. Instale o Node.js (versão 16 ou superior).
2. Instale as dependências:
   ```bash
   npm install serialport mqtt
