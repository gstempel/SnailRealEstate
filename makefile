turtleTest: shell.c shell.h
	gcc shell.c -o turtleTest

run:
	./turtleTest

clean:
	rm *~