clear
avr-gcc --save-temps -Os -Wall -g -mmcu=attiny167 --language=c -o output/device.bin --include=src/USI.c main.c
hexdump output/device.bin --canonical
sudo avrdude -e -v -v -v -P usb -p t167 -c usbasp -C avrdude.conf -U flash:w:"output/device.bin"