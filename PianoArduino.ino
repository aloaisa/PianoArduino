#include "Arduino.h"
#include "configuration.h"
#include "velas.h"
#include "juego.h"

boolean juegoActivo;

void setup() {
  Serial.println("Init nano...");
  Serial.begin(BAUDS);

  Serial.println("initialize Pins...");

  // 11 notas
  // pinMode(EYES_LED_PIN, OUTPUT);
  // pinMode(ON_PIN, INPUT_PULLUP);

  // Configuramos el sonido

  // juegoActivo = false;
  juegoActivo = true;
}

void loop() {

  if (!juegoActivo) {
    // Esperando a inicializar el juego
    // Que hay que chequear? para cambiar juegoActivo a true?

  } else {
    // Juego inicializado

    velas_EncendidoVelas();
    juego_inicarJuego();

    // Se terminó la partida
    juegoActivo = false;
  }

}
