main: main.o fim_scheduled.o
	gcc -o main main.o fim_scheduled.o -lssl -lcrypto

main.o: main.c fim_scheduled.h
	gcc -g -c main.c -lssl -lcrypto

fim_scheduled.o: fim_scheduled.c fim_scheduled.h
	gcc -g -c fim_scheduled.c -lssl -lcrypto

clean:
	rm main.o fim_scheduled.o
	rm main
