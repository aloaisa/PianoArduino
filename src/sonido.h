DFRobotDFPlayerMini soundDFPlayer;
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX

void sonido_inicializarSonido() {
    Serial.println("sonido_inicializarSonido");

    soundSoftwareSerial.begin(BAUDS);
    if (!soundDFPlayer.begin(soundSoftwareSerial)) {
        while (true)
        ;
    }

    soundDFPlayer.volume(SOUND_VOLUME);
}

void sonido_playSonidoError() {
    Serial.println("sonido_playSonidoError");
    soundDFPlayer.play(12);
}

void sonido_playNota(int nota) {
    Serial.println("sonido_playNota");
    soundDFPlayer.play(nota);
}

void sonido_sonidoGanar() {
    Serial.println("sonido_sonidoGanar");
    soundDFPlayer.play(13);
}