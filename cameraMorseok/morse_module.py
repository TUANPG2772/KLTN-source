class Node:
    def __init__(self, char=None):
        self.char = char  # Lưu trữ ký tự tại nút này
        self.left = None  # Nút con trái (ứng với ký hiệu '.')
        self.right = None # Nút con phải (ứng với ký hiệu '-')

class MorseCodeBinaryTree:
    def __init__(self):
        self.root = Node()
        self._build_tree()

    def _build_tree(self):
        # Mã Morse cho từng ký tự
        codes = {
            'A': '.-', 'B': '-...', 'C': '-.-.', 'D': '-..', 'E': '.', 'F': '..-.', 'G': '--.', 'H': '....', 
            'I': '..', 'J': '.---', 'K': '-.-', 'L': '.-..', 'M': '--', 'N': '-.', 'O': '---', 'P': '.--.', 
            'Q': '--.-', 'R': '.-.', 'S': '...', 'T': '-', 'U': '..-', 'V': '...-', 'W': '.--', 'X': '-..-', 
            'Y': '-.--', 'Z': '--..', '0': '-----', '1': '.----', '2': '..---', '3': '...--', '4': '....-', 
            '5': '.....', '6': '-....', '7': '--...', '8': '---..', '9': '----.'
        }

        # Thêm từng ký tự vào cây nhị phân
        for char, code in codes.items():
            self._insert_code(char, code)

    def _insert_code(self, char, code):
        current_node = self.root
        for symbol in code:
            if symbol == '.':
                if current_node.left is None:
                    current_node.left = Node()
                current_node = current_node.left
            elif symbol == '-':
                if current_node.right is None:
                    current_node.right = Node()
                current_node = current_node.right
        current_node.char = char  # Gán ký tự cho nút cuối cùng trong chuỗi Morse code

    def decode_string(self, sequence):
        current_node = self.root
        for symbol in sequence:
            if symbol == '.':
                if current_node.left is None:
                    return ''  # Chuỗi không hợp lệ
                current_node = current_node.left
            elif symbol == '-':
                if current_node.right is None:
                    return ''  # Chuỗi không hợp lệ
                current_node = current_node.right
        return current_node.char if current_node.char is not None else ''

class MorseCodeDecoder:
    def __init__(self):
        self.tree = MorseCodeBinaryTree()
        self.nSamplesDotDuration = 10
        self.nSamplesMinDashDuration = 17
        self.nSamplesMaxDashDuration = 23
        self.nSamplesErrorMargin = 2
        self.sequence = ''
        self.morseSequence = ''
        self.decodedLetters = ''
        self.nSamplesBetwenPosNegPeakList = []
        self.nSamplesBetweenPeaks = 0
        self.nSymbols = 0
        self.nSamplesLow = 0
        self.totalSampleCount = 0
        self.posAmplitudeThreshold = 10
        self.negAmplitudeThreshold = -10
        self.pulseSettlingSamplecCnt = 5
        self.posPeakFlag = False 
        self.negPeakFlag = False
        self.posPeakFound = False
        self.previousSample = 0
        self.timerStart = 0
        self.SamplingTimerCounter = 0
        self.nSamplesLate = 0

    def Detect(self, sample):
        if self.totalSampleCount >= 150:
            if sample > self.posAmplitudeThreshold and not self.posPeakFlag:
                self.posPeakFlag = True
                if self.nSamplesLow >= 20:
                    if self.sequence:
                        self.decodedLetters += self.tree.decode_string(self.sequence)
                        if self.nSamplesLow >= 40:
                            self.decodedLetters += ' '
                        self.morseSequence += self.sequence + ' '
                        self.sequence = ''
                    self.nSamplesLow = 0
            if sample > self.posAmplitudeThreshold and self.previousSample > sample and self.posPeakFlag:
                self.posPeakFound = True
            if sample < self.negAmplitudeThreshold and not self.negPeakFlag:
                self.negPeakFlag = True
            if sample < self.negAmplitudeThreshold and self.previousSample < sample and self.posPeakFlag and self.nSamplesBetweenPeaks >= self.pulseSettlingSamplecCnt:
                self.posPeakFound = False
                self.posPeakFlag = False
                self.negPeakFlag = False
                self.nSamplesBetwenPosNegPeakList.append(self.nSamplesBetweenPeaks)
                self.nSymbols += 1
                if self.nSamplesBetweenPeaks >= self.nSamplesMinDashDuration:
                    self.sequence += '-'
                elif (self.nSamplesDotDuration - self.nSamplesErrorMargin) <= self.nSamplesBetweenPeaks <= (self.nSamplesDotDuration + self.nSamplesErrorMargin):
                    self.sequence += '.'
                self.nSamplesBetweenPeaks = 0
        if self.posPeakFound:
            self.nSamplesBetweenPeaks += 1
            self.nSamplesLow = 0
            if self.nSamplesBetweenPeaks > self.nSamplesMaxDashDuration:
                self.posPeakFound = False
                self.posPeakFlag = False
                self.negPeakFlag = False
                self.nSamplesBetweenPeaks = 0
        else:
            self.nSamplesLow += 1
        self.previousSample = sample
        self.totalSampleCount += 1
