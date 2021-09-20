#include <iostream>
#include <csignal>
#include <thread>

#include "include/stdafx.h"
#include "include/handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


std::unique_ptr<handler> httpHandler;

void start(const string_t &address) {
    uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    httpHandler = make_unique<handler>(addr);
    httpHandler->open().wait();
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
}

void on_shutdown(int) {
    try {
        cout << "Shutting down the Server..." << endl;
        httpHandler->close().wait();
    } catch(...) {
        cout << "In server on_shutdown catch handler" << endl;
    }
    std::_Exit(0);
}

int main(int argc, char *argv[]) {
	const char* value = std::getenv("PORT");

	if(value == nullptr){
        cout << "Port not found from Environment Using 8080" << endl;
	    value = "8080";
	}
    utility::string_t port = U(value);
    if (argc == 2) {
		ucout << utility::string_t(U("Got Implicit Port of ")) << argv[1] << std::endl;
        port = argv[1];
    }

	cout << "Value of PORT is " << port.c_str() << std::endl;
    utility::string_t address = U("http://0.0.0.0:");

    address.append(port);
    start(address);
    std::signal(SIGTERM, on_shutdown);
    std::signal(SIGKILL, on_shutdown);
    getchar();
}
