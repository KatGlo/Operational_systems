#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

void statyczna() {
    // Tworzenie zmiennej lokalnej o dużym rozmiarze na stosie
    double tablica[1000000];

    // Zatrzymywanie programu
    cout << "Funkcja statyczna - Naciśnij Enter, aby kontynuować...";
    cin.get();
}

void dynamiczna() {
    // Tworzenie dynamicznej tablicy o dużym rozmiarze na stercie
    double *tablica = new double[1000000];

    // Zatrzymywanie programu
    cout << "Funkcja dynamiczna - Naciśnij Enter, aby kontynuować...";
    cin.get();

    // Zwolnienie zaalokowanej pamięci
    delete[] tablica;
}

int main() {
    // Wywołanie funkcji statyczna()
    statyczna();

    // Wstrzymanie programu
    cout << "Po funkcji statyczna() - Naciśnij Enter, aby kontynuować...";
    cin.get();

    // Wywołanie funkcji dynamiczna()
    dynamiczna();

    // Wstrzymanie programu przed zakończeniem
    cout << "Koniec programu - Naciśnij Enter, aby zakończyć...";
    cin.get();

    return 0;
}

