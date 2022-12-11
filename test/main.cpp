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
    Test test;
    Args args;
    int res = -1;
    args.parse(argc, argv);

    if (args.exist("--test-atomic"))
    {
        test_atomic(args);
    }

    if (args.exist("--test-string"))
    {
        test.test_string();
    }

    if (args.exist("--test-vector"))
    {
        std::vector<int> ids;
        test.test_vector(ids);
    }

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