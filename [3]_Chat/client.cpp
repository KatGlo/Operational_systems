#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
// Funkcja obsługująca odbieranie wiadomości od serwera
void receive_messages(int client_socket) {
    char buffer[1024]; // Bufor do przechowywania odbieranych danych, standardowy rozmiar
    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Wyczyszczenie bufora przed każdym odbiorem
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0); // Obbieranie danych od serwera
        if (bytes_received <= 0) {
            cout << "Server disconnected.\n"; // Komunikat w przypadku utraty połączenia z serwerem
            break;
        }
        cout << buffer << endl; // Wyświetlenie otrzymanej wiadomości na ekranie
    }
}

// Funkcja obsługująca wysyłanie wiadomości do serwera
void send_messages(int client_socket) {
    string username;
    cout << "Enter your username: ";
    getline(cin, username);
    send(client_socket, username.c_str(), username.size(), 0); // Wysłanie nazwy użytkownika do serwera

    while (true) {
        string message;
        getline(cin, message);
        send(client_socket, message.c_str(), message.size(), 0); // Wysłanie wiadomości do serwera
    }
}

int main() {
    // Tworzenie gniazda klienta
    int client_socket = socket(AF_INET, SOCK_STREAM, 0); // Tworzenie gniazda przy użyciu protokołu IPv4 i TCP, automatyczny wybór protokołu
    if (client_socket == -1) {
        cerr << "Error creating client socket.\n"; // Komunikat w przypadku błędu w tworzeniu gniazda
        return -1;
    }
    // Ustawienie struktury adresu serwera
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555); // Numer portu serwera
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr); // Adres IP serwera
    // Łączenie z serwerem
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        cerr << "Error connecting to server.\n"; // Komunikat w przypadku błędu w połączeniu z serwerem
        close(client_socket);
        return -1;
    }
    // Tworzenie wątków do obsługi odbierania i wysyłania wiadomości
    thread receive_thread(receive_messages, client_socket);
    thread send_thread(send_messages, client_socket);
    // Oczekiwanie na zakończenie wątków
    receive_thread.join();
    send_thread.join();
    //  Zamykanie gniazda klienta
    close(client_socket);
    return 0;
}
