main: main.o libcalc.so
	gcc $< -L. -lcalc -o $@

main.o: main.c
	gcc -c -fPIC $<

libcalc.so: add.o div.o mul.o sub.o
	gcc -shared $^ -o $@ 

add.o: add.c
	gcc -c -fPIC add.c

div.o: div.c
	gcc -c -fPIC div.c

mul.o: mul.c
	gcc -c -fPIC mul.c

sub.o: sub.c
	gcc -c -fPIC sub.c

clean:
	rm *.o

run:
	LD_LIBRARY_PATH=$$PWD ./main