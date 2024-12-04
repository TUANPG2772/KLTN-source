#include <Wire.h>                 // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>    // Include LCD library
#include <string.h>

// Initialize the LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LDR_PIN PA3
#define LOCK_PIN PA5
#define SAMPLING_TIME 20
#define USART_RX_BUFFER_SIZE 64

// Default password
const char default_password[7] = "222777";
char received_password[7] = "";
char current_password[7] = "222777";
int password_index = 0;

// UART command buffer
char usart_rx_buffer[USART_RX_BUFFER_SIZE];
int usart_rx_index = 0;

// Declaration
bool previous_state = true;
bool current_state = true;
char buff[64];

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Initialize UART1 for command reception

  lcd.init();                     // Initialize LCD
  lcd.clear();                    // Clear LCD
  lcd.backlight();                // Turn on backlight

  // Initial display message
  lcd.setCursor(0, 0);
  lcd.print(" LiFi - Wireless");
  lcd.setCursor(0, 1);
  lcd.print(" Communication  ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" using Light    ");
  lcd.setCursor(0, 1);
  lcd.print(" RX TESTING ..  ");
  delay(2000);
  lcd.clear();

  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, HIGH); // Ensure the lock is initially locked
}

void loop() {
  current_state = digitalRead(LDR_PIN); 
  if (!current_state && previous_state) {
    char received_char = get_byte();
    display_received_byte(received_char);
    delay(500); // Delay 0.5 seconds
    lcd.clear();
    display_decoded_password();
    if (password_index == 6) {
      verify_password();
    }
  }
  previous_state = current_state;

  // Process commands from UART
  while (Serial1.available()) {
    char received = Serial1.read();
    if (received == '\n' || usart_rx_index >= USART_RX_BUFFER_SIZE - 1) {
      usart_rx_buffer[usart_rx_index] = '\0';
      process_command(usart_rx_buffer);
      usart_rx_index = 0;
    } else {
      usart_rx_buffer[usart_rx_index++] = received;
    }
  }
}

char get_byte() {
  char data_byte = 0;
  delay(SAMPLING_TIME * 1.5);
  for (int i = 0; i < 8; i++) {
    data_byte = data_byte | (char)digitalRead(LDR_PIN) << i;
    delay(SAMPLING_TIME);
  }
  return data_byte;
}

void display_received_byte(char received_char) {
  lcd.clear();
  lcd.setCursor(0, 1);
  for (int i = 7; i >= 0; i--) {
    lcd.print((received_char >> i) & 0x01);
  }
  if (password_index < 6) {
    received_password[password_index++] = received_char;
  }
}

void display_decoded_password() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < password_index; i++) {
    lcd.print(received_password[i]);
  }
}

void verify_password() {
  received_password[password_index] = '\0'; // Null-terminate the received password
  if (strncmp(received_password, current_password, 6) == 0) {
    digitalWrite(LOCK_PIN, LOW); // Unlock the door
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unlocked");
    Serial1.println("Unlocked");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Password");
    Serial1.println("Wrong Password");
  }
  password_index = 0; // Reset the index for the next password
}

void process_command(const char* command) {
  if (strncmp(command, "unlock", 6) == 0) {
    digitalWrite(LOCK_PIN, LOW); // Unlock the door
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unlocked");
    Serial1.println("Unlocked");
  } else if (strncmp(command, "lock", 4) == 0) {
    digitalWrite(LOCK_PIN, HIGH); // Lock the door
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Locked");
    Serial1.println("Locked");
  } else if (strncmp(command, "change_password", 15) == 0) {
    strncpy(current_password, command + 16, 6);
    current_password[6] = '\0'; // Ensure null-terminated string
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Password Changed");
    Serial1.println("Password Changed");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid Command");
  }
}
