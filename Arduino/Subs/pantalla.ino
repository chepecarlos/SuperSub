
byte const segmentClock = 17;
byte const segmentLatch = 16; //
byte const segmentData = 5; // SER

byte const cantidadDigitos = 5;

void InicializarPantallas() {

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);
}

void mostarNumeros(float valor) {
  int numero = abs(valor);

  for (byte x = 0 ; x < cantidadDigitos ; x++)  {
    int resto = numero % 10;
    if (numero == 0) {
      enviarNumero(' ', false);
    } else {
      enviarNumero(resto, false);
    }
    numero /= 10;
  }

  digitalWrite(segmentLatch, LOW);
  digitalWrite(segmentLatch, HIGH);
}


void enviarNumero(byte numero, boolean decimal) {
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define a  1<<0
#define b  1<<6
#define c  1<<5
#define d  1<<4
#define e  1<<3
#define f  1<<1
#define g  1<<2
#define dp 1<<7

  byte segmentos;

  switch (numero)
  {
    case 1: segmentos = b | c; break;
    case 2: segmentos = a | b | d | e | g; break;
    case 3: segmentos = a | b | c | d | g; break;
    case 4: segmentos = f | g | b | c; break;
    case 5: segmentos = a | f | g | c | d; break;
    case 6: segmentos = a | f | g | e | c | d; break;
    case 7: segmentos = a | b | c; break;
    case 8: segmentos = a | b | c | d | e | f | g; break;
    case 9: segmentos = a | b | c | d | f | g; break;
    case 0: segmentos = a | b | c | d | e | f; break;
    case ' ': segmentos = 0; break;
    case 'c': segmentos = g | e | d; break;
    case '-': segmentos = g; break;
  }

  if (decimal) segmentos |= dp;

  for (byte x = 0 ; x < 8 ; x++)  {
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, segmentos & 1 << (7 - x));
    digitalWrite(segmentClock, HIGH);
  }
}
