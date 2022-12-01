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
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <map>
#include <queue>
#include <fstream>
#include "jsoncpp/json/json.h"
#include "libavutil/base64.h"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

// #include "args.hpp"

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
    std::string str ("123|1|/home/user/Pictures/test/1.jpeg|");

    const char *tmp_str = "hello world";
    std::string tmp = tmp_str;
    printf(" std::string is %s \n const char * is : %s \n", tmp.c_str(), tmp_str);

    char* cstr = new char [str.length()+1];
    const char *delimiter = "|";
    std::strcpy (cstr, str.c_str());
    printf("char buf string is %s \n", cstr);

    char* p = std::strtok(cstr, delimiter);
    while(p != 0)
    {
        std::cout << p << '\n';
        p = std::strtok(NULL, delimiter);
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

void set_name(const char *name)
{
    const char *m_name = ((name && name[0]) ? name : "");
    printf("name[0] = {%c}\n", name[0]);
    printf("m_name:{%s} \n", m_name);
}

int test_name()
{
    const char Name[10] = "world";
    const char *name = " hello";
    // std::cout << *(name+1) << std::endl;
    // std::cout << Name << std::endl;
    // printf("%s\n",Name);
    // std::cout << typeid(name).name() << std::endl;
    // std::cout << sizeof(name) << std::endl;

    set_name(name);

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
    char sentence [] = "123|0|/home/user/demo.jpeg";
    int64_t id;
    int flag;
    // char *path = (char *)malloc(4096);
    char *image_path = new char[4096];
    char str [20];
    int i;

    FILE *fp = NULL;
    // const char *path = "/home/user/20221128183801.txt";
    const char *path = "/home/user/tmp.txt";
    fp = fopen(path, "r");
    if(!fp)
    {
        printf("failed to open the file -- %s \n", path);
        fclose(fp);
        fp = NULL;
    }

    char *line_ptr = NULL;
    size_t num = 0;
    int res = 0;

    while(1)
    {
        res = getline(&line_ptr, &num, fp);
        if(res == -1)
        {
            printf("read the file over \n");
            break;
        }
        sscanf (line_ptr, "%ld|%d|%s%*[^\n]", &id, &flag, image_path);
        printf("id : %ld, flag : %d, path : %s \n", id, flag, image_path);
    }

    if(image_path)
    {
        delete [] image_path;
        image_path = NULL;
    }
    if(line_ptr)
    {
        delete line_ptr;
        line_ptr = NULL;
    }

    // printf("%s -> %d %d\n", str, i, res);

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

std::string test_fix_path(const char *file, const char *path)
{
    char exe_path[4096] = {0};
    std::string tmp;

    assert(file != NULL);

    if ((file[0] == '/') || (strncmp(file, "http://", 7) == 0) || (strncmp(file, "https://", 8) == 0)) 
    {
        tmp = file;
    }
    else
    {
        tmp = ((path && path[0]) ? path : exe_path);
        tmp += "/";
        tmp += file;
    }

    return tmp;
}

const char *test_string()
{
    const char *file = "hello.h";
    const char *path = "/tmp";

    std::string res = test_fix_path(file, NULL);

    printf("file path is :%s \n", res.c_str());

#if 0
    char str[80];
    strcpy(str, "thes ");
    strcat(str, "strings ");
    strcat(str, "are ");
    strcat(str, "concatenated.");

    puts(str);

    std::string request_data;
    size_t request_max = 16 * 1024 * 1024;
    request_data.reserve(request_max);

    bool chk = false;
    request_data = "/home/user/Pictures/test/1.jpeg";
    printf("string's size is %ld \n ",request_data.size());

    printf("string : %s \n", request_data.c_str());
#endif

    return "";
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

int test_vector(std::vector<int> &tmp_ids)
{
    for(int i = 0; i < 10; i++)
    {
        tmp_ids.push_back(i);
    }
    
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

    strcpy(str, "hello world!!! \n");
    len = strlen(str);
    printf("%s length is %d \n", str, len);

    std::string tmp;
    tmp = "/home/user/file.txt";
    printf("strlen is %d \n, string.size() is %lu \n", (int)strlen(tmp.c_str()), tmp.size());

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
        printf("the buf is : %s \n", buf);
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
        // printf("the buf is : %s \n", buf);
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

void test_getpid()
{
    printf("i am process %ld \n", static_cast<long>(getpid()));
    printf("my parent process is %ld \n", static_cast<long>(getppid()));
}

void test_getegid()
{
    printf("i am user of %ld \n", static_cast<long>(geteuid()));
    printf("i am group of %ld \n", static_cast<long> (getegid()));
    usleep(500);
}

void test_fork()
{
    int x = 0;
    fork();
    x = 1;
    printf("i am process %ld and my x is %d \n", static_cast<long> (getpid()), x);
}

void test_strchr(const char *str, char delimiter)
{
    char *ret;

    ret = const_cast<char *> (strchr(str, delimiter));
    printf("after %c is %s \n", delimiter, ret);
}

void test_lambda()
{
    int num[4] = {4, 3, 2, 1};

    std::sort(num, num+4, [=](int x, int y) -> bool {return x < y;});

    for(int n : num)
    {
        printf("%d \n", n);
    }
}

void test_strtok(char *str, const char *delimiter)
{
    char *token;
    char *save_ptr = NULL;

    int tmp_id, tmp_flag;
    char *image_path = NULL;

    token = strtok_r(str, delimiter, &save_ptr);
    for(int i = 0; i < 3; i++)
    {
        if (i == 0)
            tmp_id = atoi(token);
        else if (i == 1)
        {
            token = strtok_r(NULL, delimiter, &save_ptr);
            tmp_flag = atoi(token);
            if(tmp_flag == 0)
            {
                printf("delete id:%d \n", tmp_id);
                break;
            }
            else if(tmp_flag == 1)
            {
                token = strtok_r(NULL, delimiter, &save_ptr);
                if(token)
                {
                    image_path = token;
                    printf("add id : %d, path: %s \n", tmp_id, image_path);
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void test_fgets()
{
    FILE *fp = NULL;
    // char str[60];
    const char *file = "/home/user/file.txt";
    const char *delimiter = "|";

    fp = fopen(file, "r");
    if(fp == NULL)
    {
        perror("open file error");
        return;
    }

    size_t res = 0;
    char *line_ptr = NULL;
    size_t line_len = 0;

    char *token = NULL;
    char *save_ptr = NULL;
    char *subtoken = NULL;
    char *str = NULL;
    
    int count;
    std::string tmp_id, tmp_flag, tmp_path;
    std::map<std::string, std::string> m_images;
    typedef std::map<std::string, std::string>::iterator m_images_it;

    while(1)
    {
        res = getline(&line_ptr, &line_len, fp);
        if(res == -1)
            break;
        
        for(str = line_ptr, count = 0;;str = NULL, count++)
        {
            subtoken = strtok_r(str, delimiter, &save_ptr);
            if(subtoken == NULL)
                break;
            
            if(count == 0)
            {
                tmp_id = subtoken;
            }

            if(count == 1)
            {
                tmp_flag = subtoken;
                if(tmp_flag == "0")
                {
                    m_images_it tmp_iterator = m_images.find(tmp_id);
                    if((tmp_iterator->second).empty())
                    {
                        printf("id {%s} does not exist \n", tmp_id.c_str());
                        break;
                    }
                    else
                    {
                        printf("id {%s} has been deleted \n", tmp_id.c_str());
                        m_images.erase(tmp_id);
                        break;
                    }
                }
            }

            if(count == 2)
            {
                tmp_path = subtoken;
                m_images_it tmp_iterator = m_images.find(tmp_id);
                if((tmp_iterator->second).empty())
                {
                    m_images[tmp_id] = tmp_path;
                    printf("id {%s} has been added \n", tmp_id.c_str());
                    break;
                }
                else
                {
                    printf("id {%s} is existed \n", tmp_id.c_str());
                    break;
                }
            }
        }

    }

    for(auto &tmp : m_images)
    {
        printf("id is {%s}, and it's value is {%s} \n", (tmp.first).c_str(), (tmp.second).c_str());
    }
    // while(1)
    // {
    //     if(fgets(str, 60, fp) != NULL)
    //     {
    //         test_strtok(str, delimiter);
    //     }
    //     else
    //     {
    //         perror("no context");
    //         break;
    //     }
    // }
    if(fp)
        fclose(fp);
    
    if(line_ptr)
    {
        free(line_ptr);
        line_ptr = NULL;
    }
}

int test_pipe()
{
    char bufin[BUFSIZ] = "empty";
    char bufout[] = "hello";
    int bytesin;
    pid_t childpid;
    int fd[2];

    if(pipe(fd) == -1)
    {
        perror("Failed to create the pipe");
        return 1;
    }

    bytesin = strlen(bufin);
    childpid = fork();
    if(childpid == -1)
    {
        perror("Failed to fork");
        return 1;
    }

    if(childpid)
        write(fd[1], bufout, strlen(bufout)+1);
    else
        bytesin = read(fd[0], bufin, BUFSIZ);
    
    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s} \n", (long)getpid(), bytesin, bufin, bufout);

    return 0;
}

void test_sigset_t()
{
    sigset_t myset;
    sigemptyset(&myset);
    sigaddset(&myset,SIGINT);
    sigaddset(&myset,SIGQUIT);
    sigaddset(&myset,SIGUSR1);
    sigaddset(&myset,SIGRTMIN);
    
    for(int i = 0; i < NSIG; ++i)
    {
        if(sigismember(&myset, i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    putchar('\n');
}

void *print_ids(void *arg)
{
    const char *s = "new thread: ";
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u (0x%x) \n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int) tid);
}

void test_pthread_create()
{
    pthread_t ntid;
    pthread_create(&ntid, NULL, print_ids, NULL);
    printf("main thread \n");

    pthread_join(ntid, NULL);    
}

std::string test_map_end(int id)
{
    std::string result;
    std::map<int, std::string> test_map;
    test_map[0] = "hello";
    test_map[1] = "world";

    for(int i = 2 ; i < 10; i++)
    {
        test_map[i] = "hello";
    }
    
    std::map<int, std::string>::iterator map_iterator = test_map.find(id);
    if(map_iterator != test_map.end())
    {
        result = map_iterator->second;
    }
    else
    {
        printf("can not find id: %d \n", id);
    }
    test_map.end();
    return result;
}

typedef std::map<std::string, std::string> TmpMap;
typedef TmpMap::iterator TmpMapIterator;

const char *test_map_second(const char *id)
{
    TmpMap m_tmp;
    m_tmp["123"] = "/home/user";
    m_tmp["456"] = "/tmp";
    m_tmp["789"] = "/dev/null";

    TmpMapIterator tmp_it = m_tmp.find(id);

    // printf("iterator.second is %s \n", (tmp_it->second).c_str());

    return (tmp_it->second).c_str();
}

void test_file_parse(const char *file, const char *delimiter)
{
    size_t res = 0;
    size_t line_len = 0;
    char *line_ptr = NULL;
    char *token = NULL;
    char *save_ptr = NULL;
    std::string tmp_id, tmp_flag, tmp_path;
    TmpMap m_images;

    FILE *fp = fopen(file, "r");
    if(!fp)
    {
        printf("failed to open %s \n", file);
        goto final_end;
    }

    while(1)
    {
        res = getline(&line_ptr, &line_len, fp);
        if(res == -1)
            break;
        
        printf("line_ptr is %s \n", line_ptr);

        token = strtok_r(line_ptr, delimiter, &save_ptr);
        for(int i = 0; i < 3; i++)
        {
            if(i == 0)
            {
                tmp_id = token;
            }
            else if(i == 1)
            {
                token = strtok_r(NULL, delimiter, &save_ptr);
                tmp_flag = token;
                if(tmp_flag == "0")
                {  
                    m_images.erase(tmp_id);
                    printf("delete id:{ %s } \n", tmp_id.c_str());
                    break;
                }
            }
            else if(i == 2)
            {
                token = strtok_r(NULL, delimiter, &save_ptr);
                tmp_path = token;
                if(tmp_path.empty())
                {
                    printf("file path can not be NULL \n");
                    break;
                }
                else
                {
                    m_images[tmp_id] = tmp_path;
                    printf("add file : { %s } and it's id is { %s } \n", tmp_path.c_str(), tmp_id.c_str());
                }
            }
        }
    }

    printf("!!!!!!!!!!!!!!!!!!\n");
    for(auto &tmp : m_images)
    {
        printf("id is { %s }, and it's path is { %s } \n", (tmp.first).c_str(), (tmp.second).c_str());
    }

final_end:
    if(fp)
        fclose(fp);
    
    if(line_ptr)
        free(line_ptr);
}

void test_enum_map()
{
    enum MODEL
    {
        DETECT = 1,
        FEATURE = 2
    };

    struct ModelRuntime
    {
    public:
        int index;
        std::string engine_conf_file;
        std::string *engine_handle;
        std::string *spp_handle;
    
    public:
        ModelRuntime()
        {
            index = -1;

            engine_handle = NULL;
            spp_handle = NULL;
        }

        ModelRuntime(int idx)
        {
            index = idx;
        }

        virtual ~ModelRuntime()
        {
            engine_handle->clear();
            spp_handle->clear();
            engine_conf_file.clear();
        }
    };

    typedef std::map<MODEL, ModelRuntime *> ModelMap;
    typedef ModelMap::iterator ModelMapIterator;
    
    ModelMap m_infers;

    m_infers[DETECT] = new ModelRuntime[0];
    m_infers[FEATURE] = new ModelRuntime[1];

    m_infers[DETECT]->engine_conf_file = "/home/user/DETECT.conf";

    for(auto &tmp : m_infers)
    {
        if(tmp.first == MODEL::DETECT)
        {
            tmp.second->engine_conf_file = "/home/user/DETECT.conf";
            *(tmp.second->engine_handle) = "detect handle";
            tmp.second->index = 0;
        }
        else if(tmp.first == MODEL::FEATURE)
        {
            tmp.second->engine_conf_file = "/home/user/FEATURE.conf";
            *(tmp.second->spp_handle) = "feature handle";
            tmp.second->index = 1;
        }
    }

    printf("detect model : %s \n", m_infers[DETECT]->engine_conf_file.c_str());
    printf("detect handle : %s \n", (*(m_infers[DETECT]->engine_handle)).c_str());
}


/**
 * @brief 希望这个类接收完数据后启动线程去处理，不阻塞后面的其他业务逻辑
 * 
 */
class ObjectFirst{
public:
    pid_t m_thread_id;
    std::thread *m_init_thread;
    int val = 0;

public:
    ObjectFirst()
    {
        m_init_thread = NULL;
    }
    ~ObjectFirst()
    {
        if(m_init_thread)
        {
            if(m_init_thread->joinable())
            {
                m_init_thread->join();
            }
            delete m_init_thread;
            m_init_thread = NULL;
        }
    }

public:
    void Recv()
    {
        int a = 2;
        // std::thread t(Process, a);  // 错误： 非静态成员函数的无效使用
        m_init_thread = new std::thread([](ObjectFirst *this_ptr){this_ptr->Process(this_ptr->val);}, this);
        // std::thread t(&ObjectFirst::Process, this, a);  // 正确（方法一）

        // t.detach();
        usleep(100);
    }

    void Process(int val)
    {
        std::cout << "Process, val = " << val << "\n";
        m_thread_id = getpid();
    }
};

class ObjectSecond{
public:
    void Recv()
    {
        int a = 2;
        // std::thread t(Process, a);  // 错误： 非静态成员函数的无效使用
        std::thread t(&ObjectSecond::Process, a);  // 正确（方法二）

        t.join();
    }

    static void Process(int val)  // 正确（方法二 将调用的成员函数设置为静态成员函数）
    {
        std::cout << "Process, val = " << val << "\n";
    }
};

void test_queue()
{
    std::queue<int> q;
    if(q.empty())
    {
        printf("empty \n");
    }
    else
    {
        printf("not empty \n");
    }

    for(int i = 0; i <= 10; i++)
    {
        q.push(i);
        if(i == 6)
        {
            printf("the variable is 6, and it will jump to the flag of jump_here \n");
            goto jump_here;
        }
    }
    printf("Have push 11 number into queue, and the size of q is %lu \n", q.size());

jump_here:
    for(int i = 0; ; i++)
    {
        if(q.empty())
        {
            printf("now the queue is empty, so exit loop \n");
            break;
        }
        printf("process %d \n", q.front());
        printf("success to process, now delete %d \n", q.front());
        q.pop();

        printf("next loop !!!\n");
    }

}

// char *ffmpeg_base64_encode(const void *input_data, int input_size)
// {
//     char *result = NULL;

//     assert(input_data && input_size > 0);

//     int output_size = AV_BASE64_SIZE(input_size);
//     char *output_data = (char *)calloc(1, output_size);
//     char *chk_out = NULL;
//     if(output_data)
//     {
//         chk_out = av_base64_encode(output_data, output_size, (uint8_t *)input_data, input_size);
//     }
// }

// void test_base64()
// {
// //     std::string path = "/home/user/Pictures/test/1.jpeg";
// //     cv::Mat tmp_img = cv::imread(path);
// //     std::string windows = "tmp";
// //     cv::namedWindow(windows, 1);
// //     cv::imshow(windows, tmp_img);
// //     cv::waitKey(3);

// //     int input_size = path.size();
// //     int output_size = AV_BASE64_SIZE(input_size);
// //     char *out_data = (char *)calloc(1, output_size);


// //     av_base64_encode(out_data, output_size, (uint8_t *)path.data(), input_size);

// //     printf("%s \n", out_data);

// //     uint8_t *out;
// //     const char *in;
//     // av_base64_decode(out, in, out_size);
// }

void test_spp_search()
{
    const char *box_info = "1|620.46|195.62|860.74|492.02\n2|232.2|452.24|635.1|245.1\n";
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    int face_id = -1;

    sscanf(box_info, "%d|%lf|%lf|%lf|%lf%*[^\n]", &face_id, &x1, &y1, &x2, &y2);

    printf("%d %lf %lf %lf %lf \n", face_id, x1, y1, x2, y2);
}

/* map<uuid, recordset<{index, score}, {index, score}, {index, score}>> */
typedef std::map<std::string, std::vector<std::pair<int, int>>> RecognizeMap;


void test_jsoncpp()
{
    Json::Value root;
    Json::FastWriter writer;
    Json::Value person;

    person["name"] = "hello world";
    person["age"]  = 100;
    root.append(person);

    // Json::Value uuid;
    Json::Value x;
    Json::Value y;
    Json::Value w;
    Json::Value h;
    Json::Value box_info;

    // uuid["uuid"] = "1234";
    // x["x"] = "620";
    // y["y"] = "195";
    // w["w"] = "860";
    // h["h"] = "492";

    // box_info.append(uuid);
    // box_info.append(x);
    // box_info.append(y);
    // box_info.append(w);
    // box_info.append(h);

    // box_info.find("uuid");

    std::string box = writer.write(box_info);
    std::string json_file = writer.write(root);

    printf("%s \n", json_file.c_str());
    printf("%s \n", box.c_str());

    std::string result_str;

    std::pair<int, int> set;
    std::vector<std::pair<int, int>> pari_recordset;

    RecognizeMap m_recognize;

    set.first = 1;
    set.second = 78;
    pari_recordset.push_back(set);
    set.first = 2;
    set.second = 88;
    pari_recordset.push_back(set);
    set.first = 3;
    set.second = 99;
    pari_recordset.push_back(set);

    m_recognize["1"] = pari_recordset;
    m_recognize["2"] = pari_recordset;

    Json::Value output_json;
    Json::Value recordinfo;
    Json::Value face;
    Json::Value uuid;

    Json::Value recordset;
    Json::Value set_json;
    Json::Value index;
    Json::Value score;

    for(auto &tmp : m_recognize)
    {
        recordinfo["uuid"] = tmp.first;
        for(int i = 0; i < tmp.second.size(); i++)
        {
            set_json["index"] = tmp.second[i].first;
            set_json["score"] = tmp.second[i].second;
            recordset.append(set_json);
            set_json.clear();
        }
        recordinfo["recordset"] = recordset;
        face.append(recordinfo);
        // recordinfo.clear();
        recordset.clear();
        // recordinfo.clear();
    }
    output_json["recognize"] = face;
    std::string result = writer.write(output_json);
    printf("%s \n", result.c_str());
    
}

size_t test_base64()
{
    const char *path = "/home/user/Pictures/base64/1.txt";
    std::string pic;
    FILE *fp = NULL;
    size_t n = 0;
    fp = fopen(path, "r");
    if(!fp)
    {
        fclose(fp);
        fp = NULL;
    }

    std::ifstream input_file_stream;
    input_file_stream.open(path, std::ios::in);
    if(!input_file_stream.is_open())
    {
        std::cout << "failed to read the file" << std::endl;
        return -1;
    }

    while(1)
    {
        if(!(input_file_stream >> pic))
        {
            printf("read the base64 image file over ! \n");
            break;
        }
    }
    input_file_stream.close();
    // std::cout << pic << std::endl;

    // std::string tmp;
    // tmp = pic;
    // std::cout << tmp << std::endl;
    // printf("the size of pic variable is : %lu \n", pic.size());
    // printf("the size of tmp variable is : %lu \n", tmp.size());
    // getchar();
    return pic.size();
}

void test_usleep()
{
    printf("!!!!!!\n");

    // sleep(1);
    usleep(1000000);

    printf("!!!!!!\n");

}

void test_ReadFile(const char *file)
{
    std::ifstream ifs;
    ifs.open(file, std::ios::in);
    if(!ifs.is_open())
    {
        printf("read failed !\n");
        ifs.close();
    }

    char buf[1000] = {0};
    while(ifs >> buf)
    {
        printf("the buf is : %s \n", buf);
    }
    ifs.close();
    // getchar();

    ifs.open(file, std::ios::in);
    if(!ifs.is_open())
    {
        printf("read failed !\n");
        ifs.close();
    }
    char buf2[1000] = {0};
    while(ifs.getline(buf, sizeof(buf)))
    {
        printf("the buf2 is : %s \n", buf2);
    }
    ifs.close();

    // getchar();
    ifs.open(file, std::ios::in);
    if(!ifs.is_open())
    {
        printf("read failed !\n");
        ifs.close();
    }
    std::string buf3;
    while (getline(ifs, buf3))
    {
        printf("the buf3 is : %s \n", buf3.c_str());
    }
    ifs.close();
    
    // getchar();
    ifs.open(file, std::ios::in);
    if(!ifs.is_open())
    {
        printf("read failed !\n");
        ifs.close();
    }
    char c;
    while((c = ifs.get()) != EOF)
    {
        printf("%c \n", c);
    }
    ifs.close();
    // getchar();
}

void test_StringToJson(const char *file)
{
    char* box_info = NULL;
    FILE *fp;
    fp = fopen(file, "r");
    if(!fp)
    {
        printf("failed to open the file \n");
    }
    size_t num;
    size_t res = getline(&box_info, &num, fp);
    if(res == -1)
    {
        printf("read null \n");
    }

    // printf("%s \n", box_info);
    std::string box_str = box_info;
    printf("%s \n", box_str.c_str());

    Json::Reader read;
    Json::Value root;
    if(read.parse(box_info, root))
    {
        std::cout << "success" << "\n";
    }
    else
    {
        std::cout << "failed" << "\n";
    }
    // if(root.isMember("number"))
    // {
    //     std::cout << "exist key : {number}" << "\n";
    // }
    // else
    // {
    //     std::cout << "not exist " << "\n";
    // }
    if(root.isArray())
    {
        printf("root is a array \n");
    }
    else
    {
        printf("not \n");
    }
    printf("%d \n",root.size());
    
    std::string uuid;
    int x1, x2, y1, y2;
    std::vector<int> xy;
    std::map<std::string, std::vector<int> > boxes;
    for(int i = 0; i < root.size(); i++)
    {
        for(auto tmp : root[i].getMemberNames())
        {
            printf("key is : %s , and its value is %s \n", tmp.c_str(), (root[i][tmp].toStyledString()).c_str());
            if(tmp == "index")
            {
                uuid = root[i][tmp].asCString();
            }
            else if(tmp == "x1")
            {
                x1 = atoi((root[i][tmp].toStyledString()).c_str());
                xy.push_back(x1);
            }
            else if(tmp == "y1")
            {
                y1 = atoi((root[i][tmp].toStyledString()).c_str());
                xy.push_back(y1);
            }
            else if(tmp == "x2")
            {
                x2 = atoi((root[i][tmp].toStyledString()).c_str());
                xy.push_back(x2);
            }
            else if(tmp == "y2")
            {
                y2 = atoi((root[i][tmp].toStyledString()).c_str());
                xy.push_back(y2);
            }
        }
        if(!uuid.empty() && xy.size() != 0)
        {
            boxes[uuid] = xy;
        }
        uuid.clear();
        xy.clear();
    }

    for(auto &tmp : boxes)
    {
        printf("uuid is %s, x1:{%d}, y1:{%d}, x2:{%d}, y2:{%d} \n", (tmp.first).c_str(), tmp.second[0], tmp.second[1], tmp.second[2], tmp.second[3]);
    }
    // printf("%s", uuid.c_str());

    // printf("\n");

    // printf("uuid is %s, x1:{%d}, y1:{%d}, x2:{%d}, y2:{%d} \n", uuid.c_str(), x1, y1, x2, y2);
    // std::cout << root.begin() << "\n";

}

/* map<uuid, <x1, y1, x2, y2> */
typedef std::map<std::string, std::vector<int> > BoxMap;

void test_StringToBox(std::string box_str)
{
    char *tmp1 = new char[64];
    char *tmp2 = new char[64];
    int x1, y1, x2, y2;
    BoxMap box_info_map;
    std::vector<int> xy_info;
    // printf("%s \n", box_str);
    char *box = const_cast<char *>(box_str.data());
    // printf("box is :%s \n", box);
    char *token = NULL;
    char *save_ptr = NULL;
    char *subtoken = NULL;
    char *str = NULL;
    for(str = box;; str = NULL)
    {
        subtoken = strtok_r(str, "|", &save_ptr);
        if(!subtoken)
        {
            printf("completed to parse string , exit from loop !\n");
            break;
        }
        printf("subtoken is %s \n", subtoken);
        // sscanf(subtoken, "%[^,],%d,%d,%d,%d[^|]", tmp1, &x1, &y1, &x2, &y2);
        sscanf(subtoken, "%[^,],%d,%d,%d,%d[^|]", tmp1, &x1, &y1, &x2, &y2);
        printf("tmp1 is {%s} , x1 is [%d], y1 is [%d], x2 is [%d], y2 is [%d] \n", tmp1, x1, y1, x2, y2);
        xy_info.push_back(x1);
        xy_info.push_back(y1);
        xy_info.push_back(x2);
        xy_info.push_back(y2);
        box_info_map[tmp1] = xy_info;
        xy_info.clear();
    }

    for(auto &tmp : box_info_map)
    {
        printf("tmp1 is {%s} , x1 is [%d], y1 is [%d], x2 is [%d], y2 is [%d] \n", tmp.first.c_str(), tmp.second[0], tmp.second[1], tmp.second[2], tmp.second[3]);
    }

    // sscanf(box_str, "%s,%d,%d,%d,%d", uuid, &x1, &y1, &x2, &y2);

    // sscanf("hello|world", "%[^|]|%[^|]",tmp1, tmp2);
    // printf("%d %d \n", x1, y1);
    // printf("tmp1 is {%s} , tmp is {%s} \n", tmp1, tmp2);
    
}

void test_sizeof()
{
    char *tmp = new char[4096];
    std::cout << sizeof(tmp) << "\n";
}

void test_write()
{
    const char *tmp = "hell world";
    FILE *fp = NULL;
    fp = fopen("/home/user/workspace/notes/test/write.txt", "w");
    if(!fp)
    {
        printf("failed to open the file !\n");
        return;
    }

    int in_size = strlen(tmp);
    fprintf(fp, "%s", tmp);

    fclose(fp);
}

void test_DeleteBase64Flag()
{
    // std::string flag = "data:image;base64,lajfajlnglaj";
    std::string flag = "data:imagesfsfs;base64,asfjlagalj||fslf";
    int pos_data = flag.find("data:");
    int pos_base64 = flag.find("base64,");
    if(pos_data != -1 && pos_base64 != -1)
    {
        flag.erase(pos_data, (pos_base64 - pos_data) + 7);
        printf("%s \n", flag.c_str());
    }
}

void test_OpenWrongfile(const char *file)
{
    FILE *fp = NULL;
    fp = fopen(file, "r");
    std::cout << fp << "\n";
    if(!fp)
    {
        std::cout << "fclose(fp)" << "\n";
    }


}

void test_fwrite(const char *file)
{
    char str[] = "hello world !!!";
    FILE *fp = NULL;
    fp = fopen(file, "w");
    fwrite(str, sizeof(str), 1, fp);
    fclose(fp);
}

void test_fseek(std::string file)
{
    FILE *fp = NULL;
    void *data = NULL;
    long length = 0;
    fp = fopen(file.c_str(), "rb");
    if(!fp)
    {
        printf("Failed to open the file : %s \n", file.c_str());
        return;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    std::cout << length / 8 << std::endl;
    data = calloc(length, 1);
    
    rewind(fp);
    size_t res = fread(data, 1, length, fp);
    if(fp)
    {
        fclose(fp);
        fp = NULL;
    }

    std::cout << data << std::endl;
    std::cout << length << std::endl;
}

void test_fstream(const char *file)
{
    std::ifstream infile;
    infile.open(file, std::ios::in | std::ios::binary);

    int readNum = 0;
    infile.seekg(0, std::ios::end);
    int length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    void *data = calloc(length, 1);

    while(infile.peek() != EOF)
    {
        // infile.read(reinterpret_cast<char *>(&readNum), sizeof(int));
        infile.read((char *)data, length);
    }
    std::cout << length << std::endl;
    printf("%p \n", data);
    std::cout << infile.gcount() << std::endl;



    infile.close();
    free(data);
}

void test_open(const char *file)
{
    sleep(1);

}

void test_difftime()
{
    time_t tstart;
    tstart = time(NULL);
    test_open(NULL);
    printf("function test_open consume time %f seconds  \n", difftime(time(nullptr), tstart));
}

void test_ctime()
{
    time_t tcurrent;

    tcurrent = time(NULL);
    printf("The current time is %s \n", ctime(&tcurrent));

}

void test_localtime()
{
    struct tm *tcurrent;
    time_t current_time;
    current_time = time(NULL);
    tcurrent = localtime(&current_time);
    printf("%d days have elapsed since Jan 1 \n", tcurrent->tm_yday);
}

void test_clock()
{
    long timedif;
    struct timespec tmpend, tmpstart;

    if(clock_gettime(CLOCK_REALTIME, &tmpstart) == -1)
    {
        perror("Failed to get starting time");
        return;
    }

    test_localtime();
    if(clock_gettime(CLOCK_REALTIME, &tmpend) == -1)
    {
        perror("Failed to get ending time");
        return;
    }

    timedif = (tmpend.tv_sec - tmpstart.tv_sec) + (tmpend.tv_nsec - tmpstart.tv_nsec)/1000;
    printf("The function test_localtime() took %ld microsenconds \n", timedif);

}

int main()
{
    test_class();
    // test_localtime();
    // test_ctime();
    // test_difftime();
    const char *file = "/home/user/workspace/notes/test/write.txt";
    const char *image = "/home/user/Pictures/test/1.jpeg";
    // test_fseek(image);
    // test_fstream(image);
    // test_fwrite(file);
    // const char *file = "/home/user/file3.txt";
    // test_OpenWrongfile(file);
    // test_DeleteBase64Flag();
    // test_write();

    // test_sizeof();

    const char *single_box_str = "1,620,195,860,492";
    std::string box_str = "1,620,195,860,492|2,234,135,621,366|3,234,135,621,366|4,234,135,621,366";
    // test_StringToBox(box_str);
    // float dts = 82.123;
    // printf("%d \n", (int)dts);
    // const char *file = "/home/user/workspace/notes/test/box_info.txt";
    // test_StringToJson(file);
    // const char *file = "/home/user/workspace/notes/test/file.txt";
    // test_ReadFile(file);
    // test_usleep();
    // test_jsoncpp();

    // test_spp_search();
    // size_t file_size = test_base64();
    // printf("file size is : %lu \n", file_size);
    // test_scanf();
    // test_queue();

    // const char *file = "/home/user/file.txt";
    // const char *delimiter = "|";

    // std::vector<char> exe_path(PATH_MAX);
    // std::vector<char> exe_path(4096);
    // uint64_t sleep_time = 500;
    // usleep(sleep_time);
    // printf("sleep time is %lu \n", sleep_time);

    // ObjectFirst obj_first;
    // obj_first.Recv();
    // printf("%d \n", obj_first.m_thread_id);

    // ObjectSecond obj_second;
    // obj_second.Recv();

    // std::map<std::string, std::string> m_images;
    // m_images.clear();
    // m_images["123"] = "first.jpeg";
    // std::map<std::string, std::string>::iterator tmp_it = m_images.find("123");
    // if(tmp_it != m_images.end())
    // {
    //     // printf("first : {%s} \n", (tmp_it->first).c_str());
    //     // printf("empty \n");
    //     printf("value is {%s} \n", (tmp_it->second).c_str());
    // }
    // else
    // {
    //     // printf("first : {%s} \n", (tmp_it->first).c_str());
    //     printf("the value is not found \n");
    // }

    // std::string tmp = "";
    // if(m_images["1"].empty())
    // {
    //     printf("empty \n");
    // }
    // else
    // {
    //     printf("not empty \n");
    // }


    // test_enum_map();

    // std::vector<int> ids;

    // test_vector(ids);

    // for( int i = 0; i < ids.size(); i++)
    // {
    //     printf("%d \n", ids[i]);
    // }

    // test_file_parse(file, delimiter);

    // const char *res = test_map_second("123");
    // printf("return second is : %s \n", res);

    // std::string str = test_map_end(20);
    // printf("search result is %s \n", str.c_str());
    // test_pthread_create();
    // test_sigset_t();
    // test_pipe();
    // test_strtok();
    // test_fgets();
    // test_lambda();
    // test_strchr();
    // test_fork();

    // test_getpid();

    // test_getegid();
    // std::thread tmp_thread(test_getegid);
    // tmp_thread.detach();
    
    // printf("!!!!!!!!!!\n");
    // usleep(1000);
    // test_name();

    // std::string tmp = test_string();
    // if(tmp.empty())
    // {
    //     printf("empty\n");
    // }

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