#include "handler.h"
#include "json.hpp"
#include "KeyManager.h"
#include "SQLManager.h"

handler::handler(utility::string_t url) : listener(url) {
    listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
}

void handler::handle_get(http_request message) {
    vector<string> parts = uri::split_path(message.absolute_uri().path());
    if(parts.size() < 1){
        message.reply(status_codes::BadRequest);
        return;
    }
    if(parts[0] == "keys"){
        KeyManager manager;
        string rep = SQLManager::the().get_driver_name();
        message.reply(status_codes::OK, rep);
    }else{
        message.reply(status_codes::BadRequest);
    }
//    string body = message.extract_utf8string(true).get();
//    nlohmann::json req = nlohmann::json::parse(body);
//    for(auto& pr : req)
//        ucout << pr << endl;
    message.reply(status_codes::OK);
};

void handler::handle_post(http_request message) {
    message.reply(status_codes::OK, message.to_string());
};
