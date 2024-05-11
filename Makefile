all:
	gcc -o main src/main.c src/queue.c src/memory.c
	./main

clean:
	rm main