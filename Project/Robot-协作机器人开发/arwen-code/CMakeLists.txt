# cmake_minimum_required(VERSION 3.10...3.25)

# project(webserver.exe)

# SET(CMAKE_BUILD_TYPE "Debug")

# aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)

# add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} pthread)

####################################--旧版--################################################

# project(arwen-webserver LANGUAGES C CXX)

# set(CMAKE_DEBUG_POSTFIX "d")

# file(GLOB WEBSERVER_SOURCE_FILES "*.cpp" "*.c" "*.hpp")

# add_library(${PROJECT_NAME} SHARED ${WEBSERVER_HEADER_FILES} ${WEBSERVER_SOURCE_FILES})

# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

###########################################################################################

file(GLOB WEBSERVER_HEADER_FILES 
        ${PROJECT_SOURCE_DIR}/include/webserver/*.h
        ${PROJECT_SOURCE_DIR}/include/webserver/*.hpp
        )

file(GLOB WEBSERVER_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/webserver/*.cpp
        ${PROJECT_SOURCE_DIR}/src/webserver/*.c
        )

add_library(arwen-webserver SHARED 
        ${WEBSERVER_HEADER_FILES} 
        ${WEBSERVER_SOURCE_FILES}
        )

set_target_properties(arwen-webserver PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(arwen-webserver PUBLIC 
                ${PROJECT_SOURCE_DIR}/include/webserver
                ${PROJECT_SOURCE_DIR}/third_patry/include/jsoncpp
                )

link_directories(${PROJECT_SOURCE_DIR}/third_patry/lib/jsoncpp)

target_link_libraries(arwen-webserver PUBLIC jsoncpp) 

# cmake debug

include(CMakePrintHelpers)
cmake_print_variables(WEBSERVER_HEADER_FILES)
cmake_print_variables(WEBSERVER_SOURCE_FILES)

cmake_print_properties(TARGETS arwen-webserver PROPERTIES POSITION_INDEPENDENT_CODE)