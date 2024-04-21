#include "botao.h"

Botao::Botao(){
}

Botao::Botao(uint8_t pino, uint8_t pullUp, uint16_t debounceTime){
    if (pullUp == INPUT_PULLUP) {
        pinMode(pino, INPUT_PULLUP);
    }
    else {
        pinMode(pino, INPUT);
    }
    cPino = pino;
    cDebounceTime = debounceTime;
}

void Botao::configBotao(uint8_t pino, uint8_t pullUp, uint16_t debounceTime){ // 1ms for debounce as default{
    if (pullUp == INPUT_PULLUP) {
        pinMode(pino, INPUT_PULLUP);
    }
    else {
        pinMode(pino, INPUT);
    }
    cPino = pino;
    cDebounceTime = debounceTime;
}

int Botao::getState() {
    int estadobtn = digitalRead(cPino);

    while(1) {
        if (estadobtn != cLastEstadoBtn) {
        cLastDebounceTime = millis();
        }

        if ((millis() - cLastDebounceTime) > cDebounceTime) {
            return estadobtn;
        }
        cLastEstadoBtn = estadobtn;
    }
}