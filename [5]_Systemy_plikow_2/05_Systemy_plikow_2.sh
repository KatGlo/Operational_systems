#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Użycie: $0 <katalog>"
    exit 1
fi

directory=$1

# Funkcja do zbierania i wyświetlania statystyk uprawnień
collect_permissions_stats() {
    find "$1" -type f -exec stat --format='%A' {} \; | sort | uniq -c | awk '$1 > 1'
}

# Wywołanie funkcji na podanym katalogu
collect_permissions_stats "$directory"

# Łączna liczba możliwych konfiguracji uprawnień: 7*2^{7}*3^{3}=7*128*7=7*3456=24192 
