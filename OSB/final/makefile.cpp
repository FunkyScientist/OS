all: client.exe server.exe

client.exe:client.o
	gcc -o client.exe client.o
server.exe:server.o
	gcc -o server.exe server.o
client.o:client.c
	gcc -c client.c
	
server.o:server.c
	gcc -c server.c
