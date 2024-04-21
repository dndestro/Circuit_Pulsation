#include <LiquidCrystal.h>

class MeuLCD : public LiquidCrystal{
    public:
        MeuLCD(uint8_t rs, uint8_t enable, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7);
        void printLcdTest (uint8_t linha, uint8_t coluna, String msg);
        void print2Msg(uint8_t linha, uint8_t col1, String msg1, uint8_t col2, String msg2);
};