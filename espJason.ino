#include<ESP8266WiFi.h>

  //const char* ssid = "IFPE_JBG_POS";
  //const char* password = "p0s#1fp3";

  const char * ssid = "Edlas";
const char * password = "";

int pinoRapido = D0;
int pinoNormal = D1;
int pinoLento = D2;

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)

int idSemaforo = 1;
String fluxo;

void setup() {

  //pinMode(pinoRapido, OUTPUT);
  //pinMode(pinoNormal, OUTPUT);
  //pinMode(pinoLento, OUTPUT);

  Serial.begin(115200);

  //Conexão na rede WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");

  // Inicia o servidor WEB
  server.begin();
  Serial.println("Server iniciado");

  // Mostra o endereco IP
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }
  while (client.available()) {
    delay(10);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json;charset=utf-8");
  client.println("Connection: keep-alive"); //<------ ATENCAO
  client.println();

  String req = client.readStringUntil('\r');
  Serial.println(req);

  if (req.indexOf("/atuador/fluxo/normal") != -1)
    mudaNormal();
  if (req.indexOf("/atuador/fluxo/lento") != -1)
    mudaLento();
  if (req.indexOf("/atuador/fluxo/rapido") != -1)
    mudaRapido();
  if (req.indexOf("/atuador/info") != -1)
    Serial.println("JSON");

  else {
    // client.stop();
    return;
  }

  client.print("{\"FLUXO\":\"");
  client.print(fluxo);
  client.print("\"}");
  client.println();
}
void mudaNormal() {
  apagaTodos();
  fluxo = "NORMAL";
  digitalWrite(pinoNormal, HIGH);
}

void mudaRapido() {
  apagaTodos();
  fluxo = "RAPIDO";
  digitalWrite(pinoRapido, HIGH);
}
void mudaLento() {
  apagaTodos();
  fluxo = "LENTO";
  digitalWrite(pinoLento, HIGH);
}
void apagaTodos() {
  digitalWrite(pinoNormal, LOW);
  digitalWrite(pinoRapido, LOW);
  digitalWrite(pinoLento, LOW);
}
