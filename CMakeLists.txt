#
#The root files are made for extract variables for fisher discriminant
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set (NAME_MAIN_PROGRAM draw_corrematrix)
set (CMAKE_SOURCE_DIR "/Users/bean/work/root_basic/draw_corre" )
project(${NAME_MAIN_PROGRAM})

include_directories(${CMAKE_SOURCE_DIR})

#build
add_executable(draw_corrematrix draw_corrematrix.C)

execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOTLIBS)
execute_process(COMMAND root-config --glibs OUTPUT_VARIABLE ROOTGLIBS)

# clear the heading and tailing white space
string(STRIP ${ROOTLIBS} ROOTLIBS)
string(STRIP ${ROOTGLIBS} ROOTGLIBS)


execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOTFLAGS)
string(STRIP ${ROOTFLAGS} ROOTFLAGS)
set (CMAKE_CXX_FLAGS "${ROOTFLAGS}")

target_link_libraries(${NAME_MAIN_PROGRAM} ${ROOTLIBS} ${ROOTGLIBS})

#set install directory
set (CMAKE_INSTALL_PREFIX /Users/bean/work/root_basic/draw_corre)

install(TARGETS draw_corrematrix
	DESTINATION bin		
	)
