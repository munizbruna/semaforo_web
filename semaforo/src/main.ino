// Importações das bibliotecas
#include <WiFi.h>         // Padrão do Esp32
#include <PubSubClient.h> // Necessário para fazer comunicação broker

// Configurar a conexão com Wifi
const char *SSID = "POCOX7";
const char *PASSWORD = "12345678";

// Configurações do Broker MQTT
const char *MQTT_HOST = "broker.emqx.io";
const int MQTT_PORT = 1883;

// Criando as instâncias (objetos)
WiFiClient espClient;
PubSubClient client(espClient);

// Tópicos que vai escutar
const char *MQTT_TOPICO_VR = "senai510/led/vermelho";
const char *MQTT_TOPICO_VD = "senai510/led/verde";
const char *MQTT_TOPICO_AM = "senai510/led/amarelo";

const char *MQTT_TOPICO_DESLIGAR = "senai510/led/desligar";

const int PINO_VR = 21;
const int PINO_VD = 22;
const int PINO_AM = 23;

int VermelhoState = digitalRead(PINO_VR);
int VerdeState = digitalRead(PINO_VD);

void setup()
{
  Serial.begin(115200);
  conectarWifi();
  conectarMQTT();
  pinMode(PINO_VR, OUTPUT);
  pinMode(PINO_VD, OUTPUT);
  pinMode(PINO_AM, OUTPUT);
}

void loop()
{
  if (!client.connected())
  {
    Serial.println("MQTT desconectado");
    conectarMQTT();
  }

  client.loop();
  delay(1000);

  VermelhoState = digitalRead(PINO_VR);
  VerdeState = digitalRead(PINO_VD);
}

void conectarWifi()
{
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Conectando no Wifi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  String ip = " " + WiFi.localIP().toString();
  Serial.println("Conectado WiFi");
  Serial.println(ip.c_str());
}

void conectarMQTT()
{
  // Define o servidor do MQTT que vai receber as mensagens
  client.setServer(MQTT_HOST, MQTT_PORT);

  // Define a função que será chamada quando receber uma mensagem
  client.setCallback(mensagemRecebida);

  while (!client.connected())
  {
    // Cria um identificador único para a conexão
    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("Conectado ao Broker :)");
      Serial.println(clientId);
    }
    else
    {
      Serial.println("Erro ao conectar no Broker :(");
      String mqttError = "Codigo do erro: " + String(client.state());
      Serial.println(mqttError.c_str());
    }
  }

  // Se inscreve no(s) tópico(s)
  client.subscribe(MQTT_TOPICO_VR);
  client.subscribe(MQTT_TOPICO_VD);
  client.subscribe(MQTT_TOPICO_AM);
  client.subscribe(MQTT_TOPICO_DESLIGAR);
}

void mensagemRecebida(char *topico, byte *payload, unsigned int tamanho)
{
  Serial.println(topico);

  if (strcmp(topico, MQTT_TOPICO_VR) == 0)
  {
    if (VerdeState == HIGH)
    {
      digitalWrite(PINO_VD, LOW);
      digitalWrite(PINO_AM, HIGH);
      delay(3000);
      digitalWrite(PINO_AM, LOW);
    }
    digitalWrite(PINO_VR, HIGH);
  }
  if (strcmp(topico, MQTT_TOPICO_VD) == 0)
  {
    digitalWrite(PINO_VR, LOW);
    digitalWrite(PINO_AM, LOW);

    digitalWrite(PINO_VD, HIGH);
  }
  if (strcmp(topico, MQTT_TOPICO_AM) == 0)
  {
    digitalWrite(PINO_VR, LOW);
    digitalWrite(PINO_VD, LOW);
    digitalWrite(PINO_AM, HIGH);
  }
  else if (strcmp(topico, MQTT_TOPICO_DESLIGAR) == 0)
  {
    digitalWrite(PINO_VR, LOW);
    digitalWrite(PINO_VD, LOW);
    digitalWrite(PINO_AM, LOW);
  }
}