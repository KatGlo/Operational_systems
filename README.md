# Systemy_operacyjne
Przykładowe programy w C/C++ ilustrujące procesy, sygnały, komunikację sieciową, zarządzanie pamięcią i bezpieczeństwo w systemie Linux.

## Ogólny opis

W tym repozytorium znajdziesz zróżnicowany zestaw przykładów i skryptów w językach C oraz C++, które mają na celu przybliżyć zagadnienia związane z programowaniem systemowym w środowisku Linux:

- **Procesy i sygnały**  
  Tworzenie nowych procesów (`fork()`), zastępowanie obrazu procesu (`exec()`), wysyłanie i obsługa sygnałów (`kill()`, rejestrowanie handlerów).

- **Komunikacja klient–serwer**  
  Prosty model komunikacji przez gniazda TCP, pokazujący podstawy tworzenia serwera obsługującego wielu klientów oraz klienta wysyłającego i odbierającego wiadomości.

- **Zarządzanie pamięcią**  
  Przykłady alokacji na stosie i na stercie, wpływ wielkości bufora na wydajność kopiowania plików, pomiar czasu operacji I/O.

- **Bezpieczeństwo i wielowątkowość**  
  Synchronizacja wątków POSIX, unikanie zakleszczeń (problem ucztujących filozofów), potencjalne zagadnienia buffer overflow, dobre praktyki w programowaniu systemowym.

- **Analiza uprawnień w systemie plików**  
  Skrypt do rekurencyjnego przeglądania katalogu i wyświetlania statystyk uprawnień.

Materiał pozwala zapoznać się z kluczowymi aspektami niskopoziomowego programowania w Linux, takimi jak komunikacja między procesami, wielowątkowość czy bezpieczeństwo. Zachęcam do eksperymentowania, modyfikowania kodu i testowania go w różnych konfiguracjach (różne systemy plików, rozmiary bufora, liczba wątków itp.).


