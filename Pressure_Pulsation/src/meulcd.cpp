#include "meulcd.h"

MeuLCD::MeuLCD(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : LiquidCrystal(rs, enable, d4, d5, d6, d7){}

void MeuLCD::printLcdTest(uint8_t linha, uint8_t coluna, String msg){
    setCursor(coluna, linha);
    print(msg);
}

void MeuLCD::print2Msg(uint8_t linha, uint8_t col1, String msg1, uint8_t col2, String msg2){
    setCursor(col1, linha);
    print(msg1);
    setCursor(col2, linha);
    print(msg2);
}