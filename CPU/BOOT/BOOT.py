import serial
import time

# Configure the serial port (Replace 'COM3' or '/dev/ttyUSB1' with your actual port)
# Match the baud rate to your FPGA's UART baud rate
ser = serial.Serial('COM4', 115200, timeout=1)
time.sleep(2) # Wait for connection to stabilize

with open("E:\RV32IM\Mezuniyet_Projesi\CPU\BOOT\instructions.txt", "r") as file:
    for line in file:
        clean_line = line.strip()
        if not clean_line:
            continue
        
        # Convert hex string to raw bytes (e.g., "00200513" -> b'\x00\x20\x05\x13')
        instruction_bytes = bytes.fromhex(clean_line)
        
        # Send the bytes over USB
        ser.write(instruction_bytes)
        
        # Optional: short pause if your FPGA needs processing time per instruction
        time.sleep(0.01) 

ser.close()
print("Instructions sent successfully!")