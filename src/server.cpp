// #include <httplib.h>
#include "httplib.h"
#include "routes.h"

using namespace httplib;

int PORT = 8888;
string ADDR = "localhost";

int main(void) {

    // load music files
    vector<string> filenames;

    for (const auto &f : directory_iterator(TUNES_PATH)) {
        filenames.push_back(f.path());
    }

    cout << "found " << filenames.size() << " songs in " << TUNES_PATH << endl;

    auto audio = thread([&](){
        while (true) {
            current_time = 0;
            srand(time(nullptr));
            int i = rand() % filenames.size();
            current_song = filenames.at(i);
            int first = current_song.find_last_of("/") + 1;
            int last = current_song.find_first_of(".");
            
            int duration = stoi(current_song.substr(first, last));

            cout << "playing: " << current_song << " for " << duration << " seconds" << endl;

            for (int i = 0; i < duration+2; i++) {
                this_thread::sleep_for(1000ms);
                current_time++;
            }
        }
    });


    Server svr;

    // routes
    svr.Get("/", Routes::root);
    svr.Get("/favicon.ico", Routes::favicon);
    svr.Get("/bomb", Routes::bomb);
    svr.Get("/pong", Routes::pong);
    svr.Get("/radio", Routes::radio);
    svr.Get("/radio/elapsed", Routes::radio_elapsed);

    svr.set_base_dir("./share");

    svr.set_logger([](const Request& req, const auto& res) {
        string user_agent = "";
        if (req.has_header("User-Agent")) {
            user_agent = req.get_header_value("User-Agent");
        }

        if (user_agent.length() == 0) {
            user_agent = "bot";
        }

         cout << req.remote_addr << ": " << req.path << " [" << user_agent << "]" << endl;
    });

    svr.listen(ADDR, PORT);
}
