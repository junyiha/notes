#ifndef __HEADER_H
#define __HEADER_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
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
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#endif // __HEADER_H