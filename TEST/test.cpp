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
    char str[80];
    strcpy(str, "thes ");
    strcat(str, "strings ");
    strcat(str, "are ");
    strcat(str, "concatenated.");

    puts(str);

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

int main()
{
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

    test_strrchr();

    return 0;
}