#ifndef ARGS_HPP
#define ARGS_HPP

#include "base.hpp"

class Args :public Base
{
private:
    std::string m_key_prefix;

    /*map<key, <value1, value2, ...>*/
    std::map<std::string, std::vector<std::string>> m_data;

public:
    Args(const char *key_prefix = "--");

    virtual ~Args();

public:
    void copy_from(const Args &src);

    void copy_to(Args &dst);

public:
    virtual void reset(const char *key_prefix);

public:
    ssize_t dump(void *buf, size_t size);

    ssize_t dump(FILE *output = stderr);

    ssize_t dump(const char *pathfile);

public:
    void parse(int argc, char *argv[]);

    void parse(FILE *file, const char *argv0 = NULL, int delimiter = '\n');

    void parse(const void *data, int size, const char *argv0 = NULL, int delimiter = '\n');

    void parse(const char *pathfile, const char *argv0 = NULL, int delimiter = '\n');

public:
    void remove(const char *key, int index = 0);

    int count(const char *key);

    bool exist(const char *key);

    void upset(const char *key, const char *value);

public:
    const char* value(const char *key, const char *default_value, int index = 0);

    int valtoi(const char *key, int default_value, int index = 0);

    long valtol(const char *key, long default_value, int index = 0);

    double valtof(const char *key, double default_value, int index = 0);
};

Args::Args(const char *key_prefix)
{
    reset(key_prefix);
}

Args::~Args()
{
    reset("");
}

void Args::copy_from(const Args &src)
{
    m_key_prefix = src.m_key_prefix;
    m_data = src.m_data;
}

void Args::copy_to(Args &dst)
{
    dst.m_key_prefix = m_key_prefix;
    dst.m_data = m_data;
}

void Args::reset(const char *key_prefix)
{
    m_data.clear();

    if(key_prefix && key_prefix[0])
    {
        m_key_prefix = key_prefix;
    }
    else
    {
        m_key_prefix = "--";
    }
}

ssize_t Args::dump(void *buf, size_t size)
{
    size_t result = -1;

    assert(buf && size > 0);

    FILE *file = fmemopen(buf, size, "w");
    if(file)
    {
        result = dump(file);

        fclose(file);
    }

    return result;
}

ssize_t Args::dump(FILE *output /*= stderr*/)
{
    size_t result = 0;

    assert(output);

    for(auto &tmp : m_data)
    {
        int chk = 0;

        chk = fprintf(output, "\n%s\n", tmp.first.c_str());
        if(chk <= 0)
        {
            break;
        }
        result += chk;

        for(auto &tmp2 : tmp.second)
        {
            chk = fprintf(output, "%s\n", tmp2.c_str());
            if(chk <= 0)
            {
                break;
            }
        }

        if(chk <= 0)
        {
            break;
        }
    }

    return result;
}

ssize_t Args::dump(const char *pathfile)
{
    ssize_t result = 0;

    assert(pathfile && pathfile[0]);

    FILE *file = fopen(pathfile, "w");
    if(file)
    {
        result = dump(file);

        fclose(file);
    }

    return result;
}

void Args::parse(int argc, char *argv[])
{
    assert(argv > 0 && argv != NULL);

    std::string it_key = m_key_prefix;

    for(int i = 0; i < argc;)
    {
        if(strncmp(argv[i], m_key_prefix.c_str(), m_key_prefix.length()) != 0)
        {
            m_data[it_key].push_back(argv[i++]);
        }
        else
        {
            it_key = argv[i++];

            m_data[it_key];
        }
    }
}

void Args::parse(FILE *file, const char *argv0 /*= NULL*/, int delimiter /*= '\n'*/)
{
    assert(file != NULL);

    std::string it_key = m_key_prefix;

    if(argv0)
    {
        m_data[it_key].push_back(argv0);
    }

    char *text = nullptr;
    size_t length = 0;

    while(GetDelimiterWithNote(&text, &length, delimiter, file, '#') != -1)
    {
        /* 去掉两端不需要的字符 */
        strtrim_both(text, delimiter);
        strtrim_both(text, '\n');
        strtrim_both(text, '\r');
        strtrim_both(text, '\n');
        strtrim_both(text, '\r');
        strtrim_both(text, ' ');

        if(text[0] == '\0')
        {
            continue;
        }

        if(strncmp(text, m_key_prefix.c_str(), m_key_prefix.length()) != 0)
        {
            m_data[it_key].push_back(text);
        }
        else
        {
            it_key = text;
            m_data[it_key];
        }
    }

    if(text)
    {
        free(text);
        text = nullptr;
    }
}

void Args::parse(const void *data, int size, const char *argv0 /*= NULL*/, int delimiter /*= '\n'*/)
{
    assert(data && size > 0);

    FILE *file = fmemopen((void *)data, size, "r");
    if(file)
    {
        parse(file, argv0, delimiter);
        fclose(file);
    }
}

void Args::parse(const char *pathfile, const char *argv0 /*= NULL*/, int delimiter /*= '\n'*/)
{
    assert(pathfile && pathfile[0]);

    FILE *file = fopen(pathfile, "r");
    if(file)
    {
        parse(file, argv0, delimiter);

        fclose(file);
    }
}

void Args::remove(const char *key, int index /*= 0*/)
{
    assert(key && key[0]);

    if(index >= 0)
    {
        std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
        if(it != m_data.end() && index < it->second.size())
        {
            it->second.erase(it->second.begin() + index);
        }
        else
        {
            m_data.erase(key);
        }
    }
}

int Args::count(const char *key)
{
    int result = -1;

    assert(key && key[0]);

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    if(it != m_data.end())
    {
        result = it->second.size();
    }

    return result;
}

bool Args::exist(const char *key)
{
    bool result = false;

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    result = (it != m_data.end());

    return result;
}

void Args::upset(const char *key, const char *value)
{
    assert(key && key[0]);

    if(value)
    {
        m_data[key].push_back(value);
    }
    else
    {
        m_data[key];
    }
}

const char* Args::value(const char *key, const char *default_value, int index /*= 0*/)
{
    const char *result = default_value;

    assert(key && key[0]);

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    if(it != m_data.end() && index < it->second.size())
    {
        result = it->second[index].c_str();
    }

    return result;
}

int Args::valtoi(const char *key, int default_value, int index /*= 0*/)
{
    int result = default_value;

    assert(key && key[0]);

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    if(it != m_data.end() && index < it->second.size())
    {
        result = atoi(it->second[index].c_str());
    }

    return result;
}

long Args::valtol(const char *key, long default_value, int index /*= 0*/)
{
    long result = default_value;

    assert(key && key[0]);

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    if(it != m_data.end() && index < it->second.size())
    {
        result = atol(it->second[index].c_str());
    }

    return result;
}

double Args::valtof(const char *key, double default_value, int index /*= 0*/)
{
    double result = default_value;

    assert(key && key[0]);

    std::map<std::string, std::vector<std::string>>::iterator it = m_data.find(key);
    if(it != m_data.end() && index < it->second.size())
    {
        result = atof(it->second[index].c_str());
    }

    return result;
}

#endif  // ARGS_HPP