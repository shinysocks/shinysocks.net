#include "routes.h"
#include <fstream>
#include <httplib.h>
#include <filesystem>

using namespace httplib;

int PORT = 8888;
string ADDR = "localhost";
ofstream LOGFILE("server.log");

void log(const Request &req, const Response &res);
void log(string m, int n = 0);

int main(void) {
    vector<string> filenames;

    for (const auto &f : directory_iterator(TUNES_PATH)) filenames.push_back(f.path());
    log("found tunes: ", (int) filenames.size());

    auto audio = thread([&](){
        log("started ticker thread ");
        while (true) {
            current_time = 0.0;
            srand(time(nullptr));
            int i = rand() % filenames.size();
            current_song = filenames.at(i);
            int first = current_song.find_last_of("/") + 1;
            int last = current_song.find_first_of(".");
            
            double duration = stod(current_song.substr(first, last));

            for (int i = 0; i < (duration+2)*10; i++) {
                this_thread::sleep_for(100ms);
                current_time += 0.1;
            }
        }
    });

    Server svr;

    svr.Get("/", Routes::root);
    svr.Get("/favicon.ico", Routes::favicon);
    svr.Get("/bomb", Routes::bomb);
    svr.Get("/pong", Routes::pong);
    svr.Get("/radio", Routes::radio);
    svr.Get("/radio/elapsed", Routes::radio_elapsed);

    svr.set_base_dir("./share");
    svr.set_logger([&](const auto& req, const auto& res) { log(req, res); });

    log("starting web server :", PORT);
    svr.listen(ADDR, PORT);
    LOGFILE.close();
}

void log(const Request &req, const Response &res) {
    string user_agent = "";
    if (req.has_header("User-Agent")) user_agent = req.get_header_value("User-Agent");
    if (user_agent.length() == 0) user_agent = "bot";

    cout << req.remote_addr << ": " << req.path << " [" << user_agent << "] <- " << res.status << endl;
    LOGFILE << req.remote_addr << ": " << req.path << " [" << user_agent << "] <- "<< res.status << endl;
}

void log(string m, int n) {
    cout << m << n << endl;
    LOGFILE << m << n << endl;
}
