turtletest: parse.c run.c shell.h
	gcc -g parse.c run.c
	gcc -o shell parse.c run.c

run: shell
	./shell

clean:
	rm *~
