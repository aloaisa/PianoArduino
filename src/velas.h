void velas_EncendidoVelas() {
    Serial.println("velas_EncendidoVelas");
    digitalWrite(PIN_VELAS, HIGH);
}

void velas_ApagadoVelas() {
    Serial.println("velas_ApagadoVelas");
    digitalWrite(PIN_VELAS, LOW);
}

void velas_aciertoEfectoVelas() {
    Serial.println("velas_aciertoEfectoVelas");

    digitalWrite(PIN_VELAS, LOW);
    delay(250);
    digitalWrite(PIN_VELAS, HIGH);
    delay(250);
    digitalWrite(PIN_VELAS, LOW);
    delay(250);
    digitalWrite(PIN_VELAS, HIGH);
    delay(250);
    digitalWrite(PIN_VELAS, LOW);
    delay(250);
    digitalWrite(PIN_VELAS, HIGH);
    delay(250);
    digitalWrite(PIN_VELAS, LOW);
    delay(250);
    digitalWrite(PIN_VELAS, HIGH);
    delay(250);
    digitalWrite(PIN_VELAS, LOW);
    delay(250);
    digitalWrite(PIN_VELAS, HIGH);
}

void velas_falloEfectoVelas() {
    Serial.println("velas_falloEfectoVelas");
    digitalWrite(PIN_VELAS, LOW);
    delay(500);
    digitalWrite(PIN_VELAS, HIGH);
    delay(1500);
    digitalWrite(PIN_VELAS, LOW);
}