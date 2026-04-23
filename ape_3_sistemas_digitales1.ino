const int pinCanal1 = 2; // 555
const int pinCanal2 = 3; // Flip-Flop

void setup() {
  Serial.begin(9600);
  pinMode(pinCanal1, INPUT);
  pinMode(pinCanal2, INPUT);
}

void loop() {
  // --- LEER CANAL 1 (555) ---
  float frec1, duty1;
  medirSenal(pinCanal1, frec1, duty1);
  
  // --- LEER CANAL 2 (Flip-Flop) ---
  float frec2, duty2;
  medirSenal(pinCanal2, frec2, duty2);

  // --- IMPRIMIR RESULTADOS ---
  Serial.print("555 | Frec: "); Serial.print(frec1, 2); 
  Serial.print(" Hz | Duty: "); Serial.print(duty1, 1); Serial.println(" %");
  
  Serial.print("FF  | Frec: "); Serial.print(frec2, 2); 
  Serial.print(" Hz | Duty: "); Serial.print(duty2, 1); Serial.println(" %");
  Serial.println("-------------------------");

  delay(1000); // Esperamos 1 segundo antes de volver a medir
}

// Función auxiliar usando pulseIn()
void medirSenal(int pin, float &frecuencia, float &duty) {
  // Medimos el tiempo en microsegundos que la señal está en ALTO y en BAJO
  unsigned long tHigh = pulseIn(pin, HIGH, 1000000); // Espera máxima de 1 seg
  unsigned long tLow = pulseIn(pin, LOW, 1000000);

  unsigned long periodoMicros = tHigh + tLow;

  if (periodoMicros > 0) {
    // Frecuencia = 1 segundo (1,000,000 micros) / periodo
    frecuencia = 1000000.0 / periodoMicros;
    // Duty cycle = (Tiempo en alto / Periodo total) * 100
    duty = ((float)tHigh / periodoMicros) * 100.0;
  } else {
    // Si no hay pulsos (0 Hz)
    frecuencia = 0;
    duty = 0;
  }
}