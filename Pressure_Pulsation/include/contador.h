#include <Arduino.h>

#define DOWN 0
#define UP 1

class Contador{
    uint32_t cValorAtual;
    uint32_t cValorTarget;
    uint8_t cSentContagem;

    public:
        uint8_t contAtingida;
        Contador();
        void configContador(uint32_t valTarget, uint32_t valInicial = (uint32_t)0, uint8_t contAscend = (uint8_t)1);
        void setValorAtual(uint32_t valor);
        void setValorTarget(uint32_t valor);
        void setSentContagem (uint8_t sentido);
        uint32_t getValorAtual();
        uint32_t getValorTarget();
        uint8_t getSentidoContagem();
        uint32_t atContagem(uint32_t passo = 1); //incrementa ou decrementa o valor atual da contagem
};