# cmake_minimum_required(VERSION 3.10...3.25)

# project(webserver.exe)

# SET(CMAKE_BUILD_TYPE "Debug")

# aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)

# add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} pthread)

project(arwen-webserver LANGUAGES C CXX)

set(CMAKE_DEBUG_POSTFIX "d")

file(GLOB WEBSERVER_SOURCE_FILES "*.cpp" "*.c" "*.hpp")

add_library(${PROJECT_NAME} SHARED 
            ${WEBSERVER_HEADER_FILES} ${WEBSERVER_SOURCE_FILES})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PRJECT_SOURCE_DIR})