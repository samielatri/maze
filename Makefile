build:
	gcc -std=c99 ./src/*.c -lSDL2 -o ./bin/maze;

run:
	./bin/maze;

clean:
	rm ./bin/maze;