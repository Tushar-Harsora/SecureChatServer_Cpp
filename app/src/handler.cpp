#include "handler.h"
#include "json.hpp"
#include "KeyManager.h"
#include "SQLManager.h"

handler::handler(utility::string_t url) : listener(url) {
    listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
}

void handler::handle_get(http_request message) {
    cout << "in get handler : " << message.extract_string().get() << endl;
    cout << (getenv("DATABASE_PASSWORD") ? getenv("DATABASE_PASSWORD") : "NO PASSWORD in ENV") << endl;
    try{
        vector<string> parts = uri::split_path(message.absolute_uri().path());
        if(parts.size() < 1){
            message.reply(status_codes::BadRequest);
            return;
        }

        if(parts[0] == "keys"){
            KeyManager manager;
            string rep = SQLManager::the().get_driver_name() + "Database password is ";
            rep += getenv("DATABASE_PASSWORD") ? getenv("DATABASE_PASSWORD") : "";
            message.reply(status_codes::OK, rep);
        }
        else if(parts[0] == "status"){
            message.reply(status_codes::Accepted, "Server is up and Running!!");
        }else{
            message.reply(status_codes::BadRequest);
        }
    } catch(const exception& e){
        cout << e.what() << endl;
    } catch(const string& s){
        cout << s << endl;
    }
}

void handler::handle_post(http_request message) {
    message.reply(status_codes::OK, message.to_string());
}
