#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

// Funkcja do mierzenia czasu
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec) * 1000.0 + (tv.tv_usec) / 1000.0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Użycie: %s <rozmiar bufora> <plik.src> <plik.trg>\n", argv[0]);
        return 1;
    }

    int buf_size = atoi(argv[1]);
    char *buffer = malloc(buf_size);
    if (!buffer) {
        perror("Nie można przydzielić bufora");
        return 2;
    }

    int src_fd = open(argv[2], O_RDONLY);
    if (src_fd == -1) {
        perror("Nie można otworzyć pliku źródłowego");
        free(buffer);
        return 3;
    }

    int trg_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (trg_fd == -1) {
        perror("Nie można otworzyć/utworzyć pliku docelowego");
        close(src_fd);
        free(buffer);
        return 4;
    }

    double start_time = get_time();

    ssize_t read_bytes;
    while ((read_bytes = read(src_fd, buffer, buf_size)) > 0) {
        write(trg_fd, buffer, read_bytes);
    }

    double end_time = get_time();

    close(src_fd);
    close(trg_fd);
    free(buffer);

    printf("Czas kopiowania: %.2f ms\n", end_time - start_time);
    return 0;
}
