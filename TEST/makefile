
makefile_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
cur_makefile_path:=$(patsubst %/makefile, %/, ${shell ls $(makefile_path)})

src=${wildcard ${cur_makefile_path}*.cpp}
target=${patsubst %.cpp, %, ${src}}

CXX=g++

${target}:${src}
	${CXX} $^ -o $@

all:${target}
	@echo ${makefile_path}
	@echo ${cur_makefile_path}
	@echo ${src}
	@echo ${target}

.PATHON:clean

clean:
	rm ${target}
	


