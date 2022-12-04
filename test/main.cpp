#include "args.hpp"
#include "test.hpp"

int main(int argc, char *argv[])
{
    Test test;
    Args args;
    int res = -1;
    args.parse(argc, argv);

    int var = '@';
    std::cout << var << std::endl;

    if(args.exist("--fixpath"))
    {
        res = test.test_FixPath(args);
        if(res == -1)
        {
            std::cout << "Error !!! \n";
        }
    }

    if(args.exist("--detector-conf-inline"))
    {
        res = test.test_ConfInline(args);
        if(res == -1)
        {
            std::cout << "Error !!! \n";
        }
    }

    return 0;
}