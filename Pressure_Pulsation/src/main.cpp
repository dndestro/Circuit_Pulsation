#include <Arduino.h>
//#include <LiquidCrystal.h>
#include "meulcd.h"
#include "teste.h"
#include "botao.h"
#include "timer.h"

//-----  DEFINITIONS -----
#define PINOBTNLIGA   53
#define PINOSOMA100K  31
#define PINOSOMA10K   33
#define PINOSOMA500   35
#define PINOFALHA     37
#define PINBOBINA1    LED_BUILTIN  
#define PINBOBINA2    22

//LCD PINS
#define RS          51
#define EN          49
#define D4          41
#define D5          43
#define D6          45
#define D7          47
#define ULTIMACOL   15


#define INC100K 100000
#define INC10K  10000
#define INC500  500

#define CICLOPADRAO   20
#define CICLOSMAXIMOS 1000000
#define TEMPOBOBINA   500

#define TEMPOFUNC2BOTAO 4   // Tempo de espera = TEMPOFUNC2BOTAO * 500ms

// ----- VARIAVEIS GLOBAIS -----
Botao ligaTeste;
Botao soma100K;
Botao soma10K;
Botao soma500;
Botao falha;
uint8_t flagBotao = 0; //identifica se tem algum botao pressionado
uint8_t contaTempoBotaoPress = 0; // conta o tempo que o botao ficou pressionado

Teste teste(PINBOBINA1, PINBOBINA2, CICLOPADRAO);
Timer *timer500ms = new Timer(TEMPOBOBINA);
MeuLCD lcd(RS, EN, D4, D5, D6, D7);

// variáveis para reconhecimento da borda de descida da chave de controle do teste
int chave = 0;
int prevChave = 1; //Start in one because the PULLUP Resistor is ON

// REMOVER ESTAS VARIÁVEIS AUXILIARES
unsigned long temp = 0, lastTemp = 0;

// ----- FUNCOES GLOBAIS -----

void exibeMsg(const char texto[100], long valor){
  Serial.print(texto);
  Serial.println(valor);
}

void fTimerTempoCiclo(){
  //exibeMsg("Tempo: ", (temp - lastTemp));

  if(teste.getTestStatus() == TESTERODANDO){
    teste.executaCicloTeste();
    //Serial.println("Passou");
  }
  lastTemp = millis();

  if(flagBotao){
    contaTempoBotaoPress++;
  }
}

void setup() {
  uint8_t col = 0;
  
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  
  //config de botoes
  ligaTeste.configBotao(PINOBTNLIGA, INPUT_PULLUP);
  soma100K.configBotao(PINOSOMA100K, INPUT_PULLUP);
  soma10K.configBotao(PINOSOMA10K, INPUT_PULLUP);
  soma500.configBotao(PINOSOMA500, INPUT_PULLUP);
  falha.configBotao(PINOFALHA, INPUT_PULLUP);

  //Config do timer
  timer500ms->setOnTimer(&fTimerTempoCiclo);
  timer500ms->Start();

  //Config do Teste
  teste.setCiclosTesteTarget(CICLOPADRAO);
  teste.setContagemAtual(0);

  //Config do LCD
  lcd.begin(16, 4);
  delay(1);
  lcd.printLcdTest(0, 0, "ENG EXPERIMENTAL");
  lcd.printLcdTest(1, 0, "STATUS: PAUSADO");
  
  col = (uint8_t) ULTIMACOL - (uint8_t)log10(CICLOPADRAO);
  lcd.print2Msg(2, 0, "PROG: ", col, (String) CICLOPADRAO);
  
  lcd.print2Msg(3, 0, "EXEC: ", 15, (String) 0);
}

//----- FUNCAO PRINCIPAL -----

void loop() {
  
  // Cria uma flag geral para indicar que tem um botao pressionado
  // e uma flag para cada botao
  
  static uint8_t flagSoma100K = 0;
  static uint8_t flagSoma10K = 0;
  static uint8_t flagSoma500 = 0;

  uint8_t col = 0; // coluna do LCD
  uint32_t ciclosContados = 0; //armazena os ciclos contados de teste para exibir no LCD

  // ---------------------------------------------

  // Somente executa algo se não estiver em falha
  if(!falha.getState()){
    chave = ligaTeste.getState();
    //exibeMsg("Chave = ", chave);

    //verifica borda de descida no botao de ligar teste
    if((!chave) && (prevChave)){
      
      if(teste.getTestStatus() != TESTEFINALIZADO){
        
        // Faz o Toggle do status do teste Rodando ou Parado
        if(teste.getTestStatus() == TESTEPAUSDADO){
          teste.setTestStatus(TESTERODANDO);
          lcd.printLcdTest(1, 0, "SATUS: RODANDO");
        }
        else{
          teste.setTestStatus(TESTEPAUSDADO);
          lcd.printLcdTest(1, 0, "STATUS: PAUSADO");
        }
      }
    }
    prevChave = chave;  //necessario para garantir que o botao liga/desliga faca o toggle do ligaCiclo
    
    if(teste.getTestStatus() == TESTEFINALIZADO){
      lcd.printLcdTest(1, 0, "STATUS: FIM     ");
    }


    temp = millis();
    timer500ms->Update();

    ciclosContados = teste.getCiclosTeste();
    col = (uint8_t) ULTIMACOL - (uint8_t)log10(ciclosContados);
    lcd.printLcdTest(3, col, (String) ciclosContados);

    if(teste.getTestStatus() == TESTEPAUSDADO){
          
      // --------- Botao de 100K -----------------
      if(!soma100K.getState() && !flagBotao){
        flagBotao = 1;
        flagSoma100K = 1;
        teste.setCiclosTesteTarget(teste.getCiclosTarget() + INC100K);

        if(teste.getCiclosTarget() > CICLOSMAXIMOS){
          teste.setCiclosTesteTarget(CICLOSMAXIMOS);
        }
        col = (uint8_t) ULTIMACOL - (uint8_t)log10(teste.getCiclosTarget());
        lcd.printLcdTest(2, col, (String) teste.getCiclosTarget());
      }
      else if(soma100K.getState() && flagSoma100K){
        flagBotao = 0;
        flagSoma100K = 0;
      }

      // --------- Botao de 10K --------------------
      if(!soma10K.getState() && !flagBotao){
        flagBotao = 1;
        flagSoma10K = 1;
        contaTempoBotaoPress = 0;
      }

      if(!soma10K.getState() && flagSoma10K){
        if(contaTempoBotaoPress >= TEMPOFUNC2BOTAO){
          teste.setContagemAtual(0);
          lcd.printLcdTest(3, 15, (String) 0);
        }
      }

      if(soma10K.getState() && flagSoma10K){
        
        if(contaTempoBotaoPress <= TEMPOFUNC2BOTAO){
          exibeMsg("Teste Pausado = ", soma10K.getState());
          teste.setCiclosTesteTarget(teste.getCiclosTarget() + INC10K);
          
          if(teste.getCiclosTarget() > CICLOSMAXIMOS){
            teste.setCiclosTesteTarget(CICLOSMAXIMOS);
          }
          col = (uint8_t) ULTIMACOL - (uint8_t)log10(teste.getCiclosTarget());
          lcd.printLcdTest(2, col, (String) teste.getCiclosTarget());
        }

        flagBotao = 0;
        flagSoma10K = 0;
      }

      // ------------- Botao de 500 --------------------
      
      if(!soma500.getState() && !flagBotao){
        flagBotao = 1;
        flagSoma500 = 1;
        contaTempoBotaoPress = 0;
      }

      if(!soma500.getState() && flagSoma500){
        if(contaTempoBotaoPress >= TEMPOFUNC2BOTAO){
          teste.setCiclosTesteTarget(0);
          lcd.printLcdTest(2, 0, "PROG:          0");
        }
      }

      if(soma500.getState() && flagSoma500){
        if(contaTempoBotaoPress <= TEMPOFUNC2BOTAO){
          teste.setCiclosTesteTarget(teste.getCiclosTarget() + INC500);
          
          if(teste.getCiclosTarget() > CICLOSMAXIMOS){
            teste.setCiclosTesteTarget(CICLOSMAXIMOS);
          }
          col = (uint8_t) ULTIMACOL - (uint8_t)log10(teste.getCiclosTarget());
          lcd.printLcdTest(2, col, (String) teste.getCiclosTarget());
        }
        flagBotao = 0;
        flagSoma500 = 0;
      }
    }
  }
  else {
      lcd.printLcdTest(1, 0, "STATUS:  FALHA  ");
  }
}