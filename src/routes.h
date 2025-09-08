#include <httplib.h>

using namespace httplib;
using namespace std;

const string HTML_RES = R"(
    <!DOCTYPE html>
    <head>
    <title>Noah Dinan</title>
    </head>
    <style>
    @import url(https://fonts.googleapis.com/css2?family=Fira+Code);
    * { font-family: Fira Code;background-color:black;font-weight:bolder;display:inline; }
    img { width:310px;-moz-user-select:none;-webkit-user-select:none;user-select:none; }
    div { position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);text-align:center; }
    p { color:#9399b2; }
    a { color:#b4befe; }
    audio { display:none; }
    </style>
    <body>
      <div>
        <img src="logo.png" />
        <br/>
        <br/>
        <a href="https://github.com/shinysocks">github.com/shinysocks</a>
        <br/><br/>
        <p style="color:#a6e3a1;-moz-user-select:none;-webkit-user-select:none;user-select:none;">$ </p>
        <p>curl shinysocks.net</p>
        <audio autoplay="true" src="http://localhost:8888/radio"/>
      </div>
    </body>
    </html>
)";

class Routes {
    public:

    constexpr static auto root = [](const auto &req, auto &res) {
        string user_agent;
        if (req.has_header("User-Agent")) {
            user_agent = req.get_header_value("User-Agent");
            cout << user_agent << endl;
            res.set_header("Secret-Agent", user_agent);
        } else {
            // bot found!
        }

        if (user_agent.find("curl") != std::string::npos) {
            res.set_file_content("./share/index");
        } else if (user_agent.length() == 0) {
            res.status = 418;
            res.set_content("hello bot", "text/html");
        } else {
            res.set_content(HTML_RES, "text/html");
        }
    };

    constexpr static auto favicon = [](const auto &, auto &res) {
        // res.status = 200; <- do I need this?
        res.set_content("", "image/jpeg");
    };

    constexpr static auto bomb = [](const auto &req, auto &res) {
        // Inspired by https://idiallo.com/blog/zipbomb-protection
        res.set_file_content("./share/bomb.html", "text/html");
        res.set_header("Content-Encoding", "gzip");
        res.set_header("Content-Length", "1000");
    };

    constexpr static auto pong = [](const auto &req, auto &res) {
        res.set_content("ping", "text/plain");
    };

    constexpr static auto radio = [](const auto &req, auto &res) {
        res.set_file_content("./share/indigo.mp3", "audio/mp3");

        // res.set_chunked_content_provider(
        //     "audio/mpeg",
        //     [](size_t offset, DataSink &sink) {
        //         for (int i = 0; i < 10000000; i++) {
        //             sink.write("hi", 2);
        //         } sink.done();
        //         return true;
        //     }
        // );
    };
};


