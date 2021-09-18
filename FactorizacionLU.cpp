#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

class Matriz {
    short n;
    short** matriz;
public:
    Matriz(short n) : n(n) {
        matriz = new short* [n];
        for (size_t i = 0; i < n; i++) {
            matriz[i] = new short[n];
            for (size_t j = 0; j < n; j++) {
                matriz[i][j] = rand() % 10;
                if (rand() % 2) matriz[i][j] *= -1;
            }
        }
        std::cout << "Matriz generada exitosamente\n";
    }
    ~Matriz() {
        for (size_t i = 0; i < n; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
    void Imprimir() {
        std::cout << "IMPRESIÓN: \n";
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (matriz[i][j] >= 100) std::cout << matriz[i][j] << " ";
                else if (matriz[i][j] >= 10) std::cout << " " << matriz[i][j] << " ";
                else if (matriz[i][j] >= 0) std::cout << "  " << matriz[i][j] << " ";
                else if (matriz[i][j] > -10) std::cout << " " << matriz[i][j] << " ";
                else if (matriz[i][j] > -100) std::cout << matriz[i][j] << " ";
                else std::cout << matriz[i][j];
            }
            std::cout << "\n";
        }
    }
    int EnPosicion(int i, int j) { return matriz[i][j]; }
    void CambiarEnPosicion(int i, int j, int n) { matriz[i][j] = n; }
};

void leer_bienvenida() {
    ifstream file("A.txt");
    if (file.is_open()) {
        SetConsoleOutputCP(CP_UTF8);
        string line;
        unsigned char aux;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        SetConsoleOutputCP(CP_UTF7);
    }
    file.close();
}

void alertNotification(int min, int max) {

    printf("\033[1;31m"); // Cambiar Texto Color Rojo
    printf("¡El número debe pertenecer al rango: [%d-%d]!\n\n", min, max);
    printf("\033[0m"); // Reset Color
}

bool inRangeVerification(unsigned x, int min, int max) {
    if ((x - min) <= (max - min)) return true;
    else {
        alertNotification(min, max);
        std::cout << "Vuelve a ingresar el número:\n";
        return false;
    }
}

void LUFactorization(int n, Matriz* A) {
    Matriz L = Matriz(n);
    Matriz U = Matriz(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (j < i)
                L.CambiarEnPosicion(j, i, 0);
            else {
                L.CambiarEnPosicion(j, i, A->EnPosicion(j, i));
                for (size_t k = 0; k < i; k++) {
                    L.CambiarEnPosicion(j, i, L.EnPosicion(j, i) - L.EnPosicion(j, k) * U.EnPosicion(k, i));
                }
            }
        }
        for (size_t j = 0; j < n; j++) {
            if (j < i)
                U.CambiarEnPosicion(i, j, 0);
            else if (j == i)
                U.CambiarEnPosicion(i, j, 1);
            else {
                U.CambiarEnPosicion(i, j, A->EnPosicion(i, j) / L.EnPosicion(i, i)); 
                for (size_t k = 0; k < i; k++) {
                    U.CambiarEnPosicion(i, j, U.EnPosicion(i, j) - ((L.EnPosicion(i, k) * U.EnPosicion(k, j)) / L.EnPosicion(i, i)));
                }
            }
        }
    }
    std::cout << "DESCOMPOSICIÓN LU\nMatriz L\n";
    L.Imprimir();
    std::cout << "\nMatriz U\n";
    U.Imprimir();
}

void boton_calcular(int n, Matriz* A) {
    cout << "\nPresiona ENTER para calcular la factorizacion LU de la matriz" << endl;
    if (getchar()) {
        LUFactorization(n, A);
    }
}

int main() {

    leer_bienvenida();
    setlocale(LC_ALL, ""); // Función para que se impriman las tildes
    srand(time(NULL));
    short n;

    std::cout << "\nIngrese el orden de la matriz a generar: \n";
    do { 
        std::cin >> n;
        cout << "\n";

    } while (!inRangeVerification(n, 4, 10));
    Matriz* A = new Matriz(n);
    A->Imprimir();

    if (getchar()) {
        boton_calcular(n, A);
    }

    delete A;
    return 0;
}
