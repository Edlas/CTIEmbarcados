int carroVermelho = D2; 
int carroAmarelo = D1; 
int carroVerde = D0; 

int pinoRapido = D5;
int pinoNormal = D6;
int pinoLento = D7;

unsigned long mudaTempo;

long tempoStatusVerdeNormal = 5000;
long tempoStatusVermelhoNormal = 5000;

long tempoStatusVerdeRapido = 2000;
long tempoStatusVermelhoRapido = 8000;

long tempoStatusVerdeLento = 8000;
long tempoStatusVermelhoLento = 2000;

long tempoStatusAmarelo = 2000;
long tempoStatusVerde = tempoStatusVerdeNormal;
long tempoStatusVermelho = tempoStatusVermelhoNormal;

void setup() {
  mudaTempo = millis();
  
  pinMode(carroVermelho, OUTPUT);
  pinMode(carroAmarelo, OUTPUT);
  pinMode(carroVerde, OUTPUT);

  pinMode(pinoRapido,INPUT);
  pinMode(pinoNormal,INPUT);
  pinMode(pinoLento,INPUT);
  
  digitalWrite(carroVerde, HIGH);
  digitalWrite(carroVermelho, LOW);
  digitalWrite(carroAmarelo, LOW);
  Serial.begin(115200);
}
 
void loop() {
  verificaMudancaStatus();
  if ((millis() - mudaTempo) > tempoStatusVerde) {
    mudaLuzes();
  }
}
 
void mudaLuzes() {
  
  mudaAmarelo();

  mudaVermelho();
  
  mudaVerde();
  
  mudaTempo = millis();
 }

 void mudaVermelho(){
  digitalWrite(carroAmarelo, LOW); // A luz amarela vai desligar
  digitalWrite(carroVermelho, HIGH); // A luz vermelha vai ligar por 5 segundos
  delay(tempoStatusVermelho);
  verificaMudancaStatus();
 }

 void mudaVerde(){
  digitalWrite(carroVermelho, LOW);
  digitalWrite(carroVerde, HIGH);
  verificaMudancaStatus();
 }
 void mudaAmarelo(){
  digitalWrite(carroVerde, LOW);    
  digitalWrite(carroAmarelo, HIGH);
  delay(tempoStatusAmarelo); 
  verificaMudancaStatus();
 }
 
 void verificaMudancaStatus(){
  int pinRapido = digitalRead(pinoRapido);
  if(pinRapido == HIGH){
    tempoStatusVerde = tempoStatusVerdeRapido;
    tempoStatusVermelho =  tempoStatusVermelhoRapido;
    Serial.println("Fluxo Rapido");
  }
  int pinNormal = digitalRead(pinoNormal);
  if(pinNormal == HIGH){
    tempoStatusVerde = tempoStatusVerdeNormal;
    tempoStatusVermelho =  tempoStatusVermelhoNormal;
    Serial.println("Fluxo Normal");
  }
  int pinLento = digitalRead(pinoLento);
  if(pinLento == HIGH){
    tempoStatusVerde = tempoStatusVerdeLento;
    tempoStatusVermelho =  tempoStatusVermelhoLento;
    Serial.println("Fluxo Lento");
  }
 }
