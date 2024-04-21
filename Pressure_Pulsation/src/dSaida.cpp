#include "dSaida.h"

dSaida::dSaida(){
    
}

int dSaida::getSaida(){
    cEstado = digitalRead(cPino);
    return cEstado;
}

byte dSaida::setSaida(uint8_t valor){
    digitalWrite(cPino, valor);
    cEstado = valor;
    delayMicroseconds(10);
    if( cEstado == getSaida()) {
        return 0; //Sucesso
    }
    else {
        return -1; //Erro
    }
}

byte dSaida::togSaida(){
    return setSaida(!cEstado);
}

void dSaida::configPino(uint8_t pino){
    cPino = pino;
    cEstado = 0;
    pinMode(cPino, OUTPUT);
}