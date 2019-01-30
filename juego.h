unsigned long contadorTiempoAbandono;

int chequearTeclas() {
    Serial.println("chequearTeclas");
    // Leer el pulsador de teclas a ver cual se ha pulsado de todas
    
    return 0; // 0 es el valor en el caso de que no devolvamos nada
}

int obtenerTeclaPulsada() {
    Serial.println("obtenerTeclaPulsada");

    int teclaPulsada;
    boolean waiting = true;

    while(waiting) {
        teclaPulsada = chequearTeclas();
        if (teclaPulsada != 0) {
            waiting = false;
        }

        if (contadorTiempoAbandono < millis()) {
            // Sonido feo
            velas_falloEfectoVelas();
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
    Serial.println("pulsadoTeclaValida");
    // Suena nota
    velas_aciertoEfectoVelas();
    iniciarContadorAbandono();
}

void pulsadoTeclaNoValida(int teclaPulsada) {
    Serial.println("pulsadoTeclaNoValida");
    
    // Suena nota
    delay(1000);
    // Sonido feo
    velas_falloEfectoVelas();
}

void juegoGanado() {
    Serial.println("JuegoGanado");

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
            Serial.println("Tecla válida pulsada: " + teclaPulsada);

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
