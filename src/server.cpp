#include "routes.h"
#include <httplib.h>
#include <filesystem>

using namespace httplib;

int PORT = 8888;
string ADDR = "localhost";

Server::HandlerResponse bomb(const Request &req, Response &res);

int main(void) {
    vector<string> filenames;

    if (TUNES_PATH.size() > 0) {
        for (const auto &f : directory_iterator(TUNES_PATH)) filenames.push_back(f.path());

        auto audio = thread([&](){
            log("started ticker thread");
            while (true) {
                current_time = 0.0;
                srand(time(nullptr));
                int i = rand() % filenames.size();
                current_song = filenames.at(i);
                int first = current_song.find_last_of("/") + 1;
                int last = current_song.find_first_of(".");
                
                double duration = stod(current_song.substr(first, last));

                for (int i = 0; i < (duration+4)*10; i++) {
                    this_thread::sleep_for(100ms);
                    current_time += 0.1;
                }
            }
        });
    }

    Server svr;

    svr.Get("/", Routes::root);
    svr.Get("/favicon.ico", Routes::favicon);
    svr.Get("/pong", Routes::pong);
    svr.Get("/radio/song", Routes::radio_song);
    svr.Get("/radio/elapsed", Routes::radio_elapsed);

    svr.set_base_dir("./share");

    svr.set_pre_routing_handler([&](const auto& req, Response& res) {
        Server::HandlerResponse ret = Server::HandlerResponse::Unhandled;
        string user_agent = "";
        string status = "";

        if (req.has_header("User-Agent")) {
            user_agent = req.get_header_value("User-Agent");
        }

        if (user_agent.length() == 0) ret = bomb(req, res);
        else if (user_agent.find("Python-urllib") != std::string::npos) ret = bomb(req, res);
        else if (user_agent.find("crawler") != std::string::npos) ret = bomb(req, res);
        else if (req.path.find("php") != std::string::npos) ret = bomb(req, res);
        else if (req.path.find("env") != std::string::npos) ret = bomb(req, res);

        if (ret == Server::HandlerResponse::Handled) {
           status = " <- 💣";
        }

        cout << get_ip(req) << ": " << req.path << " [" << user_agent << "]" << status << endl;
        LOGFILE << get_ip(req) << ": " << req.path << " [" << user_agent << "]" << status << endl;

        return ret;
    });

    log("starting web server :8888");
    svr.listen(ADDR, PORT);
    LOGFILE.close();
}

Server::HandlerResponse bomb(const Request &req, Response &res) {
    // Inspired by https://idiallo.com/blog/zipbomb-protection
    res.set_file_content("./share/bomb", "text/php");
    res.set_header("Content-Encoding", "gzip");
    return Server::HandlerResponse::Handled;
}

