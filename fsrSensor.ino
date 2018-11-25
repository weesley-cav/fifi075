/* FSR Teste. 

Conectar o FSR à tensão e à saída analógica A0, com pulldown de 10k resistor

Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
*/
 
const int fsrPin = 0;     // o sensor FSR e 10K pulldown conectados a A0
int fsrReading;     // leitura analógica do FSR
int fsrVoltage;     // leitura analógica convertida em tensão
unsigned long fsrResistance;  // tensão convertida em resistência
unsigned long fsrConductance; 
long fsrForce;       // resistência convertida em força
 
void setup(void) {
  Serial.begin(9600);  
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin);  
  Serial.print("Leitura analógica = ");
  Serial.println(fsrReading);
 
  // leitura analogica de 0 a 1023 mapeando 0V a 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  Serial.print("Tensão lida em mV = ");
  Serial.println(fsrVoltage);  
 
  if (fsrVoltage == 0) {
    Serial.println("Sem pressão");  
  } else {
    // tensao = Vcc * R / (R + FSR) onde R = 10K e Vcc = 5V
    // entao FSR = ((Vcc - V) * R) / V
    fsrResistance = 5000 - fsrVoltage;     // tensao em mV, 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
    Serial.print("resistencia FSR em ohms = ");
    Serial.println(fsrResistance);
 
    fsrConductance = 1000000;
    fsrConductance /= fsrResistance;
    Serial.print("Condutância em uS: ");
    Serial.println(fsrConductance);
 
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Força em Newtons: ");
      Serial.println(fsrForce);      
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Força em Newtons: ");
      Serial.println(fsrForce);            
    }
  }
  Serial.println("--------------------");
  delay(1000);
}
