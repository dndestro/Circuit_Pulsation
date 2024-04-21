#include "teste.h"


Teste::Teste( uint8_t pinoBobina1,
              uint8_t pinoBobina2,
              uint32_t ciclosTeste){

    bobina1.configPino(pinoBobina1);
    bobina2.configPino(pinoBobina2);
    cTeste.configContador(ciclosTeste, 0, CONTAGEMSCEND); //inicia contador em zero, conta ate ciclosTeste, contagem ascendente
}

void Teste::setCiclosTesteTarget(uint32_t ciclos){
    cTeste.setValorTarget(ciclos);
}

void Teste::setContagemAtual(uint32_t valorAtual){
    cTeste.setValorAtual(valorAtual);
}

void Teste::setTestStatus(uint8_t status){
    cTesteRodando = status;
    if(status != TESTERODANDO){
        maqEstado = 0;
        bobina1.setSaida(LOW);
        bobina2.setSaida(LOW);
    }
}

uint8_t Teste::getTestStatus(){
    return cTesteRodando;
}

uint32_t Teste::getCiclosTarget(){
    return cTeste.getValorTarget();
}

uint32_t Teste::getCiclosTeste(){
    return cTeste.getValorAtual();
}


void Teste::executaCicloTeste(){
  
  if(cTesteRodando == TESTERODANDO){
    if(!cTeste.contAtingida){
    
        if(maqEstado == 0){
            bobina1.setSaida(HIGH);
        }
        
        if(maqEstado == 1){
            bobina1.setSaida(LOW);
            delay(1);
            bobina2.setSaida(HIGH);
        }

        if(maqEstado == 2){
            bobina2.setSaida(LOW);
            delay(1);
            bobina1.setSaida(HIGH);
            maqEstado = 1;
            cTeste.atContagem();
        }
        else{
            maqEstado++;
        }
    }
    else{
        setTestStatus(TESTEFINALIZADO);
    }
    
  }
}