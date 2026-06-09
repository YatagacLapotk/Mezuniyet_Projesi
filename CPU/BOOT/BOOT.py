import serial
import time

# 1. DÜZELTME: Baud rate donanım ile birebir aynı olmalı 
ser = serial.Serial('COM4', 19200 , timeout=1)
time.sleep(2) # Bağlantının oturması için bekle

# Dosya yolunun başına 'r' ekleyerek kaçış karakteri (escape) hatalarını önlüyoruz
with open(r"E:\RV32IM\Mezuniyet_Projesi\CPU\BOOT\instructions.txt", "r") as file:
    for line in file:
        clean_line = line.strip()
        if not clean_line:
            continue
        
        # 2. DÜZELTME: [::-1] ile byte sıralamasını (Endianness) donanıma uygun şekilde ters çeviriyoruz.
        # Örnek: "00500093" -> b'\x93\x00\x50\x00' haline gelir.
        instruction_bytes = bytes.fromhex(clean_line)[::-1]
        
        # USB üzerinden baytları gönder
        ser.write(instruction_bytes)
        
        time.sleep(0.001)
ser.close()
print("Buyruklar başarıyla gönderildi ve işlemci çalışmaya başladı!")