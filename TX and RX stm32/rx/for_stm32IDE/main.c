#include "main.h"
#include <string.h>
#include <stdio.h>

// Define constants and variables
#define USART_RX_BUFFER_SIZE 256

UART_HandleTypeDef huart1;
char usart_rx_buffer[USART_RX_BUFFER_SIZE];
int usart_rx_index = 0;

const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

uint16_t rowPins[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_10, GPIO_PIN_11};
GPIO_TypeDef* rowPorts[4] = {GPIOB, GPIOB, GPIOB, GPIOB};

uint16_t colPins[4] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
GPIO_TypeDef* colPorts[4] = {GPIOB, GPIOB, GPIOB, GPIOB};

#define TRANSMIT_LED_Pin GPIO_PIN_2
#define TRANSMIT_LED_GPIO_Port GPIOA
#define LOCK_PIN_Pin GPIO_PIN_3
#define LOCK_PIN_GPIO_Port GPIOA
#define SAMPLING_TIME 20

char entered_password[7] = ""; 
char correct_password[7] = "222777"; 

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void process_command(const char* command);
void transmit_byte(char data_byte);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    HAL_UART_Transmit(&huart1, (uint8_t*)"Welcome to Tuan PG27!\r\n", 22, HAL_MAX_DELAY);
    HAL_Delay(2000);

    HAL_UART_Transmit(&huart1, (uint8_t*)" LiFi - Wireless\r\n Communication\r\n", 33, HAL_MAX_DELAY);
    HAL_Delay(2000);

    HAL_UART_Transmit(&huart1, (uint8_t*)" using Light\r\n TX TESTING ..\r\n", 32, HAL_MAX_DELAY);
    HAL_Delay(3000);

    while (1) {
        // Read keypad and process input
        for (int row = 0; row < 4; row++) {
            for (int i = 0; i < 4; i++) {
                HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);
            }
            HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_RESET);
            for (int col = 0; col < 4; col++) {
                if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                    HAL_Delay(50); 
                    if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                        char key = keys[row][col];
                        char msg[16];
                        sprintf(msg, "Key Pressed: %c\r\n", key);
                        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
                        if (key != '*' && key != '#') {
                            int len = strlen(entered_password);
                            if (len < 6) {
                                entered_password[len] = key;
                                entered_password[len+1] = '\0';
                            }
                        }
                        if (strcmp(entered_password, correct_password) == 0) {
                            HAL_UART_Transmit(&huart1, (uint8_t*)"Access Granted\r\n", 16, HAL_MAX_DELAY);
                            HAL_GPIO_WritePin(LOCK_PIN_GPIO_Port, LOCK_PIN_Pin, GPIO_PIN_SET);  
                            HAL_Delay(5000);                   
                            HAL_GPIO_WritePin(LOCK_PIN_GPIO_Port, LOCK_PIN_Pin, GPIO_PIN_RESET);   
                            strcpy(entered_password, "");         
                        } else if (strlen(entered_password) >= 6) {
                            HAL_UART_Transmit(&huart1, (uint8_t*)"Access Denied\r\n", 15, HAL_MAX_DELAY);
                            HAL_Delay(2000);
                            strcpy(entered_password, "");  
                        }
                        transmit_byte(key);
                        while (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET);
                    }
                }
            }
            HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_SET);
        }

        // Process commands from USART
        while (HAL_UART_Receive(&huart1, (uint8_t*)&usart_rx_buffer[usart_rx_index], 1, HAL_MAX_DELAY) == HAL_OK) {
            char received = usart_rx_buffer[usart_rx_index];
            if (received == '\n' || usart_rx_index >= USART_RX_BUFFER_SIZE - 1) {
                usart_rx_buffer[usart_rx_index] = '\0';
                process_command(usart_rx_buffer);
                usart_rx_index = 0;
            } else {
                usart_rx_index++;
            }
        }
    }
}

void process_command(const char* command) {
    if (strcmp(command, "unlock") == 0) {
        HAL_UART_Transmit(&huart1, (uint8_t*)"Access Granted\r\n", 16, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(LOCK_PIN_GPIO_Port, LOCK_PIN_Pin, GPIO_PIN_SET);  
        HAL_Delay(5000);                   
        HAL_GPIO_WritePin(LOCK_PIN_GPIO_Port, LOCK_PIN_Pin, GPIO_PIN_RESET);   
        strcpy(entered_password, "");         
    } else if (strncmp(command, "change_password", 15) == 0) {
        strcpy(correct_password, command + 16);
        HAL_UART_Transmit(&huart1, (uint8_t*)"Password Changed\r\n", 18, HAL_MAX_DELAY);
        HAL_Delay(2000);
    }
}

void transmit_byte(char data_byte) {
    HAL_GPIO_WritePin(TRANSMIT_LED_GPIO_Port, TRANSMIT_LED_Pin, GPIO_PIN_RESET); 
    HAL_Delay(SAMPLING_TIME);
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(TRANSMIT_LED_GPIO_Port, TRANSMIT_LED_Pin, (data_byte >> i) & 0x01);
        HAL_Delay(SAMPLING_TIME);
    }
    HAL_GPIO_WritePin(TRANSMIT_LED_GPIO_Port, TRANSMIT_LED_Pin, GPIO_PIN_SET);  
}

