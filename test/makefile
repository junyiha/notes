
makefile_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
cur_makefile_path:=$(patsubst %/makefile, %/, ${shell ls $(makefile_path)})

src=${wildcard ${cur_makefile_path}*.cpp}
target=${patsubst %.cpp, %, ${src}}

CXX=g++
CXX_FLAGS=-g 
DEPEND_LIBS= -lpthread -lopencv_highgui -lopencv_imgcodecs -lopencv_core -ljsoncpp

INCLUDE_PATH= -I/home/user/workspace/notes/test/include/ -I/usr/local/include/opencv4/  -I/usr/local/include/
LIBRARY_PATH= -L/usr/local/lib/ -L/usr/local/lib/

${target}:${src}
	${CXX} ${CXX_FLAGS} $^ -o $@ ${INCLUDE_PATH} ${DEPEND_LIBS}

all:${target}
	@echo ${makefile_path}
	@echo ${cur_makefile_path}
	@echo ${src}
	@echo ${target}

.PATHON:clean

clean:
	rm ${target}