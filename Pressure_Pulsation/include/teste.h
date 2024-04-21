#include "contador.h"
#include "dSaida.h"

#define TESTEPAUSDADO   0
#define TESTERODANDO    1
#define TESTEFINALIZADO 2
#define CONTAGEMSCEND   1

class Teste{
    uint8_t cTesteRodando = 0;
    dSaida bobina1;
    dSaida bobina2;
    Contador cTeste;
    uint8_t maqEstado = 0;


    public:
        Teste(uint8_t pinoBobina1,
              uint8_t pinoBobina2,
              uint32_t ciclosTeste);

        void setCiclosTesteTarget(uint32_t ciclos);
        void setContagemAtual(uint32_t valorAtual);
        void setTestStatus(uint8_t status); // 0 = sparado 1 = rodando
        uint8_t getTestStatus();
        uint32_t getCiclosTarget();
        uint32_t getCiclosTeste();
        void executaCicloTeste();
};