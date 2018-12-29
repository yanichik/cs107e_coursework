all : itoa.o itoap.o

itoa.o: itoa.c
	gcc -c $< -o $@ 

itoap.o: itoa.c
	g++ -c $< -o $@ 

clean:
	rm -f *.o 
