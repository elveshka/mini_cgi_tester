//
// Created by Etrigan Snowball on 6/23/21.
// With butthurt and love.
//

#include "./webserv.hpp"
#include <cstdlib>

static const char * strJOINMATHAFAKA(const char * str1, const char * str2) {
	int size1 = strlen(str1);
	int size2 = strlen(str2);

	char *ret = (char*)malloc(sizeof(char) * (size1 + size2 + 1));
	strcpy(ret, str1);
	char *tmp = ret + size1;
	strcpy(tmp, str2);
	return ret;
}

int main(){
	//1st arg interpreter
	//2nd arg cgi script
	//3rd arg script argument
	char * const argv[4] = {
			(char * const )"/usr/bin/perl",
			(char * const )"gif_image",
			(char * const )"t.gif",
			nullptr
		};
	// const char ** env = (const char **)malloc(sizeof (const char *) * 19);
	const char *env[19];
	int fdCoutPipe[2];
	int tmpFileFd = open("response", O_CREAT | O_TRUNC | O_RDWR, 0666);
	fdCoutPipe[0] = fdCoutPipe[1] = -1;
	if (pipe(fdCoutPipe) != 0) {
		std::cout << "Cannot create CGI pipe\n";
		return 0;
	}
	int fdOldCout = dup(1);
	if ((dup2(fdCoutPipe[1], 1) == -1))
		return 0;
	close(fdCoutPipe[1]);
	
	env[0] = strJOINMATHAFAKA("SERVER_ADDR=", "sobaka");
	env[1] = ((std::string("SERVER_SOFTWARE=NCSA/12"))).c_str();
	env[2] = ((std::string("SERVER_NAME=sobaka"))).c_str();
	env[3] = strJOINMATHAFAKA("SERVER_PROTOCOL=", std::string("HTTP/1.1").c_str());
	env[4] = ((std::string("SERVER_PORT=1234"))).c_str();
	env[5] = ((std::string("REQUEST_METHOD=DELETE"))).c_str();
	env[6] = strJOINMATHAFAKA("PATH_INFO=", "./");
	env[7] = ((std::string("PATH_TRANSLATED="))).c_str(); //+ request.getPathToCgi()).c_str();
	env[8] = ((std::string("SCRIPT_NAME=")) + argv[0]).c_str();
	env[9] = ((std::string("QUERY_STRING="))).c_str();
	env[10] = ((std::string("REMOTE_HOST="))).c_str();
	env[11] = ((std::string("REMOTE_ADDR=127.0.0.1"))).c_str();
	env[12] = ((std::string("AUTH_TYPE=basic"))).c_str();
	env[13] = ((std::string("REMOTE_USER="))).c_str();
	env[14] = ((std::string("REMOTE_IDENT"))).c_str();
	env[15] = ((std::string("CONTENT_TYPE="))).c_str();
	env[16] = ((std::string("CONTENT_LENGTH="))).c_str();
	env[17] = (std::string("HTTP_ACCEPT=text/html")).c_str();
	env[18] = NULL;
//	env[0] = (std::string("SERVER_ADDR=") + server.getIp()).c_str();
//	env[1] = (std::string("SERVER_SOFTWARE=?")).c_str();
//	env[2] = (std::string("SERVER_NAME") + server.getIp()).c_str();
//	env[3] = (std::string("SERVER_PROTOCOL=HTTP/1.1")).c_str();;
//	env[4] = (std::string("SERVER_PORT=") + server.getPortStr()).c_str();
//	env[5] = (std::string("REQUEST_METHOD=") + request.getStartingLine()->getMethod()).c_str();
//	env[6] = (std::string("PATH_INFO=") + request.getPathInfo()).c_str();
//	env[7] = (std::string("PATH_TRANSLATED=")).c_str(); //root + path_info
//	env[8] = (std::string("SCRIPT_NAME=")).c_str();//todo virtual path to cgi programm
//	env[9] = (std::string("QUERY_STRING=") + request.getQueryString()).c_str();
//	env[10] = (std::string("REMOTE_HOST=localhost")).c_str();
//	env[11] = (std::string("REMOTE_ADDR=127.0.0.1")).c_str();
//	env[12] = std::string("AUTH_TYPE=basic").c_str();
//	env[13] = (std::string("REMOTE_USER=")).c_str();//todo mb need for session management
//	env[14] = (std::string("REMOTE_IDENT")).c_str();
//	env[15] = (std::string("CONTENT_TYPE=") + request.getRequestHeaders()->find("Content-Type")->second.value).c_str();
//	env[16] = (std::string("CONTENT_LENGTH=") + request.getRequestHeaders()->find("Content-Length")->second.value).c_str();
//	env[17] = (std::string("HTTP_FROM=")).c_str(); //todo client's mail
//	env[18] = (std::string("HTTP_ACCEPT=text/html")).c_str();
//	env[19] = (std::string("HTTP_USER_AGENT=Chrome/91.0.4472.114")).c_str();
//	env[20] = (std::string("HTTP_REFERRER=21-school.ru")).c_str();
//	env[21] = nullptr;
	int pid;
	if (! (pid = fork()))
	{
		execve(argv[0], argv, (char * const *)env);
		return 0;
	}
	dup2(fdOldCout, fileno(stdout));
	print_colored(env[1], MAGENTA);
	print_colored("processing", GREEN);
	close(fdOldCout);
	while (true) {
		char bufferOut[100000];
		int n = read(fdCoutPipe[0], bufferOut, 100000);
		if (n > 0) {
			write(tmpFileFd, bufferOut, n);
		}
		int status;
		if (waitpid(pid, &status, WNOHANG) > 0)
			break;
	}
	// free(env);
	close(tmpFileFd);
}
