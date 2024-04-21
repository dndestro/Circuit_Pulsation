#include <Arduino.h>

class dSaida {
    uint8_t cPino;
    int cEstado;

    public:
        dSaida();
        byte setSaida(uint8_t valor);
        int getSaida();
        byte togSaida();
        void configPino(uint8_t pino);
};