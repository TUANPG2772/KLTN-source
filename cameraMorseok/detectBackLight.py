import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from morse_module import MorseCodeDecoder
import filter_module
import threading
import cv2
import queue
import socket
import time

# Queue to hold decoded characters
char_queue = queue.Queue()

class Webcam2rgb:
    def start(self, callback, cameraNumber=0, width=None, height=None, fps=None, directShow=False):
        self.callback = callback
        try:
            self.cam = cv2.VideoCapture(cameraNumber + cv2.CAP_DSHOW if directShow else cv2.CAP_ANY)
            if not self.cam.isOpened():
                print('opening camera')
                self.cam.open(0)
                
            if width:
                self.cam.set(cv2.CAP_PROP_FRAME_WIDTH, width)
            if height:
                self.cam.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
            if fps:
                self.cam.set(cv2.CAP_PROP_FPS, fps)
            self.running = True
            self.thread = threading.Thread(target=self.calc_BRG)
            self.thread.start()
            self.ret_val = True
        except:
            self.running = False
            self.ret_val = False

    def stop(self):
        self.running = False
        self.thread.join()
        self.release()  # Ensure the camera is released

    def release(self):
        if self.cam is not None:
            self.cam.release()
            
            cv2.destroyAllWindows()

    def calc_BRG(self):
        while self.running:
            try:
                self.ret_val = False
                self.ret_val, img = self.cam.read()
                if self.ret_val:
                    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                    h, w = gray.shape
                    brg = np.mean(gray[int(h/2)-10:int(h/2)+10, int(w/2)-10:int(w/2)+10])
                    self.callback(self.ret_val, brg)
            except:
                self.running = False

    def cameraFs(self):
        return self.cam.get(cv2.CAP_PROP_FPS)

class RealtimeWindow:
    def __init__(self, channel: str):
        self.fig, (self.ax, self.ax1) = plt.subplots(2, 1, figsize=(10, 8))
        self.fig.suptitle(f"Kênh: {channel}")
        self.ax.set_title('Độ sáng')
        self.ax1.set_title('Tín hiệu sau khi lọc')
        self.plotbuffer = np.zeros(800)
        self.plotbuffer1 = np.zeros(800)
        self.line, = self.ax.plot(self.plotbuffer)
        self.line2, = self.ax1.plot(self.plotbuffer1)
        self.ax.set_ylim(-1, 1)
        self.ax1.set_ylim(-1, 1)
        self.ringbuffer = []
        self.ringbuffer1 = []
        self.decodedSequence = ''
        samplingFrequency = 30
        cutOfFrequencyHighPass = 0.1
        order = 2
        sos = np.array(filter_module.GenerateHighPassCoeff(cutOfFrequencyHighPass, samplingFrequency, order))
        self.decoder = MorseCodeDecoder()
        self.iirFilter = filter_module.IIRFilter(sos)
        self.filterOutput = 0
        self.ani = animation.FuncAnimation(self.fig, self.update, interval=100)
        self.previous_decoded_letters = ''

    def update(self, frame):
        self.plotbuffer = np.append(self.plotbuffer, self.ringbuffer)
        self.plotbuffer1 = np.append(self.plotbuffer1, self.ringbuffer1)
        self.plotbuffer = self.plotbuffer[-800:]
        self.plotbuffer1 = self.plotbuffer1[-800:]
        self.ringbuffer = []
        self.ringbuffer1 = []
        self.line.set_ydata(self.plotbuffer)
        self.line2.set_ydata(self.plotbuffer1)
        self.ax.set_ylim((min(self.plotbuffer) - 1), max(self.plotbuffer) + 1)
        self.ax1.set_ylim((min(self.plotbuffer1) - 1), max(self.plotbuffer1) + 1)
        self.ax.set_title('Độ sáng - Chuỗi đã phát hiện: ' + self.decoder.morseSequence)
        self.ax1.set_title('Tín hiệu sau khi lọc - Chuỗi đã giải mã: ' + self.decoder.decodedLetters)
        
        return self.line, self.line2

    def addData(self, signal):
        self.ringbuffer.append(signal)
        self.filterOutput = self.iirFilter.Filter(signal)
        self.ringbuffer1.append(self.filterOutput)
        self.decoder.Detect(self.filterOutput)

def camera_callback(ret_val, brg):
    if ret_val:
        window.addData(brg)

def send_data_via_socket(realTimeWindow):
    """
    Gửi dữ liệu qua socket đến địa chỉ IP và cổng cụ thể.
    """
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(('192.168.7.2', 12345))
            while True:
                message = realTimeWindow.decoder.decodedLetters
                if message:
                    sock.sendall(message.encode('utf-8'))
                time.sleep(5)
    except KeyboardInterrupt:
        print("Người dùng ngắt, đóng kết nối socket.")
    except Exception as e:
        print(f"Lỗi socket: {e}")

def main():
    global window
    channel = 'Camera'
    window = RealtimeWindow(channel)
    
    # Start the socket sending thread
    socket_thread = threading.Thread(target=send_data_via_socket, args=(window,))
    socket_thread.daemon = True
    socket_thread.start()
    
    cam = Webcam2rgb()
    cam.start(camera_callback, cameraNumber=0, width=640, height=480, fps=30)
    
    plt.show()
    
    # Stop the camera gracefully
    cam.stop()

if __name__ == "__main__":
    main()
