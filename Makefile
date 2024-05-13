all:
	gcc -o main src/*.c
	./main

clean:
	rm main