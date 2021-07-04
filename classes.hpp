#ifndef CLASSES_HPP
#define CLASSES_HPP

class Request;
class Server;
class ServConfig;
class Location;
class Socket;
class Select;
class Response;
class Client;
class MyCGI;
class Processer;

#include "../config_parser/ServConfig.hpp"
#include "../config_parser/Location.hpp"

#include "../socket/Socket.hpp"
#include "../select/Select.hpp"

#include "../server/Server.hpp"
#include "../server/Client.hpp"

#include "../request/Request.hpp"

#include "../response/Response.hpp"
#include "../response/Processer.hpp"

#include "../myCgi/myCgi.hpp"

//#include "../utilities/utilities.hpp"

#endif
