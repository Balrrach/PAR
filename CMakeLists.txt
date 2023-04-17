#Minimum version required to run this CMakeLists
CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

#Project name
PROJECT(PAR)
SET(CMAKE_CXX_STANDARD 17)

#Source files
file(GLOB_RECURSE PAR_SRC "src/*.cpp")
ADD_EXECUTABLE(PAR ${PAR_SRC})

#Include directories
INCLUDE_DIRECTORIES("include")

#Libraries used(m for math)
TARGET_LINK_LIBRARIES(PAR m stdc++fs)

#Para compilar con -O3 por defecto
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -w")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")
endif()
