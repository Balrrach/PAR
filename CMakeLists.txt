#Minimum version required to run this CMakeLists
CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

#Project name
PROJECT(PAR)

#Executables can be added one by one
#ADD_EXECUTABLE(PAR "src/main.cpp" "src/Random.cpp")
#Executables can be added making a recursive search from the project folder
#file(GLOB_RECURSE source_list "*.cpp" "*.hpp")
#Executables can be added specifying a directory
file(GLOB_RECURSE PAR_SRC "src/*.cpp")
ADD_EXECUTABLE(PAR ${PAR_SRC})

#Include directories
INCLUDE_DIRECTORIES("include")

#Libraries used(m for math)
TARGET_LINK_LIBRARIES(PAR m)

#Para compilar con -O3 por defecto
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -w -g") Para debuggear
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -w")