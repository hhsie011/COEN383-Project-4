all:
	gcc -o main src/*.c
	./main > output.txt

clean:
	rm main
