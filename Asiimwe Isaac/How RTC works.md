The RTC is a component in our system that is used to keep track of time. It uses I2C protocol which is basically like a language that enables the computer,esp32 and the RTC to communicate on two wires. The two wires are the SDA(serial data line) where communication of data happen, The SCL (serial clock) controls the sending and receiving of data between the Esp32 and the RTC. 

How is the RTC connected ?
The SDA is connected to pin 21 of the esp32 which is a serial pin of the Esp32.
The SCL is connected to pin 22 of the esp32.
The VCC is connected to 5V pin of the esp 32.
Then the ground to ground
