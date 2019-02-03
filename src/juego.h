unsigned long contadorTiempoAbandono;

int juego_chequearTeclas() {
    Serial.println("juego_chequearTeclas");
    
    // Leer el pulsador de teclas a ver cual se ha pulsado de todas
    int nota1 = digitalRead(PIN_NOTA_1);
    int nota2 = digitalRead(PIN_NOTA_2);
    int nota3 = digitalRead(PIN_NOTA_3);
    int nota4 = digitalRead(PIN_NOTA_4);
    int nota5 = digitalRead(PIN_NOTA_5);
    int nota6 = digitalRead(PIN_NOTA_6);
    int nota7 = digitalRead(PIN_NOTA_7);
    int nota8 = digitalRead(PIN_NOTA_8);
    int nota9 = digitalRead(PIN_NOTA_9);
    int nota10 = digitalRead(PIN_NOTA_10);
    int nota11 = digitalRead(PIN_NOTA_11);

    if (nota1 == HIGH) {
        return 1;
    } else if (nota2 == HIGH) {
        return 2;
    } else if (nota3 == HIGH) {
        return 3;
    } else if (nota4 == HIGH) {
        return 4;
    } else if (nota5 == HIGH) {
        return 5;
    } else if (nota6 == HIGH) {
        return 6;
    } else if (nota7 == HIGH) {
        return 7;
    } else if (nota8 == HIGH) {
        return 8;
    } else if (nota9 == HIGH) {
        return 9;
    } else if (nota10 == HIGH) {
        return 10;
    } else if (nota11 == HIGH) {
        return 11;
    }

    return 0; // 0 es el valor en el caso de que no devolvamos nada
}

int obtenerTeclaPulsada() {
    Serial.println("obtenerTeclaPulsada");

    int teclaPulsada;
    boolean waiting = true;

    while(waiting) {
        teclaPulsada = juego_chequearTeclas();
        if (teclaPulsada != 0) {
            waiting = false;
        }

        if (contadorTiempoAbandono < millis()) {
            sonido_playSonidoError();
            velas_falloEfectoVelas();
            delay(2000);
            waiting = false;
        }
    }

    return teclaPulsada;
}

boolean siguienteTeclaValida(int teclaPulsada, int posicionAChequear) {
    Serial.println("siguienteTeclaValida");
    // Chequeamos si la tecla pulsada es la siguiente a pulsar en el juego
    return NOTAS_VALIDAS[posicionAChequear] == teclaPulsada;
}

void iniciarContadorAbandono() {
    contadorTiempoAbandono = millis() + TIEMPO_DE_ABANDONO;
}

void pulsadoTeclaValida(int teclaPulsada) {
    Serial.println("//////////////////////////////////////");
    Serial.println("////////// Tecla Valida //////////////");
    Serial.println("//////////////////////////////////////");

    sonido_playNota(teclaPulsada);
    velas_aciertoEfectoVelas();
    iniciarContadorAbandono();
}

void pulsadoTeclaNoValida(int teclaPulsada) {
    Serial.println("//////////////////////////////////////");
    Serial.println("/////// Tecla NO Valida //////////////");
    Serial.println("//////////////////////////////////////");
    
    sonido_playNota(teclaPulsada);
    delay(2000);
    sonido_playSonidoError();
    velas_falloEfectoVelas();
    delay(2000);
    
}

void juegoGanado() {
    Serial.println("JuegoGanado");
    sonido_sonidoGanar();
    velas_aciertoEfectoVelas();
    velas_aciertoEfectoVelas();
    velas_aciertoEfectoVelas();
    delay(2000);
}

boolean juego_inicarJuego() {
    Serial.println("juego_inicarJuego");

    boolean resultWin = false;
    int posicionAChequear = 0;
    boolean juegoActivo = true;

    // La 1º vez esperamos también 7 segundos para fallar?
    iniciarContadorAbandono();

    while (juegoActivo) {

        int teclaPulsada = obtenerTeclaPulsada();
        if (teclaPulsada != 0) {
            Serial.print("Tecla pulsada: ");
            Serial.println(teclaPulsada);

            if (siguienteTeclaValida(teclaPulsada, posicionAChequear)) {
                pulsadoTeclaValida(teclaPulsada);
                posicionAChequear++;
                
                if (posicionAChequear == (sizeof(NOTAS_VALIDAS) / sizeof(int))) {
                    juegoGanado();
                    juegoActivo = false;
                    resultWin = true;
                }

            } else {
                pulsadoTeclaNoValida(teclaPulsada);
                juegoActivo = false; // Fin juego
            }

        } else {
            Serial.println("Tiempo de abandono sobrepasado");
            juegoActivo = false;
        }
    }

    Serial.println("El juego ha finalizado");
    return resultWin;
}
