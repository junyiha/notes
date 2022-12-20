#include "args.hpp"
#include "test.hpp"
#include "image.hpp"

__BEGIN_DECLS

#include "mongoose.h"

__END_DECLS

#include "test_macro.h"

#include "websocket_server.hpp"

static int s_signo;
std::string s_root_dir;
std::string s_ssi_pattern;

static void EventHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (mg_http_message *)ev_data, tmp = {0};
        struct mg_str unknown = mg_str_n("?", 1), *cl;
        struct mg_http_serve_opts opts = {0};

        opts.root_dir = s_root_dir.c_str();
        opts.ssi_pattern = s_ssi_pattern.c_str();
        mg_http_serve_dir(c, hm, &opts);
        mg_http_parse((char *)c->send.buf, c->send.len, &tmp);

        if (cl == NULL) {
            cl = &unknown;
        }
        MG_INFO(("%.*s %.*s %.*s %.*s", 
                (int)hm->message.len, hm->method.ptr, 
                (int)hm->uri.len, hm->uri.ptr, 
                (int)tmp.uri.len, tmp.uri.ptr, 
                (int)cl->len, cl->ptr));
    }
    (void) fn_data;
}

int test_http_server(Args &args) {
    struct mg_mgr mgr;
    struct mg_connection *c;
    std::string s_listening_address;
    std::string s_enable_hexdump;

    s_listening_address = args.value("--http-listen-address", "http://127.0.0.1:9900");
    s_enable_hexdump = args.value("--enable-hexdump", "yes");
    s_ssi_pattern = args.value("--ssi-pattern", "#.html");
    s_root_dir = args.value("--root-dir", ".");

    mg_mgr_init(&mgr);
    c = mg_http_listen(&mgr, s_listening_address.c_str(), (mg_event_handler_t)EventHandler, &mgr);
    if (c == NULL) {
        MG_ERROR(("Cannot listen on %s. Use Http://address:port or :port", s_listening_address.c_str()));
        exit(EXIT_FAILURE);
    }

    if (mg_casecmp(s_enable_hexdump.c_str(), "yes") == 0) {
        c->is_hexdumping = 1;
    }

    MG_INFO(("Mongoose version : v%s", MG_VERSION));
    MG_INFO(("Listening on     : %s", s_listening_address.c_str()));
    MG_INFO(("Web root         : %s", s_root_dir.c_str()));

    while (s_signo == 0) {
        mg_mgr_poll(&mgr, 1000);
    }
    MG_INFO(("Exiting on signal %d \n", s_signo));

    return 0;
}

static void func_client(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_OPEN) {
        c->is_hexdumping = 1;
    }
    else if (ev == MG_EV_ERROR) {
        MG_ERROR(("%p %s", c->fd, (char *)ev_data));
    }
    else if (ev == MG_EV_WS_OPEN) {
        mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
    }
    else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *)ev_data;
        printf("Got echo reply: [%.*s]\n", (int)wm->data.len, wm->data.ptr);
    }

    if (ev == MG_EV_ERROR || ev == MG_EV_CLOSE || ev == MG_EV_WS_MSG) {
        *(bool *) fn_data = true;
    }
}

int test_mongoose_client(Args &args) {
    struct mg_mgr mgr;
    struct mg_connection *c;
    std::string s_url;
    bool done = false;

    s_url = args.value("--websocket-server", "ws://localhost:9999/websocket");
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_DEBUG);

    c = mg_ws_connect(&mgr, s_url.c_str(), (mg_event_handler_t)func_client, &done, NULL);
    while (c && done == false) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}

std::string s_listen_address;
std::string s_web_root;
static void func(struct mg_connection *c, int ev, void *ev_data, void *func_data) {
    struct mg_http_serve_opts  opts = {.root_dir = "."};
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_http_match_uri(hm, "/websocket")) {
            mg_ws_upgrade(c, hm, NULL);
        }
        else if (mg_http_match_uri(hm, "/rest")) {
            mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
        }
        else {
            struct mg_http_serve_opts opts = {.root_dir = s_web_root.c_str()};
            mg_http_serve_dir(c, (mg_http_message *)ev_data, &opts);
        }
    }
    else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *)ev_data;
        mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
    }

    (void *)func_data;
}

int test_mongoose_server(Args &args) {
    struct mg_mgr mgr;

    s_listen_address = args.value("--listen-address", "127.0.0.1:9999");
    s_web_root = args.value("--web-root", ".");
    printf("Starting WS listener on %s/websocket \n", s_listen_address.c_str());

    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, s_listen_address.c_str(), func, NULL);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}

int test_atomic(Args &args)
{
    int tmp = 0;

    _atomic_compare_and_swap(&tmp, 0, 1);
    std::cout << "compare and swap, tmp is : " << tmp << "\n";

    if (_atomic_load(&tmp) == 1)
    {
        std::cout << "the tmp equal 1 \n";
    }

    _atomic_store(&tmp, 3);
    std::cout << "atomice store, tmp is : " << tmp << "\n";

    return 0;
}

int main(int argc, char *argv[])
{
    Args args;
    Test test;
    Image img;
    Server server;
    int res = -1;
    args.parse(argc, argv);

    if (args.exist("--test-server")) {
        server.demo();
    }

    if (args.exist("--test-pngtojpeg")) {
        img.m_file = args.value("--png-image", "");
        img.m_dir_path = args.value("--dir-path", "/home/user/Face_Images/");
        img.PngToJpeg();
    }

    if (args.exist("--test-mmap")) {
        test.test_mmap(args);
    }

    if (args.exist("--test-atomic")) {
        test_atomic(args);
    }

    if (args.exist("--test-string")) {
        test.test_string();
    }

    if (args.exist("--test-vector")) {
        std::vector<int> ids;
        test.test_vector(ids);
    }

    if (args.exist("--test-http-server")) {
        test_http_server(args);
    }

    if (args.exist("--test-mongoose-server")) {
        test_mongoose_server(args);
    }

    if (args.exist("--test-mongoose-client")) {
        test_mongoose_client(args);
    }

    if (args.exist("--test-flag")) {
        test.set_exit_flag(1);
        if (test.get_exit_flag()) {
            printf("Exiting !!!\n");
        }
    }

    if (args.exist("--download-tmpfile")) {
        char *dst = const_cast<char *>(args.value("--dst", ""));
        const char *src = args.value("--src", "");
        test.DownloadTmpFile(src, dst, NULL);
    }

    if (args.exist("--access")) {
        test.test_access(args);
    }

    if (args.exist("--mkstemp")) {
        test.test_mkstemp(args);
    }

    if (args.exist("--fixpath")) {
        res = test.test_FixPath(args);
        if (res == -1) {
            std::cout << "Error !!! \n";
        }
    }

    if (args.exist("--detector-conf-inline")) {
        res = test.test_ConfInline(args);
        if (res == -1) {
            std::cout << "Error !!! \n";
        }
    }

    return 0;
}