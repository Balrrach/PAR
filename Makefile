RELEASEDIR := build/release
DEBUGDIR := build/debug

default: make-release

make-release: create-release-directory
	cd ${RELEASEDIR}; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../../CMakeLists.txt; cp compile_commands.json ../..

make-debug: create-debud-directory
	cd ${DEBUGDIRia}; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../../CMakeLists.txt; cp compile_commands.json ../..

create-release-directory:
	mkdir -p ${RELEASEDIR}

create-debud-directory:
	mkdir -p ${DEBUGDIR}

