#CC = gcc -I /home/user/Documents/c/advanced/list/src
CC = gcc -I../list/src
CFLAGS = -c -Wall -Werror -ansi -pedantic -g

hash1: hashMapTest.o libHash.so ../list/src/list.o ../list/src/list_itr.o ../list/src/list_functions.o
	$(CC) -o hash1 hashMapTest.o ../list/src/list.o ../list/src/list_itr.o ../list/src/list_functions.o -lHash -L.
	


libHash.so : HashMap.o 
	$(CC) -o libHash.so -shared HashMap.o


hashMapTest.o: hashMapTest.c mu_test.h src/HashMap.h
	$(CC) $(CFLAGS) hashMapTest.c
	
HashMap.o: src/HashMap.c ../list/src/list_functions.h src/HashMap.h
	$(CC) -fPIC $(CFLAGS) src/HashMap.c
	



clean:
	rm -rf *.o
	rm -f *.a
	rm -f *.so

