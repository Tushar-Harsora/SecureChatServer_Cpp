#include "../include/handler.h"
#include "../include/json.hpp"

handler::handler(utility::string_t url) : listener(url) {
    listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));
}

void handler::handle_get(http_request message) {
    ucout << "Fragment of uri : " << message.absolute_uri().path() << endl;
    string body = message.extract_utf8string(true).get();
    nlohmann::json req = nlohmann::json::parse(body);
    message.reply(status_codes::OK, body);
};

void handler::handle_post(http_request message) {
    message.reply(status_codes::OK, message.to_string());
};

void handler::handle_delete(http_request message) {
    ucout << message.to_string() << endl;
    string rep = U("WRITE YOUR OWN DELETE OPERATION");
    message.reply(status_codes::OK, rep);
};
