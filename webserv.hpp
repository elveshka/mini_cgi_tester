#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <unistd.h> // ??? unlink
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <dirent.h>

//
////STL containers
# include <vector>
# include <map>
# include <algorithm>
# define SERV_POTRT 8080

// -------COLOURS --------
#define FALSE 0
#define TRUE 1

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

inline void 		print_colored(const char * str, int color = WHITE, int newline = TRUE) {
	color = ( color > 37 || color < 30) ? WHITE : color;
	std::cout << "\x1B[" << color << "m" << str << "\033[0m";
	if (newline)
		std::cout << std::endl;
}

inline void 		print_err_coloured(const char * str, int color = RED, int newline = TRUE) {
	color = ( color > 37 || color < 30) ? RED : color;
	std::cerr << "\x1B[" << color << "m" << str << "\033[0m";
	if (newline)
		std::cerr << std::endl;
}

//void		exit_error(const char * str, int color = RED, int newline = TRUE) {
//	color = ( color > 37 || color < 30) ? RED : color;
//	std::cerr << "\x1B[" << color << "m" << str << "\033[0m";
//	if (newline)
//		std::cerr << std::endl;
//	exit(1);
//}

// -------COLOURS --------

struct headerInfo {
	std::string value;
	int isSet;
};

//
////STL containers
# include <vector>
# include <map>
# include <algorithm>

# define SERV_POTRT 8080

#endif
