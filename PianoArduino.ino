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

  // juegoActivo = false;
  juegoActivo = true;
  juegoPerdido = false;
}

void esperarParaVolverAJugar() {
  Serial.println("esperarParaVolverAJugar");
  unsigned long contadorTiempo = millis() + TIEMPO_DE_ESPERA;
  boolean pararJuego = true;

  while(pararJuego) {
    if (juego_chequearTeclas() != 0 || contadorTiempo < millis()) {
      pararJuego = false;
    }
  }
}

void probarSonidos() {
  // Serial.println("1");
  // sonido_playNota(1);
  // delay(5000);
  // Serial.println("2");
  // sonido_playNota(2);
  // delay(5000);
  // Serial.println("3");
  // sonido_playNota(3);
  // delay(5000);
  // Serial.println("4");
  // sonido_playNota(4);
  // delay(5000);
  // Serial.println("5");
  // sonido_playNota(5);
  // delay(5000);
  // Serial.println("6");
  // sonido_playNota(6);
  // delay(5000);
  // Serial.println("7");
  // sonido_playNota(7);
  // delay(5000);
  // Serial.println("8");
  // sonido_playNota(8);
  // delay(5000);
  // Serial.println("9");
  // sonido_playNota(9);
  // delay(5000);
  // Serial.println("10");
  // sonido_playNota(10);
  // delay(5000);
  // Serial.println("11");
  // sonido_playNota(11);
  // delay(5000);
  // Serial.println("12");
  // sonido_playNota(12);
  // delay(5000);
  // Serial.println("13");
  // sonido_playNota(13);
  // delay(5000);
  // Serial.println("14");
  // sonido_playNota(14);
  // delay(5000);
  // Serial.println("15");
  // sonido_playNota(15);
  // delay(5000);
  // Serial.println("16");
  // sonido_playNota(16);
  // delay(5000);
  // Serial.println("17");
  // sonido_playNota(17);
  // delay(5000);
  // Serial.println("18");
  // sonido_playNota(18);
  // delay(5000);
  // Serial.println("19");
  // sonido_playNota(19);
  // delay(5000);
  // Serial.println("20");
  // sonido_playNota(20);
  // delay(5000);
  // Serial.println("21");
  // sonido_playNota(21);
  // delay(5000);
  // Serial.println("22");
  // sonido_playNota(22);
  // delay(5000);

  Serial.println("23");
  sonido_playNota(23);
  delay(5000);
  // Serial.println("24");
  // sonido_playNota(24);
  // delay(5000);
  Serial.println("25");
  sonido_playNota(25);
  delay(5000);
  // Serial.println("26");
  // sonido_playNota(26);
  // delay(5000);
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
  // probarSonidos();
  
  if (!juegoActivo) {
    esperaSignalInicioJuego();

  } else {
    // Juego inicializado
    Serial.println("//////////////////////////////////////");
    Serial.println("//////////////////////////////////////");
    Serial.println("/////////// INICIO JUEGO /////////////");
    Serial.println("//////////////////////////////////////");
    Serial.println("//////////////////////////////////////");

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
        Serial.println("//////////////////////////////////////");
        Serial.println("//////// Volvemos a Jugar ////////////");
        Serial.println("//////////////////////////////////////");
      }
    }
  }

}
