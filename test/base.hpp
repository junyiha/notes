#ifndef BASE_HPP
#define BASE_HPP

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <utility>   // std::pair, std::make_pair
#include <typeinfo>  // std::typeid
#include <assert.h>
#include <cstdlib>
#include <ctype.h>   // iscntrl() 
#include <cstdarg>   // va_start va_arg va_end va_list
#include <cstring>
#include <algorithm> // std::sort()
#include <functional>
#include <string_view>  // std::string_view()
#include <cmath>

#include <signal.h>
#include <thread>    // std::thread

#include <map>
#include <tuple>     // std::tuple
#include <string>    // std::string
#include <vector>    // std::vector
#include <array>     // std::array
#include <queue>

#include <iostream>  // std::cin, std::cout
#include <fstream>

#include "jsoncpp/json/json.h"
#include "libavutil/base64.h"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

class Base
{
public:

public:
    Base();

    virtual ~Base();

public:
    void FreePtr(void **pptr);

public:
    void FileClose(int *file);

    int FileOpen(const char *pathfile, int read_only, int non_block, int try_create);

    int FileReopen(int file, const char *pathfile, int read_only, int non_block, int try_create);

    int ProcPopen(const char *cmd, int *in_pipe, int *out_pipe, int *err_pipe);

    long FileRead(int file, void *data, long size);

public:
    int DownloadFile(const char *src, const char *dst, char err[1000]); 

    int DownloadTmpFile(const char *src, char *dst, char err[1000]);

public:
    char* strtrim_right(char *string, uint8_t c);

    char* strtrim_left(char* string, uint8_t c);

    char* strtrim_both(char* string, uint8_t c);

public: 
    /**
     * @brief Get the Delimiter With Note object
     * 
     * @param line      output
     * @param length    output
     * @param delimiter input
     * @param file      input
     * @param note      input
     * @return int 
     */
    int GetDelimiterWithNote(char **line, size_t *length, int delimiter, FILE *file, char note);
};

Base::Base()
{

}

Base::~Base()
{
    
}

void Base::FreePtr(void **pptr)
{
    if (!pptr)
        return;
    
    if (!(*pptr))
        return;
    
    free(*pptr);

    *pptr = nullptr;
}

void Base::FileClose(int *file)
{
    if (!file)
        return;

    if (*file >= 0)
    {
        close(*file);
        *file = -1;
    }
}

int Base::FileOpen(const char *pathfile, int read_only, int non_block, int try_create)
{
    int result = -1;

    do
    {
        if (!pathfile)
            break;
        
        int flag = O_RDWR;
        uint32_t mode = 0;

        if (read_only)
        {
            flag = O_RDONLY;
        }
        else if (try_create)
        {
            flag |= O_CREAT; /*flag = flag | O_CREAT*/
            mode = S_IRWXU;
        }

        if (non_block)
        {
            flag |= O_NONBLOCK;
        }

        result = open(pathfile, flag |__O_LARGEFILE |__O_CLOEXEC, mode);

    } while (0);
    
    return result;
}

int Base::FileReopen(int file, const char *pathfile, int read_only, int non_block, int try_create)
{
    int result = -1;
    int file1 = -1;
    int file2 = -1;

    do
    {
        if (file < 0)
        {
            break;
        }

        file1 = FileOpen(pathfile, read_only, non_block, try_create);
        if (file1 < 0)
        {
            break;
        }

        file2 = dup2(file1, file);
        if (file2 < 0)
        {
            break;
        }

        result = file;
    } while (0);

    FileClose(&file1);

    return result;
}

int Base::ProcPopen(const char *cmd, int *in_pipe, int *out_pipe, int *err_pipe)
{
    int child_fd = -1;

    int out2in_fd[2] = {-1};

    int in2out_fd[2] = {-1};

    int in2err_fd[2] = {-1};

    do
    {
        bool enable_in2out = (in_pipe  != NULL);
        bool enable_out2in = (out_pipe != NULL);
        bool enable_in2err = (err_pipe != NULL);

        if (pipe(out2in_fd) != 0)
        {
            break;
        }

        if (pipe(in2out_fd) != 0)
        {
            break;
        }

        if (pipe(in2err_fd) != 0)
        {
            break;
        }

        child_fd = fork();
        if (child_fd < 0)
        {
            break;
        }

        if (child_fd == 0)
        {
            FileClose(&out2in_fd[1]);
            if (enable_out2in)
            {
                dup2(out2in_fd[0], STDIN_FILENO);
            }
            else
            {
                FileReopen(STDIN_FILENO, "/dev/null", 0, 0, 0);
            }
            FileClose(&out2in_fd[0]);

            FileClose(&in2out_fd[0]);
            if (enable_in2out)
            {
                dup2(in2out_fd[1], STDOUT_FILENO);
            }
            else
            {
                FileReopen(STDOUT_FILENO, "/dev/null", 0, 0, 0);
            }
            FileClose(&in2out_fd[1]);

            FileClose(&in2err_fd[0]);
            if (enable_in2err)
            {
                dup2(in2err_fd[1], STDERR_FILENO);
            }
            else
            {
                FileReopen(STDERR_FILENO, "/dev/null", 0, 0, 0);
            }
            FileClose(&in2err_fd[1]);

            execl("/bin/sh", "sh", "-c", cmd, (char *)0);
            _exit(127);
        }
        else
        {
            FileClose(&out2in_fd[0]);
            FileClose(&in2out_fd[1]);
            FileClose(&in2err_fd[1]);

            if (!enable_out2in)
            {
                FileClose(&out2in_fd[1]);
            }
            else
            {
                *in_pipe = out2in_fd[1];
            }

            if (!enable_in2out)
            {
                FileClose(&in2out_fd[0]);
            }
            else
            {
                *out_pipe = in2out_fd[0];
            }

            if (!enable_in2err)
            {
                FileClose(&in2err_fd[0]);
            }
            else
            {
                *err_pipe = in2err_fd[0];
            }
        }
    } while (0);

    return child_fd;
}

long Base::FileRead(int file, void *data, long size)
{
    long read_total = 0;

    while (size > read_total)
    {
        long read_per = read(file, ((char *)data) + read_total, size - read_total);
        if (read_per <= 0)
        {
            break;
        }
        else
        {
            read_total += read_per;
        }
    }

    return read_total;
}

int Base::DownloadFile(const char *src, const char *dst, char err[1000])
{
    int cmd_max = 40960;
    char *cmd = nullptr;
    int cmd_fd = -1;
    int err_fd = -1;
    int err_len = 0;
    char err_buf[1] = {0};
    long read_len = 0;
    int status = 0;
    int chk = -1;

    assert(src != NULL && dst != NULL && err != NULL);

    cmd = (char *)calloc(1, cmd_max);
    if (!cmd)
        goto FINAL;
    
    snprintf(cmd, cmd_max,
             "wget -c -t 3 -T 5 --no-cache --continue --no-check-certificate -O \"%s\" \"%s\"",
             dst, src);

    cmd_fd = ProcPopen(cmd, NULL, NULL, &err_fd);
    if (cmd_fd < 0)
        goto FINAL;
    
    while (1)
    {
        read_len = FileRead(err_fd, err_buf, 1);
        if (read_len <= 0)
            break;
        
        if (err_len < 1000)
        {
            err[err_len++] = err_buf[0];
        }
    }

    waitpid(cmd_fd, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
    {
        chk = 0;
    }

FINAL:
    err[MIN(err_len, 999)] = '\0';
    FileClose(&err_fd);
    FreePtr((void **)&cmd);

    return chk;
}

int Base::DownloadTmpFile(const char *src, char *dst, char err[1000])
{
    int chk = -1;
    int tmp_fd = -1;
    std::vector<char> err2(1000);

    tmp_fd = mkstemp(dst);
    if (tmp_fd < 0)
        return chk;
    
    chk = DownloadFile(src, dst, err ? err : err2.data());
    if (!err)
    {
        printf("wget:{\n %s }", err2.data());
    }

    FileClose(&tmp_fd);

    return chk;
}


char* Base::strtrim_right(char *string, uint8_t c)
{
    char* result = nullptr;

    if(string && c != 0)
    {
        char* temp = string;

        while(*(temp))
        {
            temp++;
        }

        if(c != 0xff)
        {
            while(*(--temp) == c)
            {
                *temp = '\0';
            }
        }
        else
        {
            while(iscntrl(*(--temp)))
            {
                *temp = '\0';
            }
        }

        result = string;
    }

    return result;
}

char* Base::strtrim_left(char* string, uint8_t c)
{
    char* result = nullptr;

    if(string && c != 0)
    {
        size_t str_len = strlen(string);
        size_t blank_len = 0;
        char* temp = string;

        if(c != 0xff)
        {
            while(*(temp) == c)
            {
                temp++;
                blank_len++;
            }
        }
        else
        {
            while(iscntrl(*(temp)))
            {
                temp++;
                blank_len++;
            }
        }

        for(size_t i = 0; i < str_len - blank_len; i++)
        {
            string[i] = string[i + blank_len];
        }
        
        for(size_t j = str_len - blank_len; j < str_len; j++)
        {
            string[j] = '\0';
        }

        result = string;
    }

    return result;
}

char* Base::strtrim_both(char* string, uint8_t c)
{
    strtrim_right(string, c);

    return strtrim_left(string, c);
}

int Base::GetDelimiterWithNote(char **line, size_t *length, int delimiter, FILE *file, char note)
{
    int result = -1;

    while((result = getdelim(line, length, delimiter, file)) != -1)
    {
        char *line_ptr = *line;

        if(*line_ptr == '\0' || *line_ptr == note || iscntrl(*line_ptr))
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return result;
}

#endif  // BASE_HPP