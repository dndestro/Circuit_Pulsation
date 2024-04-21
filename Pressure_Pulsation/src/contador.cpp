#include "contador.h"

Contador::Contador(){
    
}

void Contador::configContador(uint32_t valTarget, uint32_t valInicial, uint8_t contAscend){
    cValorAtual = valInicial;
    cValorTarget = valTarget;
    cSentContagem = contAscend;
}

void Contador::setValorAtual(uint32_t valor){
    contAtingida = false;
    cValorAtual = valor;
}

void Contador::setValorTarget(uint32_t valor){
    cValorTarget = valor;
}

void Contador::setSentContagem(uint8_t sentido){
    cSentContagem = sentido;
}

uint32_t Contador::getValorAtual(){
    return cValorAtual;
}

uint32_t Contador::getValorTarget(){
    return cValorTarget;
}

byte Contador::getSentidoContagem(){
    return cSentContagem;
}

uint32_t Contador::atContagem(uint32_t passo){
    if( cSentContagem ){
        cValorAtual += passo;
        if( cValorAtual >= cValorTarget ){
            cValorAtual = cValorTarget;
            contAtingida = true;
        }
    }
    else{
        cValorAtual -= passo;
        if( cValorAtual <= cValorTarget ){
            cValorAtual = cValorTarget;
            contAtingida = true;
        }
    }
    return cValorAtual;
}