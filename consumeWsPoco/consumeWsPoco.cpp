// consumeWsPoco.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char **argv)
{
	string parametro;
	string metodo;
	Poco::JSON::Object obj;
	
	if (argc < 2) {
		parametro = string("FechaAct");
		metodo = string("getCurDate");
	}
	else {
		parametro = string(argv[1]);
		metodo = string("getParam/") + parametro;
	}

	//Poco::URI uri("http://127.0.0.1:8080/SBIWS/rest/WSApi/getCurDate");
	Poco::URI uri("http://192.168.0.200:8080/SBIWS/rest/WSApi/" + metodo);
	std::string path(uri.getPathAndQuery());
	if (path.empty()) path = "/";

	HTTPClientSession session(uri.getHost(), uri.getPort());
	HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	HTTPResponse response;

	//request.setContentType("application/json");
	std::ostream& o = session.sendRequest(request);

	obj.stringify(o);

	// this line is where you get your response
	std::istream& s = session.receiveResponse(response);

	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr ret = parser.parse(s).extract<Poco::JSON::Object::Ptr>();

	// (*ret) will contain all the members in a json structure returned
	/*if ((*ret).get("FechaAct") != true) {
		std::cout << "Failed to upload: " << (*ret).get("message").toString();
		return 1;
	}*/

	//DynamicAny var = ret->get("FechaAct");
	DynamicAny var = ret->get(parametro);
	string valor = var.toString();

	cout << "Valor:" << valor << endl;

    return 0;
}

