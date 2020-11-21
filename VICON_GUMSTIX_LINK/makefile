all:			ClientSocket

ClientSocket:		class_socket.o ClientSocket.cpp
			g++ class_socket.o -o ClientSocket ClientSocket.cpp

class_socket.o:		class_socket.cpp
			g++ -c class_socket.cpp

clean:
			rm -rf *o ClientSocket
