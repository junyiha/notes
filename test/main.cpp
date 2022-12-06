#include "args.hpp"
#include "test.hpp"

int main(int argc, char *argv[])
{
    Test test;
    Args args;
    int res = -1;
    args.parse(argc, argv);

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