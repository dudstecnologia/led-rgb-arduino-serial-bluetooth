class LedRgb {
  private:
    byte rPin, gPin, bPin;
  public:
    LedRgb () {}

    LedRgb (byte r, byte g, byte b) {
      this->rPin = r;
      this->gPin = g;
      this->bPin = b;

      pinMode(this->rPin, OUTPUT);
      pinMode(this->gPin, OUTPUT);
      pinMode(this->bPin, OUTPUT);
    }

    void acionaRgb (int r, int g, int b) {
      analogWrite(this->rPin, r);
      analogWrite(this->gPin, g);
      analogWrite(this->bPin, b);
    }
};

LedRgb* ledRgb = new LedRgb[2];

void setup() {
  Serial.begin(9600);
  ledRgb[0] = LedRgb(3, 5, 6);
  ledRgb[1] = LedRgb(9, 10, 11);
}

void loop() {
  if (Serial.available()) {
    String valorSerial;
    while(Serial.available()) {
      valorSerial += (char) Serial.read();
      delay(10);
    }

    processarDados(valorSerial);
  }
}

void processarDados (String serial) {
  int valor[4];
  int indice = 0;
  String temp;

  for (int i = 0; i < serial.length(); i++) {
    if (serial.charAt(i) != ',') {
      temp += serial.charAt(i);
    }

    if (serial.charAt(i) == ',' || i == (serial.length() - 1)) {
      valor[indice] = temp.toInt();
      temp = "";
      indice++;
    }
  }

  Serial.println(valor[0]);
  Serial.println(valor[1]);
  Serial.println(valor[2]);
  Serial.println(valor[3]);

  ledRgb[valor[0]].acionaRgb(valor[1], valor[2], valor[3]);
}
