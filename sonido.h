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
    soundDFPlayer.play(25);
    // soundDFPlayer.play(12);
}

void sonido_playNota(int nota) {
    Serial.println("sonido_playNota");
    
    // Esto es solo por que no me coge los mp3 pares
    if ( nota % 2 == 0) {
        nota = nota + 1;
    }

    soundDFPlayer.play(nota);
}

void sonido_sonidoGanar() {
    Serial.println("sonido_sonidoGanar");
    // soundDFPlayer.play(13);
    soundDFPlayer.play(23);
}