import socket

# Hàm ghi dữ liệu vào file và kiểm tra độ dài
def write_to_file(data):
    with open('outputMorse1.txt', 'a') as file:
        file.write(data)

    with open('outputMorse1.txt', 'r') as file:
        content = file.read()

    if len(content) > 100:
        with open('outputMorse1.txt', 'w') as file:
            file.write("")

# Tạo một socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('0.0.0.0', 56789))
sock.listen(1)
print("Waiting for connection...")
conn, addr = sock.accept()
print(f"Connected by {addr}")

try:
    while True:
        data = conn.recv(1024)
        if not data:
            break
        decoded_data = data.decode('utf-8')
        print(decoded_data)
        write_to_file(decoded_data)
except KeyboardInterrupt:
    print("Interrupted by user, closing connection.")
finally:
    conn.close()
    sock.close()

