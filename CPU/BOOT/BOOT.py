import serial
import time

#Baud rate donanım ile birebir aynı olmalı 
ser = serial.Serial(port='/dev/tty.usbserial-210183AA0DDB1', baudrate=19200, timeout=1)
time.sleep(2) # Bağlantının oturması için bekle


with open(r"/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/BOOT/instructions.txt", "r") as file:
    for line in file:
        clean_line = line.strip()
        if not clean_line:
            continue
        
        
        instruction_bytes = bytes.fromhex(clean_line)[::-1]
        
       
        ser.write(instruction_bytes)
        
        time.sleep(0.001)
ser.close()
print("Buyruklar başarıyla gönderildi ve işlemci çalışmaya başladı!")