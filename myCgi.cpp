#include "myCgi.hpp"

//int MyCGI::setEnv(const char **env, Request & request, Server & server){
//	std::string pair;
//	env[0] = "SERVER_NAME=" + std::to_string(server.getIp());
//	env[1] = "SERVER_SOFTWARE=?";
//	env[2] = "GATEWAY_INTERFACE=";
//	env[3] = "SERVER_PROTOCOL=HTTP/1.1");
//	env[4] = "SERVER_PORT=" + std::to_string(server.getPort()).c_str();
//	env[5] = "REQUEST_METHOD=" + request.getMetod().c_str();
//	env[6] = "PATH_INFO=" + request.getURI().c_str();
//	env[7] = "PATH_TRANSLATED=" + request.getPathToCgi().c_str();
//	env[8] = "SCRIPT_NAME=" + strrchr(request.getPathToCgi().c_str(), '/');
//	env[9] = "QUERY_STRING=" + request.getQueryString().c_str();
//	env[10] = "REMOTE_HOST=" + request.getURI().c_str();
//	env[11] = "REMOTE_ADDR=";
//	env[12] = "AUTH_TYPE=basic";
//	env[13] = "REMOTE_USER=";
//	env[14] = "REMOTE_IDENT";
//	env[15] = "CONTENT_TYPE=" + request.getContentType().c_str();
//	env[16] = "CONTENT_LENGTH=" + (request.getQueryString() == "" ? request.getContentLength().c_str() : std::to_string(request.getQueryString().length()).c_str()));
//	env[17] = "REQUEST_URI=http://" + (server.getIp() + ":" + std::to_string(server.getPort()) + request.getURI()).c_str());
//	env[19] = NULL;
//	return 0;
//}

//get cgi answer
void MyCGI::sendToCgi(Response &response, Request & request, Server & server) {
	char *env[];
	char *argv[];
	int trumpet_fd[2];
	int fd_final = open("tmpFileToCGI", O_CREAT | O_RDWR | O_TRUNC, 0666);

	print_colored("cgi", MAGENTA);
	pipe(trumpet_fd);
	getEnv(env, request, server);
	argv[0] = ft_strdup(request.getInterPath() == "" ? request.getPathToCgi().c_str() : request.getInterPath().c_str());
	argv[1] = ft_strdup(request.getPathToCgi().c_str());
	argv[2] = NULL;
	int fdCinPipe[2], fdCoutPipe[2];
	fdCinPipe[0] = fdCinPipe[1] = fdCoutPipe[0] = fdCoutPipe[1] = -1;
	if (pipe(fdCinPipe) != 0 || pipe(fdCoutPipe) != 0) {
		std::cout << "Cannot create CGI pipe\n";
	}
	// Duplicate stdin and stdout file descriptors
	int fdOldCin = dup(0);
	int fdOldCout = dup(1);
	// Duplicate end of pipe to stdout and stdin file descriptors
	if ((dup2(fdCoutPipe[1], 1) == -1) || (dup2(fdCinPipe[0], 0) == -1))
		// Close original end of pipe
		close(fdCinPipe[0]);
	close(fdCoutPipe[1]);
	//Запускаем дочерний процесс, отдаем ему переменные командной строки и окружения
	int pid;
	if (!(pid = fork()))
		execve("./hello_world.py", argv, envp);
	// Duplicate copy of original stdin an stdout back into stdout
	dup2(fdOldCin, 0);
	dup2(fdOldCout, 1);

	// Close duplicate copy of original stdin and stdout
	close(fdOldCin);
	close(fdOldCout);
	//Отдаем тело запроса дочернему процессу
	write(fdCinPipe[1], "--body--", 9);
	while (true) {
		//Читаем ответ от дочернего процесса
		char bufferOut[100000];

		int n = read(fdCoutPipe[0], bufferOut, 100000);
		if (n > 0) {
			//Выводим ответ на экран
			fwrite(bufferOut, 1, n, stdout);
			fflush(stdout);
		}

		//Если дочерний процесс завершился, то завершаем и родительский процесс

		int status;
		if (waitpid(pid, &status, WNOHANG) > 0)
			break;
	}
}
