from machine import ADC, UART, Pin
import time

sensor = ADC(4)
uart = UART(1, baudrate=9600, tx=Pin(4), rx=Pin(5))

while True:
    reading = sensor.read_u16()
    voltage = reading * 3.3 / 65535
    temp = 27 - (voltage - 0.706) / 0.001721

    print(temp)
    uart.write(str(temp) + "\n")  # Send to ESP8266
    time.sleep(5)