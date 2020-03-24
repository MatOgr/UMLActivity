.PHONY: init submodule prepare

main:
	g++ -std=c++14 *.cpp backend-nice/*.cpp backend-nano/*.cpp -o ActUML -lncurses

init: submodule prepare

submodule:
	git submodule update --init --recursive
	
prepare:
	# nano
	rm -f backend-nano/main.cpp
	rm -f backend-nano/main