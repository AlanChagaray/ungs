#include <stdio.h>
#include <unistd.h> // sleep()

int validateOperation(int *typeoperation);
int validateNumber(int *num);
int operation(int typeoperation, int num1, int num2);
void estate_process();
int main() {

    int typeoperation;
    int num1, num2;

    printf("Elija una operación:\n");
    printf("1. Sumar\n");
    printf("2. Restar\n");
    printf("3. Multiplicar\n");
    printf("4. Dividir\n");
    if(validateOperation(&typeoperation) == 0){
        return 1;
    }

    printf("Ingrese primer número:\n");
    if(validateNumber(&num1) == 0){
        return 1;
    }
    
    printf("Ingrese segundo número:\n");
    if(validateNumber(&num2) == 0){
        return 1;
    }

    if(operation(typeoperation, num1, num2) == 0){
        return 1;
    }

    return 0;
}

int validateOperation(int *typeoperation){
    scanf("%d", typeoperation); 
    if(*typeoperation != 1 && *typeoperation != 2 && *typeoperation != 3 && *typeoperation != 4 ){
        printf("Error: Operación no válida. Por favor, ingrese un número de operación.\n");
        return 0;
    }
    return 1;
}
int validateNumber(int *num){
    if(scanf("%d", num) != 1){ 
        printf("Error: Entrada no válida. Por favor, ingrese un número entero.\n");
        return 0;
    }
    return 1;
}

int operation(int typeoperation,int num1,int num2){
    estate_process();
    sleep(15);
    switch(typeoperation){
        case 1:
            printf("La SUMA entre %d + %d = %d\n", num1, num2 ,num1 + num2);
            break;
        case 2:
            printf("La RESTA entre %d - %d = %d\n", num1, num2, num1 - num2);
            break;
        case 3:
            printf("La MULTIPLICACIÓN entre %d + %d = %d\n", num1, num2 , num1 * num2);
            break;
        case 4:
            if(num2 != 0){
                printf("La DIVISIÓN entre %d + %d = %d\n", num1, num2 , num1 / num2);
            }else{
                printf("Error: División por cero no permitida.\n");
            }
            break;
        default:
            printf("Error: Operación no válida.\n");
    }
}
void estate_process(){
    volatile long long int cont = 0;
    for(long long int i =0 ; i < 10000000000; ++i){
        cont += i;
    }
}