#include <Arduino.h>

#define TEMPODEBOUNCEPADRAO 10

class Botao {
    uint8_t cPino;
    uint16_t cLastDebounceTime = 0;
    uint16_t cDebounceTime = 0;
    uint8_t cLastEstadoBtn = 0;

    public:
        Botao();
        Botao(uint8_t pino, uint8_t pullUp, uint16_t debounceTime = TEMPODEBOUNCEPADRAO);
        void configBotao(uint8_t pino, uint8_t pullUp, uint16_t debounceTime = TEMPODEBOUNCEPADRAO); // 1ms for debounce as default
        int getState();
};