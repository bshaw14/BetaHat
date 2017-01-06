betahat.so: betahat.cpp	betahat.o
	g++ -I/usr/local/include -I/usr/include/python2.7 -fpic -c -o betahat.o betahat.cpp
	g++ -shared -Wl,-soname,"betahat.so" -L/usr/local/lib betahat.o -lboost_python -fpic -o betahat.so



