#ifndef BASE_HPP
#define BASE_HPP

#include <sys/types.h>
#include <unistd.h>
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