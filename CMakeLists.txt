cmake_minimum_required(VERSION 3.13)
project(nURI)

message(STATUS "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "${CMAKE_BINARY_DIR}")


set(CMAKE_CXX_STANDARD 17)

include_directories( ${CMAKE_SOURCE_DIR}/include )

message(STATUS "Configuring tests")
enable_testing()
add_subdirectory(lib/googletest)
add_subdirectory(test)

add_library(nURI SHARED include/nova/uri.h src/uri.cpp src/uri_parse.cpp src/strutil.h)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(doxyfile_in ${CMAKE_SOURCE_DIR}/doxy.conf)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
endif()
