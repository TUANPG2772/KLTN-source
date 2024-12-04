#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#define UART_PORT "/dev/ttyS1"
  // Replace with the correct UART port

int uart_init(const char *port) {
    int uart_filestream = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_filestream == -1) {
        perror("Failed to open UART");
        return -1;
    }

    struct termios options;
    tcgetattr(uart_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_filestream, TCIFLUSH);
    tcsetattr(uart_filestream, TCSANOW, &options);

    return uart_filestream;
}

void uart_close(int uart_filestream) {
    close(uart_filestream);
}

void uart_send(int uart_filestream, const char *message) {
    if (uart_filestream != -1) {
        int count = write(uart_filestream, message, strlen(message));
        if (count < 0) {
            perror("UART TX error");
        }
    }
}

int main() {
    int uart_filestream = uart_init(UART_PORT);
    if (uart_filestream == -1) {
        return -1;
    }

    char command[256];
    while (1) {
        printf("Enter command (unlock/change_password <new_password>): ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "unlock", 6) == 0) {
            uart_send(uart_filestream, "unlock\n");
        } else if (strncmp(command, "change_password", 15) == 0) {
            uart_send(uart_filestream, command);
        } else {
            printf("Invalid command\n");
        }

        usleep(100000);  // Wait for 100ms
    }

    uart_close(uart_filestream);
    return 0;
}

