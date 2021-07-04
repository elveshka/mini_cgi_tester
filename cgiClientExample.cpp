//
// Created by Etrigan Snowball on 6/23/21.
// With butthurt and love.
//
#include "./webserv.hpp"
using namespace std;

int main(int argc, char *argv[], char **env) {
	//Отдаем в stdout переменные командной строки, которые получили от родителя
	print_colored("Child process started\n", GREEN);
	for (int n=0; n<argc; n++)
		cout << "argv[" << n << "] = " << argv[n] << "\n";

	//Отдаем в stdout переменные окружения, которые получили от родителя
	const int nContentLength = atoi(getenv("Content-Length"));
	cout <<
		 "\n" <<
		 "Content-Length = " << nContentLength << "\n" <<
		 "VARIABLE2 = " << getenv("VARIABLE2") << "\n" <<
		 "VARIABLE3 = " << getenv("VARIABLE3") << "\n" <<
		 "\n\n";
	fflush(stdout);


	vector<unsigned char> vBuffer(nContentLength);

	//Получаем из stdin все, что прислал туда родительский процесс
	const size_t nBytes = fread(&vBuffer[0],  1, nContentLength, stdin);

	//Отдаем в stdout то, что только что получили от родителя и добавляем свое
	cout << "Request body:\n";
	fwrite(&vBuffer[0], 1, nBytes, stdout);
	fflush(stdout);


	return 0;
}
