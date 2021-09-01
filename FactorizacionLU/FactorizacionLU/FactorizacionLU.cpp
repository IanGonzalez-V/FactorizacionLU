#include <iostream>
#include <locale.h>

void alertNotification(int min, int max) {

    printf("\033[1;31m"); // Cambiar Texto Color Rojo
    printf("¡El número debe pertenecer al rango: [%d-%d]!\n", min, max);
    printf("\033[0m"); // Reset Color
}

bool inRange(unsigned x, int min, int max) {
    return (x - min) <= (max - min);
}

int main()
{
    setlocale(LC_ALL, ""); // Función para que se impriman las tildes

    int x = 15, min = 4, max = 10;
    if (!inRange(x, min, max)) {
        alertNotification(min, max);
    }
}
