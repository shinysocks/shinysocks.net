#include <httplib.h>

using namespace httplib;
using namespace std;

int main(void) {
    Server svr;

    svr.set_base_dir("./share");

    svr.Get("/favicon.ico", [](const Request &req, Response &res) {
        res.status = 200;
        res.set_content("", "image/jpeg");
    });
    
    svr.Get("/bomb", [](const Request &req, Response &res) {
        // https://idiallo.com/blog/zipbomb-protection
        res.status = 418;
        res.set_header("Can-Teapot-Bomb", "Nope!");
    });

    svr.Get("/mostlycats", [](const Request &req, Response &res) {
        res.set_file_content("./memes/walk_your_bike.jpg");
    });

    svr.Get("/ping", [](const Request &, Response &res) {
        res.set_content("pong", "text/plain");
    });

    svr.Get("/pong", [](const Request &, Response &res) {
        res.set_content("ping", "text/plain");
    });

    svr.Get("/", [=](const Request &req, Response &res) {
        res.set_file_content("./share/index.html");
    });

    // TODO: downscale all audio to 128kpbs
    // send content chunked (radio?)
    svr.Get("/radio", [&](const Request& req, Response& res) {
        res.set_chunked_content_provider(
            "audio/mpeg",
            [](size_t offset, DataSink &sink) {
                for (int i = 0; i < 10000000; i++) {
                    sink.write("hi", 2);
                } sink.done();
                return true;
            }
        );
    });

    svr.set_error_handler([](const Request &, Response &res) {

    });

    svr.listen("localhost", 8888);
}
