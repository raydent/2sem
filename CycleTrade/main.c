// #include "cl-impl.h"
#include "trade.h"
int main(){
    int summ = 0;
    int amount = 0;
    FILE* source = fopen("009.dat", "r");
    int* money = readFile(&amount, &summ, source);
    bestTrade(money, amount, summ);
    fclose(source);
}
