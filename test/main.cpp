#include "args.hpp"
#include "test.hpp"
#include "mongoose.h"

#include "test_macro.h"

static void func(struct mg_connection *c, int ev, void *ev_data, void *func_data)
{
    struct mg_http_serve_opts  opts = {.root_dir = "."};
    if (ev == MG_EV_HTTP_MSG)
    {
        mg_http_serve_dir(c, (struct mg_http_message *)ev_data, &opts);
    }
}

int test_mongoose(Args &args)
{
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "0.0.0.0:8000", func, NULL);

    for (;;)
    {
        mg_mgr_poll(&mgr, 100);
    }
}

int main(int argc, char *argv[])
{
    Test test;
    Args args;
    int res = -1;
    args.parse(argc, argv);

    if (args.exist("--test-mongoose"))
    {
        test_mongoose(args);
    }

    if (args.exist("--test-flag"))
    {
        test.set_exit_flag(1);
        if (test.get_exit_flag())
        {
            printf("Exiting !!!\n");
        }
    }

    if (args.exist("--download-tmpfile"))
    {
        char *dst = const_cast<char *>(args.value("--dst", ""));
        const char *src = args.value("--src", "");
        test.DownloadTmpFile(src, dst, NULL);
    }

    if (args.exist("--access"))
    {
        test.test_access(args);
    }

    if (args.exist("--mkstemp"))
    {
        test.test_mkstemp(args);
    }

    if (args.exist("--fixpath"))
    {
        res = test.test_FixPath(args);
        if (res == -1)
        {
            std::cout << "Error !!! \n";
        }
    }

    if (args.exist("--detector-conf-inline"))
    {
        res = test.test_ConfInline(args);
        if (res == -1)
        {
            std::cout << "Error !!! \n";
        }
    }

    return 0;
}