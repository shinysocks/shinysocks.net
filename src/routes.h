#include <filesystem>
#include <httplib.h>

using namespace httplib;
using namespace std;
using namespace filesystem;

string current_song;
int current_time;

const string TUNES_PATH = "/home/shinysocks/sync/tunes/";

class Routes {
    public:

    constexpr static auto root = [](const auto &req, Response &res) {
        string user_agent = "";
        if (req.has_header("User-Agent")) {
            user_agent = req.get_header_value("User-Agent");
        }

        if (user_agent.find("curl") != std::string::npos) {
            res.set_file_content("./share/index");
        } else if (user_agent.length() == 0) {
            res.set_redirect("http://localhost:8888/bomb");
        } else {
            res.set_file_content("./share/home.html", "text/html");
        }
    };

    constexpr static auto favicon = [](const auto &, auto &res) {
        res.set_content("", "image/jpeg");
    };

    constexpr static auto bomb = [](const auto &req, auto &res) {
        // Inspired by https://idiallo.com/blog/zipbomb-protection
        res.set_file_content("./share/bomb", "text/html");
        res.set_header("Content-Encoding", "gzip");
        res.set_header("Content-Length", "1000");
    };

    constexpr static auto pong = [](const auto &req, auto &res) {
        res.set_content("ping", "text/plain");
    };

    constexpr static auto radio = [](const auto &req, auto &res) {
        res.set_file_content(current_song, "audio/mp3");
        res.set_header("Song", current_song);
    };

    constexpr static auto radio_elapsed = [](const auto &req, auto &res) {
        res.set_content(to_string(current_time), "text/plain");
    };

};


