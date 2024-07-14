main: main.o libcalc.so
	gcc $< -L. -lcalc -o $@

main.o: main.c
	gcc -c $<

libcalc.so: add.o div.o mul.o sub.o
	gcc -shared $^ -o $@ 

add.o: add.c
	gcc -c add.c

div.o: div.c
	gcc -c div.c

mul.o: mul.c
	gcc -c mul.c

sub.o: sub.c
	gcc -c sub.c

clean:
	rm *.o

run:
	LD_LIBRARY_PATH=$$PWD ./main