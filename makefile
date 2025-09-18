a.out : main.o createdatabase.o displaydatabase.o searchdatabase.o savedatabase.o updatedatabase.o
	gcc -o a.out main.o createdatabase.o displaydatabase.o searchdatabase.o savedatabase.o updatedatabase.o

main.o : main.c
	gcc -c main.c

createdatabase.o : createdatabase.c
	gcc -c createdatabase.c

displaydatabase.o : displaydatabase.c 
	gcc -c displaydatabase.c

searchdatabase.o : searchdatabase.c 
	gcc -c searchdatabase.c

savedatabase.o : savedatabase.c
	gcc -c savedatabase.c

updatedatabase.o :updatedatabase.c
	gcc -c updatedatabase.c 

clean :
	rm *.o *.out



