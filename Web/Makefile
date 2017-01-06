CC=g++
CFLAGS=-fpic -c -o
LFLAGS=-L/usr/local/lib
INCLUDES=-I/usr/local/include -I/usr/include/python2.7

all: betahat.o betahat.so

betahat.o: betahat.cpp
	@echo "Building target object file..."
	$(CC) $(INCLUDES) $(CFLAGS) betahat.o betahat.cpp
betahat.so: betahat.o
	@echo "Building module..."
	$(CC) -shared -Wl,-soname,"betahat.so" $(LFLAGS) betahat.o -lboost_python -fpic -o betahat.so
	@echo "Module built successfully."

clean:
	@echo "Removing target object file..."
	rm -f betahat.o
	@echo "Remoing target module..."
	rm -f betahat.so
	@echo "Clean successful."


