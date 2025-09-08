#include <httplib.h>
#include "routes.h"

using namespace httplib;

int PORT = 8888;
string ADDR = "localhost";

int main(void) {
    Server svr;

    // routes
    svr.Get("/", Routes::root);
    svr.Get("/favicon.ico", Routes::favicon);
    svr.Get("/bomb.html", Routes::bomb);
    svr.Get("/pong", Routes::pong);
    svr.Get("/radio", Routes::radio);

    svr.set_base_dir("./share");

    svr.set_error_handler([](const Request &, Response &res) {

    });

    svr.set_logger([](const auto& req, const auto& res) {

    });

    svr.listen(ADDR, PORT);
}
