import scipy.signal as signal

def GenerateHighPassCoeff(cutOffFreq, samplingFreq, order):
    nyquist = 0.5 * samplingFreq
    normal_cutoff = cutOffFreq / nyquist
    sos = signal.butter(order, normal_cutoff, btype='high', analog=False, output='sos')
    return sos

# Ví dụ cụ thể
cutOffFreq = 0.1  # Tần số cắt
samplingFreq = 30  # Tần số lấy mẫu
order = 2  # Bậc của bộ lọc
sos = GenerateHighPassCoeff(cutOffFreq, samplingFreq, order)
print(sos)

class IIRFilter:
    def __init__(self, sos):
        self.sos = sos
        self.zi = signal.sosfilt_zi(sos)
    
    def Filter(self, data):
        y, self.zi = signal.sosfilt(self.sos, [data], zi=self.zi)
        return y[0]

# Tạo bộ lọc
iir_filter = IIRFilter(sos)

# Dữ liệu mẫu để lọc
data_samples = [150, 200, 250, 100, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4]

# Lọc dữ liệu
filtered_samples = [iir_filter.Filter(sample) for sample in data_samples]
print(filtered_samples)
