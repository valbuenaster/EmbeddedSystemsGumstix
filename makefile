all: 			actionProgram calGimbal panzerProgram

panzerProgram:		driver_pwm_motor.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o driver_gpio.o panzer.o panzerProgram.cpp
			g++ driver_pwm_motor.o driver_gpio.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o panzer.o -o panzerProgram panzerProgram.cpp

actionProgram:		driver_pwm_motor.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o driver_gpio.o programTestdevmem.cpp
			g++ driver_pwm_motor.o driver_gpio.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o -o actionProgram programTestdevmem.cpp

calGimbal:		driver_pwm_motor.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o calibrationGimbal.cpp
			g++ driver_pwm_motor.o driver_tty_port.o driver_gimbal.o ViconGumstix.o class_socket.o -o calGimbal calibrationGimbal.cpp

panzer.o:		panzer.cpp
			g++ -c panzer.cpp

driver_gimbal.o:	driver_tty_port.o driver_gimbal.cpp
			g++ -c driver_gimbal.cpp

driver_pwm_motor.o:	driver_pwm_motor.cpp
			g++ -c driver_pwm_motor.cpp

driver_gpio.o:		driver_gpio.cpp
			g++ -c driver_gpio.cpp

driver_tty_port.o:	driver_tty_port.cpp
			g++ -c driver_tty_port.cpp

ViconGumstix.o:		ViconGumstix.cpp
			g++ -c ViconGumstix.cpp

class_socket.o:		class_socket.cpp
			g++ -c class_socket.cpp

clean:
			rm -rf *o actionProgram 
			rm -rf *o calGimbal
