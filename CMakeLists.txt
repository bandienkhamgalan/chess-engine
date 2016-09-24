cmake_minimum_required(VERSION 3.4.3)

# Project settings
project(ChessEngine CXX)
set(ChessEngine_VERSION_MAJOR 0)
set(ChessEngine_VERSION_MINOR 0)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)

# Google Test & Google Mock
set(GTEST_DIR ${PROJECT_SOURCE_DIR}/lib/googletest)
set(GMOCK_DIR ${PROJECT_SOURCE_DIR}/lib/googlemock)
include_directories(${PROJECT_SOURCE_DIR}/inc ${GTEST_DIR} ${GMOCK_DIR})
include_directories(SYSTEM ${GTEST_DIR}/include ${GMOCK_DIR}/include)
add_library(googletest STATIC ${GTEST_DIR}/src/gtest-all.cc ${GMOCK_DIR}/src/gmock-all.cc)
set_target_properties(googletest PROPERTIES COMPILE_FLAGS -pthread LINKER_FLAGS -pthread)

# Source files
set(SUTs Board FENParser Game Helpers Location Piece Player SimpleSquare SimpleSquareFactory KnightMoveLogic)
foreach(SUT ${SUTs})
	list(APPEND SUTSrc "test/Test${SUT}.cpp")
	list(APPEND Src "src/${SUT}.cpp")
endforeach()
list(APPEND Src "src/PieceFactory.cpp")

# Test files
add_executable(ChessTest ${SUTSrc} ${Src} "${GTEST_DIR}/src/gtest_main.cc")
add_executable(ChessTestCC ${SUTSrc} ${Src} "${GTEST_DIR}/src/gtest_main.cc")
target_link_libraries(ChessTest googletest)
target_link_libraries(ChessTestCC googletest)
if(APPLE)
	find_library(clang_rt NAMES clang_rt.profile_osx PATHS "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/8.0.0/lib/darwin/")
	target_link_libraries(ChessTestCC ${clang_rt})
endif()
set_target_properties(ChessTest PROPERTIES LINKER_FLAGS "-pthread" COMPILE_FLAGS "-Wno-c++11-extensions -Wall -Werror -std=c++1z -stdlib=libc++ -g" )
set_target_properties(ChessTestCC PROPERTIES LINKER_FLAGS "-pthread" COMPILE_FLAGS "-Wno-c++11-extensions -Wall -Werror -std=c++1z -stdlib=libc++ -g -O0 -fprofile-arcs -ftest-coverage")

add_custom_target(_clean COMMAND rm -rf ${PROJECT_SOURCE_DIR}/build/*)
add_custom_target(_test COMMAND ${PROJECT_SOURCE_DIR}/ChessTest --report_level=short)

include(CodeCoverage)
SETUP_TARGET_FOR_COVERAGE(codecoverage ${PROJECT_SOURCE_DIR}/ChessTestCC coverage --report_level=short)