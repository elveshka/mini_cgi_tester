#pragma once

#include "./webserv.hpp"
#include "./classes.hpp"

class MyCGI {
	private:
		const static int envSize = 20;
		const static int argvSize = 3;
		const static size_t bufSize = 100000200;
	public:
		MyCGI() {};
		~MyCGI() {};

		const char *concatinateStrings(const char* s1, std::string s2 = "");
		int setEnv(const char **env, Request & request, Server & server);
		void sendToCgi(Response &response, Request & request, Server & server);
};
// void toCGI(Response &response, Request & request, Server & server);
