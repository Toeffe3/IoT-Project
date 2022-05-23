#*!/bin/bash
mkdir -p output
cd output
while test $# -gt 0; do
	if [ $1 = "--compile" ]; then
		avr-gcc --save-temps -Os -Wall -g -mmcu=attiny167 --language=c -o odevice.bin --include=../src/usi.c --include-directory=/usr/lib/avr/include/ ../main.c
	elif [ $1 = "--list-output" ]; then
		readelf -a device.bin
		ls
	elif [ $1 = "--upload" ]; then 
		sudo avrdude -e -v -v -v -P usb -p t167 -c usbasp -C avrdude.conf -U flash:w:"device.bin"
	fi
	shift #shift next argument into $1
done
