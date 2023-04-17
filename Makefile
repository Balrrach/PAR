RELEASEDIR := build/release
DEBUGDIR := build/debug

default: debug

release: create-build
	cd ${RELEASEDIR}; \
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../../CMakeLists.txt; \
	cp compile_commands.json ../..; \
	make

debug: create-build
	cd ${DEBUGDIR}; \
	cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../../CMakeLists.txt; \
	cp compile_commands.json ../..; \
	make

create-build:
	mkdir -p ${RELEASEDIR}; \
	mkdir -p ${DEBUGDIR}

