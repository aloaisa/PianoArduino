#include "Arduino.h"
#include "configuration.h"
#include "velas.h"
#include "juego.h"

boolean juegoActivo;
boolean juegoPerdido;

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
  juegoPerdido = false;
}

void esperarParaVolverAJugar() {
  unsigned long contadorTiempo = millis() + TIEMPO_DE_ESPERA;
  boolean pararJuego = true;

  while(pararJuego) {
    if (chequearTeclas() != 0 || contadorTiempo < millis()) {
      pararJuego = false;
    }
  }
}

void loop() {

  if (!juegoActivo) {
    // Esperando a inicializar el juego
    // Que hay que chequear? para cambiar juegoActivo a true?

  } else {
    // Juego inicializado

    // Controlamos que si pierden se vuelva a activar el juego a los 30s
    // o cuando toquen cualquier tecla.
    while(!juegoPerdido) {

      velas_EncendidoVelas();

      if (juego_inicarJuego()) {
        // Se ha ganado el juego
        juegoActivo = false;
        juegoPerdido = false;
        
      } else {
        // Se ha perdido el juego
        esperarParaVolverAJugar();
      }
    }
  }

}
