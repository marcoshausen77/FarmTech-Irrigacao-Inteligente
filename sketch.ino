
#include <Arduino.h>
#include <DHTesp.h>
#include <math.h>

// FarmTech Solutions - Grupo 77
// Projeto 2: Irrigacao Inteligente
// Cultura escolhida: tomate
// Sensores simulados para fins academicos

const int PIN_N = 18;
const int PIN_P = 19;
const int PIN_K = 21;
const int PIN_LDR = 34;
const int PIN_DHT = 15;
const int PIN_RELE = 26;

// Parametros didaticos de funcionamento
const float PH_MINIMO = 5.5;
const float PH_MAXIMO = 7.5;
const float UMIDADE_LIGAR = 55.0;
const float UMIDADE_DESLIGAR = 65.0;

DHTesp dht;

struct Botao {
  int pino;
  bool presente;
  bool leituraAnterior;
  bool leituraEstavel;
  unsigned long ultimaMudanca;
};

Botao nitrogenio = {PIN_N, false, HIGH, HIGH, 0};
Botao fosforo   = {PIN_P, false, HIGH, HIGH, 0};
Botao potassio  = {PIN_K, false, HIGH, HIGH, 0};

bool bombaLigada = false;
unsigned long ultimaLeitura = 0;

// Cada clique alterna o nutriente entre presente e ausente.
void atualizarBotao(Botao &botao) {
  bool leitura = digitalRead(botao.pino);

  if (leitura != botao.leituraAnterior) {
    botao.ultimaMudanca = millis();
  }

  if (millis() - botao.ultimaMudanca > 35) {
    if (leitura != botao.leituraEstavel) {
      botao.leituraEstavel = leitura;

      if (leitura == LOW) {
        botao.presente = !botao.presente;
      }
    }
  }

  botao.leituraAnterior = leitura;
}

void controlarIrrigacao() {
  TempAndHumidity dados = dht.getTempAndHumidity();

  float umidade = dados.humidity;
  int leituraLDR = analogRead(PIN_LDR);

  // Conversao didatica do LDR para escala de pH (0 a 14).
  float ph = leituraLDR * 14.0 / 4095.0;

  bool leituraValida = !isnan(umidade);
  bool nutrientesOK =
      nitrogenio.presente &&
      fosforo.presente &&
      potassio.presente;

  bool phOK = ph >= PH_MINIMO && ph <= PH_MAXIMO;

  if (!leituraValida || !nutrientesOK || !phOK) {
    bombaLigada = false;
  } else if (umidade < UMIDADE_LIGAR) {
    bombaLigada = true;
  } else if (umidade >= UMIDADE_DESLIGAR) {
    bombaLigada = false;
  }

  // Relé configurado como PNP: HIGH aciona.
  digitalWrite(PIN_RELE, bombaLigada ? HIGH : LOW);

  Serial.println();
  Serial.println("====== FARMTECH SOLUTIONS ======");

  Serial.print("Nitrogenio (N): ");
  Serial.println(nitrogenio.presente ? "PRESENTE" : "AUSENTE");

  Serial.print("Fosforo (P): ");
  Serial.println(fosforo.presente ? "PRESENTE" : "AUSENTE");

  Serial.print("Potassio (K): ");
  Serial.println(potassio.presente ? "PRESENTE" : "AUSENTE");

  Serial.print("pH simulado: ");
  Serial.println(ph, 2);

  Serial.print("Umidade simulada do solo: ");
  if (leituraValida) {
    Serial.print(umidade, 1);
    Serial.println("%");
  } else {
    Serial.println("LEITURA INVALIDA");
  }

  Serial.print("Irrigacao: ");
  Serial.println(bombaLigada ? "LIGADA" : "DESLIGADA");

  if (!leituraValida) {
    Serial.println("Motivo: falha na leitura do DHT22.");
  } else if (!nutrientesOK) {
    Serial.println("Motivo: verificar NPK.");
  } else if (!phOK) {
    Serial.println("Motivo: pH fora da faixa definida.");
  } else if (bombaLigada) {
    Serial.println("Motivo: solo com umidade baixa.");
  } else {
    Serial.println("Motivo: irrigacao nao necessaria.");
  }

  Serial.println("================================");
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_N, INPUT_PULLUP);
  pinMode(PIN_P, INPUT_PULLUP);
  pinMode(PIN_K, INPUT_PULLUP);

  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);

  analogReadResolution(12);

  dht.setup(PIN_DHT, DHTesp::DHT22);

  Serial.println("FarmTech Solutions - Grupo 77");
  Serial.println("Sistema de irrigacao iniciado.");
  Serial.println("Clique nos botoes para alternar N, P e K.");
  Serial.println("Altere o LDR para simular o pH.");
  Serial.println("Altere o DHT22 para simular a umidade.");
}

void loop() {
  atualizarBotao(nitrogenio);
  atualizarBotao(fosforo);
  atualizarBotao(potassio);

  if (millis() - ultimaLeitura >= 2000) {
    ultimaLeitura = millis();
    controlarIrrigacao();
  }

  delay(10);
}
