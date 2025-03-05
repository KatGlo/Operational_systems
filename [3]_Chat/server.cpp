#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>  
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
// Wektor do przechowywania identyfikatorów klientów
vector<int> clients;
// Mutex do synchronizacji dostępu do wektora klientów, zapewnia bezpieczny dostęp do zasobów
mutex mtx;
// Obsługa klienta
void handle_client(int client_socket) {
    char buffer[1024]; // Bufor do przechowywania danych 
    string username;
    recv(client_socket, buffer, sizeof(buffer), 0);
    username = buffer;
    // Odbieranie nazwy użytkownika od klienta
    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Służy do czyszczenia bufora
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0); // Odbieranie wiadomości od klienta
        if (bytes_received <= 0) { // Sprawdzanie, czy klient się rozłączył
            lock_guard<mutex> lock(mtx); // Blokowanie mutexa dla bezpiecznego dostępu do wektora klientów 
            cout << "Client " << username << " disconnected.\n"; // Komunikat o rozłączeniu klienta
            
            clients.erase(remove(clients.begin(), clients.end(), client_socket), clients.end()); // Usuwanie klienta z wektora
            
            close(client_socket); // Zamykanie gniazda klienta
            break;
        }
        //Blokowanie mutexa dla bezpiecznego dostępu do konsoli i wektora klientów
        lock_guard<mutex> lock(mtx); 
        cout << "[" << username << "] " << buffer << endl; // WYświetlenie otrzymanej wiadomości na konsoli

        for (int other_client : clients) { // Przesyłanie wiadomości do innych klientów
            if (other_client != client_socket) {
                send(other_client, buffer, bytes_received, 0);
            }
        }
    }
}

int main() { // Tworzenie gniazda serwera
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Error creating server socket.\n";
        return -1;
    }
    // Konfiguracja adresu serwera 
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5555);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // Przypisanie gniazda do konkretnego adresu
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        cerr << "Error binding socket.\n"; // Strumień błędów
        close(server_socket);
        return -1;
    }
    // Nasłuchiwanie na gnieździe
    if (listen(server_socket, 5) == -1) {
        cerr << "Error listening on socket.\n";
        close(server_socket);
        return -1;
    }
    // Informacja o gotowości serwera 
    cout << "Server listening on port 5555...\n";

    while (true) {
        sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        // Akceptowanie połączenia od klienta
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size); 
        if (client_socket == -1) {
            cerr << "Error accepting client connection.\n";
            continue;
        }
        // Blokowanie mutexa dla bezpiecznego dostępu do wektora klienta
        {
            lock_guard<mutex> lock(mtx);
            clients.push_back(client_socket);
        }
        // Tworzenie wątku obsługującego klienta
        thread client_thread(handle_client, client_socket); 
        client_thread.detach(); // Oddzielenie wątku do głównego wątku serwera
    }
    // Zamykanie gniazda serwera (nieosiągalne w praktyce z powodu nieskończonej pętli)
    close(server_socket); 
    return 0;
}

 
