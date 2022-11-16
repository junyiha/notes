#include <iostream>  // std::cin, std::cout
#include <array>     // std::array
#include <vector>    // std::vector
#include <cstring>
#include <tuple>     // std::tuple
#include <unistd.h>
#include <utility>   // std::pair, std::make_pair
#include <string>    // std::string
#include <cstdlib>
#include <ctype.h>   // iscntrl() 
#include <cstdarg>   // va_start va_arg va_end va_list
#include <algorithm> // std::sort()
#include <functional>
#include <string_view>  // std::string_view()
#include <cmath>
#include <typeinfo>  // std::typeid
#include <thread>    // std::thread

int test_access()
{
    int i = access("/home/user/workspace/stdlib/access.cpp", R_OK);

    std::cout << i << std::endl;
}

int test_array_at()
{
    std::array<int, 10> data;
    
    for(int i = 0; i < 10; i++)
    {
        data.at(i) = i + 1;
    }

    std::cout << "data:";
    for(int i = 0; i < 10; i++)
    {
        std::cout << " " << data.at(i);
    }

    std::cout << "\n";

    return 0;
}

int test_c_str()
{
    std::string str ("Please split this sentence into tokens");

    char* cstr = new char [str.length()+1];
    std::strcpy (cstr, str.c_str());
    printf("char buf string is %s \n", cstr);

    char* p = std::strtok(cstr, " ");
    while(p != 0)
    {
        std::cout << p << '\n';
        p = std::strtok(NULL, " ");
    }

    delete[] cstr;
    return 0; 
}

int test_class()
{
    class tmp
    {
    private:
        int i = 1;

    public:
        int pri()
        {
            printf("%d\n", i);
            return 0;
        }
    };

    tmp p;
    p.pri();

    tmp *x;
    x->pri();
    std::cout << x << std::endl;
    std::cout << &p << std::endl;

    return 0;
}

int test_double_pointer()
{
    int i = 0;
    int* j = &i;
    int** k = &j;
    int* l = j;
    std::cout << i << std::endl;

    std::cout << &i << std::endl;
    std::cout << j << std::endl;
    std::cout << *j << std::endl;

    std::cout << **k << std::endl;
    std::cout << *k << std::endl;
    std::cout << l << std::endl;
    std::cout << *l << std::endl;
    return 0;
}

int test_fopen()
{
    const char *file_name = "./test.txt";

    FILE *pst_file = fopen(file_name, "wb");

    fclose(pst_file);

    pst_file = NULL;
    
    return 0;
}

int test_get()
{
    std::tuple<int, char, float> mytuple(10, 'a', 2.3);
    std::get<0>(mytuple) = 20;
    std::cout << "mytuple contains: ";
    std::cout << std::get<0>(mytuple) << "and " << std::get<1>(mytuple);
    std::cout << std::endl;
    std::cout << std::get<2>(mytuple) << std::endl;

    return 0;
}

int test_getenv()
{
    char* pPath;
    pPath = getenv("PATH");
    if(pPath != NULL)
        printf("The current path is : %s \n", pPath);
    
    return 0;
}

int test_max()
{
    std::cout << "max(1,2) == " << std::max(1,2) << std::endl;
    std::cout << "max(2,1) == " << std::max(2,1) << std::endl;

    return 0;
}

int test_memset()
{
    char str[] = "almost every programmer shold know memset!";
    memset(str, '-', 6);
    puts(str);
    
    return 0;
}

int test_name()
{
    const char Name[10] = "world";
    const char *name = "hello";
    std::cout << *(name+1) << std::endl;
    std::cout << Name << std::endl;
    printf("%s\n",Name);
    std::cout << typeid(name).name() << std::endl;
    std::cout << sizeof(name) << std::endl;

    return 0;
}

int test_remove()
{
    const char* file = "/home/user/workspace/stdlib/hit";
    // remove(file);
    // std::cout << "remove the hit file" << *file << std::endl;
    const char* New_name = "hitter";
    rename(file, New_name);

    return 0;
}

int test_snprintf()
{
    char buffer[100];
    int cx;

    cx = snprintf(buffer, 100, "The half of %d is %d", 60, 60/2);

    if(cx > 0 && cx < 100)
        snprintf(buffer+cx, 100-cx, ", and the half of that is %d", 60/2/2);
    
    puts(buffer);

    return 0;
}

int test_scanf()
{
    char sentence [] = "Rudolph is 12 years old";
    char str [20];
    int i;

    int res = sscanf (sentence, "%s %*s %d", str, &i);
    printf("%s -> %d %d\n", str, i, res);

    return 0;
}

int test_strcasecmp()
{
    const char* s1 = "helloworld";
    const char* s2 = "case";

    int res = strcasecmp(s1, s2);
    
    std::cout << res << std::endl;

    return 0;
}

int test_string()
{
#if 0
    char str[80];
    strcpy(str, "thes ");
    strcat(str, "strings ");
    strcat(str, "are ");
    strcat(str, "concatenated.");

    puts(str);
#endif

    std::string request_data;
    size_t request_max = 16 * 1024 * 1024;
    request_data.reserve(request_max);

    bool chk = false;
    request_data = "/home/user/Pictures/test/1.jpeg";
    printf("string's size is %ld \n ",request_data.size());

    printf("string : %s \n", request_data.c_str());

    return 0;
}

int test_strtol()
{
    char szNumbers[] = "00001 abcde -111111111111111111 0x6ffffffff";
    char* pEnd;
    long int li1, li2, li3, li4;
    li1 = strtol(szNumbers, &pEnd, 20);
    li2 = strtol(pEnd, &pEnd, 16);

    printf("the decimal equivalents are: %ld, %ld \n", li1, li2);

    return 0;
}

#ifdef TEST_TEMPLATE

template <typename T>
inline T const& Max(T const& a, T const& b)
{
    return a < b ? b:a;
}

int test_template()
{


    int i = 20;
    int j = 4;
    std::cout << "Max(i,j)" << Max(i, j) << std::endl;

    double f1 = 145.4;
    double f2 = 34.34;
    std::cout << "Max(f1,f2)" << Max(f1, f2) << std::endl;

    std::string s1 = "hello";
    std::string s2 = "world";
    std::cout << "Max(s1,s2)" << Max(s1, s2) << std::endl;

    return 0;
}

#endif //TEST_TEMPLATE

int test_union()
{
    typedef union image{
        int a;
        struct {
            int inside;
            int inside_2;
        }b;
    }img;

    img test;
    test.a = 1;
    test.b.inside = 200;
    test.b.inside_2 = 10000;
    std::cout << test.a << std::endl;
    std::cout << test.b.inside << std::endl;
    std::cout << test.b.inside_2 << std::endl;

    return 0;
}

int test_vector()
{
    std::vector<int> myvector (5);
    int* p = myvector.data();

    *p = 10;
    ++p;
    *p = 20;
    p[2] = 100;

    std::cout << "myvector contains:";
    for(unsigned i = 0; i < myvector.size(); ++i)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';

    return 0;
}

int test_virtual()
{
    class A
    {
    public:
        virtual void foo()
        {
            std::cout << "A::foo()" << std::endl;
        }
    };

    class B:public A
    {
    public:
        virtual void foo()
        {
            std::cout << "B::foo()" << std::endl;
        }
    };

    A *a = new A();  // A::foo()
    // A *a = new B();  // B::foo()
    a->foo();

    return 0;
}

#ifdef TEST_VSSCANF

void GetMatches(const char* str, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsscanf(str, format, args);
    va_end(args);
}

int test_vsscanf()
{


    int val;
    char buf[100];

    GetMatches("99 bottles of beer on the wall", "%d %s", &val, buf);

    printf("Product:%s \n Quantity: %d \n", buf, val);
    return 0; 

}

#endif  // TEST_VSSCANF

int test_pair()
{
    std::pair <std::string, double> product1;  // default constructor
    std::pair <std::string, double> product2("tomatoes", 2.30);  // value init
    std::pair <std::string, double> product3(product2);  // copy constructor

    product1 = std::make_pair(std::string("lightbulbs"), 0.99);  // using make_pair(move)

    product2.first = "shoes";  // the type of first is string
    product2.second = 39.80;   // the type of second is double

    std::cout << "The price of " << product1.first << "is $" << product1.second << '\n';
    std::cout << "The price of " << product2.first << "is $" << product2.second << '\n';
    std::cout << "The price of " << product3.first << "is $" << product3.second << '\n';

    return 0;
}

int test_iterating_for_loop()
{
    // iterating over array
    int arr[] = {10, 20, 30, 40, 50};
    for (int num : arr)
        printf("%d ", num);
    
    printf("\n");
    // traditinal for loop
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}

int test_atoi()
{
    int val;
    char str[20];

    strcpy(str, "8797913");
    val = atoi(str);
    printf("string value = %s, int value = %d \n", str, val);

    strcpy(str, "helloworld");
    val = atoi(str);
    printf("string value = %s, int value = %d \n", str, val);

    return 0;
}

int test_iscntrl()
{
    int i = 0, j = 0;
    char str1[] = "all \a about \t programming";
    char str2[] = "Runoob \n tutrials";

    while(!iscntrl(str1[i]))
    {
        putchar(str1[i]);
        i++;
    }

    while(!iscntrl(str2[j]))
    {
        putchar(str2[j]);
        j++;
    }

    return 0;
}

int test_strlen()
{
    char str[50];
    int len;

    strcpy(str, "hello world!!!");
    len = strlen(str);
    printf("%s length is %d \n", str, len);

    return 0;
}

char* test_basename(const char *path)
{
    char* result = NULL;
    char* name = strdup(path);
    if(name)
    {
        char* find = basename(name);
        if(find)
            result = find;
            
        free(name);
    }

    return result;
}

int test_readlink()
{
    char buf[1024] = { 0 };
    int n;

    n = readlink("/proc/self/exe", buf, sizeof(buf));
    if(n > 0 && n < sizeof(buf))
        printf("%s \n", buf);
    
    return 0;
}

int test_strrchr()
{
    int len;
     char str[1024] = "hello world / hahaha";
    const char ch = '/';
    char *res = strrchr(str, ch);

    printf("after %c is string: %s\n", ch, res);

    return 0;
}

int test_stdarg(int num_args, ...)
{
    int val = 0;
    va_list ap;
    int i;

    va_start(ap, num_args);
    for(i = 0; i < num_args; i++)
    {
        val += va_arg(ap, int);
    }
    va_end(ap);

    return val;
}

void PrintFError(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    perror(buffer);
    va_end(args);
}

int test_vsnprintf()
{
    FILE *pFile;
    char szFileName[] = "myfile.txt";
    
    pFile = fopen(szFileName, "r");
    if(pFile == NULL)
        PrintFError("Error opening '%s'", szFileName);
    else
    {
        fclose(pFile);
    }

    return 0;
}

#if 0
int test_sort()
{
    std::array<int, 10> s = { 3, 1, 45, 2 ,6 ,2 ,67 ,12, 45, 41};
    auto print = [&s](std::string_view const rem)
    {

    }
}
#endif

int test_sqrt()
{
    printf("%lf 's sqrt is %lf \n", 4.0, sqrt(4.0));
    printf("%lf 's sqrt is %lf \n", 9.0, sqrt(9.0));

    return 0;
}

typedef void *_mathcer;

/*左移n位，原数乘以2的n次方; 右移n位，原数除以2的n次方*/
int test_move_left()
{
    int num_left = 2;
    printf("[%d] move left (<<) 8  is [%d] \n", num_left, num_left << 2);

    int num_right = 8;
    printf("[%d] move right (>>) 8 is [%d] \n", num_right, num_right >> 2);

    return 0;
}

// 迭代器
int test_iterator()
{
    std::vector<int> var;

    var.push_back(1);
    var.push_back(2);
    var.push_back(3);
    var.push_back(4);

    for(std::vector<int>::iterator iter = var.begin(); iter != var.end(); ++iter)
        std::cout << *iter << std::endl;

    for(auto i:var)
        std::cout << i << std::endl;

    return 0;
}

// 并发，并行
int test_thread()
{
    std::cout << "hello world" << std::endl;

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported. \n";
    
    return 0;
}

int test_clock_gettime()
{
    struct timespec tms = {0};
    clockid_t clock_id = CLOCK_REALTIME;
    clock_gettime(clock_id, &tms);
    printf("clock_gettime: tv_sec = %ld, tv_nsec = %lf \n", tms.tv_sec, (double)tms.tv_nsec / 1000000000);

    return 0;
}

int test_func_join()
{
    printf("print in test_join() function \n");
}

int test_join(int &num)
{
    for (int i = 0; i < num; i++)
    {
        printf("from test_join function : %d \n", i);
    }

    std::thread child_thread(test_func_join);

    child_thread.join();

    printf("the test_func_join() function out \n");
    
    num++;

    return num;
}

int main()
{
    test_string();

    // int num = 5;
    // std::thread var_thread(test_join, std::ref(num));
    // printf("main() function \n");
    // var_thread.join();
    // sleep(1);
    

    // test_clock_gettime();
    // for (int i = 0; i < 1000; i++)
    //     int val = i;
    // sleep(1);
    // test_clock_gettime();

    // test_c_str();
    // std::thread t(test_thread);
    // t.join();

    // test_iterator();

    // test_virtual();

    // test_pair();

    // test_iterating_for_loop();

    // test_atoi();

    // test_iscntrl();

    // test_strlen();
    // const char *pathfile = "/home/user/workspace/notes/TEST/test.cpp";
    // char *res = test_basename(pathfile);
    // printf("input path %s \n output path %s \n", pathfile, res);
    // input path /home/user/workspace/notes/TEST/test.cpp   output path test.cpp

    // test_readlink();

    // test_strrchr();

    // printf("the sum of 10, 20 and 30 is %d \n ", test_stdarg(3, 10, 20, 30));

    // test_vsnprintf();

    // test_sqrt();

    // _mathcer val;

    // void * res;
    // std::cout << typeid(val).name() << std::endl;
    // std::cout << typeid(res).name() << std::endl;

    // test_move_left();
    
    return 0;
}