#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include "src/configuration.h"
#include "src/sonido.h"
#include "src/velas.h"
#include "src/juego.h"

boolean juegoActivo;
boolean juegoPerdido;

void setup() {
  Serial.println("Init nano...");
  Serial.begin(BAUDS);

  Serial.println("initialize Pins...");

  // 11 notas
  pinMode(PIN_NOTA_1, INPUT_PULLUP);
  pinMode(PIN_NOTA_2, INPUT_PULLUP);
  pinMode(PIN_NOTA_3, INPUT_PULLUP);
  pinMode(PIN_NOTA_4, INPUT_PULLUP);
  pinMode(PIN_NOTA_5, INPUT_PULLUP);

  pinMode(PIN_NOTA_6, INPUT_PULLUP);
  pinMode(PIN_NOTA_7, INPUT_PULLUP);
  pinMode(PIN_NOTA_8, INPUT_PULLUP);
  pinMode(PIN_NOTA_9, INPUT_PULLUP);
  pinMode(PIN_NOTA_10, INPUT_PULLUP);

  pinMode(PIN_NOTA_11, INPUT_PULLUP);

  pinMode(PIN_VELAS, OUTPUT);
  pinMode(PIN_INICIO, INPUT_PULLUP);

  velas_ApagadoVelas();
  sonido_inicializarSonido();

  juegoActivo = false;
  juegoPerdido = false;
}

void esperarParaVolverAJugar() {
  Serial.println("esperarParaVolverAJugar");
  unsigned long contadorTiempo = millis() + TIEMPO_DE_ESPERA;
  boolean pararJuego = true;

  while(pararJuego) {
    if (chequearTeclas() != 0 || contadorTiempo < millis()) {
      pararJuego = false;
    }
  }
}

void esperaSignalInicioJuego() {
  Serial.println("esperaSignalInicioJuego");

  boolean signalInicio = false;  
  while(!signalInicio) {
    int activateSignal = digitalRead(PIN_INICIO);
    if (activateSignal == HIGH) {
      signalInicio = true;
    }
  }

  juegoActivo = true;
}    

void loop() {

  if (!juegoActivo) {
    esperaSignalInicioJuego();

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
