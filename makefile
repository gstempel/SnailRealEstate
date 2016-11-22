turtletest: shell.c shell.h
	gcc shell.c -o turtleTest

run: turtleTest
	./turtleTest

clean:
	rm *~
