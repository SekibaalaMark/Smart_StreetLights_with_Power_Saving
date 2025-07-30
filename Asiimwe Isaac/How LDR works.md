
The LDR is used to detect light and darkness. The LDR uses resistance to determine the level of darkness. The higher the darkness level, the higher the level of resistance and vice versa. How does the LDR communicate with the esp32? Since the Esp32 cannot receive resistance as a value input reading, a voltage divider(potentiometer) is used to convert the resistance into voltage that can be understood by the Esp32.
When the Lrd value is high, the darkness is high and viceversa

How is the LDR connected to the esp32.
One leg is connected to the ground.
Second leg connected to pin34 which is an analog input pin.
The potentiometer middle pin is connected to the pin 34.
The other pin of the potentiometer is connected to the 3V pin
