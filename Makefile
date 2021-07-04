all:
	clang++ cgiServerExample.cpp -o server
	clang++ cgiClientExample.cpp -o client
	./server
#	cat response
