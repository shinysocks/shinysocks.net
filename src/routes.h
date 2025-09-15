#include <httplib.h>

using namespace httplib;
using namespace std;
using namespace filesystem;

string current_song;
double current_time;

const string TUNES_PATH = "/home/shinysocks/sync/tunes/";

const string HTML_RES = R"(
    <!DOCTYPE html>
    <head>
    <title>Noah Dinan</title>
    <style>
    @import url(https://fonts.googleapis.com/css2?family=Fira+Code);
    @media only print { * { font-family: Fira Code, sans-serif;background-color:white;font-weight:bolder; }}
    @media only screen { * { font-family: Fira Code, sans-serif;background-color:black;font-weight:bolder; }}
    img { width:310px;-moz-user-select:none;-webkit-user-select:none;user-select:none; }
    div { position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);text-align:center; }
    p { color:#9399b2;display:inline; }
    a { color:#b4befe; }
    </style>
    </head>
    <body>
      <div>
        <img src="logo.png"><br><br>
        <a href="https://github.com/shinysocks">github.com/shinysocks</a><br><br>
        <p style="color:#a6e3a1;-moz-user-select:none;-webkit-user-select:none;user-select:none;">$ </p>
        <p>curl shinysocks.net</p>
      </div>
    </body>
    </html>
)";

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
            res.set_redirect("http://shinysocks.net/bomb");
        } else {
            res.set_content(HTML_RES, "text/html");
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

    constexpr static auto radio_song = [](const auto &req, auto &res) {
        res.set_file_content(current_song, "audio/mp3");
    };

    constexpr static auto radio_elapsed = [](const auto &req, auto &res) {
        res.set_content(to_string(current_time), "text/plain");
    };
};


