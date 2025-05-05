#include <stdio.h>

void calculo_aritmetico() {
    int contador = 0;
    while (contador < 2147483647) {
        contador = contador + 1;
    }
}

int main() {
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();

    return 0;
}